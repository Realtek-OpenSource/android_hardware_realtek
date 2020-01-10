#ifndef __BOOT_CONTROL_H__
#define __BOOT_CONTROL_H__



#include <stdint.h>
#include <bootloader.h> //inner include bootloader message.h

/* struct boot_ctrl occupies the slot_suffix field of
 * struct bootloader_message_ab */
#define OFFSETOF_SLOT_SUFFIX offsetof(struct bootloader_message_ab, slot_suffix)

#define BOOTCTRL_MAGIC 0x42424100   //BAA\0
#define BOOTCTRL_SUFFIX_A           "_a"
#define BOOTCTRL_SUFFIX_B           "_b"
#define BOOT_CONTROL_VERSION    1



typedef struct slot_metadata_rtk{

	uint8_t priority:4;
	uint8_t tries_remaining:3;
	uint8_t successful_boot:1;
}slot_metadata_rtk_t;


typedef struct boot_ctrl{

	//usually "\0ABB"
	uint32_t magic;  

	//no use now
	uint8_t version;

	//definition above
	slot_metadata_rtk_t slot_info[2];

	//no use now
	uint8_t recovery_tries_remaining;

}boot_ctrl_t;






#endif 




























