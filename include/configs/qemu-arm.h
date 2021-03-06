/*
 * Copyright (c) 2017 Tuomas Tynkkynen
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __CONFIG_H
#define __CONFIG_H

#include <linux/sizes.h>

/* Physical memory map */
#define CONFIG_SYS_TEXT_BASE		0x00000000

#define CONFIG_NR_DRAM_BANKS		1
#define CONFIG_SYS_SDRAM_BASE		0x40000000

/* The DTB generated by QEMU is placed at start of RAM, stay away from there */
#define CONFIG_SYS_INIT_SP_ADDR         (CONFIG_SYS_SDRAM_BASE + SZ_2M)
#define CONFIG_SYS_LOAD_ADDR		(CONFIG_SYS_SDRAM_BASE + SZ_2M)
#define CONFIG_SYS_MALLOC_LEN		SZ_16M

/* QEMU's PL011 serial port is detected via FDT using the device model */
#define CONFIG_PL01X_SERIAL

/* QEMU implements a 62.5MHz architected timer */
/* FIXME: can we rely on CNTFREQ instead of hardcoding this fact here? */
#define CONFIG_SYS_ARCH_TIMER
#define CONFIG_SYS_HZ                       1000
#define CONFIG_SYS_HZ_CLOCK                 62500000

/* For block devices, QEMU emulates an ICH9 AHCI controller over PCI */
#define CONFIG_SYS_SCSI_MAX_SCSI_ID 6
#define CONFIG_SCSI_AHCI
#define CONFIG_LIBATA

/* Environment options */
#define CONFIG_ENV_SIZE				SZ_64K

#include <config_distro_defaults.h>

#define BOOT_TARGET_DEVICES(func) \
	func(SCSI, scsi, 0)

#include <config_distro_bootcmd.h>

#define CONFIG_CMD_BOOTMENU
#define CONFIG_AUTOBOOT_KEYED
#define CONFIG_MENU_SHOW

#define CONFIG_PREBOOT "pci enum"
#define CONFIG_EXTRA_ENV_SETTINGS \
	"fdt_high=0xffffffff\0" \
	"initrd_high=0xffffffff\0" \
	"fdt_addr=0x40000000\0" \
	"scriptaddr=0x40200000\0" \
	"pxefile_addr_r=0x40300000\0" \
	"kernel_addr_r=0x40400000\0" \
	"ramdisk_addr_r=0x44000000\0" \
	"bootmenu_0=Attached kernel=run attachboot\0" \
	"bootmenu_1=Internal eMMC=run emmcboot\0" \
	"bootmenu_2=External SD card=run sdboot\0" \
	"bootmenu_3=U-Boot boot order=boot\0" \
	"bootmenu_delay=30\0" \
	BOOTENV
#endif /* __CONFIG_H */
