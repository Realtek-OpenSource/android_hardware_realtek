#ifndef __RTK_BANDWIDTH_CONTROL_H_
#define __RTK_BANDWIDTH_CONTROL_H_

#include <hardware/power.h>

typedef enum BW_DEVICE{
    BW_GPU,
} BW_DEVICE;

#ifdef __cplusplus
class BWControl {
public:
    BWControl()                     {};
    virtual ~BWControl(void)        {};
    virtual void LowPriority(void)  {};
    virtual void HighPriority(void) {};
};
#else
typedef struct BWControl BWControl;
#endif

#ifdef __cplusplus
extern "C" {
#endif

BWControl * BWControl_create        (BW_DEVICE device);
void        BWControl_destroy       (BWControl * instance);

void        BWControl_LowPriority   (BWControl * instance);
void        BWControl_HighPriority  (BWControl * instance);

#ifdef __cplusplus
}
#endif
#endif /* End of __RTK_BANDWIDTH_CONTROL_H_ */
