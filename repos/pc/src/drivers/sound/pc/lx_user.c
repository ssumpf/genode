
#include <linux/delay.h>
#include <linux/fs.h>
#include <linux/sched/task.h>
#include <linux/slab.h>
#include <sound/asound.h>
#include <sound/core.h>
#include <sound/pcm.h>


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


static int sound_device_open(struct snd_card *card, int dev)
{
	struct snd_device *device;
	struct snd_pcm *pcm;
	struct file  *file;
	struct inode *inode;
	bool found = false;
	int cidx;
	struct device *pcm_device;

	list_for_each_entry(device, &card->devices, list) {
		pcm = device->device_data;
		if (pcm->device == dev) {
			found = true;
			break;
		}
	}

	if (!found) {
		printk("%s:%d: dev %d not found\n", __func__, __LINE__, dev);
		return -ENODEV;
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

	return _alsa_fops->open(inode, file);
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
	err = sound_device_open(card, 0);
	printk("open device returned: %d\n", err);

	lx_emul_task_schedule(true);
	return 0;
}


void lx_user_init(void)
{
	int pid = kernel_thread(sound_card_task, NULL, CLONE_FS | CLONE_FILES);
}
