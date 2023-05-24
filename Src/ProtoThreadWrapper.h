//
// Created by kosmx on 2023-05-24.
//

#ifndef MAL_HOMEWORK_PROTOTHREADWRAPPER_H
#define MAL_HOMEWORK_PROTOTHREADWRAPPER_H
#ifdef __cplusplus

#include <cassert>
#include "ctx_switch.h"
#include<functional>
#include<cstdint>


template<int STACK_SIZE>
class ProtoThreadWrapper {
public:

    void* call(void* data) {
        assert(isThread == false); // it shouldn't be called from thread
        if (thread_SP != stack + STACK_SIZE) {
            isThread = true;
            return ctx_switch(thread_SP, &callee_SP, data);
        } else {
            throw 0; // what to do if thread exited or was never started
        }
    }
    void* suspend(void* data) {
        assert(isThread == true); // it shouldn't be called from thread
        isThread = false;
        return ctx_switch(callee_SP, &thread_SP, data);
    }

    /**
     * Starts the execution of threadFunction parameter until suspend is invoked
     * @param threadFunction threadFunction function
     * @return first suspend data of threadFunction
     */
    void* start(std::function<void*(ProtoThreadWrapper<STACK_SIZE>*)> threadFunction) {
        this->entry = threadFunction;
        isThread = true; // I :/
        return start_thread(thread_SP, &callee_SP, entryFunctionImpl, this);
    }

private:
    uint8_t stack[STACK_SIZE]{}; // stack filled with garbage
    void* callee_SP{};

    // ARM M4 uses full-descending stack, it is okay to point to invalid address if nothing is on the stack
    void* thread_SP = &stack[0] + STACK_SIZE;

    volatile bool isThread = false;

    std::function<void*(ProtoThreadWrapper<STACK_SIZE>*)> entry;

    static void entryFunctionImpl(void* data) {
        auto thisPtr = reinterpret_cast<ProtoThreadWrapper<STACK_SIZE>*>(data);
        auto res = thisPtr->entry(thisPtr);
        asm("isb"); // try to disable compiler optimizing callee_SP variable
        exit_thread(thisPtr->callee_SP, &thisPtr->thread_SP, res);
    }
};




#endif
#endif //MAL_HOMEWORK_PROTOTHREADWRAPPER_H
