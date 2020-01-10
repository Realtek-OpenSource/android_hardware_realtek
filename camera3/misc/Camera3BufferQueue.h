#ifndef __CAMERA3_BUFFER_QUEUE__
#define __CAMERA3_BUFFER_QUEUE__

#include <utils/Log.h>
#include <utils/Vector.h>
#include <utils/KeyedVector.h>
#include <utils/SortedVector.h>
#include <utils/threads.h>
#include <utils/Mutex.h>
#include "Debug.h"

using namespace android;

static const nsecs_t kWaitNs = (1*1E9);

namespace androidcamera3 {

template <typename T>
class BufferQueue {
public:
    BufferQueue(int32_t size, const char *name);
    ~BufferQueue();

    void                    enqueue(T buf);
    void                    dequeue();
    T                       peek();
    int32_t                 size();
    void                    wait();
    void                    signal();

private:
    int32_t                 mSize;
    Mutex                   mQueueLock;
    Mutex                   mWaitLock;
    Condition               mSignal;
    Vector<T>               mQueue;
    const char *                  mName;
};

// basic implementation here
template <typename T>
BufferQueue<T>::BufferQueue(
    int32_t size,
    const char *name)
: mSize(size),
  mName(name)
{
    ALOGD("Camera3BufferQueue() : %s",name);
    mQueue.setCapacity(size);
}

template <typename T>
BufferQueue<T>::~BufferQueue()
{
    ALOGD("~Camera3BufferQueue() : %s size %d",
        mName,
        mQueue.size());
}

template <typename T>
void BufferQueue<T>::enqueue(T buf)
{
    //ALOGD("%s %s",mName,__FUNCTION__);
    Mutex::Autolock l(mQueueLock);
    mQueue.push_back(buf);
}

template <typename T>
void BufferQueue<T>::dequeue()
{
    CHECK(mQueue.size() > 0);
    Mutex::Autolock l(mQueueLock);
    mQueue.removeItemsAt(0);
}

template <typename T>
T BufferQueue<T>::peek()
{
    CHECK(mQueue.size() > 0);
    Mutex::Autolock l(mQueueLock);
    return mQueue[0];
}

template <typename T>
int32_t BufferQueue<T>::size()
{
    return mQueue.size();
}

template <typename T>
void BufferQueue<T>::wait()
{
    Mutex::Autolock l(mWaitLock);
    mSignal.waitRelative(mWaitLock,kWaitNs);
}

template <typename T>
void BufferQueue<T>::signal()
{
    Mutex::Autolock l(mWaitLock);
    mSignal.signal();
}


};  // namespace androidcamera3


#endif // __CAMERA3_BUFFER_QUEUE__
