/*
 * Driver interaction with Linux nl80211/cfg80211
 * Copyright (c) 2002-2014, Jouni Malinen <j@w1.fi>
 * Copyright (c) 2003-2004, Instant802 Networks, Inc.
 * Copyright (c) 2005-2006, Devicescape Software, Inc.
 * Copyright (c) 2007, Johannes Berg <johannes@sipsolutions.net>
 * Copyright (c) 2009-2010, Atheros Communications
 *
 * This software may be distributed under the terms of the BSD license.
 * See README for more details.
 */

#ifndef _DRIVER_NL80211_H_
#define _DRIVER_NL80211_H_

#include "includes.h"
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <net/if.h>
#include <netlink/genl/genl.h>
#include <netlink/genl/family.h>
#include <netlink/genl/ctrl.h>
#ifdef CONFIG_LIBNL3_ROUTE
#include <netlink/route/neighbour.h>
#endif /* CONFIG_LIBNL3_ROUTE */
#include <linux/rtnetlink.h>
#include <netpacket/packet.h>
#include <linux/filter.h>
#include <linux/errqueue.h>
#include "nl80211_copy.h"

#include "common.h"
#include "eloop.h"
#include "utils/list.h"
#include "common/qca-vendor.h"
#include "common/qca-vendor-attr.h"
#include "common/ieee802_11_defs.h"
#include "common/ieee802_11_common.h"
#include "l2_packet/l2_packet.h"
#include "netlink.h"
#include "linux_ioctl.h"
#include "radiotap.h"
#include "radiotap_iter.h"
#include "rfkill.h"
#include "driver.h"

#ifdef CONFIG_LIBNL20
/* libnl 2.0 compatibility code */
#define nl_handle nl_sock
#define nl80211_handle_alloc nl_socket_alloc_cb
#define nl80211_handle_destroy nl_socket_free
#endif /* CONFIG_LIBNL20 */

#ifndef IFF_LOWER_UP
#define IFF_LOWER_UP   0x10000         /* driver signals L1 up         */
#endif
#ifndef IFF_DORMANT
#define IFF_DORMANT    0x20000         /* driver signals dormant       */
#endif

#ifndef IF_OPER_DORMANT
#define IF_OPER_DORMANT 5
#endif
#ifndef IF_OPER_UP
#define IF_OPER_UP 6
#endif

struct nl80211_global {
	void *ctx;
	struct dl_list interfaces;
	int if_add_ifindex;
	u64 if_add_wdevid;
	int if_add_wdevid_set;
	struct netlink_data *netlink;
	struct nl_cb *nl_cb;
	struct nl_handle *nl;
	int nl80211_id;
	int ioctl_sock; /* socket for ioctl() use */

	struct nl_handle *nl_event;
};

struct nl80211_wiphy_data {
	struct dl_list list;
	struct dl_list bsss;
	struct dl_list drvs;

	struct nl_handle *nl_beacons;
	struct nl_cb *nl_cb;

	int wiphy_idx;
};

struct i802_bss {
	struct wpa_driver_nl80211_data *drv;
	struct i802_bss *next;
	int ifindex;
	int br_ifindex;
	u64 wdev_id;
	char ifname[IFNAMSIZ + 1];
	char brname[IFNAMSIZ];
	unsigned int beacon_set:1;
	unsigned int added_if_into_bridge:1;
	unsigned int added_bridge:1;
	unsigned int in_deinit:1;
	unsigned int wdev_id_set:1;
	unsigned int added_if:1;
	unsigned int static_ap:1;

	u8 addr[ETH_ALEN];

	int freq;
	int bandwidth;
	int if_dynamic;

	void *ctx;
	struct nl_handle *nl_preq, *nl_mgmt;
	struct nl_cb *nl_cb;

	struct nl80211_wiphy_data *wiphy_data;
	struct dl_list wiphy_list;
};

struct wpa_driver_nl80211_data {
	struct nl80211_global *global;
	struct dl_list list;
	struct dl_list wiphy_list;
	char phyname[32];
	unsigned int wiphy_idx;
	u8 perm_addr[ETH_ALEN];
	void *ctx;
	int ifindex;
	int if_removed;
	int if_disabled;
	int ignore_if_down_event;
	struct rfkill_data *rfkill;
	struct wpa_driver_capa capa;
	u8 *extended_capa, *extended_capa_mask;
	unsigned int extended_capa_len;
	int has_capability;

