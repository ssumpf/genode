#
# Linux kernel configuration
#

# kernel fundamentals
LX_ENABLE += TTY SERIAL_EARLYCON SERIAL_OF_PLATFORM PRINTK HAS_IOMEM

# initrd support
LX_ENABLE += BINFMT_ELF BINFMT_SCRIPT BLK_DEV_INITRD

# UART device
LX_ENABLE += SERIAL_8250 SERIAL_8250_CONSOLE

# PCI support
LX_ENABLE += PCI

# ACPI support
LX_ENABLE += ACPI

# EFI support (enable for tests on EFI-only devices)
#LX_ENABLE += EFI

# general network and WLAN support
LX_ENABLE += NET NETDEVICES PACKET
LX_ENABLE += WLAN CFG80211 MAC80211
LX_ENABLE += RFKILL

# iwlwifi
LX_ENABLE += WLAN_VENDOR_INTEL IWLWIFI IWLDVM IWLMVM

# USB host-controller support (keep USB_USBNET hook)
LX_ENABLE += USB_USBNET
LX_ENABLE += USB_SUPPORT USB USB_ARCH_HAS_HCD USB_XHCI_HCD USB_EHCI_HCD USB_OHCI_HCD
LX_ENABLE += USB_PCI USB_UHCI_HCD

# Intel framebuffer
LX_ENABLE += DRM DRM_I915

# required for GPIO irqchip on tigerlake
LX_ENABLE += PINCTRL PINCTRL_TIGERLAKE

# I2C HID touchpad support (keep INPUT_EVDEV hook)
LX_ENABLE += INPUT_EVDEV HID_GENERIC
LX_ENABLE += MFD_INTEL_LPSS_PCI
LX_ENABLE += I2C_DESIGNWARE_PLATFORM
LX_ENABLE += I2C I2C_HID_ACPI

# no AML code is run that uses this feature
LX_DISABLE += ACPI_I2C_OPREGION

# uncomment to log all input events (requires "debug" on the kernel commandline)
#LX_ENABLE += INPUT_EVBUG

# uncomment for Linux in-kernel symbolic backtraces with show_stack(NULL, NULL, KERN_DEFAULT)
#LX_ENABLE += KALLSYMS

# to automatically set up screen mode at boot time
LX_ENABLE += FB

# mandatory fs support
LX_ENABLE += PROC_FS SYSFS

LX_DISABLE += CC_HAS_ASM_GOTO

# slim down kernel by removing superfluous drivers
LX_DISABLE += USB_HID VGA_CONSOLE DUMMY_CONSOLE NLS VGA_ARB DEBUG_LIST
