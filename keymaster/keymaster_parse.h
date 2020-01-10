//#include <utee_defines.h>

#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include <assert.h>

//#include <hardware/hardware.h>
#include <hardware/keymaster_defs.h>
#include <hardware/keymaster2.h>

#include <hardware/keymaster_common.h>

#define LOG_TAG "RTKOpteeKeyMaster"

#include <log/log.h>
#include "ta_keymaster.h"



/* OP-TEE TEE client API (built by optee_client) */
#include <tee_client_api.h>

/* Round up the even multiple of size, size has to be a multiple of 2 */
#define ROUNDUP(v, size) (((v) + (size - 1)) & ~(size - 1))


#define PARAM_KEYMASTER_VALUE 0x00000001
#define PARAM_KEYMASTER_BLOB 	0x00000002
#define PARAM_KEYMASTER_KEYPAREM 0x00000003
#define PARAM_KEYMASTER_KEYPAREMSET 0x00000004
#define PARAM_KEYMASTER_KEYCHARACTERISTICS 0x00000005
#define PARAM_KEYMASTER_KEYBLOB 0x00000006
#define PARAM_KEYMASTER_CERTCHAIN 0x00000007
#define PARAM_KEYMASTER_BLOB_SIG	0x00000008
#define PARAM_KEYMASTER_BLOB_CLIENTID	0x00000009
#define PARAM_KEYMASTER_BLOB_APPDATA	0x0000000a



typedef struct {
        uint32_t attributeID;
        union {
                struct {
                        void *buffer;
                        uint32_t length;
                } ref;
                struct {
                        uint32_t a, b;
                } value;
        } content;
} KEYSTORE_PARAM_SET;

struct param_packed {
        uint32_t attr_id;
        uint32_t a;
        uint32_t b;
};

struct key_param_packed {
        uint32_t tag;
        uint64_t a;
        uint32_t b;
};


void keystore_add_param(size_t *attr_count, KEYSTORE_PARAM_SET *attrs, uint32_t attr_id,
                const void *buf, size_t len)
{
        attrs[*attr_count].attributeID = attr_id;
        attrs[*attr_count].content.ref.buffer = (void *)buf;
        attrs[*attr_count].content.ref.length = len;
        (*attr_count)++;
}

void keystore_add_param_value(size_t *attr_count, KEYSTORE_PARAM_SET *attrs,
                uint32_t attr_id, uint32_t value_a, uint32_t value_b)
{
        attrs[*attr_count].attributeID = attr_id;
        attrs[*attr_count].content.value.a = value_a;
        attrs[*attr_count].content.value.b = value_b;
        (*attr_count)++;
}




bool pack_attrs(const KEYSTORE_PARAM_SET *attrs, uint32_t attr_count,
                uint8_t **buf, size_t *blen)
{
        struct param_packed *a = NULL;
        uint8_t *b = NULL;
        size_t bl = 0;
        size_t n = 0;

        *buf = NULL;
        *blen = 0;
        if (attr_count == 0)
                return true;

        bl = sizeof(uint32_t) + sizeof(struct param_packed) * attr_count;
        for (n = 0; n < attr_count; n++) {
                if ((attrs[n].attributeID & PARAM_KEYMASTER_VALUE) != 0)
                        continue; /* Only memrefs need to be updated */

                if (!attrs[n].content.ref.buffer)
                        continue;

                /* Make room for padding */
                bl += ROUNDUP(attrs[n].content.ref.length, 4);
        }

        b = (uint8_t *)calloc(1, bl);
        if (!b)
                return false;

        *buf = b;
        *blen = bl;

        *(uint32_t *)(void *)b = attr_count;
        b += sizeof(uint32_t);
        a = (struct param_packed *)(void *)b;
        b += sizeof(struct param_packed) * attr_count;

        for (n = 0; n < attr_count; n++) {
                a[n].attr_id = attrs[n].attributeID;
                if (attrs[n].attributeID & PARAM_KEYMASTER_VALUE) {
                        a[n].a = attrs[n].content.value.a;
                        a[n].b = attrs[n].content.value.b;
                        continue;
                }

                a[n].b = attrs[n].content.ref.length;

                if (!attrs[n].content.ref.buffer) {
                        a[n].a = 0;
                        continue;
                }

                memcpy(b, attrs[n].content.ref.buffer,
                                attrs[n].content.ref.length);

                /* Make buffer pointer relative to *buf */
                a[n].a = (uint32_t)(uintptr_t)(b - *buf);

                /* Round up to good alignment */
                b += ROUNDUP(attrs[n].content.ref.length, 4);
        }

        return true;
}

