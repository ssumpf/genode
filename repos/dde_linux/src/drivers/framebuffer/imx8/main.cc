/*
 * \brief  i.MX8 framebuffer driver
 * \author Norman Feske
 * \author Stefan Kalkowski
 * \author Christian Prochaska
 * \date   2015-08-19
 */

/*
 * Copyright (C) 2015-2019 Genode Labs GmbH
 *
 * This file is distributed under the terms of the GNU General Public License
 * version 2.
 */

/* Genode includes */
#include <base/log.h>
#include <base/component.h>
#include <base/heap.h>
#include <base/attached_rom_dataspace.h>

/* Server related local includes */
#include <component.h>

/* Linux emulation environment includes */
#include <lx_emul.h>
#include <lx_kit/env.h>
#include <lx_kit/malloc.h>
#include <lx_kit/scheduler.h>
#include <lx_kit/timer.h>
#include <lx_kit/irq.h>
#include <lx_kit/work.h>

/* Linux module functions */
extern "C" void radix_tree_init(); /* called by start_kernel(void) normally */
extern "C" void drm_connector_ida_init(); /* called by drm_core_init(void) normally */
extern "C" int module_irq_imx_irqsteer_init();
extern "C" int module_imx_drm_pdrv_init();
extern "C" int module_dcss_driver_init();
extern "C" int module_dcss_crtc_driver_init();
extern "C" int module_imx_hdp_imx_platform_driver_init();
extern "C" int module_mixel_mipi_phy_driver_init();
extern "C" int module_imx_nwl_dsi_driver_bridge_init();
extern "C" int module_imx_nwl_dsi_driver_init();
extern "C" int module_rad_panel_driver_init();
extern "C" void postcore_mipi_dsi_bus_init();


static void run_linux(void * m);

unsigned long jiffies;


struct Main
{
	Genode::Env                   &env;
	Genode::Entrypoint            &ep     { env.ep() };
	Genode::Attached_rom_dataspace config { env, "config" };
	Genode::Heap                   heap   { env.ram(), env.rm() };
	Framebuffer::Root              root   { env, heap, config };


	/* Linux task that handles the initialization */
	Genode::Constructible<Lx::Task> linux;

	Main(Genode::Env &env) : env(env)
	{
		Genode::log("--- i.MX8 framebuffer driver ---");

		Lx_kit::construct_env(env);

		LX_MUTEX_INIT(bridge_lock);
		LX_MUTEX_INIT(core_lock);
		LX_MUTEX_INIT(component_mutex);
		LX_MUTEX_INIT(host_lock);

		/* init singleton Lx::Scheduler */
		Lx::scheduler(&env);

		Lx::malloc_init(env, heap);

		/* init singleton Lx::Timer */
		Lx::timer(&env, &ep, &heap, &jiffies);

		/* init singleton Lx::Irq */
		Lx::Irq::irq(&ep, &heap);

		/* init singleton Lx::Work */
		Lx::Work::work_queue(&heap);

		linux.construct(run_linux, reinterpret_cast<void*>(this),
		                "linux", Lx::Task::PRIORITY_0, Lx::scheduler());

		/* give all task a first kick before returning */
		Lx::scheduler().schedule();
	}

	void announce() { env.parent().announce(ep.manage(root)); }

	Lx::Task &linux_task() { return *linux; }
};


struct Policy_agent
{
	Main &main;
	Genode::Signal_handler<Policy_agent> handler;
	bool _pending = false;

	void handle()
	{
		_pending = true;
		main.linux_task().unblock();
		Lx::scheduler().schedule();
	}

	bool pending()
	{
		bool ret = _pending;
		_pending = false;
		return ret;
	}

	Policy_agent(Main &m)
	: main(m), handler(main.ep, *this, &Policy_agent::handle) {}
};


