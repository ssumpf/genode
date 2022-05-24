
#include <linux/delay.h>
#include <linux/fs.h>
#include <linux/input.h>
#include <linux/sched/task.h>
#include <linux/slab.h>
#include <sound/asound.h>
#include <sound/core.h>
#include <sound/pcm.h>

#include <audio.h>

/* routes, needs to be configured per platform */
struct sound_routing
{
	char const name[64];
	char const playback[64];
	char const mic_headset[64];
	char const mic_internal[64];

	/* mixer ids */
	unsigned const mute_headset;
	unsigned const mute_speaker;
};


/* routes for tigerlake */
struct sound_routing tigerlake = {
	.name = "TigerLake",
	.playback     = "pcmC0D0p",
	.mic_headset  = "pcmC0D0c",
	.mic_internal = "pcmC0D6c",
	.mute_headset = 1,
	.mute_speaker = 3,
};


/* mixer */
struct mixer;

enum { MAX_CTL_VALS = 2 };

struct mixer_control
{
	struct snd_ctl_elem_info info;
	struct mixer            *mixer;
	int                      value[MAX_CTL_VALS];
	char                   **enum_strings;
};


struct mixer
{
	struct sound_handle  *handle;
	struct mixer_control *controls;
	unsigned              control_count;
};


/* device events */
enum Sound_event {
	INALID = 0,
	PLAYBACK,
	PLAYBACK_STOP,
	JACK_PLUGGED,
	JACK_UNPLUGGED,
	CAPTURE,
	CAPTURE_STOP
};


/* modes for jack operation */
enum Jack_mode {
	HEADPHONE,
	HEADSET,
	MICROPHONE,
	DEFAULT = HEADSET
};


static const char *const jack_mode_labels[] = {
	[HEADPHONE]  = "headphone",
	[HEADSET]    = "headset",
	[MICROPHONE] = "microphone",
};


/* handle for PCM device */
struct sound_handle
{
	struct file  *file;
	struct inode *inode;
};


/*
 * used for private data in drivers
 */
struct sound_card
{
	unsigned              sound_events;
	enum Jack_mode        jack_mode;
	struct sound_routing *routing;
	struct mixer         *mixer;
	struct sound_handle  *playback;
	struct sound_handle  *mic_headset;
	struct sound_handle  *mic_internal;
};


static struct task_struct *_lx_user_task;
static struct file_operations const *_alsa_fops;


enum Stream_direction {
	DIR_PLAYBACK = SNDRV_PCM_STREAM_PLAYBACK,
	DIR_CAPTURE  = SNDRV_PCM_STREAM_CAPTURE,
};


static const char *const direction_labels[] = {
	[DIR_PLAYBACK] = "playback",
	[DIR_CAPTURE]  = "capture"
};


static const char *const control_labels[] = {
	[SNDRV_CTL_ELEM_TYPE_NONE]       = "none",
	[SNDRV_CTL_ELEM_TYPE_BOOLEAN]    = "bool",
	[SNDRV_CTL_ELEM_TYPE_INTEGER]    = "int",
	[SNDRV_CTL_ELEM_TYPE_ENUMERATED] = "enum",
};


/*
 * Helper
 */
static void sound_event_set(struct sound_card *card, enum Sound_event event)
{
	enum Sound_event clear;

	if (event == JACK_PLUGGED)
		clear = JACK_UNPLUGGED;

	if (event == JACK_UNPLUGGED)
		clear = JACK_PLUGGED;

	card->sound_events |= 1u << event;
	card->sound_events &= ~(1u << clear);
}


static bool sound_event(struct sound_card *card, enum Sound_event event)
{
	return !!(card->sound_events & (1u << event));
}


typedef int (*stream_func_t)(struct snd_pcm_str *, void *);

static struct snd_pcm_str *for_each_stream(struct snd_card *card,
                                           stream_func_t func, void *arg)
{
	struct snd_device *device;
	struct snd_pcm *pcm;
	int i;

	list_for_each_entry(device, &card->devices, list) {
		if (device->type != SNDRV_DEV_PCM) continue;

		pcm = device->device_data;
		if (pcm->internal) continue;
		for (i = DIR_PLAYBACK; i <= DIR_CAPTURE; i++) {
			if (pcm->streams[i].substream == NULL) continue;
			if(func(&pcm->streams[i], arg))
				return &pcm->streams[i];
		}
	}

	return NULL;
}


