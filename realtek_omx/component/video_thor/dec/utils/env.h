#ifndef __RTK_ENV_H__
#define __RTK_ENV_H__

#include <pthread.h>
#include "list.h"

/*
 * Format for default variable:
 * {FEATURE_NAME}={VALUE}
 *
 * Format for process specific variable:
 * {PROCESS_NAME}:{FEATURE_NAME}={VALUE}
 */

#define DEF_ENF_CONFIG_FILE "/vendor/etc/env.txt"

typedef struct ENV ENV;
typedef struct ENV_OPS ENV_OPS;

typedef enum {
    ENV_LOG_INFO,
    ENV_LOG_DEBUG,
    ENV_LOG_DUMP,
    ENV_LOG_ERROR,
} ENV_LOG_LEVEL;

struct ENV_OPS {
    void            (*destroy)              (ENV* env);
    const char *    (*get_prefix)           (ENV* env);
    size_t          (*get_env)              (ENV* env, const char * name, char * value, size_t value_len);
    int             (*set_env)              (ENV* env, const char * name, const char * value);
    const char *    (*get_config_filename)  (ENV* env);
    int             (*read_in_default)      (ENV* env, const char * process_name);
    int             (*print)                (ENV* env, ENV_LOG_LEVEL level, const char * str);
};

struct ENV {
    size_t              sizes_prefix;
    size_t              sizes_key_buffer;
    size_t              sizes_value_buffer;
    size_t              sizes_process_name;
    struct list         mList;
    pthread_mutex_t     mLock;
    ENV_OPS    ops;
};

void         env_init                   (ENV* env);
void         env_destroy                (ENV* env);
const char * env_get_prefix             (ENV* env);
size_t       env_get                    (ENV* env, const char * name, char * value, size_t value_len);
int          env_set                    (ENV* env, const char * name, const char * value);
const char * env_get_config_filename    (ENV* env);
int          env_read_in_default        (ENV* env, const char * process_name);
void         env_dump                   (ENV* env, const char * prefix);
int          env_print                  (ENV* env, ENV_LOG_LEVEL level, const char * fmt, ...);

#endif /* End of __RTK_ENV_H__ */
