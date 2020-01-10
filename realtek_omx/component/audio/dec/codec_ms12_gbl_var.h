#ifndef CODEC_MS12_GBL_VAR_H
#define CODEC_MS12_GBL_VAR_H

void reset_omx_audio_global_info();
void set_dec_global_id(OMX_AUDIO_MS12_INPUT_PIN_TYPE inputPinType, int instanceID);
void set_global_thread_map(int inputPinMap);
void set_omx_audio_thread_inited(OMX_AUDIO_MS12_INPUT_PIN_TYPE inputPinType);
void set_omx_audio_thread_run(OMX_AUDIO_MS12_INPUT_PIN_TYPE inputPinType);
int delete_omx_audio_thread(OMX_AUDIO_MS12_INPUT_PIN_TYPE inputPinType);
int get_decoder_main_id();
int get_decoder_assoc_id();
int get_decoder_sys_id();
int get_decoder_app_id();
OMX_BOOL check_is_all_thread_inited();
OMX_BOOL check_is_all_thread_run();
void set_ddpdec_global_instance_id(int instanceID);
int get_ddpdec_global_instance_id();
void set_ms12pp_global_instance_id(int instanceID);
int get_ms12pp_global_instance_id();
OMX_BOOL is_ddpdec_created();
OMX_BOOL is_ms12pp_created();
OMX_BOOL check_if_create_dec(CODEC_RTK *this);
void set_omx_init_params_sent(OMX_BOOL IsSent);
OMX_BOOL is_omx_init_params_sent();
int get_omx_thread_inited_cnt();
int get_omx_thread_run_cnt();
void set_ddpdec_thread_map(OMX_AUDIO_MS12_INPUT_PIN_TYPE inputPinType);
void set_dec_thread_map(OMX_AUDIO_MS12_INPUT_PIN_TYPE inputPinType);
OMX_BOOL check_is_last_thread();
OMX_BOOL check_if_should_destroy_ms12pp();
OMX_BOOL check_if_should_destroy_decoder();
void delete_ddpdec_from_global_map(OMX_AUDIO_MS12_INPUT_PIN_TYPE inputPinType);
void delete_ms12pp_from_global_map(OMX_AUDIO_MS12_INPUT_PIN_TYPE inputPinType);
void delete_dec_from_global_map(OMX_AUDIO_MS12_INPUT_PIN_TYPE inputPinType);
OMX_BOOL check_is_ready_to_destroy_all_thread();
void set_ready_to_destroy_all_thread(OMX_BOOL isTrue);
OMX_BOOL check_if_pin_exist(OMX_AUDIO_MS12_INPUT_PIN_TYPE inputPinType);
void set_omx_audio_dec_destroy(OMX_AUDIO_MS12_INPUT_PIN_TYPE inputPinType);
OMX_BOOL check_is_mutex_inited();
void set_omx_mutex_inited();
void set_ms12pp_thread_map(OMX_AUDIO_MS12_INPUT_PIN_TYPE inputPinType);



#endif