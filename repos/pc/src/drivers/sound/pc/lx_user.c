
#include <linux/delay.h>
#include <linux/fs.h>
#include <linux/sched/task.h>
#include <linux/slab.h>
#include <sound/asound.h>
#include <sound/core.h>
#include <sound/pcm.h>

struct timespec {
	__kernel_old_time_t	tv_sec;		/* seconds */
	long			tv_nsec;	/* nanoseconds */
};

typedef signed long time_t;
typedef struct { unsigned char pad[sizeof(time_t) - sizeof(int)]; } __time_pad;
struct snd_pcm_status {
	snd_pcm_state_t state;		/* stream state */
	__time_pad pad1;		/* align to timespec */
	struct timespec trigger_tstamp;	/* time when stream was started/stopped/paused */
	struct timespec tstamp;		/* reference timestamp */
	snd_pcm_uframes_t appl_ptr;	/* appl ptr */
	snd_pcm_uframes_t hw_ptr;	/* hw ptr */
	snd_pcm_sframes_t delay;	/* current delay in frames */
	snd_pcm_uframes_t avail;	/* number of frames available */
	snd_pcm_uframes_t avail_max;	/* max frames available on hw since last status */
	snd_pcm_uframes_t overrange;	/* count of ADC (capture) overrange detections from last status */
	snd_pcm_state_t suspended_state; /* suspended stream state */
	__u32 audio_tstamp_data;	 /* needed for 64-bit alignment, used for configs/report to/from userspace */
	struct timespec audio_tstamp;	/* sample counter, wall clock, PHC or on-demand sync'ed */
	struct timespec driver_tstamp;	/* useful in case reference system tstamp is reported with delay */
	__u32 audio_tstamp_accuracy;	/* in ns units, only valid if indicated in audio_tstamp_data */
	unsigned char reserved[52-2*sizeof(struct timespec)]; /* must be filled with zero */
};

static int sound_ioctl(struct file *file, unsigned cmd, void *arg)
{
	return file->f_op->unlocked_ioctl(file, cmd, (unsigned long)arg);
}


/** TESTING */
static const char *const class_labels[] = {
    [SNDRV_PCM_CLASS_GENERIC]   = "generic",
    [SNDRV_PCM_CLASS_MULTI]     = "multi",
    [SNDRV_PCM_CLASS_MODEM]     = "modem",
    [SNDRV_PCM_CLASS_DIGITIZER] = "digitizer"
};
static const char *const subclass_labels[] = {
    [SNDRV_PCM_SUBCLASS_GENERIC_MIX]    = "generic-mix",
    [SNDRV_PCM_SUBCLASS_MULTI_MIX]      = "multi-mix"
};
static const char *const direction_labels[] = {
    [SNDRV_PCM_STREAM_PLAYBACK] = "playback",
    [SNDRV_PCM_STREAM_CAPTURE]  = "capture"
};
#if 1
static void dump_pcm_info(const struct snd_pcm_info *info)
{
    printk("        id:             %s\n", info->id);
    printk("        name:           %s\n", info->name);
    printk("        subname:        %s\n", info->subname);
    printk("        dev_class:      %s\n", class_labels[info->dev_class]);
    printk("        dev_subclass:   %s\n", subclass_labels[info->dev_subclass]);
}

static int enumerate_pcm_subdevices(struct file *file, int card, int device)
{
    static const int dirs[SNDRV_PCM_STREAM_LAST + 1] = {
        [0] = SNDRV_PCM_STREAM_PLAYBACK,
        [1] = SNDRV_PCM_STREAM_CAPTURE,
    };
    struct snd_pcm_info info;
    int subdevice;
    int i, err;

    for (i = 0; i < sizeof(dirs) / sizeof(dirs[0]); ++i) {
        subdevice = 0;
        while (1) {
            memset(&info, 0, sizeof(struct snd_pcm_info));
            info.device = device;
            info.subdevice = subdevice;
            info.card = card;
            info.stream = dirs[i];

            err = sound_ioctl(file, SNDRV_CTL_IOCTL_PCM_INFO, &info);
            if (err < 0) {
                if (err != -ENOENT) {
                    printk("ioctl(2) with PCM_INFO: %d\n", err);
                    return -err;
                }
            } else {
                if (subdevice == 0) {
                    printk("    direction:          %s\n",
                           direction_labels[dirs[i]]);
                    printk("    node:               pcmC%dD%d%c\n",
                           card, device,
                           dirs[i] == SNDRV_PCM_STREAM_CAPTURE ? 'c' : 'p');
                }

                printk("      subdevice:        %u\n", info.subdevice);

                dump_pcm_info(&info);
            }

            if (++subdevice >= info.subdevices_count)
                break;
        }
    }

    return 0;
}