/* generate report later */
static int _report_pcm_device(struct snd_pcm_str *stream, void *arg)
{
	printk("device: %d ", stream->pcm->device);
	printk("direction: %s%s ", direction_labels[stream->stream],
	       stream->stream == CAPTURE ? " " : "");
	printk("node: %s ", dev_name(&stream->dev));
	printk("id: %s\n", stream->pcm->id);

	return 0;
}


static void report_pcm_devices(struct snd_card *card)
{
	for_each_stream(card, _report_pcm_device, NULL);
}


static struct snd_card *wait_for_card(void)
{
	int i, j;
	bool found = false;
	struct snd_card *card = NULL;

	for (i = 0; i < 10; i++) {

		for (j = 0; j < SNDRV_CARDS; j++) {

			if (snd_card_ref(j)) {
				card = snd_card_ref(j);
				found = true;
				break;
			}
		}

		if (found == true) break;

		msleep(1000);
	}

	return card;
}


static int sound_ioctl(struct sound_handle *handle, unsigned cmd, void *arg)
{
	struct file *file = handle->file;
	return file->f_op->unlocked_ioctl(file, cmd, (unsigned long)arg);
}


/*
 * Linux implementations
 */

/* retrieve ALSA file operations */
int __register_chrdev(unsigned int major, unsigned int baseminor,
                      unsigned int count, const char * name,
                      const struct file_operations * fops)
{
	lx_emul_trace(__func__);

	if (major == CONFIG_SND_MAJOR) {
		printk("Registered sound fops\n");
		_alsa_fops = fops;
	}

	return 0;
}


/* called at end of IRQ handler for playback */
void kill_fasync(struct fasync_struct **fp,int sig,int band)
{
	struct sound_card *card;

	if (fp[0] && fp[0]->fa_file) {
		card = (struct sound_card *)fp[0]->fa_file;
		sound_event_set(card, PLAYBACK);
		printk("%s:%d: %p\n", __func__, __LINE__, fp[0]->fa_file);
	}

	if (_lx_user_task)
		lx_emul_task_unblock(_lx_user_task);
}



/*
 * Hardware parameter
 */
static void sound_param_set_mask(struct snd_pcm_hw_params *params, unsigned index, unsigned bit)
{
	if (bit == ~0u)
		memset(params->masks[index].bits, 0xff, sizeof(params->masks[index].bits));
	else
		params->masks[index].bits[0] = 1u << bit;

	params->rmask |= 1u << index;
}


static void sound_param_set_interval(struct snd_pcm_hw_params *params, unsigned index, unsigned value)
{
	unsigned i = index - SNDRV_PCM_HW_PARAM_FIRST_INTERVAL;
	struct snd_interval *interval = &params->intervals[i];

	interval->min = interval->max = value;
	if (value == ~0u) {
		interval->min = 0;
		interval->max = value;
	}
	else {
		interval->min = interval->max = value;
		interval->integer = 1;
	}

	params->rmask |= 1u << index;
}


static void sound_param_init(struct snd_pcm_hw_params *params)
{
	unsigned i;
	for (i = 0; i <= SNDRV_PCM_HW_PARAM_LAST_MASK; i++)
		sound_param_set_mask(params, i, ~0u);

	for (i = SNDRV_PCM_HW_PARAM_FIRST_INTERVAL; i <= SNDRV_PCM_HW_PARAM_LAST_INTERVAL; i++)
		sound_param_set_interval(params, i, ~0u);

	params->cmask = 0;
	params->info  = 0;
}


