#ifndef __RTK_HWC_PROPERTY_H_
#define __RTK_HWC_PROPERTY_H_
#include <hwc_utils.h>

#define HWC_PROPERTY_V1_X                           "vendor.hwc.v1.x"
#define HWC_PROPERTY_V1_Y                           "vendor.hwc.v1.y"
#define HWC_PROPERTY_V1_WIDTH                       "vendor.hwc.v1.width"
#define HWC_PROPERTY_V1_HEIGHT                      "vendor.hwc.v1.height"
#define HWC_PROPERTY_V1_RESET                       "vendor.hwc.v1.reset"
#define HWC_PROPERTY_V1_FREEZE                      "vendor.hwc.v1.freeze"
#define HWC_PROPERTY_V1_SCALE_BYPASS                "vendor.hwc.v1.scale.bypass"

#define HWC_PROPERTY_V2_X                           "vendor.hwc.v2.x"
#define HWC_PROPERTY_V2_Y                           "vendor.hwc.v2.y"
#define HWC_PROPERTY_V2_WIDTH                       "vendor.hwc.v2.width"
#define HWC_PROPERTY_V2_HEIGHT                      "vendor.hwc.v2.height"
#define HWC_PROPERTY_V2_RESET                       "vendor.hwc.v2.reset"
#define HWC_PROPERTY_V2_SCALE_BYPASS                "vendor.hwc.v2.scale.bypass"

#define HWC_PROPERTY_V1_FORCE_ENABLE                "vendor.hwc.v1.force.enable"
#define HWC_PROPERTY_V1_FORCE_FULLSCREEN            "vendor.hwc.v1.force.fullscreen"
#define HWC_PROPERTY_V1_FORCE_RESET                 "vendor.hwc.v1.force.reset"
#define HWC_PROPERTY_V1_FORCE_X                     "vendor.hwc.v1.force.x"
#define HWC_PROPERTY_V1_FORCE_Y                     "vendor.hwc.v1.force.y"
#define HWC_PROPERTY_V1_FORCE_WIDTH                 "vendor.hwc.v1.force.width"
#define HWC_PROPERTY_V1_FORCE_HEIGHT                "vendor.hwc.v1.force.height"

#define HWC_PROPERTY_V1_CROP_LEFT                   "vendor.hwc.v1.crop.left"
#define HWC_PROPERTY_V1_CROP_TOP                    "vendor.hwc.v1.crop.top"
#define HWC_PROPERTY_V1_CROP_RIGHT                  "vendor.hwc.v1.crop.right"
#define HWC_PROPERTY_V1_CROP_BOTTOM                 "vendor.hwc.v1.crop.bottom"

#define HWC_PROPERTY_V2_CROP_LEFT                   "vendor.hwc.v2.crop.left"
#define HWC_PROPERTY_V2_CROP_TOP                    "vendor.hwc.v2.crop.top"
#define HWC_PROPERTY_V2_CROP_RIGHT                  "vendor.hwc.v2.crop.right"
#define HWC_PROPERTY_V2_CROP_BOTTOM                 "vendor.hwc.v2.crop.bottom"

#define HWC_PROPERTY_V1_FLIP                        "vendor.hwc.support.v1.flip"
#define HWC_PROPERTY_V2_FLIP                        "vendor.hwc.support.v2.flip"
#define HWC_PROPERTY_V1_FLIP_BUFFER_CNT             "vendor.hwc.v1.flip.buffer"

#define HWC_PROPERTY_SECODE_DISPLAY                 "persist.vendor.rtk.hdmitx.dpdiffsource"
#define HWC_PROPERTY_DISABLE_VO_WRITEBACK           "vendor.hwc.disable.vo.writeback"

/* DP_PRIMARY default by SECODE_DISPLAY */
#define HWC_PROPERTY_DP_PRIMARY                     "persist.vendor.hwc.dp.primary"

#define HWC_PROPERTY_PLANE_V1                       0
#define HWC_PROPERTY_PLANE_V2                       1

#if 0 // unused
#define HWC_PROPERTY_SCALE_PLANE                    "vendor.hwc.scale.plane" /* 0:V1 1:V2 other:V1*/

#define HWC_PROPERTY_LINEAR_PLAVE_DEF               HWC_PROPERTY_PLANE_V1
#define HWC_PROPERTY_LINEAR_SETUP                   "persist.vendor.hwc.linear.setup"
#define HWC_PROPERTY_LINEAR_PLAVE                   "vendor.hwc.linear.plane" /* 0:V1 1:V2 other:V1 */

#define HWC_PROPERTY_LINEAR_PLAVE_EN                "vendor.hwc.linear.plane.en" /* 0:disable 1:enable */
#endif

#define HWC_PROPERTY_OSD_HIDE                       "vendor.hwc.osd.hide"
//#define HWC_PROPERTY_OSD_HIDE_DELAY                 "vendor.hwc.osd.hide.delay.ms"
#define HWC_PROPERTY_OSD_TOUT                       "vendor.hwc.osd.hide.ms"

#define HWC_PROPERTY_OSD_WIDTH                      "vendor.hwc.osd.w"
#define HWC_PROPERTY_OSD_HEIGHT                     "vendor.hwc.osd.h"