static void enumerate_pcm_devices(struct file *file, int card)
{
    int device;
    int err;

    device = -1;
    while (1) {
        err = sound_ioctl(file, SNDRV_CTL_IOCTL_PCM_NEXT_DEVICE, &device);
        if (err < 0) {
            printk("ioctl(2) with PCM_NEXT_DEVICE: %d\n", err);
            return;
        }
        if (device < 0)
          break;

        printk("  device:               %d\n", device);

        enumerate_pcm_subdevices(file, card, device);
        //++device;
    }
}
#endif
static int dump_card_info(struct file *file, struct snd_ctl_card_info *info)
{
    int err = sound_ioctl(file, SNDRV_CTL_IOCTL_CARD_INFO, info);
    if (err < 0) {
        printk("ioctl(2) for card info: %d\n", err);
        return err;
    }

    printk("  card:                 %d\n", info->card);
    printk("  id:                   %s\n", info->id);
    printk("  driver:               %s\n", info->driver);
    printk("  name:                 %s\n", info->name);
    printk("  longname:             %s\n", info->longname);
    printk("  mixername:            %s\n", info->mixername);
    printk("  component:            %s\n", info->components);

    return 0;
}

/** END TESTING */

static struct file_operations const *_alsa_fops;

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


static void hw_set_mask(struct snd_pcm_hw_params *params, unsigned index, unsigned bit)
{
	if (bit == ~0u)
		memset(params->masks[index].bits, 0xff, sizeof(params->masks[index].bits));
	else
		params->masks[index].bits[0] = 1u << bit;

	params->rmask |= 1u << index;
}


static void hw_set_interval(struct snd_pcm_hw_params *params, unsigned index, unsigned value)
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


static void hw_init_params(struct snd_pcm_hw_params *params)
{
	unsigned i;
	for (i = 0; i <= SNDRV_PCM_HW_PARAM_LAST_MASK; i++)
		hw_set_mask(params, i, ~0u);

	for (i = SNDRV_PCM_HW_PARAM_FIRST_INTERVAL; i <= SNDRV_PCM_HW_PARAM_LAST_INTERVAL; i++)
		hw_set_interval(params, i, ~0u);

	params->cmask = 0;
	params->info  = 0;
}


static void hw_param_configure(struct file *pcm_file)
{
	int err;
	struct snd_pcm_hw_params *params = kzalloc(sizeof(*params), 0);

	hw_init_params(params);

	printk("%s:%d: ioctl refine\n", __func__, __LINE__);
	err = sound_ioctl(pcm_file, SNDRV_PCM_IOCTL_HW_REFINE, params);
	printk("%s:%d ioctl refine ret: %d access: %x\n", __func__, __LINE__, err, params->masks[0].bits[0]);
	hw_set_mask(params, SNDRV_PCM_HW_PARAM_ACCESS, SNDRV_PCM_ACCESS_RW_INTERLEAVED);
	hw_set_mask(params, SNDRV_PCM_HW_PARAM_FORMAT, SNDRV_PCM_FORMAT_S16_LE);
	hw_set_mask(params, SNDRV_PCM_HW_PARAM_SUBFORMAT, SNDRV_PCM_SUBFORMAT_STD);
	hw_set_interval(params, SNDRV_PCM_HW_PARAM_RATE, 48000);
	hw_set_interval(params, SNDRV_PCM_HW_PARAM_CHANNELS, 2);
	/* period_size = period * format_size * channels = 512 * 2 * 2 */
	hw_set_interval(params, SNDRV_PCM_HW_PARAM_PERIOD_SIZE, 2048);

	printk("%s:%d ioctl params\n", __func__, __LINE__);
	err = sound_ioctl(pcm_file, SNDRV_PCM_IOCTL_HW_PARAMS, params);
	printk("%s:%d ioctl params: %d\n", __func__, __LINE__, err);
	kfree(params);
}


