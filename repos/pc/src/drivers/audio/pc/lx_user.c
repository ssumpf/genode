/*
 * \brief  Bindings from C-API to kernel interface
 * \author Sebastian Sumpf
 * \date   2022-05-31
 */

/*
 * Copyright (C) 2023 Genode Labs GmbH
 *
 * This file is distributed under the terms of the GNU General Public License
 * version 2.
 */

#include <linux/delay.h>
#include <linux/fs.h>
#include <linux/input.h>
#include <linux/sched/task.h>
#include <linux/slab.h>
#include <sound/asound.h>
#include <sound/core.h>
#include <sound/pcm.h>

#include <audio.h>

struct mixer;
typedef void (*mixer_default_func_t)(struct mixer *);

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
	unsigned const mute_mic_internal;
	unsigned const mute_mic_headset;
	mixer_default_func_t defaults;
};


static void mixer_tigerlake_default(struct mixer *mixer);

/* routes for tigerlake */
struct sound_routing tigerlake = {
	.name = "TigerLake",
	.playback     = "pcmC0D0p",
	.mic_headset  = "pcmC0D0c",
	.mic_internal = "pcmC0D6c",
	.mute_headset = 1,
	.mute_speaker = 3,
	.mute_mic_internal = 33,
	.mute_mic_headset  = 6,
	.defaults = mixer_tigerlake_default,
};


/* mixer */
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
	EVENT_INVALID = 0,
	EVENT_PCM,
	EVENT_PLAYBACK_STOP, //TODO
	EVENT_JACK_PLUGGED,
	EVENT_JACK_UNPLUGGED,
	EVENT_CAPTURE_STOP, //TODO
	EVENT_MIXER,
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
	bool                  jack_plugged;
	struct sound_routing *routing;
	struct mixer         *mixer;
	struct sound_handle  *playback;
	struct sound_handle  *capture;
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
static void sound_events_add(struct sound_card *card, enum Sound_event event)
{
	enum Sound_event clear = EVENT_INVALID;

	if (event == EVENT_JACK_PLUGGED)
		clear = EVENT_JACK_UNPLUGGED;

	if (event == EVENT_JACK_UNPLUGGED)
		clear = EVENT_JACK_PLUGGED;

	card->sound_events |= 1u << event;
	card->sound_events &= ~(1u << clear);
}


static void sound_events_clear(struct sound_card *card)
{
	card->sound_events = EVENT_INVALID;
}


static bool sound_events_empty(struct sound_card *card)
{
	return card->sound_events == EVENT_INVALID;
}


