#ifndef CAM_CAP_DEF
#define CAM_CAP_DEF

#define CAM_APERTURES_MAX 1
#define CAM_FILTER_DENSITIES_MAX 1
#define SENSOR_PHYSICAL_SIZE_CNT 2
#define EXPOSURE_TIME_RANGE_CNT 2
#define MAX_SIZES_CNT 30
#define MAX_TEST_PATTERN_CNT 8
#define MAX_INFLIGHT_REQUESTS  6
#define MAX_REPROCESS_STALL 4

typedef enum {
    CAM_HAL_V1 = 1,
    CAM_HAL_V3 = 3
} cam_hal_version_t;

typedef enum {
    CAM_AF_LENS_STATE_STATIONARY,
    CAM_AF_LENS_STATE_MOVING,
} cam_af_lens_state_t;

typedef enum {
    CAM_FLASH_MODE_OFF,
    CAM_FLASH_MODE_AUTO,
    CAM_FLASH_MODE_ON,
    CAM_FLASH_MODE_TORCH,
    CAM_FLASH_MODE_SINGLE,
    CAM_FLASH_MODE_MAX
} cam_flash_mode_t;

typedef enum {
    CAM_FACE_DETECT_MODE_OFF,
    CAM_FACE_DETECT_MODE_SIMPLE,
    CAM_FACE_DETECT_MODE_FULL,
} cam_face_detect_mode_t;

typedef enum {
  CAM_CDS_MODE_OFF,
  CAM_CDS_MODE_ON,
  CAM_CDS_MODE_AUTO,
  CAM_CDS_MODE_MAX
} cam_cds_mode_type_t;

typedef enum {
    CAM_AWB_D50,
    CAM_AWB_D65,
    CAM_AWB_D75,
    CAM_AWB_A,
    CAM_AWB_CUSTOM_A,
    CAM_AWB_WARM_FLO,
    CAM_AWB_COLD_FLO,
    CAM_AWB_CUSTOM_FLO,
    CAM_AWB_NOON,
    CAM_AWB_CUSTOM_DAYLIGHT,
    CAM_AWB_INVALID_ALL_LIGHT,
} cam_illuminat_t;

typedef enum {
    CAM_SENSOR_RAW,
    CAM_SENSOR_YUV
} cam_sensor_t;

typedef enum {
    CAM_FORMAT_YUV_420_NV12,
    // maybe more
    CAM_FORMAT_MAX
} cam_format_t;

typedef struct {
    cam_sensor_t sens_type;
    cam_format_t native_format;
} cam_sensor_type_t;

typedef enum {
    CAM_POSITION_BACK,
    CAM_POSITION_FRONT
} cam_position_t;

typedef enum {
    CAM_OPT_STAB_OFF,
    CAM_OPT_STAB_ON,
    CAM_OPT_STAB_MAX
} cam_optical_stab_modes_t;

typedef struct {
    int32_t width;
    int32_t height;
} cam_dimension_t;

typedef struct {
    float min_fps;
    float max_fps;
    float video_min_fps;
    float video_max_fps;
} cam_fps_range_t;

typedef enum {
    CAM_EFFECT_MODE_OFF,
    CAM_EFFECT_MODE_MONO,
    CAM_EFFECT_MODE_NEGATIVE,
    CAM_EFFECT_MODE_SOLARIZE,
    CAM_EFFECT_MODE_SEPIA,
    CAM_EFFECT_MODE_POSTERIZE,
    CAM_EFFECT_MODE_WHITEBOARD,
    CAM_EFFECT_MODE_BLACKBOARD,
    CAM_EFFECT_MODE_AQUA,
    CAM_EFFECT_MODE_EMBOSS,
    CAM_EFFECT_MODE_SKETCH,
    CAM_EFFECT_MODE_NEON,
    CAM_EFFECT_MODE_MAX
} cam_effect_mode_type;

typedef enum {
    CAM_SCENE_MODE_OFF,
    CAM_SCENE_MODE_AUTO,
    CAM_SCENE_MODE_LANDSCAPE,
    CAM_SCENE_MODE_SNOW,
    CAM_SCENE_MODE_BEACH,
    CAM_SCENE_MODE_SUNSET,
    CAM_SCENE_MODE_NIGHT,
    CAM_SCENE_MODE_PORTRAIT,
    CAM_SCENE_MODE_BACKLIGHT,
    CAM_SCENE_MODE_SPORTS,
    CAM_SCENE_MODE_ANTISHAKE,
    CAM_SCENE_MODE_FLOWERS,
    CAM_SCENE_MODE_CANDLELIGHT,
    CAM_SCENE_MODE_FIREWORKS,
    CAM_SCENE_MODE_PARTY,
    CAM_SCENE_MODE_NIGHT_PORTRAIT,
    CAM_SCENE_MODE_THEATRE,
    CAM_SCENE_MODE_ACTION,
    CAM_SCENE_MODE_AR,
    CAM_SCENE_MODE_FACE_PRIORITY,
    CAM_SCENE_MODE_BARCODE,
    CAM_SCENE_MODE_HDR,
    CAM_SCENE_MODE_MAX
} cam_scene_mode_type;

