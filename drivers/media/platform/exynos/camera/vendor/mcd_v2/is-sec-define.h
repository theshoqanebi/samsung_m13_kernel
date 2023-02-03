/*
 * Samsung Exynos5 SoC series IS driver
 *
 *
 * Copyright (c) 2011 Samsung Electronics Co., Ltd
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef IS_SEC_DEFINE_H
#define IS_SEC_DEFINE_H

#include <linux/module.h>
#include <linux/delay.h>
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/interrupt.h>
#include <linux/device.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <video/videonode.h>
#include <asm/cacheflush.h>
#include <asm/pgtable.h>
#include <linux/firmware.h>
#include <linux/dma-mapping.h>
#include <linux/scatterlist.h>
#include <linux/videodev2.h>
#include <linux/videodev2_exynos_camera.h>
#include <linux/v4l2-mediabus.h>
#include <linux/bug.h>
#include <linux/syscalls.h>
#include <linux/vmalloc.h>

#include <linux/gpio.h>
#include <linux/regulator/consumer.h>
#include <linux/zlib.h>

#include "is-core.h"
#include "is-cmd.h"
#include "is-err.h"
#include "is-video.h"

#include "is-device-sensor.h"
#include "is-device-ischain.h"
#include "crc32.h"
#include "is-dt.h"

#define FW_CORE_VER		0
#define FW_PIXEL_SIZE		1
#define FW_ISP_COMPANY		3
#define FW_SENSOR_MAKER		4
#define FW_PUB_YEAR		5
#define FW_PUB_MON		6
#define FW_PUB_NUM		7
#define FW_MODULE_COMPANY	9
#define FW_VERSION_INFO		10

#define FW_ISP_COMPANY_BROADCOMM	'B'
#define FW_ISP_COMPANY_TN		'C'
#define FW_ISP_COMPANY_FUJITSU		'F'
#define FW_ISP_COMPANY_INTEL		'I'
#define FW_ISP_COMPANY_LSI		'L'
#define FW_ISP_COMPANY_MARVELL		'M'
#define FW_ISP_COMPANY_QUALCOMM		'Q'
#define FW_ISP_COMPANY_RENESAS		'R'
#define FW_ISP_COMPANY_STE		'S'
#define FW_ISP_COMPANY_TI		'T'
#define FW_ISP_COMPANY_DMC		'D'
#define FW_ISP_COMPANY_LSI_STANDARD_CAL		'E'

#define FW_SENSOR_MAKER_SF		'F'
#define FW_SENSOR_MAKER_SLSI		'L'
#define FW_SENSOR_MAKER_SONY		'S'

#define FW_MODULE_COMPANY_SEMCO		'S'
#define FW_MODULE_COMPANY_GUMI		'O'
#define FW_MODULE_COMPANY_CAMSYS	'C'
#define FW_MODULE_COMPANY_PATRON	'P'
#define FW_MODULE_COMPANY_MCNEX		'M'
#define FW_MODULE_COMPANY_LITEON	'L'
#define FW_MODULE_COMPANY_VIETNAM	'V'
#define FW_MODULE_COMPANY_SHARP		'J'
#define FW_MODULE_COMPANY_NAMUGA	'N'
#define FW_MODULE_COMPANY_POWER_LOGIX	'A'
#define FW_MODULE_COMPANY_DI		'D'

#define FW_3M3_D			"D13LL"
#define FW_3M3			"E13LL"

#define FW_2P6_Q			"Q16LL" /*2P6 REAR*/
#define FW_3P8SP_P			"P16LL" /*3P8SP FRONT*/

#define FW_4H5YC_P			"P08LL" /*4H5YC FRONT*/
#define FW_4H5YC_Q			"Q08LL" /*4H5YC REAR*/

#define FW_IMX576			"B24LS" /*IMX576 REAR*/
#define FW_IMX576_C			"C24LS" /*IMX576 FRONT*/

#define FW_IMX582			"K48LS" /*IMX582 REAR*/
#define FW_IMX586			"K48LS" /*IMX586 REAR*/

#define FW_SR846			"B08LF" /*SR846 REAR*/
#define FW_SR846_P			"P08LF" /*SR846 FRONT*/

#define SDCARD_FW
/*#define IS_FW_SDCARD			"/data/media/0/is_fw.bin" */

#define IS_DDK				"is_lib.bin"
#define IS_RTA				"is_rta.bin"

