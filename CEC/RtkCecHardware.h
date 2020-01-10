/*
 * Copyright (C) 2008 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ANDROID_RTK_CEC_HARDWARE_H
#define ANDROID_RTK_CEC_HARDWARE_H

#include <hardware/hardware.h>
#include <utils/Log.h>

#include <stdint.h>
#include <sys/cdefs.h>
#include <sys/types.h>
#include <utils/threads.h>
#include <hardware/hdmi_cec.h>
#include <sysutils/NetlinkEvent.h>
#include <hardware_legacy/uevent.h>
#include "hdmi_common.h"


// Copy from device/realtek/frameworks/services/jni/CEC/CECAPBridgeImplPriv.h
//-----------------------------------------------
// Device Information
//-----------------------------------------------

#define CEC_FILE1        "/dev/cec-0"
#define CEC_FILE2        "/dev/cec-1"
#define HDMI_RX_PATH        "/sys/devices/virtual/switch/rx_video/state"
#define HDMI_TX_PATH        "/sys/devices/virtual/switch/hdmi/state"

#define LOG_FUNCTION_NAME           ALOGV("\033[0;32m%s: %d() ENTER\033[m", __FUNCTION__, __LINE__);

#define DEC_RET(x)      ((x<0) ? CEC_CTRL_FAIL : CEC_CTRL_OK)
#define MAX_PATH_LENGTH  128
#define MAX_OSD_LENGTH  32
#define MAX_SYSFS_DATA   128

#define PHY_ENABLE          0x00
#define PHY_LOGICAL_ADDR    0x01
#define PHY_PHYSICAL_ADDR   0x02
#define PHY_POWER_STATUS    0x03
#define PHY_STANDBY_MODE    0x04
#define PHY_RX_MASK         0x05
#define PHY_CEC_VERSION     0x07
#define PHY_DEVICE_VENDOR_ID  0x08

// Standby Flags
#define BIT(x)                      (1UL << x)
#define CEC_STANBY_RESPONSE_GIVE_POWER_STATUS       BIT(0)
#define CEC_STANBY_RESPONSE_POOLING                 BIT(1)
#define CEC_STANBY_RESPONSE_GIVE_PHYSICAL_ADDR      BIT(2)
#define CEC_STANBY_RESPONSE_GET_CEC_VERISON         BIT(3)
#define CEC_STANBY_RESPONSE_GIVE_DEVICE_VENDOR_ID   BIT(4)
#define CEC_STANBY_WAKEUP_BY_ROUTING_INFO           BIT(26)
#define CEC_STANBY_WAKEUP_BY_ROUTING_CHANGE         BIT(27)
#define CEC_STANBY_WAKEUP_BY_REQUEST_AUDIO_SYSTEM   BIT(28)
#define CEC_STANBY_WAKEUP_BY_USER_CONTROL           BIT(29)
#define CEC_STANBY_WAKEUP_BY_IMAGE_VIEW_ON          BIT(30)
#define CEC_STANBY_WAKEUP_BY_SET_STREAM_PATH        BIT(31)

typedef enum 
{    
    //One Touch Play	    
    CEC_IMAGE_VIEW_ON                   = 0x04,	 
    CEC_TEXT_VIEW_ON                    = 0x0D,	
	                                    
    //Routing Control	                
    CEC_ACTIVE_SOURCE                   = 0x82, 
    CEC_INACTIVE_SOURCE                 = 0x9D, // <HDMI 1.3a>
    CEC_REQUEST_ACTIVE_SOURCE           = 0x85,	
    CEC_SET_STREAM_PATH                 = 0x86,	
    CEC_ROUTING_CHANGE                  = 0x80,	
    CEC_ROUTING_INFORMATION             = 0x81,
	                                    
    //System Standby	                
    CEC_STANDBY                         = 0x36, 
	                                    
    //One Touch Record	                
    CEC_RECORD_ON                       = 0x09,	
    CEC_RECORD_OFF                      = 0x0B,	
    CEC_RECORD_STATUS                   = 0x0A,	
    CEC_RECORD_TV_SCREEN                = 0x0F,	
	                                    
	//Timer Programming	                
	CEC_CLEAR_ANALOGUE_TIMER            = 0x33, // <HDMI 1.3a>
    CEC_CLEAR_DIGITAL_TIMER             = 0x99, // <HDMI 1.3a>
    CEC_CLEAR_EXTERNAL_TIMER            = 0xA1, // <HDMI 1.3a>   
    CEC_SET_ANALOGUE_TIMER              = 0x34, // <HDMI 1.3a>
    CEC_SET_DIGITAL_TIMER               = 0x97, // <HDMI 1.3a>
    CEC_SET_EXTERNAL_TIMER              = 0xA2, // <HDMI 1.3a>
    CEC_SET_TIMER_PROGRAM_TITLE         = 0x67, // <HDMI 1.3a>
    CEC_TIMER_CLEARED_STATUS            = 0x43, // <HDMI 1.3a>
    CEC_TIMER_STATUS                    = 0x35, // <HDMI 1.3a> 
	                                    
    //System Information	            
    CEC_CEC_VERSION                     = 0x9E, // <HDMI 1.3a>     
	CEC_GET_CEC_VERSION                 = 0x9F, // <HDMI 1.3a>
	CEC_GET_MENU_LANGUAGE               = 0x91, 
	CEC_SET_MENU_LANGUAGE               = 0x32,
	CEC_GIVE_PHYSICAL_ADDRESS           = 0x83,
	CEC_REPORT_PHYSICAL_ADDRESS         = 0x84,    
	                                    
    //Deck Control	                    
    CEC_GIVE_DECK_STATUS                = 0x1A,	
    CEC_DECK_STATUS                     = 0x1B,	
    CEC_DECK_CONTROL                    = 0x42,	
    CEC_PLAY                            = 0x41,	
	                                    
    //Tuner Control	                    
    CEC_GIVE_TUNER_DEVICE_STATUS        = 0x08,	
    CEC_TUNER_DEVICE_STATUS             = 0x07,	
    CEC_SELECT_ANALOGUE_SERVICE         = 0x92,	// <HDMI 1.3a>
    CEC_SELECT_DIGITAL_SERVICE          = 0x93,	
    CEC_TUNER_STEP_DECREMENT            = 0x06,	
    CEC_TUNER_STEP_INCREMENT             = 0x05,	
	                                    
    //Vendor Specific Command	        
	CEC_DEVICE_VENDOR_ID                = 0x87,
	CEC_GIVE_DEVICE_VENDOR_ID           = 0x8C,
	CEC_VENDOR_COMMAND                  = 0x89,
	CEC_VENDOR_COMMAND_WITH_ID          = 0xA0,	// <HDMI 1.3a>
	CEC_VENDOR_REMOTE_BUTTON_DOWN       = 0x8A,
	CEC_VENDOR_REMOTE_BUTTON_UP         = 0x8B,
	                                    
    //OSD Status Display	            
    CEC_SET_OSD_STRING                  = 0x64,
	                                    
    //OSD Status Display	            
    CEC_GIVE_OSD_NAME                   = 0x46,	
    CEC_SET_OSD_NAME                    = 0x47,
	                                    
    //Device Menu Control	            
    CEC_MENU_REQUEST                    = 0x8D,	
    CEC_MENU_STATUS                     = 0x8E,	
	                                    
    //Remote Control Pass Through	    
    CEC_USER_CONTROL_PRESSED            = 0x44,
    CEC_USER_CONTROL_RELEASED           = 0x45,
	                                    
    //Power Status Feature	            
    CEC_GIVE_DEVICE_POWER_STATUS        = 0x8F,
    CEC_REPORT_POWER_STATUS             = 0x90,
	                                    
    //General  Protocol 	            
    CEC_FEATURE_ABORT                   = 0x00,
    CEC_ABORT                           = 0xFF,
                                        
    //System Audio Control              
    CEC_GIVE_AUDIO_STATUS               = 0x71, // <HDMI 1.3a>
    CEC_GIVE_SYSTEM_AUDIO_MODE_STATUS   = 0x7D, // <HDMI 1.3a>   
    CEC_REPORT_AUDIO_STATUS             = 0x7A, // <HDMI 1.3a>
    CEC_SET_SYSTEM_AUDIO_MODE           = 0x72, // <HDMI 1.3a>
    CEC_SYSTEM_AUDIO_MODE_REQUEST       = 0x70, // <HDMI 1.3a>
    CEC_SYSTEM_AUDIO_MODE_STATUS        = 0x7E, // <HDMI 1.3a>
                                                             
    // Audio Rate Control                                    
    CEC_SET_AUDIO_RATE                  = 0x9A, // <HDMI 1.3a>
    
    // Audio Return channel
    CEC_INITIATE_ARC                    = 0xC0, // <HDMI 1.4>
    CEC_REPORT_ARC_INITIATED            = 0xC1, // <HDMI 1.4>
    CEC_REPORT_ARC_TERMINATED           = 0xC2, // <HDMI 1.4>
    CEC_REQUEST_ARC_INITIATION          = 0xC3, // <HDMI 1.4>
    CEC_REQUEST_ARC_TERMINATION         = 0xC4, // <HDMI 1.4>
    CEC_TERMINATE_ARC                   = 0xC5, // <HDMI 1.4>
    
    // Capability Discovery and Control 
    CEC_CDC_MESSAGE                     = 0xF8, // <HDMI 1.4>

}CEC_MSG_OPCODE;

/* Copy from /device/realtek/proprietary/libs/Include/Platform_Lib/CECControl/CEC_Def.h */
typedef enum {
    CEC_VERSION_1_1                         = 0x00,
    CEC_VERSION_1_2                         = 0x01,
    CEC_VERSION_1_2A                        = 0x02,
    CEC_VERSION_1_3                         = 0x03,
    CEC_VERSION_1_3A                        = 0x04,
    CEC_VERSION_1_4                         = 0x05,
    CEC_VERSION_UNKNOWN                     = 0xFF,
}CEC_VERSION;

