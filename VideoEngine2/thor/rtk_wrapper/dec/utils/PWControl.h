#ifndef __RTK_POWER_CONTROL_H_
#define __RTK_POWER_CONTROL_H_

typedef enum PW_DEVICE{
    PW_CPU,
    PW_GPU,
} PW_DEVICE;

#ifdef __cplusplus
class PWControl {
public:
    PWControl()                                 {};
    virtual ~PWControl(void)                    {};
    virtual void SetPerformance(bool enable)    {enable = false;};
    virtual void SetPerformanceWDT(void)        {};
};
#else
typedef struct PWControl PWControl;
#endif

#ifdef __cplusplus
extern "C" {
#endif

PWControl * PWControl_create            (PW_DEVICE device);
void        PWControl_destroy           (PWControl * instance);

void        PWControl_SetPerformance    (PWControl * instance, bool enable);
void        PWControl_SetPerformanceWDT (PWControl * instance);

#ifdef __cplusplus
}
#endif
#endif /* End of __RTK_POWER_CONTROL_H_ */