#define IS_2P6_SETF			"setfile_2p6.bin"
#define IS_3M3_SETF			"setfile_3m3.bin"
#define IS_3L2_SETF			"setfile_3l2.bin"
#define IS_3L6_SETF			"setfile_3l6.bin"
#define IS_3P8SP_SETF			"setfile_3p8sp.bin"
#define IS_4H5YC_SETF			"setfile_4h5yc.bin"
#define IS_4HA_SETF			"setfile_4ha.bin"
#define IS_4HA_FRONT_SETF		"setfile_4ha_front.bin"
#define IS_5E3_SETF			"setfile_5e3.bin"
#define IS_5E9_SETF			"setfile_5e9.bin"
#define IS_2X5_SETF			"setfile_2x5.bin"
#define IS_GM2_SETF			"setfile_gm2.bin"
#define IS_GW1_SETF			"setfile_gw1.bin"
#define IS_JN1_SETF			"setfile_jn1.bin"

#define IS_IMX258_SETF			"setfile_imx258.bin"
#define IS_IMX576_SETF			"setfile_imx576.bin"
#define IS_IMX576_FRONT_SETF	"setfile_imx576_front.bin"
#define IS_IMX582_SETF			"setfile_imx582.bin"
#define IS_IMX586_SETF			"setfile_imx586.bin"
#define IS_IMX616_SETF			"setfile_imx616.bin"
#define IS_IMX686_SETF			"setfile_imx686.bin"
#define IS_IMX355_SETF			"setfile_imx355.bin"

#define IS_SR556_SETF			"setfile_sr556.bin"
#define IS_SR846_SETF			"setfile_sr846.bin"
#define IS_SR846_FRONT_SETF	"setfile_sr846_front.bin"

#define IS_GC5035_SETF			"setfile_gc5035.bin"
#define IS_GC5035_MACRO_SETF		"setfile_gc5035_macro.bin"
#define IS_HI1336_SETF			"setfile_hi1336.bin"
#define IS_HI556_SETF			"setfile_hi556.bin"
#define IS_GC02M1_SETF			"setfile_gc02m1.bin"
#define IS_GC02M1_MACRO_SETF		"setfile_gc02m1_macro.bin"
#define IS_SC201_SETF			"setfile_sc201.bin"
#define IS_GC08A3_SETF			"setfile_gc08a3.bin"

#define IS_CAL_SDCARD_FRONT		"/data/cal_data_front.bin"
#define IS_FW_FROM_SDCARD			"/data/media/0/CamFW_Main.bin"
#define IS_SETFILE_FROM_SDCARD		"/data/media/0/CamSetfile_Main.bin"
#define IS_COMPANION_FROM_SDCARD	"/data/media/0/CamFW_Companion.bin"
#define IS_KEY_FROM_SDCARD			"/data/media/0/1q2w3e4r.key"

#define IS_HEADER_VER_SIZE      11
#define IS_OEM_VER_SIZE         11
#define IS_AWB_VER_SIZE         11
#define IS_SHADING_VER_SIZE     11
#define IS_CAL_MAP_VER_SIZE     4
#define IS_PROJECT_NAME_SIZE    8
#define IS_ISP_SETFILE_VER_SIZE 6
#define IS_SENSOR_ID_SIZE       16
#define IS_CAL_DLL_VERSION_SIZE 4
#define IS_MODULE_ID_SIZE       10
#ifdef SAMSUNG_LIVE_OUTFOCUS
#define IS_DUAL_CAL_VER_SIZE    11
#endif
#ifdef ENABLE_REMOSAIC_CAPTURE
#define IS_SENSOR_CAL_DATA_VER_SIZE 11
#endif
#ifdef USE_AP_PDAF
#define IS_AP_PDAF_VER_SIZE     11
#endif
#ifdef USE_AE_CAL
#define IS_AE_CAL_VER_SIZE      11
#endif

#define IS_RESOLUTION_DATA_SIZE 54

/* #define CONFIG_RELOAD_CAL_DATA 1 */

struct is_rom_info {
	u32		oem_start_addr;
	u32		oem_end_addr;
	u32		awb_start_addr;
	u32		awb_end_addr;
	u32		shading_start_addr;
	u32		shading_end_addr;

	u32		header_section_crc_addr;
	u32		oem_section_crc_addr;
	u32		awb_section_crc_addr;
	u32		shading_section_crc_addr;

	u32		mtf_data_addr;
	u32		af_cal_pan;
	u32		af_cal_macro;

	char		header_ver[IS_HEADER_VER_SIZE + 1];
	char		oem_ver[IS_OEM_VER_SIZE + 1];
	char		awb_ver[IS_AWB_VER_SIZE + 1];
	char		shading_ver[IS_SHADING_VER_SIZE + 1];

	char		cal_map_ver[IS_CAL_MAP_VER_SIZE + 1];
	char		project_name[IS_PROJECT_NAME_SIZE + 1];
	u8		rom_module_id[IS_MODULE_ID_SIZE + 1];
	char		rom_sensor_id[IS_SENSOR_ID_SIZE + 1];