#define HWC_PROPERTY_SUSPEND_CTL                    "vendor.hwc.suspend.ctl"
#define HWC_PROPERTY_SUSPEND_DELAY_MS               "vendor.hwc.suspend.delay.ms"
#define HWC_PROPERTY_SUSPEND_WAIT_ENABLE            "vendor.hwc.suspend.wait.enable"
//#define HWC_PROPERTY_SUSPEND_WAIT_LOCK              "vendor.hwc.suspend.wait.lock"     /* 0: release state 1: suspend start 2: lock 3: unlock */
//#define HWC_PROPERTY_SUSPEND_BMP                    "vendor.hwc.suspend.bmp"
#define HWC_PROPERTY_SUSPEND_WATCHDOG_EN            "vendor.hwc.suspend.watchdog.en"
#define HWC_PROPERTY_SUSPEND_WATCHDOG_SEC           "vendor.hwc.suspend.watchdog.sec"

#define HWC_PROPERTY_VIDEO_MAX_ACQUIRED_COUNT       "persist.vendor.rtk.video.maxAcqCnt"

#define HWC_PROPERTY_CURSOR_SUPPORT                 "vendor.hwc.support.cursor"
#define HWC_PROPERTY_VIDEO_STANDARD                 "persist.vendor.display.standard"

#define HWC_PROPERTY_EXTERNAL_FORCE_WIDTH           "persist.vendor.hwc.ext.force.w"
#define HWC_PROPERTY_EXTERNAL_FORCE_HEIGHT          "persist.vendor.hwc.ext.force.h"

#define HWC_PROPERTY_PRO_PLAYBACK                   "persist.vendor.rtk.pro.playback"

class HWCProperty {
public:
    HWCProperty();
    virtual ~HWCProperty() {};

    bool        get_hwc_v1_force_enable(void);
    bool        get_hwc_v1_force_reset(void);
    bool        get_hwc_v1_force_fullscreen(void);
    void        clean_hwc_v1_force_enable(void);
    void        clean_hwc_v1_force_reset(void);
    void        clean_hwc_v1_force_fullscreen(void);
    hwc_rect_t  get_hwc_v1_force_rect(void);
    void        set_hwc_v1_force_rect(hwc_rect_t rect);
    void        clean_hwc_v1_force_rect(void);
    bool        get_hwc_v1_reset(void);
    void        clean_hwc_v1_reset(void);
    bool        get_hwc_v2_reset(void);
    void        clean_hwc_v2_reset(void);
    void        set_hwc_v1_frame(int x, int y, int w, int h);
    bool        get_hwc_v1_scale_bypass();
    void        set_hwc_v2_frame(int x, int y, int w, int h);
    bool        get_hwc_v2_scale_bypass();
    bool        get_hwc_v1_flip_support(void);
    void        init_hwc_v1_flip_support(void);
    int         get_hwc_v1_flip_buffer_count(void);
    void        init_hwc_v1_flip_buffer_count(void);
    int         get_hwc_v1_flip_freeze(void);
    void        clean_hwc_v1_flip_freeze(void);
    hwc_rect_t  get_hwc_v1_crop(void);
    void        clean_hwc_v1_crop(void);
    hwc_rect_t  get_hwc_v2_crop(void);
    void        clean_hwc_v2_crop(void);
    hwc_rect_t  get_hwc_osd_resolution();
    bool        get_hwc_osd_hide_enable();
    bool        get_hwc_osd_hide_continue();
    int         get_hwc_osd_hide_timeout_ms();
    void        set_hwc_osd_hide_timeout_ms(int timeoutMs);
    void        clear_hwc_osd_hide_enable();
    void        set_hwc_osd_hide_continue();
    bool        get_hwc_second_display_support(void);
    bool        get_hwc_dp_is_primary_display(void);
    void        disable_hwc_vo_writeback_support(bool enable);
    int         get_hwc_suspend_watchdog_sec(void);
    bool        get_hwc_suspend_watchdog_en(void);
    void        clean_hwc_suspend_watchdog_en(void);
    int         get_hwc_suspend_delay_ms(void);
    void        set_hwc_suspend_delay_ms(int delayMs);
    int         get_hwc_suspend_ctl(void);
    void        set_hwc_suspend_ctl(int ctl);
    bool        get_hwc_cursor_support(void);
    void        set_hwc_cursor_support(bool enable);
    int         get_hwc_video_max_acquired_count(void);
    int         get_hwc_video_standard(void);
    bool        get_hwc_v2_flip_support(void);
    void        init_hwc_v2_flip_support(void);
    hwc_rect_t  get_hwc_external_force_size(void);
    bool        get_hwc_pro_playback(void);
#if 0
    void        set_hwc_scale_plane(int plane);
    int         get_hwc_scale_plane(void);
    void        init_hwc_linear_plane(void);
    int         get_hwc_linear_plane(void);
    void        set_hwc_linear_plane_enable(bool enable);
    bool        get_hwc_linear_plane_enable(void);
#endif
};

#endif /* End of __RTK_HWC_PROPERTY_H_ */