static void sound_param_configure(struct sound_handle *handle)
{
	int err;
	struct snd_pcm_hw_params *params = kzalloc(sizeof(*params), 0);

	if (!params) return;

	sound_param_init(params);

	err = sound_ioctl(handle, SNDRV_PCM_IOCTL_HW_REFINE, params);
	if (err) {
		printk("Error: IOCTL_HW_REFINE: %d\n", err);
		return;
	}

	sound_param_set_mask(params, SNDRV_PCM_HW_PARAM_ACCESS,    SNDRV_PCM_ACCESS_RW_INTERLEAVED);
	sound_param_set_mask(params, SNDRV_PCM_HW_PARAM_FORMAT,    SNDRV_PCM_FORMAT_S16_LE);
	sound_param_set_mask(params, SNDRV_PCM_HW_PARAM_SUBFORMAT, SNDRV_PCM_SUBFORMAT_STD);

	sound_param_set_interval(params, SNDRV_PCM_HW_PARAM_RATE,        48000);
	sound_param_set_interval(params, SNDRV_PCM_HW_PARAM_CHANNELS,    2);
	sound_param_set_interval(params, SNDRV_PCM_HW_PARAM_PERIOD_SIZE, 512);


	err = sound_ioctl(handle, SNDRV_PCM_IOCTL_HW_PARAMS, params);
	if (err)
		printk("IOCTL_HW_PARAMS: %d\n", err);

	kfree(params);
}


/*
 * sound handles
 */
void free_sound_handle(struct sound_handle *handle)
{
	if (!handle) return;
	if (handle->inode) kfree(handle->inode);
	if (handle->file) kfree(handle->file);
	kfree(handle);
}


static struct sound_handle *alloc_sound_handle(void)
{
	struct sound_handle *handle = (struct sound_handle *)
	                               kzalloc(sizeof(struct sound_handle), 0);
	if (!handle) return NULL;

	handle->inode = (struct inode *)kzalloc(sizeof(struct inode), 0);
	if (!handle->inode) goto err;

	handle->file = (struct file *)kzalloc(sizeof (struct file), 0);
	if (!handle->file) goto err;

	return handle;

err:
	free_sound_handle(handle);
	return NULL;
}


/*
 * open/close
 */
static struct sound_handle *sound_devt_open(dev_t devt)
{
	int err;
	struct sound_handle *handle;

	if (!_alsa_fops) {
		printk("Error: No ALSA file operations registered\n");
		return NULL;
	}

	handle = alloc_sound_handle();
	if (!handle) return NULL;

	handle->inode->i_rdev = MKDEV(MAJOR(devt), MINOR(devt));

	err = _alsa_fops->open(handle->inode, handle->file);
	if (err) {
		printk("failed to open sound device: %d\n", err);
		free_sound_handle(handle);
		return NULL;
	}

	return handle;
}


static int _match_node(struct snd_pcm_str *stream, void *arg)
{
	char const *node = (char const *)arg;

	if (strcmp(node, dev_name(&stream->dev)) == 0) return 1;

	return 0;

}


static
struct sound_handle *sound_device_open(struct snd_card *card, char const *node,
                                       void *data)
{
	struct snd_pcm_str *stream;
	struct sound_handle *handle;
	struct fasync_struct *fasync;

	stream = for_each_stream(card, _match_node, node);

	if (!stream) {
		printk("PCM node '%s' not found\n");
		return NULL;
	}

	printk("%s:%d runtime: %p\n", __func__, __LINE__, stream->substream->runtime);
	printk("PCM device major: %u minor: %u\n",
	        MAJOR(stream->dev.devt), MINOR(stream->dev.devt));

	handle =  sound_devt_open(stream->dev.devt);

	/* hide data in fasync of runtime */
	if (stream->substream->runtime && data) {
		fasync = kzalloc(sizeof(struct fasync_struct), 0);
		if (!fasync) return NULL;
		fasync->fa_file = data;
		stream->substream->runtime->fasync = fasync;
	}

	return handle;
}


static int sound_device_close(struct sound_handle *handle)
{
	int err = 0;
	if (handle->file->f_op->release)
		err = handle->file->f_op->release(handle->inode, handle->file);

	free_sound_handle(handle);
	return err;
}


/*
 * mixer controls
 */
