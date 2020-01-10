#ifndef _WIFI_MOD_MAPPER_H
#define _WIFI_MOD_MAPPER_H
#ifdef __cplusplus
extern "C" {
#endif
int init_wifi_mod_mapper();
int get_insmod_names(char** result);
void uninit_wifi_mod_mapper();
#define MAX_WIFI 20
#define MAX_LEN  20
#ifdef __cplusplus
}
#endif
#endif //_WIFI_MOD_MAPPER_H