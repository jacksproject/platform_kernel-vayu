/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (C) 2018-2020 Oplus. All rights reserved.
 */

#ifndef __QCOM_PLATFORM_MSMNILE_H__
#define __QCOM_PLATFORM_MSMNILE_H__

#include "oplus_wakelock_profiler.h"

static struct wakeup_count_desc_t wc_powerkey_msmnile = {
	.module_name = "powerkey",
	.module_mask = WS_CNT_POWERKEY,
	.ws_number = 1,
	.ws_desc[0] = {
		.prop = IRQ_PROP_REAL,
		.name = IRQ_NAME_POWERKEY,
	},
};

static struct wakeup_count_desc_t wc_rtc_alarm_msmnile = {
	.module_name = "rtc_alarm",
	.module_mask = WS_CNT_ALARM,
	.ws_number = 1,
	.ws_desc[0] = {
		.prop = IRQ_PROP_REAL,
		.name = IRQ_NAME_ALARM,
	},
};

static struct wakeup_count_desc_t wc_modem_msmnile = {
	.module_name = "modem",
	.module_mask = WS_CNT_MODEM,
	.ws_number = 4,
	.ws_desc[0] = {
		.prop = IRQ_PROP_EXCHANGE,
		.name = IRQ_NAME_MODEM_QSI,
	},
	.ws_desc[1] = {
		.prop = IRQ_PROP_REAL,
		.name = IRQ_NAME_MODEM_GLINK,
	},
	.ws_desc[2] = {
		.prop = IRQ_PROP_REAL,
		.name = IRQ_NAME_MODEM_IPA,
	},
	.ws_desc[3] = {
		.prop = IRQ_PROP_EXCHANGE,
		.name = IRQ_NAME_MODEM_QMI,
	},
};

static struct wakeup_count_desc_t wc_wlan_msmnile = {
	.module_name = "wlan",
	.module_mask = WS_CNT_WLAN,
	.ws_number = 2,
	.ws_desc[0] = {
		.prop = IRQ_PROP_EXCHANGE,
		.name = IRQ_NAME_WLAN_MSI,
	},
	.ws_desc[1] = {
		.prop = IRQ_PROP_REAL,
		.name = IRQ_NAME_WLAN_IPCC_DATA,
	},
};

static struct wakeup_count_desc_t wc_adsp_msmnile = {
	.module_name = "adsp",
	.module_mask = WS_CNT_ADSP,
	.ws_number = 2,
	.ws_desc[0] = {
		.prop = IRQ_PROP_REAL,
		.name = IRQ_NAME_ADSP,
	},
	.ws_desc[1] = {
		.prop = IRQ_PROP_REAL,
		.name = IRQ_NAME_ADSP_GLINK,
	},
};

static struct wakeup_count_desc_t wc_cdsp_msmnile = {
	.module_name = "cdsp",
	.module_mask = WS_CNT_CDSP,
	.ws_number = 2,
	.ws_desc[0] = {
		.prop = IRQ_PROP_REAL,
		.name = IRQ_NAME_CDSP,
	},
	.ws_desc[1] = {
		.prop = IRQ_PROP_REAL,
		.name = IRQ_NAME_CDSP_GLINK,
	},
};

static struct wakeup_count_desc_t wc_slpi_msmnile = {
	.module_name = "slpi",
	.module_mask = WS_CNT_SLPI,
	.ws_number = 2,
	.ws_desc[0] = {
		.prop = IRQ_PROP_REAL,
		.name = IRQ_NAME_SLPI,
	},
	.ws_desc[1] = {
		.prop = IRQ_PROP_REAL,
		.name = IRQ_NAME_SLPI_GLINK,
	},
};


static struct wakeup_count_desc_t wc_glink_msmnile = {
	.module_name = "glink", /* all platform should be the same */
	.module_mask = WS_CNT_GLINK,
	.ws_number = 1,
	.ws_desc[0] = {
		.prop = IRQ_PROP_DUMMY_STATICS,
		.name = IRQ_NAME_GLINK,
	},
};

static struct wakeup_count_desc_t wc_abort_msmnile = {
	.module_name = "abort", /* all platform should be the same */
	.module_mask = WS_CNT_ABORT,
	.ws_number = 1,
	.ws_desc[0] = {
		.prop = IRQ_PROP_DUMMY_STATICS,
		.name = IRQ_NAME_ABORT,
	},
};

static struct wakeup_count_desc_t wc_sum_msmnile = {
	.module_name = "wakeup_sum", /* all platform should be the same */
	.module_mask = WS_CNT_SUM,
	.ws_number = 1,
	.ws_desc[0] = {
		.prop = IRQ_PROP_DUMMY_STATICS,
		.name = IRQ_NAME_WAKE_SUM,
	},
};

/*
 * Abstract each statistical item as a wake-up source
 * interrupt, including sum statistics and abort statistics.
 * The prop property of ws_desc_t determines the statistical
 * behavior of this "wake source interrupt".
 * Each wakeup_count_desc_t represents a statistical module.
 */
static struct wakeup_count_desc_t * const all_modules_msmnile[] = {
	&wc_powerkey_msmnile,
	&wc_rtc_alarm_msmnile,
	/*&wc_alarm_msmnile,*/
	&wc_modem_msmnile,
	&wc_wlan_msmnile,
	&wc_adsp_msmnile,
	&wc_cdsp_msmnile,
	&wc_slpi_msmnile,
	&wc_glink_msmnile,
	&wc_abort_msmnile,
	&wc_sum_msmnile,
	NULL,
};

/*
 * The upper layer requires report IPA_WS/QMI_WS,
 * so a conversion must be done.
 * [x][0] --> IPA_WS, [x][1] --> QMI_WS
 */
static const char* const modem_report_exchange_msmnile[][MODEM_REPORT_NUMBER] = {
	{IRQ_NAME_MODEM_IPA, IRQ_NAME_MODEM_QMI},
	{NULL, NULL},
};

#endif /*__QCOM_PLATFORM_MSMNILE_H__*/
