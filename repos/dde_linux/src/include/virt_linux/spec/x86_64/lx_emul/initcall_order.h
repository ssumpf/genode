/*
 * \brief  Array defining order of Linux Kernel initcalls
 * \author Automatically generated file - do no edit
 * \date   2023-06-21
 */

#pragma once

static const char * lx_emul_initcall_order[] = {
	"__initcall_init_hw_perf_eventsearly",
	"__initcall_start",
	"__initcall_do_init_real_modeearly",
	"__initcall_bp_init_aperfmperfearly",
	"__initcall_register_nmi_cpu_backtrace_handlerearly",
	"__initcall_spawn_ksoftirqdearly",
	"__initcall_migration_initearly",
	"__initcall_srcu_bootup_announceearly",
	"__initcall_rcu_spawn_gp_kthreadearly",
	"__initcall_check_cpu_stall_initearly",
	"__initcall_rcu_sysrq_initearly",
	"__initcall_cpu_stop_initearly",
	"__initcall_irq_work_init_threadsearly",
	"__initcall_static_call_initearly",
	"__initcall_init_zero_pfnearly",
	"__initcall_init_mmap_min_addr0",
	"__initcall_pci_realloc_setup_params0",
	"__initcall_inet_frag_wq_init0",
	"__initcall_reboot_init1",
	"__initcall_ksysfs_init1",
	"__initcall_rcu_set_runtime_mode1",
	"__initcall_init_jiffies_clocksource1",
	"__initcall_init_elf_binfmt1",
	"__initcall_virtio_init1",
	"__initcall_sock_init1",
	"__initcall_net_defaults_init1",
	"__initcall_init_default_flow_dissectors1",
	"__initcall_netlink_proto_init1",
	"__initcall_genl_init1",
	"__initcall_bdi_class_init2",
	"__initcall_mm_sysfs_init2",
	"__initcall_init_per_zone_wmark_min2",
	"__initcall_pcibus_class_init2",
	"__initcall_pci_driver_init2",
	"__initcall_tty_class_init2",
	"__initcall_vtconsole_class_init2",
	"__initcall_devlink_class_init2",
	"__initcall_software_node_init2",
	"__initcall_amd_postcore_init2",
	"__initcall_kobject_uevent_init2",
	"__initcall_bts_init3",
	"__initcall_pt_init3",
	"__initcall_sbf_init3",
	"__initcall_arch_kdebugfs_init3",
	"__initcall_xfd_update_static_branch3",
	"__initcall_intel_pconfig_init3",
	"__initcall_pci_arch_init3",
	"__initcall_init_vdso4",
	"__initcall_fixup_ht_bug4",
	"__initcall_topology_init4",
	"__initcall_uid_cache_init4",
	"__initcall_user_namespace_sysctl_init4",
	"__initcall_oom_init4",
	"__initcall_default_bdi_init4",
	"__initcall_percpu_enable_async4",
	"__initcall_init_user_reserve4",
	"__initcall_init_admin_reserve4",
	"__initcall_init_reserve_notifier4",
	"__initcall_aes_init4",
	"__initcall_prng_mod_init4",
	"__initcall_misc_init4",
	"__initcall_usb_common_init4",
	"__initcall_usb_init4",
	"__initcall_input_init4",
	"__initcall_power_supply_class_init4",
	"__initcall_leds_init4",
	"__initcall_net_dev_init4",
	"__initcall_neigh_init4",
	"__initcall_fib_notifier_init4",
	"__initcall_ethnl_init4",
	"__initcall_nexthop_init4",
	"__initcall_pci_subsys_init4",
	"__initcall_vsprintf_init_hashval4",
	"__initcall_nmi_warning_debugfs5",
	"__initcall_hpet_late_init5",
	"__initcall_init_amd_nbs5",
	"__initcall_iomem_init_inode5",
	"__initcall_clocksource_done_booting5",
	"__initcall_init_pipe_fs5",
	"__initcall_anon_inode_init5",
	"__initcall_init_ramfs_fs5",
	"__initcall_chr_dev_init5",
	"__initcall_hwrng_modinit5",
	"__initcall_eth_offload_init5",
	"__initcall_ipv4_offload_init5",
	"__initcall_inet_init5",
	"__initcall_ipv6_offload_init5",
	"__initcall_pcibios_assign_resources5",
	"__initcall_pci_apply_final_quirks5s",
	"__initcall_populate_rootfsrootfs",
	"__initcall_pci_iommu_initrootfs",
	"__initcall_rapl_pmu_init6",
	"__initcall_amd_ibs_init6",
	"__initcall_msr_init6",
	"__initcall_intel_uncore_init6",
	"__initcall_cstate_pmu_init6",
	"__initcall_register_kernel_offset_dumper6",
	"__initcall_i8259A_init_ops6",
	"__initcall_init_tsc_clocksource6",
	"__initcall_add_rtc_cmos6",
	"__initcall_umwait_init6",
	"__initcall_ioapic_init_ops6",
	"__initcall_chacha_simd_mod_init6",
	"__initcall_blake2s_mod_init6",
	"__initcall_poly1305_simd_mod_init6",
	"__initcall_curve25519_mod_init6",
	"__initcall_timekeeping_init_ops6",
	"__initcall_alarmtimer_init6",
	"__initcall_perf_event_sysfs_init6",
	"__initcall_kswapd_init6",
	"__initcall_mm_compute_batch_init6",
	"__initcall_workingset_init6",
	"__initcall_fcntl_init6",
	"__initcall_start_dirtytime_writeback6",
	"__initcall_init_devpts_fs6",
	"__initcall_jent_mod_init6",
	"__initcall_blake2s_mod_init6",
	"__initcall_chacha20poly1305_init6",
	"__initcall_curve25519_init6",
	"__initcall_percpu_counter_startup6",
	"__initcall_virtio_pci_driver_init6",
	"__initcall_n_null_init6",
	"__initcall_pty_init6",
	"__initcall_virtio_console_init6",
	"__initcall_timeriomem_rng_driver_init6",
	"__initcall_intel_rng_mod_init6",
	"__initcall_amd_rng_mod_init6",
	"__initcall_via_rng_mod_init6",
	"__initcall_topology_sysfs_init6",
	"__initcall_cacheinfo_sysfs_init6",
	"__initcall_wg_mod_init6",
	"__initcall_blackhole_netdev_init6",
	"__initcall_virtio_net_driver_init6",
	"__initcall_net_failover_init6",
	"__initcall_input_leds_init6",
	"__initcall_evdev_init6",
	"__initcall_hid_init6",
	"__initcall_hid_generic_init6",
	"__initcall_apple_driver_init6",
	"__initcall_ch_driver_init6",
	"__initcall_holtek_kbd_driver_init6",
	"__initcall_holtek_mouse_driver_init6",
	"__initcall_holtek_driver_init6",
	"__initcall_ms_driver_init6",
	"__initcall_mt_driver_init6",
	"__initcall_wacom_driver_init6",
	"__initcall_hid_init6",
	"__initcall_sock_diag_init6",
	"__initcall_failover_init6",
	"__initcall_gre_offload_init6",
	"__initcall_tunnel4_init6",
	"__initcall_inet_diag_init6",
	"__initcall_tcp_diag_init6",
	"__initcall_cubictcp_register6",
	"__initcall_inet6_init6",
	"__initcall_sit_init6",
	"__initcall_start_sync_check_timer7",
	"__initcall_update_mp_table7",
	"__initcall_lapic_insert_resource7",
	"__initcall_print_ipi_mode7",
	"__initcall_print_ICs7",
	"__initcall_create_tlb_single_page_flush_ceiling7",
	"__initcall_sched_clock_init_late7",
	"__initcall_printk_late_init7",
	"__initcall_check_early_ioremap_leak7",
	"__initcall_crypto_algapi_init7",
	"__initcall_pci_resource_alignment_sysfs_init7",
	"__initcall_pci_sysfs_init7",
	"__initcall_sync_state_resume_initcall7",
	"__initcall_deferred_probe_initcall7",
	"__initcall_tcp_congestion_default7",
	"__initcall_udp_tunnel_nic_init_module7",
	"__initcall_ip_auto_config7",
	"__initcall_con_initcon",
	"__initcall_end",
	"__initcall_hvc_console_initcon",
	"END_OF_INITCALL_ORDER_ARRAY_DUMMY_ENTRY"
};