static bool _event(unsigned events, enum Sound_event event)
{
	return !!(events & (1u << event));
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


static int _report_pcm_device(struct snd_pcm_str *stream, void *arg)
{
	struct genode_devices *devices = arg;
	struct genode_device  *device;

	int num       = stream->pcm->device;
	int direction = stream->stream;

	if (num > 64 || direction > 1) {
		printk("%s:%d device number/direction invalid\n", __func__, __LINE__);
		return 0;
	}

	device = &devices->device[num][direction];
	device->direction = direction_labels[direction];
	device->node      = dev_name(&stream->dev);
	device->name      = stream->pcm->id;
	device->valid     = true;

	return 0;
}


static void report_pcm_devices(struct snd_card *card)
{
	struct genode_devices *devices = kzalloc(sizeof(*devices), 0);

	for_each_stream(card, _report_pcm_device, devices);

	genode_devices_report(devices);

	kfree(devices);
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


static void sleep_forever(void)
{
	while (1) lx_emul_task_schedule(true);
}


/*
 * Linux implementations
 */

/* retrieve ALSA file operations */
int __register_chrdev(unsigned int major, unsigned int baseminor,
                      unsigned int count, const char * name,
                      const struct file_operations * fops)
{
	if (major == CONFIG_SND_MAJOR) {
		_alsa_fops = fops;
	}

	return 0;
}


int fasync_helper(int fd, struct file *filp, int on, struct fasync_struct **fapp)
{
	*fapp = kzalloc(sizeof(struct fasync_struct), 0);
	if (!*fapp) return -ENOMEM;
	(*fapp)->fa_file = filp;
	return 0;
}


/* called at end of IRQ handler for pcm irqs */
void kill_fasync(struct fasync_struct **fp,int sig,int band)
{
	struct sound_card *card;

	if (fp[0] && fp[0]->fa_file) {
		card = (struct sound_card *)fp[0]->fa_file;
		sound_events_add(card, EVENT_PCM);

		if (genode_mixer_update())
			sound_events_add(card, EVENT_MIXER);
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
	sound_param_set_interval(params, SNDRV_PCM_HW_PARAM_PERIOD_SIZE, genode_audio_period());


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
	struct snd_fasync   *fasync = NULL;
	stream = for_each_stream(card, _match_node, node);

	if (!stream) {
		printk("PCM node '%s' not found\n", node);
		return NULL;
	}

	handle =  sound_devt_open(stream->dev.devt);

	/* hide data in fasync of runtime */
	if (stream->substream->runtime && data) {

		/*
		 * this will call 'fasyc_helper' above where we will hide the data in
		 * fa_file
		 */
		if (snd_fasync_helper(0, data, 1, &fasync))
			return NULL;

		stream->substream->runtime->fasync = fasync;
	}

	return handle;
}


static
struct sound_handle *sound_device_setup(struct snd_card *card, char const *node,
                                        void *data)
{
	int err;
	struct sound_handle *handle = sound_device_open(card, node, data);
	if (!handle) {
		printk("%s:%d: Error could not open '%s'\n", __func__, __LINE__, node);
		return NULL;
	}

	sound_param_configure(handle);

	err = sound_ioctl(handle, SNDRV_PCM_IOCTL_PREPARE, NULL);
	if (err) {
		printk("%s:%d: Error could not prepare '%s' err=%d\n", __func__, __LINE__,
		       node, err);
		return NULL;
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
 * Mixer controls
 */

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


static int mixer_control_values_update(struct mixer *mixer)
{
	unsigned i, j, ret;
	struct snd_ctl_elem_info *info;

	for (i = 0; i < mixer->control_count; i++) {
		info = &mixer->controls[i].info;

		if (info->type == SNDRV_CTL_ELEM_TYPE_BYTES) continue;

		for (j = 0; j < info->count; j++) {
			ret = mixer_control_value(&mixer->controls[i], j);
			if (ret < 1) return ret;
			mixer->controls[i].value[j] = ret;
		}
	}

	return 0;
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

	err = sound_ioctl(control->mixer->handle, SNDRV_CTL_IOCTL_ELEM_WRITE, &element);
	if (err) return err;

	control->value[id] = value;
	return 0;
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


static enum Ctrl_type genode_control_type(unsigned type)
{
	switch (type) {
	case SNDRV_CTL_ELEM_TYPE_BOOLEAN:    return CTRL_BOOL;
	case SNDRV_CTL_ELEM_TYPE_INTEGER:    return CTRL_INTEGER;
	case SNDRV_CTL_ELEM_TYPE_ENUMERATED: return CTRL_ENUMERATED;
	default: return CTRL_INVALID;
	}
}


static void mixer_report_controls(struct mixer *mixer)
{
	unsigned i, j;
	struct snd_ctl_elem_info *info;
	struct genode_mixer_controls *controls;
	mixer_control_values_update(mixer);

	if (mixer->control_count > 64) {
		printk("Error: more than 64 controls\n");
		return;
	}

	controls = kzalloc(sizeof(struct genode_mixer_controls), 0);
	if (!controls) return;
	controls->count = mixer->control_count;

	for (i = 0; i < mixer->control_count; i++) {
		struct genode_mixer_control *control = &controls->control[i];
		info = &mixer->controls[i].info;

		if (info->type == SNDRV_CTL_ELEM_TYPE_BYTES) continue;

		control->id          = i;
		control->type        = genode_control_type(info->type);
		control->type_label  = control_labels[info->type];
		control->value_count = info->count;
		control->name        = (char const *)info->id.name;

		for (j = 0; j < info->count && j < 2; j++) {
			control->values[j] = mixer->controls[i].value[j];
		}

		if (info->type == SNDRV_CTL_ELEM_TYPE_INTEGER) {
			control->min = info->value.integer.min;
			control->max = info->value.integer.max;
		}

		if (info->type != SNDRV_CTL_ELEM_TYPE_ENUMERATED)  continue;

		control->enum_count   = info->value.enumerated.items;
		control->enum_strings = mixer->controls[i].enum_strings;
	}

	genode_mixer_report_controls(controls);
	kfree(controls);
}


static bool mixer_update_controls(struct mixer *mixer)
{
	struct genode_mixer_controls *controls;
	unsigned i, j;
	bool changed = false;

	controls = kzalloc(sizeof(struct genode_mixer_controls), 0);
	if (!controls) return false;
	controls->count = 64;

	genode_mixer_update_controls(controls);

	for (i = 0; i < controls->count; i++) {
		struct genode_mixer_control *control = &controls->control[i];
		struct mixer_control *mixer_control;

		if (control->id >= mixer->control_count) continue;
		mixer_control = &mixer->controls[control->id];

		switch (control->type) {
		case CTRL_BOOL:
		{
			for (j = 0; j < mixer_control->info.count; j++) {

				if (control->values[j] == ~0u ||
				    control->values[j] == mixer_control->value[j]) continue;

				mixer_control_set(mixer_control, j, control->values[j]);
				changed = true;
			}
			break;
		}
		case CTRL_INTEGER:
		{
			for (j = 0; j < mixer_control->info.count; j++) {

				if (control->values[j] == ~0u ||
				    control->values[j] == mixer_control->value[j]) continue;

				if (control->values[j] < mixer_control->info.value.integer.min ||
				    control->values[j] > mixer_control->info.value.integer.max) {
					changed = true;
					continue;
				}

				mixer_control_set(mixer_control, j, control->values[j]);
				changed = true;
			}
			break;
		}
		case CTRL_ENUMERATED:
		{
			if (control->values[0] >= mixer_control->info.value.enumerated.items) {
				changed = true;
				break;
			}

			if (control->values[0] == mixer_control->value[0])
				break;

			mixer_control_set(mixer_control, 0, control->values[0]);
			changed = true;
			break;
		}
		case CTRL_INVALID: break;
		}
	}

	kfree(controls);

	return changed;
}


/*
 *  PCM
 */

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


static void dump_pcm_state(struct sound_handle *handle, char const *msg)
{
	int err;
	struct snd_pcm_status64 status = { 0 };

	err = sound_ioctl(handle, SNDRV_PCM_IOCTL_STATUS64, &status);
	if (err) printk("%s:%d err=%d\n", __func__, __LINE__, err);
	else printk("%s: %s avail: %lu avail_max: %lu "
	            "appl_ptr: %lu hw_ptr: %lu from %s\n", __func__,
	            state_labels[status.state], status.avail, status.avail_max,
	            status.appl_ptr, status.hw_ptr, msg);
}


bool sound_pcm_play_watermark(struct sound_handle *handle)
{
	int err;
	struct snd_pcm_status64 status = { 0 };
	snd_pcm_uframes_t frames = 0;

	err = sound_ioctl(handle, SNDRV_PCM_IOCTL_STATUS64, &status);
	if (err) {
		printk("%s:%d err=%d\n", __func__, __LINE__, err);
		return false;
	}

	if (status.state == SNDRV_PCM_STATE_XRUN) {
		dump_pcm_state(handle, __func__);
		err = sound_ioctl(handle, SNDRV_PCM_IOCTL_DRAIN, NULL);
		if (err) printk("%s:%d err=%d\n", __func__, __LINE__, err);
		err = sound_ioctl(handle, SNDRV_PCM_IOCTL_PREPARE, NULL);
		if (err) printk("%s:%d err=%d\n", __func__, __LINE__, err);
		return false;
	}

	if (status.state == SNDRV_PCM_STATE_DRAINING) return false;
	if (status.state == SNDRV_PCM_STATE_PREPARED) return true;

	frames = status.appl_ptr - status.hw_ptr;
	/* keep two periods on card */
	return frames >= 2 * genode_audio_period() &&
	       status.avail >=  2 * genode_audio_period() ? false : true;
}


bool sound_pcm_capture_watermark(struct sound_handle *handle)
{
	int err;
	struct snd_pcm_status64 status = { 0 };

	err = sound_ioctl(handle, SNDRV_PCM_IOCTL_STATUS64, &status);
	if (err) {
		printk("%s:%d err=%d\n", __func__, __LINE__, err);
		return false;
	}

	if (status.state == SNDRV_PCM_STATE_XRUN) {
		dump_pcm_state(handle, __func__);
		err = sound_ioctl(handle, SNDRV_PCM_IOCTL_DRAIN, NULL);
		if (err) printk("%s:%d err=%d\n", __func__, __LINE__, err);
		err = sound_ioctl(handle, SNDRV_PCM_IOCTL_PREPARE, NULL);
		if (err) printk("%s:%d err=%d\n", __func__, __LINE__, err);
		return false;
	}

	if (status.state == SNDRV_PCM_STATE_DRAINING) return false;
	if (status.state == SNDRV_PCM_STATE_PREPARED) return true;

	return status.avail >= genode_audio_period();
}


/*
 * play
 */
static void *silence_data(void)
{
	static char data[4096];
	return data;
}


static void sound_play(struct sound_handle *handle)
{
	int err;
	void *buffer;
	while (sound_pcm_play_watermark(handle)) {

		struct genode_packet packet = genode_play_packet();
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
			dump_pcm_state(handle, __func__);
			return;
		}
	}
}


/*
 * capture
 */
static void *capture_data(void)
{
	static char data[4096];
	return data;
}


static void sound_capture(struct sound_handle *handle)
{
	int err;
	struct genode_packet packet  = {
		.data = capture_data(),
		.size = genode_audio_period() * 2,
	};

	while (sound_pcm_capture_watermark(handle)) {
		struct snd_xferi xfer = { 0 };

		memset(packet.data, 0, packet.size * sizeof(short));
		xfer.buf    = packet.data;
		xfer.frames = genode_audio_period();

		err = sound_ioctl(handle, SNDRV_PCM_IOCTL_READI_FRAMES, &xfer);
		if (err) {
			printk("%s:%d err=%d\n", __func__, __LINE__, err);
			dump_pcm_state(handle, __func__);
			return;
		}
		genode_record_packet(packet);
	}
}


/*
 * Jack handler
 */

int jack_connect(struct input_handler *handler, struct input_dev *dev,
                 const struct input_device_id *id)
{
	int err;
	struct sound_card *card = handler->private;

	struct input_handle *handle = kzalloc(sizeof(struct input_handle), 0);

	if (!handle) return -ENOMEM;

	/* check if jack input is connected */
	if (test_bit(SW_HEADPHONE_INSERT, dev->sw))
		sound_events_add(card, EVENT_JACK_PLUGGED);

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

	if (type != EV_SW || code != SW_HEADPHONE_INSERT) return;

	sound_events_add(card, value ? EVENT_JACK_PLUGGED : EVENT_JACK_UNPLUGGED);

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

static void update_jack(struct sound_card *card)
{
	int err;
	struct mixer *mixer = card->mixer;
	unsigned index = card->routing->mute_headset;

	if (card->playback) {
		err = sound_ioctl(card->playback, SNDRV_PCM_IOCTL_DRAIN, NULL);
		if (err) printk("%s:%d err=%d\n", __func__, __LINE__ ,err);
		err = sound_ioctl(card->playback, SNDRV_PCM_IOCTL_PREPARE, NULL);
		if (err) printk("%s:%d err=%d\n", __func__, __LINE__ ,err);
	}

	if (card->capture) {
		err = sound_ioctl(card->capture, SNDRV_PCM_IOCTL_DRAIN, NULL);
		if (err) printk("%s:%d err=%d\n", __func__, __LINE__ ,err);
		err = sound_ioctl(card->capture, SNDRV_PCM_IOCTL_DROP, NULL);
		if (err) printk("%s:%d err=%d\n", __func__, __LINE__ ,err);
	}

	mixer_control_set(&mixer->controls[index], 0, card->jack_mode != MICROPHONE && card->jack_plugged);
	mixer_control_set(&mixer->controls[index], 1, card->jack_mode != MICROPHONE && card->jack_plugged);

	index = card->routing->mute_mic_headset;
	mixer_control_set(&mixer->controls[index], 0, card->jack_mode != HEADPHONE && card->jack_plugged);
	mixer_control_set(&mixer->controls[index], 1, card->jack_mode != HEADPHONE && card->jack_plugged);

	index = card->routing->mute_speaker;
	mixer_control_set(&mixer->controls[index], 0, !(card->jack_mode != MICROPHONE && card->jack_plugged));
	mixer_control_set(&mixer->controls[index], 1, !(card->jack_mode != MICROPHONE && card->jack_plugged));

	index = card->routing->mute_mic_internal;
	mixer_control_set(&mixer->controls[index], 0, !(card->jack_mode != HEADPHONE && card->jack_plugged));
	mixer_control_set(&mixer->controls[index], 1, !(card->jack_mode != HEADPHONE && card->jack_plugged));

	card->capture = (card->jack_mode != HEADPHONE && card->jack_plugged) ? card->mic_headset : card->mic_internal;
	err = sound_ioctl(card->capture, SNDRV_PCM_IOCTL_PREPARE, NULL);
	if (err) printk("%s:%d err=%d\n", __func__, __LINE__ ,err);
}


/*
 * Task activity
 */

static void sound_dispatch(struct sound_card *card, struct snd_card *c)
{
	while (true) {

		/*
		 * Save events and clear on card struct, we need to do this because some of
		 * the handling code here may block while in the meantime other interrupts
		 * might trigger (through kill_fasync) from the driver context. In this case
		 * we need to continue dispatching instead of blocking below
		 */
		unsigned events = card->sound_events;
		sound_events_clear(card);

		if (_event(events, EVENT_JACK_UNPLUGGED) ||
		    _event(events, EVENT_JACK_PLUGGED)) {
			card->jack_plugged = _event(events, EVENT_JACK_PLUGGED);

			update_jack(card);

			mixer_report_controls(card->mixer);
		}

		if (_event(events, EVENT_MIXER)) {
			if (mixer_update_controls(card->mixer))
				mixer_report_controls(card->mixer);

			if(genode_jack_mode() != card->jack_mode)
			{
				card->jack_mode = genode_jack_mode();

				if(card->jack_plugged)
				{
					update_jack(card);
				}

				mixer_report_controls(card->mixer);
			}
		}

		if (_event(events, EVENT_PCM)) {
			sound_capture(card->capture);
			sound_play(card->playback);
		}

		/* don't block in case new events arrived in the meantime */
		if (sound_events_empty(card))
			lx_emul_task_schedule(true);
	}
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

	/* register jack handler */
	sound_events_add(&sound_card, EVENT_JACK_UNPLUGGED);
	jack_handler.private = &sound_card;
	err = input_register_handler(&jack_handler);
	if (err) {
		printk("Error: Could not register jack input handler (err=%d\n", err);
	}

	report_pcm_devices(card);

	/* open card control channel */
	mixer.handle = sound_devt_open(card->ctl_dev.devt);
	if (!mixer.handle) {
		printk("Error: Could not open control device for card: %d\n", card->number);
		sleep_forever();
	}

	/* find mixer controls */
	err = mixer_add_controls(&mixer);
	if (err) {
		printk("Error: Mixer controls failed: %d\n", err);
		sleep_forever();
	}

	/* open devices */
	sound_card.playback = sound_device_setup(card, sound_card.routing->playback, &sound_card);
	if (!sound_card.playback) sleep_forever();

	sound_card.mic_internal = sound_device_setup(card, sound_card.routing->mic_internal, &sound_card);
	if (!sound_card.mic_internal) sleep_forever();

	sound_card.mic_headset = sound_device_setup(card, sound_card.routing->mic_headset, &sound_card);
	if (!sound_card.mic_headset) sleep_forever();

	/* mixer defaults */
	sound_card.routing->defaults(&mixer);
	/* possibly override mixer defaults */
	if (genode_mixer_update())
		sound_events_add(&sound_card, EVENT_MIXER);

	/* start event loop */
	sound_events_add(&sound_card, EVENT_PCM);
	sound_dispatch(&sound_card, card);

	err = sound_device_close(sound_card.playback);

	sleep_forever();

	return 0;
}


void lx_user_init(void)
{
	int pid = kernel_thread(sound_card_task, &tigerlake, CLONE_FS | CLONE_FILES);
	_lx_user_task = find_task_by_pid_ns(pid, NULL);
	/* highest prio because this is time critical */
	lx_emul_task_priority(_lx_user_task, 0);
}


/*
 * Mixer default functions
 */

static void mixer_tigerlake_default(struct mixer *mixer)
{
	/* headphone volume */
	mixer_control_set(&mixer->controls[0], 0, 87);
	mixer_control_set(&mixer->controls[0], 1, 87);
	/* speaker volume */
	mixer_control_set(&mixer->controls[2], 0, 87);
	mixer_control_set(&mixer->controls[2], 1, 87);
	/* auto mute */
	mixer_control_set(&mixer->controls[9], 0, 0);
	/* master volume */
	mixer_control_set(&mixer->controls[18], 0, 75);
	/* master switch */
	mixer_control_set(&mixer->controls[19], 0, 1);

	/* headset mic volume */
	mixer_control_set(&mixer->controls[5], 0, 31);
	mixer_control_set(&mixer->controls[5], 1, 31);
	/* dmic volume */
	mixer_control_set(&mixer->controls[32], 0, 50);
	mixer_control_set(&mixer->controls[32], 1, 50);
	/* capture volume */
	mixer_control_set(&mixer->controls[12], 0, 63);
	mixer_control_set(&mixer->controls[12], 1, 63);
	/* capture switch */
	mixer_control_set(&mixer->controls[13], 0, 1);
	mixer_control_set(&mixer->controls[13], 1, 1);
}
