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


/**
 * Simple thread switching class.
 * The thread is starts with the start function (passing lambda is possible :D)
 * This function may contain an infinite loop or ends the thread by returning
 *
 * The thread should call `suspend` (with 32 bit data or pointer), with this the execution is given back to the main thread.
 * The main thread may call `call` function with data, this data will be received from the thread and the thread will continue from its last suspend point.
 *
 * Consistently calling suspend in thread from an interrupt is possible, (with that, a preemptive scheduler is possible) but I don't need it here.
 *
 * ---
 * This implementation does NOT contain a scheduler
 * ---
 *
 * @tparam STACK_SIZE statically allocated thread stack size
 */
template<int STACK_SIZE>
class ProtoThreadWrapper {
public:

    /**
     * Suspend the caller thread and enter the proto-thread.
     * When the proto-thread calls suspend, the main thread will continue from this function call with returning whatever the thread sends
     * In a complete scheduler the data should represent some kind of request (wait for time/lock, interrupt, etc)
     * In this context, data can be anything
     * @param data some 32 bit data (may be a pointer)
     * @return
     */
    void* call(void* data) {
        assert(isThread == false); // it shouldn't be called from thread
        if (thread_SP != stack + STACK_SIZE) {
            isThread = true;
            return ctx_switch(thread_SP, &callee_SP, data);
        } else {
            throw 0; // what to do if thread exited or was never started
        }
    }

    /**
     * Exit from proto-thread, return to the caller.
     * @param data Some data that the caller receives
     * @return something that the next caller sends
     */
    void* suspend(void* data) {
        assert(isThread == true); // it shouldn't be called from thread
        isThread = false;
        return ctx_switch(callee_SP, &thread_SP, data);
    }

    /**
     * Starts the execution of threadFunction parameter until suspend is invoked
     * @param threadFunction threadFunction function. May contain an infinite loop. Make sure to wait with `suspend`
     * @return first suspend data of threadFunction
     */
    void* start(std::function<void*(ProtoThreadWrapper<STACK_SIZE>*)> threadFunction) {
        this->entry = threadFunction;
        isThread = true; // I :/
        return start_thread(thread_SP, &callee_SP, entryFunctionImpl, this);
    }

private:
    uint8_t stack[STACK_SIZE]{}; // stack filled with garbage
    void* callee_SP{}; // the caller SP for returning

    // ARM M4 uses full-descending stack, it is okay to point to invalid address if nothing is on the stack
    void* thread_SP = &stack[0] + STACK_SIZE;

    volatile bool isThread = false; // some thread-asserting for sanity-check

    std::function<void*(ProtoThreadWrapper<STACK_SIZE>*)> entry; // required to successfully enter the thread

    // start_thread needs a C function pointer. This is the thread entry
    static void entryFunctionImpl(void* data) {
        auto thisPtr = reinterpret_cast<ProtoThreadWrapper<STACK_SIZE>*>(data);

        // This function should NEVER run on main-thread
        assert (thisPtr->isThread == true);

        auto res = thisPtr->entry(thisPtr);
        asm("isb"); // try to disable compiler optimizing callee_SP variable
        exit_thread(thisPtr->callee_SP, &thisPtr->thread_SP, res);
    }
};




#endif
#endif //MAL_HOMEWORK_PROTOTHREADWRAPPER_H