	bool		is_caldata_read;
	bool		is_check_cal_reload;

#ifdef SAMSUNG_LIVE_OUTFOCUS
	u32		dual_data_section_crc_addr;
	u32		dual_data_start_addr;
	u32		dual_data_end_addr;
	char		dual_data_ver[IS_DUAL_CAL_VER_SIZE + 1];
#endif

#ifdef ENABLE_REMOSAIC_CAPTURE
	u32		sensor_cal_data_section_crc_addr;
	u32		sensor_cal_data_start_addr;
	u32		sensor_cal_data_end_addr;
	char		sensor_cal_data_ver[IS_SENSOR_CAL_DATA_VER_SIZE + 1];
#endif

#ifdef USE_AP_PDAF
	u32		ap_pdaf_section_crc_addr;
	u32		ap_pdaf_start_addr;
	u32		ap_pdaf_end_addr;
	char		ap_pdaf_ver[IS_AP_PDAF_VER_SIZE + 1];
#endif

#ifdef USE_AE_CAL
	u32		ae_cal_section_crc_addr;
	u32		ae_cal_start_addr;
	u32		ae_cal_end_addr;
	char		ae_cal_ver[IS_AE_CAL_VER_SIZE+1];
#endif

	u32		standard_cal_section_crc_addr;
	u32		standard_cal_start_addr;
	u32		standard_cal_end_addr;

	unsigned long		fw_size;
	unsigned long		setfile_size;
	u8		sensor_version;

	char		load_fw_name[50]; 		/* DDK */
#ifdef USE_RTA_BINARY
	char		load_rta_fw_name[50]; 	/* RTA */
#endif
	char		load_setfile_name[50];

};

bool is_sec_get_force_caldata_dump(void);
int is_sec_set_force_caldata_dump(bool fcd);

int is_sec_get_max_cal_size(struct is_core *core, int position);
int is_sec_get_cal_buf(int position, char **buf);
int is_sec_get_cal_buf_rom_data(int position, char **buf);
int is_sec_get_sysfs_finfo_by_position(int position, struct is_rom_info **finfo);
int is_sec_get_sysfs_finfo(struct is_rom_info **finfo);
int is_sec_get_sysfs_finfo_front(struct is_rom_info **finfo);
int is_sec_get_sysfs_pinfo_by_position(int position, struct is_rom_info **pinfo);
int is_sec_get_sysfs_pinfo_rear(struct is_rom_info **pinfo);
int is_sec_get_sysfs_pinfo_front(struct is_rom_info **pinfo);
int is_sec_get_front_cal_buf(char **buf);

int is_sec_get_loaded_fw(char **buf);
int is_sec_set_loaded_fw(char *buf);

int is_sec_fw_revision(char *fw_ver);
bool is_sec_fw_module_compare(char *fw_ver1, char *fw_ver2);

int is_sec_get_camid(void);
int is_sec_set_camid(int id);
int is_sec_get_camid_from_hal(char *fw_name, char *setf_name);

int is_sec_fw_find(struct is_core *core, int position);
int is_sec_run_fw_sel(struct device *dev, int position);
int is_sec_run_fw_sel_from_rom(struct device *dev, int id, bool headerOnly);

u8 is_sec_compare_ver(int position);
bool is_sec_check_rom_ver(struct is_core *core, int position);

bool is_sec_check_fw_crc32(char *buf, u32 checksum_seed, unsigned long size);
bool is_sec_check_cal_crc32(char *buf, int id);
void is_sec_make_crc32_table(u32 *table, u32 id);
bool is_sec_check_awb_lsc_crc32_post_sec2lsi(char* buf, int position, int awb_length, int lsc_length);
bool is_sec_readcal_dump_post_sec2lsi(struct is_core *core, char *buf, int position);
#ifdef USES_STANDARD_CAL_RELOAD
bool is_sec_sec2lsi_check_cal_reload(void);
#endif

int is_sec_ldo_enable(struct device *dev, char *name, bool on);
int is_sec_rom_power_on(struct is_core *core, int position);
int is_sec_rom_power_off(struct is_core *core, int position);

int is_sec_get_pixel_size(char *header_ver);
int is_sec_core_voltage_select(struct device *dev, char *header_ver);
int is_get_dual_cal_buf(int slave_position, char **buf, int *size);
int is_get_remosaic_cal_buf(int slave_position, char **buf, int *size);
#ifdef JN1_MODIFY_REMOSAIC_CAL_ORDER
int is_get_jn1_remosaic_cal_buf(int slave_position, char **buf, int *size);
#endif

void remove_dump_fw_file(void);
#endif /* IS_SEC_DEFINE_H */