typedef enum {
    CAM_AE_MODE_OFF,
    CAM_AE_MODE_ON,
    CAM_AE_MODE_MAX
} cam_ae_mode_type;

typedef struct {
    int32_t min_sensitivity;
    int32_t max_sensitivity;
} cam_sensitivity_range_t;

typedef enum {
    CAM_ANTIBANDING_MODE_OFF,
    CAM_ANTIBANDING_MODE_60HZ,
    CAM_ANTIBANDING_MODE_50HZ,
    CAM_ANTIBANDING_MODE_AUTO,
    CAM_ANTIBANDING_MODE_AUTO_50HZ,
    CAM_ANTIBANDING_MODE_AUTO_60HZ,
    CAM_ANTIBANDING_MODE_MAX,
} cam_antibanding_mode_type;

typedef enum {
    CAM_COLOR_CORRECTION_ABERRATION_OFF,
    CAM_COLOR_CORRECTION_ABERRATION_FAST,
    CAM_COLOR_CORRECTION_ABERRATION_HIGH_QUALITY,
    CAM_COLOR_CORRECTION_ABERRATION_MAX
} cam_aberration_mode_t;

typedef enum {
    CAM_FOCUS_MODE_OFF,
    CAM_FOCUS_MODE_AUTO,
    CAM_FOCUS_MODE_INFINITY,
    CAM_FOCUS_MODE_MACRO,
    CAM_FOCUS_MODE_FIXED,
    CAM_FOCUS_MODE_EDOF,
    CAM_FOCUS_MODE_CONTINOUS_VIDEO,
    CAM_FOCUS_MODE_CONTINOUS_PICTURE,
    CAM_FOCUS_MODE_MANUAL,
    CAM_FOCUS_MODE_MAX
} cam_focus_mode_type;

typedef enum {
    CAM_WB_MODE_AUTO,
    CAM_WB_MODE_CUSTOM,
    CAM_WB_MODE_INCANDESCENT,
    CAM_WB_MODE_FLUORESCENT,
    CAM_WB_MODE_WARM_FLUORESCENT,
    CAM_WB_MODE_DAYLIGHT,
    CAM_WB_MODE_CLOUDY_DAYLIGHT,
    CAM_WB_MODE_TWILIGHT,
    CAM_WB_MODE_SHADE,
    CAM_WB_MODE_MANUAL,
    CAM_WB_MODE_OFF,
    CAM_WB_MODE_MAX
} cam_wb_mode_type;

typedef enum {
    CAM_FLASH_FIRING_LEVEL_0,
    CAM_FLASH_FIRING_LEVEL_1,
    CAM_FLASH_FIRING_LEVEL_2,
    CAM_FLASH_FIRING_LEVEL_3,
    CAM_FLASH_FIRING_LEVEL_4,
    CAM_FLASH_FIRING_LEVEL_5,
    CAM_FLASH_FIRING_LEVEL_6,
    CAM_FLASH_FIRING_LEVEL_7,
    CAM_FLASH_FIRING_LEVEL_8,
    CAM_FLASH_FIRING_LEVEL_9,
    CAM_FLASH_FIRING_LEVEL_10,
    CAM_FLASH_FIRING_LEVEL_MAX
} cam_flash_firing_level_t;

typedef enum {
    CAM_FOCUS_UNCALIBRATED,
    CAM_FOCUS_APPROXIMATE,
    CAM_FOCUS_CALIBRATED
} cam_focus_calibration_t;

typedef enum {
    CAM_TEST_PATTERN_OFF,
    CAM_TEST_PATTERN_SOLID_COLOR,
    CAM_TEST_PATTERN_COLOR_BARS,
    CAM_TEST_PATTERN_COLOR_BARS_FADE_TO_GRAY,
    CAM_TEST_PATTERN_PN9,
} cam_test_pattern_mode_t;

typedef enum {
    CAM_FILTER_ARRANGEMENT_RGGB,
    CAM_FILTER_ARRANGEMENT_GRBG,
    CAM_FILTER_ARRANGEMENT_GBRG,
    CAM_FILTER_ARRANGEMENT_BGGR,
    CAM_FILTER_ARRANGEMENT_RGB,
    CAM_FILTER_ARRANGEMENT_UYVY,
    CAM_FILTER_ARRANGEMENT_YUYV,
} cam_color_filter_arrangement_t;