	int operstate;

	int scan_complete_events;
	enum scan_states {
		NO_SCAN, SCAN_REQUESTED, SCAN_STARTED, SCAN_COMPLETED,
		SCAN_ABORTED, SCHED_SCAN_STARTED, SCHED_SCAN_STOPPED,
		SCHED_SCAN_RESULTS
	} scan_state;

	//struct nl_cb *nl_cb;

	u8 auth_bssid[ETH_ALEN];
	u8 auth_attempt_bssid[ETH_ALEN];
	u8 bssid[ETH_ALEN];
	u8 prev_bssid[ETH_ALEN];
	int associated;
	u8 ssid[32];
	size_t ssid_len;
	enum nl80211_iftype nlmode;
	enum nl80211_iftype ap_scan_as_station;
	unsigned int assoc_freq;

	int monitor_sock;
	int monitor_ifidx;
	int monitor_refcount;

	unsigned int disabled_11b_rates:1;
	unsigned int pending_remain_on_chan:1;
	unsigned int in_interface_list:1;
	unsigned int device_ap_sme:1;
	unsigned int poll_command_supported:1;
	unsigned int data_tx_status:1;
	unsigned int scan_for_auth:1;
	unsigned int retry_auth:1;
	unsigned int use_monitor:1;
	unsigned int ignore_next_local_disconnect:1;
	unsigned int ignore_next_local_deauth:1;
	//unsigned int allow_p2p_device:1;
	unsigned int hostapd:1;
	unsigned int start_mode_ap:1;
	unsigned int start_iface_up:1;
	unsigned int test_use_roc_tx:1;
	unsigned int ignore_deauth_event:1;
	unsigned int vendor_cmd_test_avail:1;
	unsigned int roaming_vendor_cmd_avail:1;
	unsigned int dfs_vendor_cmd_avail:1;
	unsigned int have_low_prio_scan:1;
	unsigned int force_connect_cmd:1;
	unsigned int addr_changed:1;
	unsigned int get_features_vendor_cmd_avail:1;
	unsigned int set_rekey_offload:1;
	unsigned int p2p_go_ctwindow_supported:1;
	unsigned int setband_vendor_cmd_avail:1;
	unsigned int get_pref_freq_list:1;
	unsigned int set_prob_oper_freq:1;
	unsigned int scan_vendor_cmd_avail:1;
	unsigned int connect_reassoc:1;

	u64 vendor_scan_cookie;
	u64 remain_on_chan_cookie;
	u64 send_action_cookie;
#define MAX_SEND_ACTION_COOKIES 20
	u64 send_action_cookies[MAX_SEND_ACTION_COOKIES];
	unsigned int num_send_action_cookies;

	unsigned int last_mgmt_freq;

	struct wpa_driver_scan_filter *filter_ssids;
	size_t num_filter_ssids;

	struct i802_bss *first_bss;

	int eapol_tx_sock;

	int eapol_sock; /* socket for EAPOL frames */

	struct nl_handle *rtnl_sk; /* nl_sock for NETLINK_ROUTE */

	int default_if_indices[16];
	/* the AP/AP_VLAN iface that is in this bridge */
	int default_if_indices_reason[16];
	int *if_indices;
	int *if_indices_reason;
	int num_if_indices;

	/* From failed authentication command */
	int auth_freq;
	u8 auth_bssid_[ETH_ALEN];
	u8 auth_ssid[32];
	size_t auth_ssid_len;
	int auth_alg;
	u8 *auth_ie;
	size_t auth_ie_len;
	u8 auth_wep_key[4][16];
	size_t auth_wep_key_len[4];
	int auth_wep_tx_keyidx;
	int auth_local_state_change;
	int auth_p2p;

	/*
	 * Tells whether the last scan issued from wpa_supplicant was a normal
	 * scan (NL80211_CMD_TRIGGER_SCAN) or a vendor scan
	 * (NL80211_CMD_VENDOR). 0 if no pending scan request.
	 */
	int last_scan_cmd;
};

#endif