#define CEC_VERSION_CODE     CEC_VERSION_1_4

namespace android {

enum {
    CEC_ENABLE,
    CEC_SET_LOGICAL_ADDRESS,
    CEC_SET_POWER_STATUS,
    CEC_SEND_MESSAGE,
    CEC_RCV_MESSAGE,
    CEC_SET_PHYSICAL_ADDRESS,
    CEC_SET_STANDBY_MODE,
    CEC_SET_RX_MASK,
    CEC_SET_CEC_VERSION,
    CEC_SET_DEVICE_VENDOR_ID,
    CEC_SET_RETRY_NUM,
    CEC_GET_PHYSICAL_ADDRESS,
    CEC_RCV_EXIT,
};


typedef struct {
    unsigned char*      buf;
    unsigned char       len;
}MARS_CEC_MSG;


const int NUM_HDMI_PORTS = 2;
/** State information for each device instance */
struct cec_callback_t {
    // Function in HDMI service to call back on CEC messages
    event_callback_t callback_func;
    // This stores the object to pass back to the framework
    void* callback_arg;
};

enum {
    LOGICAL_ADDRESS_SET   =  1,
    LOGICAL_ADDRESS_UNSET = -1,
};

class RtkCECHardware;
typedef struct cec_context {
    hdmi_cec_device_t device;    // Device for HW module
    cec_callback_t callback;     // Struct storing callback object
    bool enabled;
    bool arc_enabled;
    //int fb_num;                  // Framebuffer node for HDMI
    char hdmi_sysfs_path[NUM_HDMI_PORTS][MAX_PATH_LENGTH];    // Index 0: RX, Index 1:Tx 
    hdmi_port_info *port_info;   // HDMI port info

    // Logical address is stored in an array, the index of the array is the
    // logical address and the value in the index shows whether it is set or not
    int logical_address[CEC_ADDR_BROADCAST];
    RtkCECHardware *hw;
} cec_context_t;


class RtkCECHardware {
public:
    RtkCECHardware(int Dev, int DevType, unsigned int VendorID, const char* OSDName);
    virtual void handleHdmiSwitchEvent(NetlinkEvent *evt);
    //virtual void handleHdmiSwitchEvent(/*NetlinkEvent *evt*/);
    virtual status_t cecEnable(bool option, unsigned long StandbyMode);
    virtual status_t ControllerEnable(bool option, unsigned long StandbyMode);
    virtual status_t ServiceEnable(bool option);
    virtual void register_event_callback(event_callback_t callback, void* arg);
    virtual int send_message(const cec_message_t* pMsg);
    virtual int add_logical_address(cec_logical_address_t addr);
    virtual ~RtkCECHardware();
    int SetHW(unsigned char opcode, unsigned long val);
    unsigned long getStandbyMode(){ return mStandbyMode; }
    unsigned int getCECPhysicalAddress();
protected:
    
private:
    void Init();
    void UnInit();
    const char* GetMessageName(unsigned char Opcode);
    class CECReceiveThread : public Thread {
        RtkCECHardware * mHardware;
    public:
        CECReceiveThread(RtkCECHardware* hw)
            : Thread(false), mHardware(hw){ }
        virtual void onFirstRef() {
            run("RtkCECReceiveThread", PRIORITY_DISPLAY);
        }
        virtual bool threadLoop() {
            mHardware->cecRecevieThread();
            // loop until we need to quit
            return true;
        }
    };

    static void *pthread_entry(void *ptr);
    pthread_t   mUeventThread;
    sp<CECReceiveThread> mCecReThread;
    int cecRecevieThread();
    bool mCecReStopped;
    int mHDMIState[NUM_HDMI_PORTS];
    bool mHDMIStateChange[NUM_HDMI_PORTS];
    //int mLogicalAddress;
    int mFD;
    int mDev;
    int mDevType;
    unsigned int mLogAddr;
    unsigned int mPhyAddr;
    unsigned int mVendorID;
    char mOSDName[MAX_OSD_LENGTH];
    char mCECDevPath[NUM_HDMI_PORTS][MAX_PATH_LENGTH];    // Index 0: RX, Index 1:Tx 

    /* For Call back function */
    mutable Mutex mLock;
    event_callback_t mNotifyFn;
    void* mUser;
    unsigned long mStandbyMode;
    struct sink_capabilities_t mSink_cap;
};

}; // namespace android

#endif  // ANDROID_RTK_CEC_HARDWARE_H