bool unpack_attrs(const uint8_t *buf, size_t blen,
                KEYSTORE_PARAM_SET **attrs, uint32_t *attr_count)
{
        bool res = true;
        KEYSTORE_PARAM_SET *a = NULL;
        const struct param_packed *ap;
        size_t num_attrs = 0;
        const size_t num_attrs_size = sizeof(uint32_t);

        if (blen == 0)
                goto out;

        if (((uintptr_t)buf & 0x3) != 0 || blen < num_attrs_size)
                return false;

        num_attrs = *(uint32_t *) (void *)buf;
        if ((blen - num_attrs_size) < (num_attrs * sizeof(*ap)))
                return false;
        ap = (const struct param_packed *)(const void *)(buf + num_attrs_size);

        if (num_attrs > 0) {
                size_t n;

                a = (KEYSTORE_PARAM_SET *)calloc(1, num_attrs * sizeof(KEYSTORE_PARAM_SET));
                if (!a)
                        return false;
                for (n = 0; n < num_attrs; n++) {
                        uintptr_t p;

                        a[n].attributeID = ap[n].attr_id;
                        if (ap[n].attr_id & PARAM_KEYMASTER_VALUE) {
                                a[n].content.value.a = ap[n].a;
                                a[n].content.value.b = ap[n].b;
                                continue;
                        }

                        a[n].content.ref.length = ap[n].b;
                        p = (uintptr_t)ap[n].a;
                        if (p) {
                                if ((p + a[n].content.ref.length) > blen) {
                                        res = false;
                                        goto out;
                                }
                                p += (uintptr_t)buf;
                        }
                        a[n].content.ref.buffer = (void *)p;
                }
        }

        res = true;
out:
        if (res == true) {
                *attrs = a;
                *attr_count = num_attrs;
        } else {
                free(a);
        }
        return res;
}


bool pack_keyparam_set(const keymaster_key_param_set_t *keyparam, uint8_t **buf, size_t *blen)
{
        struct key_param_packed *a = NULL;
        uint8_t *b = NULL;
        size_t bl = 0;
        size_t n = 0, keyparamCnt = 0;

        *buf = NULL;
        *blen = 0;
        keyparamCnt = keyparam->length;
        if (keyparamCnt == 0)
                return true;

        bl = sizeof(uint32_t) + sizeof(key_param_packed) * keyparamCnt;
        for (n = 0; n < keyparamCnt; n++) {
                keymaster_tag_type_t type = keymaster_tag_get_type(keyparam->params[n].tag);
                if (!(type == KM_BIGNUM || type == KM_BYTES))
                        continue; /* Only memrefs need to be updated */

                if (!keyparam->params[n].blob.data_length)
                        continue;

                /* Make room for padding */
                bl += ROUNDUP(keyparam->params[n].blob.data_length, 4);
        }

        b = (uint8_t *)calloc(1, bl);
        if (!b)
                return false;

        *buf = b;
        *blen = bl;

        *(uint32_t *)(void *)b = keyparamCnt;
        b += sizeof(uint32_t);
        a = (key_param_packed *)(void *)b;
        b += sizeof(key_param_packed) * keyparamCnt;

        for (n = 0; n < keyparamCnt; n++) {
                a[n].tag = keyparam->params[n].tag;

                keymaster_tag_type_t type = keymaster_tag_get_type(keyparam->params[n].tag);
                switch(type){
                        case KM_ENUM:
                        case KM_ENUM_REP:
                                a[n].a = keyparam->params[n].enumerated;
                                break;
                        case KM_BOOL:
                                a[n].a = keyparam->params[n].boolean;
                                break;
                        case KM_UINT:
                        case KM_UINT_REP:
                                a[n].a = keyparam->params[n].integer;
                                break;
                        case KM_ULONG:
                                a[n].a = keyparam->params[n].long_integer;
                                break;
                        case KM_DATE:
                                a[n].a = keyparam->params[n].date_time;
                                break;
                        default:
                                break;

                }

                if (!(type == KM_BIGNUM || type == KM_BYTES)){
                        a[n].b = 0;
                        continue;
                }


                a[n].b = keyparam ->params[n].blob.data_length;

                if (!keyparam ->params[n].blob.data) {
                        a[n].a = 0;
                        continue;
                }

                memcpy(b, keyparam ->params[n].blob.data, keyparam ->params[n].blob.data_length);

                /* Make buffer pointer relative to *buf */
                a[n].a = (uint32_t)(uintptr_t)(b - *buf);

                /* Round up to good alignment */
                b += ROUNDUP(keyparam ->params[n].blob.data_length, 4);
        }

        return true;
}