int hw_prepare(struct file *file)
{
	int err;
	printk("%s:%d\n", __func__, __LINE__);
	err = sound_ioctl(file, SNDRV_PCM_IOCTL_PREPARE, NULL);
	printk("%s:%d err=%d\n", __func__, __LINE__, err);
	return err;
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


void dump_state(struct file *file)
{
	int err;
	struct snd_pcm_status status = { 0 };

	printk("%s:%d\n", __func__, __LINE__);
	err = sound_ioctl(file, SNDRV_PCM_IOCTL_STATUS, &status);
	if (err) printk("%s:%d err=%d\n", __func__, __LINE__, err);
	else printk("%s:%d status: %s\n", __func__, __LINE__, state_labels[status.state]);

}


#define SOUND_DATA _binary_sinus_s16_start
extern char SOUND_DATA[];

void hw_play(struct file *file)
{
	struct snd_xferi xfer;
	int i, err;
	void *buffer = kmalloc(2048, 0);


#if 0
	xfer.result = 0;
	xfer.buf = buffer;
	xfer.frames = 512;
	err = sound_ioctl(file, SNDRV_PCM_IOCTL_WRITEI_FRAMES, &xfer);
	if (err) {
		printk("%s:%d err=%d\n", __func__, __LINE__, err);
		return;
	}
#endif
#if 0
	dump_state(file);

	printk("%s:%d\n", __func__, __LINE__);
	err = sound_ioctl(file, SNDRV_PCM_IOCTL_START, NULL);
	if (err) {
		printk("%s:%d err=%d\n", __func__, __LINE__, err);
		return;
	}

	dump_state(file);
#endif
	for (i = 0; i < 1000; i++) {
		memcpy(buffer, &SOUND_DATA[(i * 2048) % 128], 2048);
		xfer.result = 0;
		xfer.buf = buffer;
		xfer.frames = 512;

		printk("%s:%d i=%d\n", __func__, __LINE__, i);
		err = sound_ioctl(file, SNDRV_PCM_IOCTL_WRITEI_FRAMES, &xfer);
		if (err) {
			printk("%s:%d i=%d err=%d\n", __func__, __LINE__, i, err);
			return;
		}

		dump_state(file);
	}
}


static struct file *sound_device_open(struct snd_card *card, int dev)
{
	struct snd_device *device;
	struct snd_pcm *pcm;
	struct file  *file;
	struct inode *inode;
	bool found = false;
	int cidx;
	struct device *pcm_device;
	int err;

	list_for_each_entry(device, &card->devices, list) {
		pcm = device->device_data;
		if (pcm->device == dev) {
			found = true;
			break;
		}
	}

	if (!found) {
		printk("%s:%d: dev %d not found\n", __func__, __LINE__, dev);
		return NULL;
	}

	for (cidx = 0; cidx < 2; cidx++) {
		if (pcm->streams[cidx].substream != NULL)
			break;
	}
	printk("PCM cidx: %d\n", cidx);
	pcm_device = &pcm->streams[cidx].dev;
	printk("PCM device major: %u minor: %u\n",
	        MAJOR(pcm_device->devt), MINOR(pcm_device->devt));


	inode = alloc_anon_inode(NULL);
	inode->i_rdev = MKDEV(MAJOR(pcm_device->devt), MINOR(pcm_device->devt));
	file = (struct file *)kzalloc(sizeof (struct file), 0);

	err = _alsa_fops->open(inode, file);
	if (err) {
		printk("failed to open sound device: %d\n", err);
		return NULL;
	}
	return file;
}


static int sound_card_task(void *data)
{
	int i, err;
	bool found = false;
	struct snd_card *card = NULL;
	struct file  *file;
	struct inode *inode;
	struct snd_ctl_card_info info = { 0 };

	while (found == false) {

		for (i = 0; i < SNDRV_CARDS; i++) {

			if (snd_card_ref(i)) {
				card = snd_card_ref(i);
				found = true;
			}
		}

		printk("CARD: %p\n", card);
		if (found == false) msleep(1000);
	}

	printk("open control device for card%d ...\n", card->number);
	printk("control device major: %u minor: %u\n",
	       MAJOR(card->ctl_dev.devt), MINOR(card->ctl_dev.devt));
	inode = alloc_anon_inode(NULL);
	inode->i_rdev = MKDEV(MAJOR(card->ctl_dev.devt), MINOR(card->ctl_dev.devt));
	file = (struct file *)kzalloc(sizeof (struct file), 0);

	err = _alsa_fops->open(inode, file);
	printk("control open returned: %d\n", err);

	dump_card_info(file, &info);
	enumerate_pcm_devices(file, info.card);

	printk("open device 0\n");
	file = sound_device_open(card, 0);
	if (file) {
		hw_param_configure(file);
		hw_prepare(file);
		dump_state(file);
		hw_play(file);
	}

	lx_emul_task_schedule(true);
	return 0;
}


void lx_user_init(void)
{
	int pid = kernel_thread(sound_card_task, NULL, CLONE_FS | CLONE_FILES);
}
