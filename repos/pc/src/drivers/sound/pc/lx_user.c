
#include <linux/delay.h>
#include <linux/fs.h>
#include <linux/sched/task.h>
#include <linux/slab.h>
#include <sound/asound.h>
#include <sound/core.h>
#include <sound/pcm.h>

static struct task_struct *_lx_user_task;
static struct file_operations const *_alsa_fops;


enum Stream_direction {
	PLAYBACK = SNDRV_PCM_STREAM_PLAYBACK,
	CAPTURE  = SNDRV_PCM_STREAM_CAPTURE,
};


static const char *const direction_labels[] = {
	[PLAYBACK] = "playback",
	[CAPTURE]  = "capture"
};


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


/* called at end IRQ handler */
void kill_fasync(struct fasync_struct ** fp,int sig,int band)
{
	lx_emul_task_unblock(_lx_user_task);
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
		for (i = PLAYBACK; i <= CAPTURE; i++) {
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


struct sound_handle {
	struct file  *file;
	struct inode *inode;
};


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


static struct sound_handle *sound_devt_open(dev_t devt)
{
	int err;
	struct sound_handle *handle = alloc_sound_handle();
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
struct sound_handle *sound_device_open(struct snd_card *card, char const *node)
{
	struct snd_pcm_str *stream;

	stream = for_each_stream(card, _match_node, node);

	if (!stream) {
		printk("PCM node '%s' not found\n");
		return NULL;
	}

	printk("PCM device major: %u minor: %u\n",
	        MAJOR(stream->dev.devt), MINOR(stream->dev.devt));

	return sound_devt_open(stream->dev.devt);
}


static int sound_device_close(struct sound_handle *handle)
{
	int err = 0;
	if (handle->file->f_op->release)
		err = handle->file->f_op->release(handle->inode, handle->file);

	free_sound_handle(handle);
	return err;
}


static void sleep_forever(void)
{
	while (1) lx_emul_task_schedule(true);
}


static int sound_card_task(void *data)
{
	struct snd_card *card = wait_for_card();
	struct sound_handle *handle;
	int err;
	printk("Sound card: %s\n", card ? "found" : "not found");

	if (!card)
		sleep_forever();

	report_pcm_devices(card);

	handle = sound_device_open(card, "pcmC0D0c");
	printk("opened: %p\n", handle);
	err = sound_device_close(handle);
	printk("closed: %d\n", err);

	sleep_forever();

	return 0;
}


void lx_user_init(void)
{
	int pid = kernel_thread(sound_card_task, NULL, CLONE_FS | CLONE_FILES);
	_lx_user_task = find_task_by_pid_ns(pid, NULL);
}
