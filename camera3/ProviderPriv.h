#ifndef _PROVIDER_PRIV_H_
#define _PROVIDER_PRIV_H_

class Camera3ProviderPrivInfo {

public:
    Camera3ProviderPrivInfo();
    ~Camera3ProviderPrivInfo();

    const char *mProviderName;
    static Camera3ProviderPrivInfo *sInstance;

};

#endif
