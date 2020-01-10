#ifndef __RTK_HWC_DISPLAY_H_
#define __RTK_HWC_DISPLAY_H_

#include <map>
#include <set>
#include <hwc_utils.h>
#include <volayer/VOLayerBase.h>
#include <vsync/Vsync.h>
#include <callbacks/Callbacks.h>
#include <arbiter/ResourceArbiter.h>
#include <power/Power.h>
#include "DisplayInfo.h"
#include <vowindow/VOWindowBase.h>
#include <property/HWCProperty.h>
#include <vowindow/VOMixerServer.h>
#include <layer/Layer.h>
#include "hdmi_common.h"
#include "rtk_hal.h"
#include <rtk_dptx.h>
#include <HDMILib.h>
#ifdef HAS_DPTX
#include <DPTxLib.h>
#endif
#include <displayoutputinfo/DisplayOutputInfo.h>
#define MAX_SIDEBANDLAYER 2

class VOWindowBase;
class Layer;
using namespace realtek;

typedef struct _TV_SYSTEM_INFO {
    HDMI_VIC_ENUM   mVic;
    int32_t         mWidth;
    int32_t         mHeight;
    int32_t         mFps;
    bool            mProgressive;
} TV_SYSTEM_INFO;

class Display : public DisplayInfo,
    virtual public Vsync::Client,
    virtual public Power::Client,
    virtual public HWCProperty,
    virtual public DisplayOutputInfo::Client,
    public hdmilib_module_callback_2_t
#ifdef HAS_DPTX
    , public dptxlib_module_callback_t
#endif
{
public:
    enum TargetPlane {
        FLIP_V1,
        FLIP_V2,
        FLIP_V3,
        FLIP_NULL,
    };

    Display(Vsync * vsync, HWCCallbacks * callbacks, unsigned int display_type = HWC_DISPLAY_PRIMARY);
    virtual ~Display();

    virtual void    setResourceArbiter(ResourceArbiter * service);
    virtual void    setPower(Power * service);
    virtual void    setVOMixer(VOMixerServer * service);

    virtual void    dump            (android::String8& buf, const char* prefix);

    //HWC2 APIs
    virtual HWC2::Error acceptDisplayChanges();
    virtual HWC2::Error createLayer(hwc2_layer_t* out_layer_id);
    virtual HWC2::Error destroyLayer(hwc2_layer_t layer_id);
    virtual HWC2::Error getActiveConfig(hwc2_config_t *out_config);
    virtual HWC2::Error getChangedCompositionTypes(uint32_t* outNumElements, hwc2_layer_t* outLayers, int32_t* outTypes);
    virtual HWC2::Error getClientTargetSupport(uint32_t width, uint32_t height, int32_t format, int32_t dataspace);
    virtual HWC2::Error getColorModes(uint32_t* outNumModes, int32_t* outModes);
    virtual HWC2::Error getDisplayAttributes(hwc2_config_t config, HWC2::Attribute attributes, int32_t* outValue);
    virtual HWC2::Error getDisplayConfigs(hwc2_config_t* numConfigs, uint32_t* configs);
    virtual HWC2::Error getDisplayName(uint32_t *out_size, char *out_name);
    virtual HWC2::Error getDisplayRequests(int32_t* outDisplayRequests, uint32_t* outNumElements, hwc2_layer_t* outLayers, int32_t* outLayerRequests);
    virtual HWC2::Error getDisplayTypes(int32_t *out_type);
    virtual HWC2::Error getReleaseFences(uint32_t* outNumElements, hwc2_layer_t* outLayers, int32_t* outFences);
    virtual HWC2::Error presentDisplay(int32_t* outRetireFence);
    virtual HWC2::Error setActiveConfig(hwc2_config_t config);
    virtual HWC2::Error setClientTarget(buffer_handle_t target, int32_t acquireFence, int32_t dataspace, hwc_region_t damage);
    virtual HWC2::Error setColorMode(android_color_mode_t mode);
    virtual HWC2::Error setColorTransform(const float * /*matrix*/, int32_t /*hint*/) {
        //return HWC2::Error::Unsupported;
        return HWC2::Error::None;
    }
    virtual HWC2::Error setPowerMode(HWC2::PowerMode mode);
    virtual HWC2::Error setVsyncEnabled(HWC2::Vsync enabled);
    virtual HWC2::Error validateDisplay(uint32_t* outNumTypes, uint32_t* outNumRequests);
    virtual HWC2::Error setOutputBuffer(buffer_handle_t buffer, int releaseFence);
    virtual void    prepareSidebandLayer();
    /* VsyncListener */
    virtual void    VsyncEvent(void);

    Layer *getLayer(hwc2_layer_t layer);
    virtual void    initVolayer();
    virtual void setLayerList(android::Vector<VOLayerBase*> layerList) {mLayerList = layerList;};
    virtual void setDisplayWindow(VOWindowBase * displayWindow) {mDisplayWindow = displayWindow;};
    static void HDMIHandleEvent(const struct hdmilib_module_callback_2 *callback, int32_t event, int32_t vic, int32_t mode, int32_t interface_type);
#ifdef HAS_DPTX
    static void DPTxHandleEvent(const struct dptxlib_module_callback *callback, int32_t event, int32_t vic, int32_t mode);
#endif
    void InitTVSystem(void);
    void processTvSystemByVsync(void);
    void unInitTvSystem(void);

private:
    void getVideoStandard(void);
    void forceSendDisplayEvent(void);
    void windowTask(void); // in vsync event loop.

    Vsync *                 mVsync;
    HWCCallbacks *          mCallbacks;
    bool                    mVsyncEnable;
    int                     mPowerMode;
    int                     mBlank;
    bool                    mOnlyVOLayer;
    VOWindowBase *          mDisplayWindow; //framebuffer target
    int64_t                 mDisplayHideTimestampUs;
    android_color_mode_t    mActiveColorMode;
    Layer*                  mClientTarget; // Also known as framebuffer target
    pthread_mutex_t         mLayerLock;
    pthread_mutex_t         mLayerSetLock;

    android::Vector<VOLayerBase*> mLayerList;
    const native_handle_t *SidebandInUseMap[MAX_SIDEBANDLAYER];
    android::Vector<const native_handle_t *>SidebandMap;
    bool LayerInUse[MAX_SIDEBANDLAYER];

    std::map<hwc2_layer_t, Layer *> mLayerMap;
    //std::multiset<Layer *, SortLayersByZ> mLayerSet;
    std::set<Layer *> mLayerSet;
    std::map<hwc2_layer_t, HWC2::Composition> mLayerChanges;
    std::map<hwc2_layer_t, HWC2::LayerRequest> mLayerRequests;

    int                    mFBLayerIndex;
    buffer_handle_t        mOutputBuffer;
    int                    mPrevFence;
    bool mValidated = false;
//    struct hdmi_support_list hdmi_list;
//    struct dptx_support_list dptx_list;
    int hdmitx;
    int dptx;
    int mTVMode;
    int mForceTVMode;
    int mPrevForceTVMode;
    HDMILib *mHDMILib;
#ifdef HAS_DPTX
    DPTxLib *mDPTxLib;
#endif
    bool HDMIService_start;
#ifdef HAS_DPTX
    bool DPTxService_start;
#endif
};

#endif /* End of __RTK_HWC_DISPLAY_H_ */