static void report_mixer_controls(struct mixer *mixer)
{
	unsigned i, j;
	struct snd_ctl_elem_info *info;

	for (i = 0; i < mixer->control_count; i++) {
		info = &mixer->controls[i].info;

		if (info->type == SNDRV_CTL_ELEM_TYPE_BYTES) continue;

		printk("control: %u ", i);
		printk("type: %s ", control_labels[info->type]);
		printk("count: %u ", info->count);
		printk("name: %s ", (char const *)info->id.name);

		printk("values: ");
		for (j = 0; j < info->count; j++) {
			printk("%d", mixer->controls[i].value[j]);
			if (j + 1 < info->count) printk(",");
			printk(" ");
		}

		if (info->type == SNDRV_CTL_ELEM_TYPE_INTEGER)
			printk("min: %d max: %d", info->value.integer.min,
			      info->value.integer.max);

		if (info->type != SNDRV_CTL_ELEM_TYPE_ENUMERATED) {
			printk("\n");
			continue;
		}

		printk("enum_values:");
		for (j = 0; j < info->value.enumerated.items; j++) {
			printk(" %s%s",
			       mixer->controls[i].value[0] == j ? "> " : "",
			       mixer->controls[i].enum_strings[j]);
		}

		printk("\n");
	}
}


static int mixer_control_value(struct mixer_control *control, unsigned id)
{
	struct snd_ctl_elem_value element = { 0 };
	int err;

	if (!control || id > control->info.count) return -EINVAL;

	element.id.numid = control->info.id.numid;
	err = sound_ioctl(control->mixer->handle, SNDRV_CTL_IOCTL_ELEM_READ, &element);
	if (err) return err;

	switch (control->info.type) {
	case SNDRV_CTL_ELEM_TYPE_BOOLEAN:
	case SNDRV_CTL_ELEM_TYPE_INTEGER:
		return element.value.integer.value[id];
	case SNDRV_CTL_ELEM_TYPE_ENUMERATED:
		return element.value.enumerated.item[id];
	default:
		return -EINVAL;
	}
}


static int mixer_control_set(struct mixer_control *control, unsigned int id, int value)
{
    struct snd_ctl_elem_value element = { 0 };
    int err;

    if (!control || id >= control->info.count) return -EINVAL;

    element.id.numid = control->info.id.numid;
    err = sound_ioctl(control->mixer->handle, SNDRV_CTL_IOCTL_ELEM_READ, &element);;
    if (err < 0) return err;

    switch (control->info.type) {
    case SNDRV_CTL_ELEM_TYPE_BOOLEAN:
    case SNDRV_CTL_ELEM_TYPE_INTEGER:
        element.value.integer.value[id] = value;
        break;
    case SNDRV_CTL_ELEM_TYPE_ENUMERATED:
        element.value.enumerated.item[id] = value;
        break;
    default:
        return -EINVAL;
    }

    return sound_ioctl(control->mixer->handle, SNDRV_CTL_IOCTL_ELEM_WRITE, &element);
}


static int mixer_control_enum_strings(struct mixer_control *control)
{
	unsigned i;
	char **names;
	int err;
	unsigned enum_count = control->info.value.enumerated.items;

	if (control->enum_strings) return 0;

	names = kcalloc(enum_count, sizeof(char*), 0);
	if (!names) return -ENOMEM;

	for (i = 0; i < enum_count; i++) {

		struct snd_ctl_elem_info info = { 0 };
		info.id.numid = control->info.id.numid;
		info.value.enumerated.item = i;

		err = sound_ioctl(control->mixer->handle, SNDRV_CTL_IOCTL_ELEM_INFO, &info);
		if (err) return err;

		names[i] = kstrdup(info.value.enumerated.name, 0);
	}
	control->enum_strings = names;
	return 0;
}