bool unpack_keyparam_set(const uint8_t *buf, size_t blen,
                keymaster_key_param_set_t **keyparam)
{
        bool res = true;
        keymaster_key_param_set_t *a = NULL;
        struct key_param_packed *ap;
        size_t num_attrs = 0;
        const size_t num_attrs_size = sizeof(uint32_t);
        uint8_t *pblob = NULL;
        if (blen == 0)
                goto out;

        if (((uintptr_t)buf & 0x3) != 0 || blen < num_attrs_size)
                return false;
        num_attrs = *(uint32_t *) (void *)buf;
        if ((blen - num_attrs_size) < (num_attrs * sizeof(*ap)))
                return false;
        ap = (struct key_param_packed *)(const void *)(buf + num_attrs_size);

        if (num_attrs > 0) {
                size_t n;

                a =(keymaster_key_param_set_t *) calloc(1,sizeof(keymaster_key_param_set_t));
                if (!a)
                        return false;
                a->params = (keymaster_key_param_t*)calloc(1,num_attrs * sizeof(keymaster_key_param_t));
                if(!(a->params))
                        return false;

                for (n = 0; n < num_attrs; n++) {
                        uintptr_t p;

                        a->params[n].tag = (keymaster_tag_t)ap[n].tag;
                        keymaster_tag_type_t type = keymaster_tag_get_type(a->params[n].tag);
                        switch(type){
                                case KM_ENUM:
                                case KM_ENUM_REP:
                                        a->params[n].enumerated = (uint32_t)ap[n].a;
                                        break;
                                case KM_BOOL:
                                        a->params[n].boolean = (bool)ap[n].a;
                                        break;
                                case KM_UINT:
                                case KM_UINT_REP:
                                        a->params[n].integer = (uint32_t)ap[n].a;
                                        break;
                                case KM_ULONG:
                                        a->params[n].long_integer = ap[n].a;
                                        break;
                                case KM_DATE:
                                        a->params[n].date_time = ap[n].a;
                                        break;
                                default:
                                        break;

                        }

                        if (!(type == KM_BIGNUM || type == KM_BYTES)){
                                continue;
                        }

                        /*a->params[n].blob.data_length = ap[n].b;
                          p = (uintptr_t)ap[n].a;
                          if (p) {
                          if ((p + a->params[n].blob.data_length) > blen) {
                          res = false;
                          free(a);
                          goto out;
                          }
                          p += (uintptr_t)buf;
                          }
                          a->params[n].blob.data = (const uint8_t*)p;*/

                        a->params[n].blob.data_length = ap[n].b;
                        p = (uintptr_t)ap[n].a;
                        if (p) {
                                if ((p + a->params[n].blob.data_length) > blen) {
                                        res = false;
                                        free(a);
                                        goto out;
                                }
                                p += (uintptr_t)buf;
                        }

                        pblob = (uint8_t *)malloc(ap[n].b);
                        memcpy(pblob, (void *)p, ap[n].b);
                        a->params[n].blob.data= pblob;
                }

        }
        res = true;
out:
        if (res == true) {
                *keyparam = a;
                (**keyparam).length = num_attrs;
        } else {
                //free(a);
        }
        return res;
}


void CopyToParamSet(keymaster_key_param_set_t* set, keymaster_key_param_set_t *src){

        set->length = src->length;
        set->params =
                reinterpret_cast<keymaster_key_param_t*>(malloc(sizeof(keymaster_key_param_t) * (set->length)));

        for (size_t i = 0; i < set->length; i++) {
                memcpy(set->params+i, src->params+i, sizeof(keymaster_key_param_t));

                keymaster_tag_type_t type = keymaster_tag_get_type(src->params[i].tag);
                //KM_DEBUG("%s get type:%x \n ",__func__, set->params[i].tag);
                if (type == KM_UINT) {
                        KM_DEBUG("%s KM_UINT type:%x, data: %d\n ", __func__, set->params[i].tag, set->params[i].integer);
                }
                if (type == KM_BIGNUM || type == KM_BYTES) {
                        void* tmp = malloc(src->params[i].blob.data_length);
                        memcpy(tmp, src->params[i].blob.data, src->params[i].blob.data_length);
                        set->params[i].blob.data = reinterpret_cast<uint8_t*>(tmp);
                }
        }
}


int find(keymaster_key_param_set_t key_params,	keymaster_tag_t tag, int begin = -1)
{

        int i = ++begin;
        while (i < (int)key_params.length && key_params.params[i].tag != tag)
                ++i;
        if (i == (int)key_params.length)
                return -1;
        else
                return i;
}


