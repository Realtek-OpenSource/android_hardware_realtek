#ifndef TA_KEYSTORE_H
#define TA_KEYSTORE_H

#define TA_OPTEE_KEYSTORE_UUID {0x1f38c22e, 0xafc3,0x411c,\
        {0xbd,0x90,0x9c,0xa1,0x7a,0x32,0x3d, 0x04}}


#define TA_KEYSTORE_CMD_CONFIGURE		1
#define TA_KEYSTORE_CMD_ADD_RNG_ENTROPY 	2
#define TA_KEYSTORE_CMD_GENERATE_KEY 	        3
#define TA_KEYSTORE_CMD_GET_KEY_CHARACTERISTICS 4
#define TA_KEYSTORE_CMD_IMPORT_KEY		5
#define TA_KEYSTORE_CMD_EXPORT_KEY		6
#define TA_KEYSTORE_CMD_ATTEST_KEY		7
#define TA_KEYSTORE_CMD_UPGRADE_KEY		8

#define TA_KEYSTORE_CMD_BEGIN			9
#define TA_KEYSTORE_CMD_UPDATE			10
#define TA_KEYSTORE_CMD_FINISH			11
#define TA_KEYSTORE_CMD_ABORT			12

#define TEEC_OPERATION_INITIALIZER { 0 }

//#define DEBUG
#ifdef DEBUG
#define KM_DEBUG(fmt, args...) \
        do { ALOGI("%s():%d " fmt, __func__, __LINE__, ##args); } while (0)
void KM_DumpHex(const char* name,const uint8_t* vector, int length) {

        ALOGI("%s dump %u bytes\n",name,length);
        //    if(length > 256)
        //        length = 256;

        if (vector == NULL) {
                return;
        }
        // TODO(fredgc): replace with HEXEncode.
        for (int i = 0; i < length; i+=16) {
                ALOGI("[%04d/%04d] %02x%02x%02x%02x  %02x%02x%02x%02x  %02x%02x%02x%02x  %02x%02x%02x%02x", i, length,
                                vector[i+ 3], vector[i+ 2], vector[i+ 1], vector[i+ 0],
                                vector[i+ 7], vector[i+ 6], vector[i+ 5], vector[i+ 4],
                                vector[i+11], vector[i+10], vector[i+ 9], vector[i+ 8],
                                vector[i+15], vector[i+14], vector[i+13], vector[i+12]);
                /*vector[i+ 0], vector[i+ 1], vector[i+ 2], vector[i+ 3],
                  vector[i+ 4], vector[i+ 5], vector[i+ 6], vector[i+ 7],
                  vector[i+ 8], vector[i+ 9], vector[i+10], vector[i+11],
                  vector[i+12], vector[i+13], vector[i+14], vector[i+15]);*/
        }
        ALOGI("<============================================= \n");
}
#else
#define KM_DEBUG(fmt, ...)
void KM_DumpHex(const char* name __unused,const uint8_t* vector __unused, int length __unused) {};
#endif


#endif /*TA_KEYSTORE_H */