typedef struct {
    int32_t left;
    int32_t top;
    int32_t width;
    int32_t height;
} cam_rect_t;

typedef struct {
    int32_t numerator;
    int32_t denominator;
} cam_rational_type_t;

typedef enum {
    CAM_HFR_MODE_OFF,
    CAM_HFR_MODE_60FPS,
    CAM_HFR_MODE_90FPS,
    CAM_HFR_MODE_120FPS,
    CAM_HFR_MODE_150FPS,
    CAM_HFR_MODE_180FPS,
    CAM_HFR_MODE_210FPS,
    CAM_HFR_MODE_240FPS,
    CAM_HFR_MODE_480FPS,
    CAM_HFR_MODE_MAX,
} cam_hfr_mode_t;

typedef struct {
    cam_hfr_mode_t mode;
    cam_dimension_t dim;
} cam_hfr_info_t;

typedef struct {
    uint8_t ae_mode;
    uint8_t awb_mode;
    uint8_t af_mode;
} cam_scene_mode_overrides_t;

typedef struct {
    cam_hal_version_t version;
    uint8_t no_per_frame_control_support;
    cam_sensor_type_t sensor_type;
    cam_position_t position;

    float min_focus_distance;
    float hyper_focal_distance;
    float focal_length;

    float apertures[CAM_APERTURES_MAX];
    uint8_t apertures_count;

    float filter_densities[CAM_FILTER_DENSITIES_MAX];
    int filter_densities_count;

    uint8_t optical_stab_modes[CAM_OPT_STAB_MAX];
    uint8_t optical_stab_modes_count;

    cam_dimension_t lens_shading_map_size;
    float sensor_physical_size[SENSOR_PHYSICAL_SIZE_CNT];
    int64_t exposure_time_range[EXPOSURE_TIME_RANGE_CNT];

    int64_t max_frame_duration;
    cam_dimension_t pixel_array_size;

    cam_fps_range_t fps_ranges_tbl[MAX_SIZES_CNT];
    size_t fps_ranges_tbl_cnt;

    size_t picture_sizes_tbl_cnt;
    cam_dimension_t picture_sizes_tbl[MAX_SIZES_CNT];
    int64_t picture_min_duration[MAX_SIZES_CNT];

    uint8_t max_num_roi;
    int32_t exposure_compensation_min;
    int32_t exposure_compensation_max;

    size_t supported_effects_cnt;
    cam_effect_mode_type supported_effects[CAM_EFFECT_MODE_MAX];

    size_t supported_scene_modes_cnt;
    cam_scene_mode_type supported_scene_modes[CAM_SCENE_MODE_MAX];

    size_t supported_antibandings_cnt;
    cam_antibanding_mode_type supported_antibandings[CAM_ANTIBANDING_MODE_MAX];

    uint32_t aberration_modes_count;
    cam_aberration_mode_t aberration_modes[CAM_COLOR_CORRECTION_ABERRATION_MAX];

    size_t supported_focus_modes_cnt;
    cam_focus_mode_type supported_focus_modes[CAM_FOCUS_MODE_MAX];

    size_t supported_white_balances_cnt;
    cam_wb_mode_type supported_white_balances[CAM_WB_MODE_MAX];

    size_t supported_flash_firing_level_cnt;
    cam_flash_firing_level_t supported_firing_levels[CAM_FLASH_FIRING_LEVEL_MAX];

    uint8_t flash_available;

    size_t supported_ae_modes_cnt;
    cam_ae_mode_type supported_ae_modes[CAM_AE_MODE_MAX];

    cam_sensitivity_range_t sensitivity_range;
    int32_t max_analog_sensitivity;
    uint32_t sensor_mount_angle;

    uint8_t focus_dist_calibrated;

    uint8_t supported_test_pattern_modes_cnt;
    cam_test_pattern_mode_t supported_test_pattern_modes[MAX_TEST_PATTERN_CNT];

    size_t supported_raw_dim_cnt;
    cam_dimension_t raw_dim[MAX_SIZES_CNT];

    cam_color_filter_arrangement_t color_arrangement;
    cam_rect_t active_array_size;

    int32_t white_level;
    cam_rational_type_t exp_compensation_step;

    int32_t exposure_compensation_default;
    uint8_t max_downscale_factor;
    int64_t raw_min_duration[MAX_SIZES_CNT];
    size_t hfr_tbl_cnt;
    cam_hfr_info_t hfr_tbl[CAM_HFR_MODE_MAX];
    cam_scene_mode_overrides_t scene_mode_overrides[CAM_SCENE_MODE_MAX];

    int64_t jpeg_stall_durations[MAX_SIZES_CNT];
    int64_t raw16_stall_durations[MAX_SIZES_CNT];

} cam_capability_t_rtk;

#endif // CAM_CAP_DEF