bool GetTagValueInt(keymaster_key_param_set_t key_params, keymaster_tag_t tag, uint32_t* val)
{
        int pos = find(key_params, tag);
        if (pos == -1) {
                return false;
        }
        *val = key_params.params[pos].integer;
        return true;
}

bool GetTagValueEnumRep(keymaster_key_param_set_t key_params,keymaster_tag_t tag, size_t instance,
                uint32_t* val)
{
        size_t count = 0;
        int pos = -1;
        while (count <= instance) {
                pos = find(key_params, tag, pos);
                if (pos == -1) {
                        return false;
                }
                ++count;
        }
        *val = key_params.params[pos].enumerated;
        return true;
}


bool GetTagValueIntRep(keymaster_key_param_set_t key_params, keymaster_tag_t tag, size_t instance,
                uint32_t* val)
{
        size_t count = 0;
        int pos = -1;
        while (count <= instance) {
                pos = find(key_params, tag, pos);
                if (pos == -1) {
                        return false;
                }
                ++count;
        }
        *val = key_params.params[pos].integer;
        return true;
}

bool GetTagValueLong(keymaster_key_param_set_t key_params, keymaster_tag_t tag, uint64_t* val)
{
        int pos = find(key_params, tag);
        if (pos == -1) {
                return false;
        }
        *val = key_params.params[pos].long_integer;
        return true;
}

bool GetTagValueLongRep(keymaster_key_param_set_t key_params, keymaster_tag_t tag, size_t instance,
                uint64_t* val)
{
        size_t count = 0;
        int pos = -1;
        while (count <= instance) {
                pos = find(key_params, tag, pos);
                if (pos == -1) {
                        return false;
                }
                ++count;
        }
        *val = key_params.params[pos].long_integer;
        return true;
}

bool GetTagValueDate(keymaster_key_param_set_t key_params, keymaster_tag_t tag, uint64_t* val)
{
        int pos = find(key_params, tag);
        if (pos == -1) {
                return false;
        }
        *val = key_params.params[pos].date_time;
        return true;
}

bool GetTagValueBlob(keymaster_key_param_set_t key_params, keymaster_tag_t tag, keymaster_blob_t* val)
{
        int pos = find(key_params, tag);
        if (pos == -1) {
                return false;
        }
        *val = key_params.params[pos].blob;
        return true;
}

bool GetTagValueBool(keymaster_key_param_set_t key_params, keymaster_tag_t tag)
{
        int pos = find(key_params, tag);
        if (pos == -1) {
                return false;
        }
        assert(key_params.params[pos].boolean);
        return key_params.params[pos].boolean;
}

bool ContainsEnumValue(keymaster_key_param_set_t key_params, keymaster_tag_t tag, uint32_t value)
{
        int i = 0;
        for (i=0; i< (int)key_params.length; i++){
                if(key_params.params[i].tag == tag && key_params.params[i].enumerated == value)
                        return true;
        }

        return false;
}

bool ContainsIntValue(keymaster_key_param_set_t key_params, keymaster_tag_t tag, uint32_t value)
{
        int i = 0;
        for (i=0; i< (int)key_params.length; i++){
                if(key_params.params[i].tag == tag && key_params.params[i].integer == value)
                        return true;
        }

        return false;
}

bool ContainsBolbValue (keymaster_key_param_set_t *key_params, uint32_t *index, int begin)
{
        int i;

        i = begin;
        for (i=0; i< (int)key_params->length; i++){
                if(((key_params->params[i].tag & KM_BIGNUM) == KM_BIGNUM)|| ((key_params->params[i].tag & KM_BYTES) == KM_BYTES)){
                        *index = i;
                        //*val = key_params.params[i].blob;
                        return true;
                }
        }

        return false;
}

int ContainsBolbCount (keymaster_key_param_set_t *key_params)
{
        int i, index = 0;
        for (i=0; i< (int)key_params->length; i++){
                if(((key_params->params[i].tag & KM_BIGNUM) == KM_BIGNUM)|| ((key_params->params[i].tag & KM_BYTES) == KM_BYTES)){
                        index ++;
                }
        }

        return index;
}

bool IsBolbValue (keymaster_key_param_set_t* key_params, uint32_t index, keymaster_blob_t* val)
{

        if(((key_params->params[index].tag & KM_BIGNUM) == KM_BIGNUM)|| ((key_params->params[index].tag & KM_BYTES) == KM_BYTES)){
                *val = key_params->params[index].blob;
                return true;
        }

        return false;
}

