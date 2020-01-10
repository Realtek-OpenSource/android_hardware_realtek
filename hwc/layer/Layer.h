#ifndef __RTK_HWC_LAYER_H
#define __RTK_HWC_LAYER_H

#if 1
//use hwc_layer_1_t temporary
#include <hardware/hwcomposer.h>
#endif

#define HWC2_INCLUDE_STRINGIFICATION
#define HWC2_USE_CPP11
#include <hardware/hwcomposer2.h>
#undef HWC2_INCLUDE_STRINGIFICATION
#undef HWC2_USE_CPP11

#include <queue>

class Layer {
public:
    explicit Layer(hwc2_display_t display_id);
    ~Layer();

    uint32_t getZ() const;
    hwc2_layer_t getId() const;
    hwc_layer_1_t* getHwcLayer1();

    void updateDeviceCompositionType(HWC2::Composition type) { mDeviceSelect = type; }
    void updateClientCompositionType(HWC2::Composition type) { mClientRequest = type; }
    HWC2::Composition getClientCompositionType() { return mClientRequest; }
    HWC2::Composition getDeviceCompositionType() { return mDeviceSelect; }

    //HWC2 APIs
    HWC2::Error setCursorPosition(int32_t x, int32_t y);
    HWC2::Error setLayerBuffer(buffer_handle_t buffer, int32_t acquire_fence);
    HWC2::Error setLayerSurfaceDamage(hwc_region_t damage);
    HWC2::Error setLayerBlendMode(HWC2::BlendMode mode);
    HWC2::Error setLayerColor(hwc_color_t color);
    HWC2::Error setLayerCompositionType(HWC2::Composition type);
    HWC2::Error setLayerDataspace(int32_t dataspace);
    HWC2::Error setLayerDisplayFrame(hwc_rect_t frame);
    HWC2::Error setLayerPlaneAlpha(float alpha);
    HWC2::Error setLayerSidebandStream(const native_handle_t* stream);
    HWC2::Error setLayerSourceCrop(hwc_frect_t crop);
    HWC2::Error setLayerTransform(HWC2::Transform transform);
    HWC2::Error setLayerVisibleRegion(hwc_region_t visible);
    HWC2::Error setLayerZOrder(uint32_t z);
    HWC2::Error setLayerFloatColor(hwc_float_color_t color);

    void pushReleaseFence(int32_t fence);
    int32_t popReleaseFence(void);
private:
    hwc2_layer_t mId;
    //hwc2_display_t mDisplayId;
    hwc_layer_1_t* mHwcLayer;
    uint32_t mZ;
    std::queue<int32_t> mReleaseFences;

    HWC2::Composition mClientRequest = HWC2::Composition::Client;
    HWC2::Composition mDeviceSelect = HWC2::Composition::Client; // todo: force gpu composition

    static std::atomic<hwc2_layer_t> next_id_;
    native_handle_t* mSidebandStream;
};

struct SortLayersByZ {
    bool operator()(const Layer *lhs, const Layer *rhs) {
        return lhs->getZ() < rhs->getZ();
    }
};
#endif
