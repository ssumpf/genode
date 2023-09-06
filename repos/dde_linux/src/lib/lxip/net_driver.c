#include <linux/netdevice.h>
#include <linux/etherdevice.h>

#include <genode_c_api/nic_client.h>


static struct genode_nic_client *dev_nic_client(struct net_device *dev)
{
	return (struct genode_nic_client *)dev->ifalias;
}


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
	struct genode_mac_address mac;
	printk("MISC init\n");

	dev = alloc_etherdev(0);

	if (!(dev = alloc_etherdev(0)))
		goto out;

	dev->netdev_ops = &net_ops;

	dev->ifalias = (struct dev_ifalias *)genode_nic_client_create("");

	if (!dev->ifalias) {
		printk("Failed to create nic client\n");
		goto out_free;
	}

	/* set MAC */
	mac = genode_nic_client_mac_address(dev_nic_client(dev));
	dev_addr_set(dev, mac.addr);

	if ((err = register_netdev(dev))) {
		printk("Could not register net device driver %d\n", err);
		goto out_nic;
	}

	printk("%s:%d INIT done %pM\n", __func__, __LINE__, dev->dev_addr);

	return 0;

out_nic:
	genode_nic_client_destroy(dev_nic_client(dev));
out_free:
	free_netdev(dev);
out:
	return err;
}


/**
 * Let's hook into the virtio_net_driver initcall, so we do not need to register
 * an additional one
 */
module_init(virtio_net_driver_init);

