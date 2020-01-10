#ifndef RTK_FEATURE_H_
#define RTK_FEATURE_H_

#include "list.h"

typedef enum Features {
    FEATURE_VIDEO_FULLRANGE,
    FEATURE_HEVC_PERFORMANCE,
    FEATURE_IS_SURFACE_VIEW,
    FEATURE_OUTPUT_BE_DECODED,
    FEATURE_DELAY_DISPLAY_ORDER,
    FEATURE_REASONABLE_BUFFER_COUNT,
    FEATURE_COMBINED_BUFFER,
} Features;

typedef enum FeatureOpt {
    FEATURE_FALSE,
    FEATURE_TRUE,
    FEATURE_ENABLE      = FEATURE_TRUE,
    FEATURE_DISABLE     = FEATURE_FALSE,
} FeatureOpt;

typedef struct FeatureSet {
    pthread_mutex_t mLock;
    struct list     mList;
} FeatureSet;

typedef struct FeatureSlot {
    Features    feature;
    FeatureOpt  operate;
} FeatureSlot;

FeatureSet * createFeatureSetByComm (char * comm);
void         deleteFeatureSet       (FeatureSet * set);

int FeatureSet_set(FeatureSet * set, Features item, FeatureOpt opt);
int FeatureSet_get(FeatureSet * set, Features item, FeatureOpt default_opt);

#endif /* end of RTK_FEATURE_H_ */
