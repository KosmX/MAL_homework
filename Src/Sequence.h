//
// Created by kosmx on 2023-05-24.
//

#ifndef MAL_HOMEWORK_SEQUENCE_H
#define MAL_HOMEWORK_SEQUENCE_H
#ifdef __cplusplus

#include <functional>
#include "ProtoThreadWrapper.h"

// I am sorry, I have to show-off threading
template<typename R>
class Sequence {
public:
    Sequence(std::function<void(Sequence<R>*)> suspendFun): f{suspendFun} {
        coroutine.start([this](ProtoThreadWrapper<4096>* tw) -> void* {
            coroutine.suspend(nullptr); // return from this
            f(this);
            isNext = false;
            return nullptr;
        });
    }

    void yield(R d) {
        r = d;
        coroutine.suspend(nullptr);
    }

    R next() {
        if (hasNext()) {
        }
        emptyBuffer = true;
        return r;
    }

    bool hasNext() {
        if (!isNext) return false;
        if (emptyBuffer) {
            coroutine.call(nullptr);
        }
        emptyBuffer = false;
        return isNext;
    }
private:
    ProtoThreadWrapper<4096> coroutine{};
    R r;
    bool emptyBuffer = true;
    bool isNext = true;
    std::function<void(Sequence<R>*)> f;
};


#endif
#endif //MAL_HOMEWORK_SEQUENCE_H
