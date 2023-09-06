#include <linux/netdevice.h>
#include <linux/etherdevice.h>

static int net_open(struct net_device *dev)
{
	printk("%s:%d\n", __func__, __LINE__);
	while (1) ;
	return 0;
}


static const struct net_device_ops net_ops =
{
	.ndo_open       = net_open,
/*
	.ndo_start_xmit = driver_net_xmit,
	.ndo_change_mtu = driver_change_mtu,
*/
};


static int __init virtio_net_driver_init(void)
{
	struct net_device *dev;
	int err = -ENODEV;
	printk("MISC init\n");

	dev = alloc_etherdev(0);

	if (!(dev = alloc_etherdev(0)))
		goto out;

	dev->netdev_ops = &net_ops;

	/* set MAC */
	//net_mac(dev->dev_addr, ETH_ALEN);

	if ((err = register_netdev(dev))) {
		panic("driver: Could not register back-end %d\n", err);
		goto out_free;
	}

	return 0;

out_free:
	free_netdev(dev);
out:
	return err;
	return 0;
}


/**
 * Let's hook into the virtio_net_driver initcall, so we do not need to register
 * an additional one
 */
module_init(virtio_net_driver_init);

