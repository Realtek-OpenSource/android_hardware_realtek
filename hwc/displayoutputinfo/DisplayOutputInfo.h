#ifndef __RTK_HWC_DISPLAY_OUTPUT_INFO_
#define __RTK_HWC_DISPLAY_OUTPUT_INFO_
#include <display/DisplayInfo.h>

class DisplayOutputInfo {
public:
    class Client{
        public:
            Client() {};
            virtual ~Client() {};
            virtual void setDisplayOutputInfoService(DisplayOutputInfo *service) {
                    mService = service;
            }

            virtual void setDisplayOutputInfo(int display_output, int interface_type, int output_mode, int vic) {
                if(mService)
                    mService->setDisplayOutputInfo(display_output, interface_type, output_mode, vic);
            }

            virtual void getDisplayOutputInfo(int display_output, int *interface_type, int *output_mode, int *vic) {
                if(mService)
                    mService->getDisplayOutputInfo(display_output, interface_type, output_mode, vic);
            }

            virtual bool DPUpdate(void) {
                if(mService)
                    return mService->DPUpdate();
                return false;
            }

            virtual bool HDMIUpdate(void) {
                if(mService)
                    return mService->HDMIUpdate();
                return false;
            }

            virtual void DPUpdateClear(void) {
                if(mService)
                    return mService->DPUpdateClear();
            }

            virtual void HDMIUpdateClear(void) {
                if(mService)
                    return mService->HDMIUpdateClear();
            }
         private:
             DisplayOutputInfo *mService;
    };

    DisplayOutputInfo();
    virtual ~DisplayOutputInfo() {};
    void setDisplayOutputInfo(int display_output, int interface_type, int output_mode, int vic);
    void getDisplayOutputInfo(int display_output, int *interface_type, int *output_mode, int *vic);
    bool DPUpdate(void) { return dp_need_update;};
    bool HDMIUpdate(void) {return hdmi_need_update;};
    void DPUpdateClear(void) {dp_need_update = false;};
    void HDMIUpdateClear(void) {hdmi_need_update = false;}
private:
    int display_interface_type;
    int display_output_mode;
    int dp_vic;
    int hdmi_vic;
    bool dp_need_update;
    bool hdmi_need_update;
};

#endif /* End of __RTK_HWC_DISPLAY_OUTPUT_INFO_*/