static int mixer_add_controls(struct mixer *mixer)
{
	struct snd_ctl_elem_list elements = { 0 };
	struct snd_ctl_elem_id *element_id;
	struct mixer_control *control;
	struct snd_ctl_elem_info *info;
	int err, i;
	unsigned j;

	err = sound_ioctl(mixer->handle, SNDRV_CTL_IOCTL_ELEM_LIST, &elements);
	if (err) return err;

	control = kcalloc(elements.count, sizeof(struct mixer_control), 0);
	if (!control) return -ENOMEM;

	element_id = kcalloc(elements.count, sizeof(struct snd_ctl_elem_id), 0);
	if (!element_id) return -ENOMEM;

	elements.pids  = element_id;
	elements.space = elements.count;

	/* changes element_id */
	err = sound_ioctl(mixer->handle, SNDRV_CTL_IOCTL_ELEM_LIST, &elements);
	if (err) return err;

	/* fill out element information */
	for (i = 0; i < elements.count; i++) {
		control[i].info.id.numid = element_id[i].numid;
		control[i].mixer = mixer;

		err = sound_ioctl(mixer->handle, SNDRV_CTL_IOCTL_ELEM_INFO, &control[i].info);
		if (err) return err;

		info = &control[i].info;
		/* ignore bytes */
		if (info->type == SNDRV_CTL_ELEM_TYPE_BYTES) continue;

		for (j = 0; j < info->count; j++) {
			int val = mixer_control_value(&control[i], j);
			if (j < MAX_CTL_VALS) control[i].value[j] = val;
		}

		if (info->type == SNDRV_CTL_ELEM_TYPE_ENUMERATED)
			mixer_control_enum_strings(&control[i]);
	}

	mixer->control_count = elements.count;
	mixer->controls      = control;

	return 0;
}


static const char *const state_labels[] = {
	[SNDRV_PCM_STATE_OPEN] = "open",
	[SNDRV_PCM_STATE_SETUP] = "setup",
	[SNDRV_PCM_STATE_PREPARED] = "prepared",
	[SNDRV_PCM_STATE_RUNNING] = "running",
	[SNDRV_PCM_STATE_XRUN] = "xrun",
	[SNDRV_PCM_STATE_DRAINING] = "draining",
	[SNDRV_PCM_STATE_PAUSED] = "paused",
	[SNDRV_PCM_STATE_SUSPENDED] = "suspended",
	[SNDRV_PCM_STATE_DISCONNECTED] = "disconnected",
};


void dump_pcm_state(struct sound_handle *handle)
{
	int err;
	struct snd_pcm_status64 status = { 0 };

	err = sound_ioctl(handle, SNDRV_PCM_IOCTL_STATUS64, &status);
	if (err) printk("%s:%d err=%d\n", __func__, __LINE__, err);
	else printk("%s:%d status: %s avail: %lu "
	            "appl_ptr: %lu hw_ptr: %lu\n", __func__, __LINE__,
	            state_labels[status.state], status.avail,
	            status.appl_ptr, status.hw_ptr);
}


bool sound_pcm_frames_watermark(struct sound_handle *handle)
{
	int err;
	struct snd_pcm_status64 status = { 0 };
	snd_pcm_uframes_t frames = 0;

	err = sound_ioctl(handle, SNDRV_PCM_IOCTL_STATUS64, &status);
	if (err) {
		printk("%s:%d err=%d\n", __func__, __LINE__, err);
		return false;
	}

	frames = status.appl_ptr - status.hw_ptr;
	/* keep two perids on card */
	return frames > genode_audio_period() ? false : true;
}


static void *silence_data(void)
{
	static char data[4096];
	return data;
}


/*
 * play
 */
static void sound_play(struct sound_handle *handle)
{
	int err;
	void *buffer;
	struct genode_packet packet = genode_play_packet();

	while (sound_pcm_frames_watermark(handle)) {

		struct snd_xferi xfer = { 0 };

		if (packet.size < genode_audio_period() * 4) {
			buffer = silence_data();
		}
		else {
			buffer = packet.data;
		}

		xfer.buf    = buffer;
		xfer.frames = genode_audio_period();

		err = sound_ioctl(handle, SNDRV_PCM_IOCTL_WRITEI_FRAMES, &xfer);
		if (err) {
			printk("%s:%d err=%d\n", __func__, __LINE__, err);
			dump_pcm_state(handle);
			return;
		}
	}
#if 0
	if (err == -EPIPE) {
		//err = sound_ioctl(handle, SNDRV_PCM_IOCTL_DRAIN, NULL);
		err = sound_ioctl(handle, SNDRV_PCM_IOCTL_PREPARE, NULL);
	}
	//printk("%s:%d DRAIN: %d\n", __func__, __LINE__, err);
#endif
}


/*
 * jack handler
 */