static void run_linux(void * m)
{
	Main * main = reinterpret_cast<Main*>(m);

	Genode::log("Starting linux main thread ...");
	system_wq  = alloc_workqueue("system_wq", 0, 0);

	radix_tree_init();
	drm_connector_ida_init();

	module_irq_imx_irqsteer_init();
	module_dcss_driver_init();
	module_imx_drm_pdrv_init();
	module_dcss_crtc_driver_init();
	module_imx_hdp_imx_platform_driver_init();

	/* MIPI DSI */
	Genode::log("module_mixel_mipi_phy_driver_init");
	module_mixel_mipi_phy_driver_init();
	Genode::log("---------------------------------");
	Genode::log("module_imx_nwl_dsi_driver_bridge_init");
	module_imx_nwl_dsi_driver_bridge_init();
	Genode::log("---------------------------------");
	Genode::log("module_imx_nwl_dsi_driver_init");
	module_imx_nwl_dsi_driver_init();
	Genode::log("---------------------------------");
	Genode::log("postcore_mipi_dsi_bus_init");
	postcore_mipi_dsi_bus_init();
	Genode::log("---------------------------------");
	Genode::log("module_rad_panel_driver_init");
	module_rad_panel_driver_init();
	Genode::log("---------------------------------");

	/**
	 * This device is originally created with the name '32e2d000.irqsteer'
	 * via 'of_platform_bus_create()'. Here it is called 'imx-irqsteer' to match
	 * the driver name.
	 */

	struct platform_device *imx_irqsteer_pdev =
		platform_device_alloc("imx-irqsteer", 0);
	
	static resource imx_irqsteer_resources[] = 	{
		{ 0x32e2d000, 0x32e2dfff, "imx-irqsteer", IORESOURCE_MEM },
		{         50,         50, "imx-irqsteer", IORESOURCE_IRQ },
	};

	imx_irqsteer_pdev->num_resources = 2;
	imx_irqsteer_pdev->resource = imx_irqsteer_resources;

	imx_irqsteer_pdev->dev.of_node             = (device_node*)kzalloc(sizeof(device_node), 0);
	imx_irqsteer_pdev->dev.of_node->name       = "imx-irqsteer";
	imx_irqsteer_pdev->dev.of_node->full_name  = "imx-irqsteer";

	platform_device_register(imx_irqsteer_pdev);


	/**
	 * This device is originally created with the name '32e00000.dcss'
	 * via 'of_platform_bus_create()'. Here it is called 'dcss-core' to match
	 * the driver name.
	 */

	struct platform_device *dcss_pdev =
		platform_device_alloc("dcss-core", 0);

	static resource dcss_resources[] = 	{
		{ 0x32e00000, 0x32efffff, "dcss",       IORESOURCE_MEM },
		{          3,          3, "dpr_dc_ch0", IORESOURCE_IRQ },
		{          4,          4, "dpr_dc_ch1", IORESOURCE_IRQ },
		{          5,          5, "dpr_dc_ch2", IORESOURCE_IRQ },
		{          6,          6, "ctx_ld",     IORESOURCE_IRQ },
		{          8,          8, "ctxld_kick", IORESOURCE_IRQ },
		{          9,          9, "dtg_prg1",   IORESOURCE_IRQ },
		{         16,         16, "dtrc_ch1",   IORESOURCE_IRQ },
		{         17,         17, "dtrc_ch2",   IORESOURCE_IRQ },
	};

	dcss_pdev->num_resources = 9;
	dcss_pdev->resource = dcss_resources;

	dcss_pdev->dev.of_node                    = (device_node*)kzalloc(sizeof(device_node), 0);
	dcss_pdev->dev.of_node->name              = "dcss";
	dcss_pdev->dev.of_node->full_name         = "dcss";
	dcss_pdev->dev.of_node->properties        = (property*)kzalloc(sizeof(property), 0);
	dcss_pdev->dev.of_node->properties->name  = "disp-dev";
	dcss_pdev->dev.of_node->properties->value = (void*)"hdmi_disp";

	platform_device_register(dcss_pdev);


	/**
	 * This device is originally created with the name '32c00000.hdmi'
	 * via 'of_platform_bus_create()'. Here it is called 'i.mx8-hdp' to match
	 * the driver name.
	 */

/*
	struct platform_device *hdp_pdev =
		platform_device_alloc("i.mx8-hdp", 0);

	static resource hdp_resources[] = 	{
		{ 0x32c00000, 0x32cfffff, "hdp_ctrl",  IORESOURCE_MEM },
		{ 0x32e40000, 0x32e7ffff, "hdp_crs",   IORESOURCE_MEM },
		{ 0x32e2f000, 0x32e2f00f, "hdp_reset", IORESOURCE_MEM },
		{         48,         48, "plug_in",   IORESOURCE_IRQ },
		{         57,         57, "plug_out",  IORESOURCE_IRQ },
	};

	hdp_pdev->num_resources = 5;
	hdp_pdev->resource = hdp_resources;

	hdp_pdev->dev.of_node                    = (device_node*)kzalloc(sizeof(device_node), 0);
	hdp_pdev->dev.of_node->name              = "hdmi";
	hdp_pdev->dev.of_node->full_name         = "hdmi";
	hdp_pdev->dev.of_node->properties        = (property*)kzalloc(sizeof(property), 0);
	hdp_pdev->dev.of_node->properties->name  = "compatible";
	hdp_pdev->dev.of_node->properties->value = (void*)"fsl,imx8mq-hdmi";

	platform_device_register(hdp_pdev);
*/
	struct platform_device *mipi_dsi_phy_pdev =
		platform_device_alloc("mixel-mipi-dsi-phy", 0);

	static resource mipi_dsi_phy_resources[] = {
		{ 0x30a00300, 0x30a003ff, "dsi_phy", IORESOURCE_MEM }
	};

	mipi_dsi_phy_pdev->num_resources = 1;
	mipi_dsi_phy_pdev->resource      = mipi_dsi_phy_resources;

	mipi_dsi_phy_pdev->dev.of_node                      = (device_node*)kzalloc(sizeof(device_node), 0);
	mipi_dsi_phy_pdev->dev.of_node->properties          = (property*)kzalloc(2*sizeof(property), 0);
	mipi_dsi_phy_pdev->dev.of_node->properties[0].name  = "compatible";
	mipi_dsi_phy_pdev->dev.of_node->properties[0].value = (void*)"mixel,imx8mq-mipi-dsi-phy";
	mipi_dsi_phy_pdev->dev.of_node->properties[0].next  = &mipi_dsi_phy_pdev->dev.of_node->properties[1];
	mipi_dsi_phy_pdev->dev.of_node->properties[1].name  = "dsi_phy";
	mipi_dsi_phy_pdev->dev.of_node->properties[1].value = (void*)0;

	platform_device_register(mipi_dsi_phy_pdev);

	struct platform_device *mipi_dsi_bridge_pdev =
		platform_device_alloc("nwl-mipi-dsi", 0);

	static resource mipi_dsi_bridge_resources[] = {
		{ 0x30a00000, 0x30a002ff, "mipi_dsi_bridge", IORESOURCE_MEM },
		{         66,         66, "mipi_dsi",        IORESOURCE_IRQ }
	};

	mipi_dsi_bridge_pdev->num_resources = 2;
	mipi_dsi_bridge_pdev->resource      = mipi_dsi_bridge_resources;

	Genode::addr_t **phy_ptr =
	  (Genode::addr_t **)devres_find(&mipi_dsi_phy_pdev->dev, devm_phy_consume, nullptr, nullptr);
	Genode::log("main: ptr ", phy_ptr, " phy ", *phy_ptr);
	mipi_dsi_bridge_pdev->dev.of_node                      = (device_node*)kzalloc(sizeof(device_node), 0);
	mipi_dsi_bridge_pdev->dev.of_node->name                = "mipi_dsi_bridge";
	mipi_dsi_bridge_pdev->dev.of_node->properties          = (property*)kzalloc(sizeof(property), 0);
	mipi_dsi_bridge_pdev->dev.of_node->properties[0].name  = "dphy";
	mipi_dsi_bridge_pdev->dev.of_node->properties[0].value = (void*)*phy_ptr;
	mipi_dsi_bridge_pdev->dev.of_node->properties[0].next  = nullptr;

	platform_device_register(mipi_dsi_bridge_pdev);

	struct platform_device *mipi_dsi_imx_pdev =
		platform_device_alloc("nwl_dsi-imx", 0);

	mipi_dsi_imx_pdev->dev.of_node                      = (device_node*)kzalloc(sizeof(device_node), 0);
	mipi_dsi_imx_pdev->dev.of_node->name                = "mipi_dsi";

	platform_device_register(mipi_dsi_imx_pdev);
//	mipi_pdev.dev.of_node = (device_node *)kzalloc(sizeof(device_node), 0);
//	mipi_pdev
/*
	struct platform_device *rad_pdev =
		platform_device_alloc("panel-raydium-rm67191", 0);

	rad_pdev->dev.bus = mipi_dsi_bus();
	Genode::log("rad bys: ", rad_pdev->dev.bus);
	Genode::log("register rad");
	platform_device_register(rad_pdev);
	Genode::log("done rad");
*/
	/**
	 * This device is originally created with the name 'display-subsystem'
	 * via 'of_platform_bus_create()'. Here it is called 'imx-drm' to match
	 * the driver name.
	 */

	struct platform_device *display_subsystem_pdev =
		platform_device_alloc("imx-drm", 0);

	static device_node display_subsystem_of_node = { "display-subsystem" };

	display_subsystem_pdev->dev.of_node = &display_subsystem_of_node;

	platform_device_register(display_subsystem_pdev);


	main->root.session.driver().finish_initialization();
	main->announce();

	Policy_agent pa(*main);
	main->root.session.driver().config_sigh(pa.handler);
	main->config.sigh(pa.handler);

	while (1) {
		Lx::scheduler().current()->block_and_schedule();
		while (pa.pending())
			main->root.session.config_changed();
	}
}


void Component::construct(Genode::Env &env)
{
	/* XXX execute constructors of global statics */
	env.exec_static_constructors();

	static Main m(env);
}