int jack_connect(struct input_handler *handler, struct input_dev *dev,
                 const struct input_device_id *id)
{
	int err;
	struct sound_card *card = handler->private;

	struct input_handle *handle = kzalloc(sizeof(struct input_handle), 0);

	if (!handle) return -ENOMEM;

	printk("%s:%d JACK CONNECT %u\n", __func__, __LINE__, test_bit(SW_HEADPHONE_INSERT, dev->sw));

	/* check if jack input is connected */
	if (test_bit(SW_HEADPHONE_INSERT, dev->sw))
		sound_event_set(card, JACK_PLUGGED);

	handle->handler = handler;
	handle->name    = kstrdup(handle->name, 0);
	handle->dev     = dev;
	handle->private = card;


	err = input_register_handle(handle);
	if (err) {
		printk("%s:%d err=%d\n", __func__, __LINE__, err);
		return err;
	}


	err = input_open_device(handle);
	if (err) {
		printk("%s:%d err=%d\n", __func__, __LINE__, err);
		return err;
	}

	return 0;
}


void jack_event(struct input_handle *handle, unsigned int type,
                unsigned int code, int value)
{
	struct sound_card *card = handle->private;

	printk("%s:%d type: %u code: %u value: %u\n", __func__, __LINE__, type, code, value);

	if (type != EV_SW || code != SW_HEADPHONE_INSERT) return;

	sound_event(card, value ? JACK_PLUGGED : JACK_UNPLUGGED);

	if (_lx_user_task)
		lx_emul_task_unblock(_lx_user_task);
}


static const struct input_device_id jack_ids[] = {
	{ .driver_info = 1 }, /* Matches all devices */
	{ }, /* Terminating zero entry */
};


struct input_handler jack_handler = {
	.connect  = jack_connect,
	.event    = jack_event,
	.id_table = jack_ids,
};


static void sleep_forever(void)
{
	while (1) lx_emul_task_schedule(true);
}

static int sound_card_task(void *data)
{
	struct snd_card *card = wait_for_card();
	struct mixer mixer;
	int err;

	struct sound_card sound_card = {
		.sound_events = 0,
		.jack_mode    = DEFAULT,
		.routing      = data,
		.mixer        = &mixer,
	};

	if (!card) {
		printk("Error: No sound card found\n");
		sleep_forever();
	}

	sound_event_set(&sound_card, JACK_UNPLUGGED);

	/* register jack handler */
	jack_handler.private = &card;
	err = input_register_handler(&jack_handler);
	if (err) {
		printk("Error: Could not register jack input handler (err=%d\n", err);
	}

	mixer.handle = sound_devt_open(card->ctl_dev.devt);
	if (!mixer.handle) {
		printk("Error: Could not open control device for card: %d\n", card->number);
		sleep_forever();
	}

	err = mixer_add_controls(&mixer);
	if (err) {
		printk("Error: Mixer controls failed: %d\n", err);
		sleep_forever();
	}

	report_pcm_devices(card);
	report_mixer_controls(&mixer);

	err = mixer_control_set(&mixer.controls[18], 0, 87);
	printk("Master 87: %d\n", err);
	err = mixer_control_set(&mixer.controls[19], 0, 1);
	printk("Master On: %d\n", err);

	sound_card.playback = sound_device_open(card, sound_card.routing->playback, &sound_card);
	if (!sound_card.playback) {
		printk("%s:%d: Error could not open '%s'\n", __func__, __LINE__, 
		       sound_card.routing->playback);
		sleep_forever();
	}
	sound_param_configure(sound_card.playback);

#if 1
	/* play two packets */
	printk("%s:%d\n", __func__, __LINE__);
	err = sound_ioctl(sound_card.playback, SNDRV_PCM_IOCTL_PREPARE, NULL);
	printk("%s:%d err=%d\n", __func__, __LINE__, err);

	while (1) {
		sound_play(sound_card.playback);
		lx_emul_task_schedule(true);
	}
	//err = sound_device_close(handle);
	//printk("closed: %d\n", err);

	sleep_forever();
#endif
	return 0;
}


void lx_user_init(void)
{
	int pid = kernel_thread(sound_card_task, &tigerlake, CLONE_FS | CLONE_FILES);
	_lx_user_task = find_task_by_pid_ns(pid, NULL);
	/* highest prio because this is time critical */
	lx_emul_task_priority(_lx_user_task, 0);
}
