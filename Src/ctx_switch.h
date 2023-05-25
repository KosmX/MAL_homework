//
// Created by kosmx on 2023-05-24.
//
/**
 * low-level thread switching functions.
 * As an example usage, see ProtoThreadWrapper class.
 */

#ifndef MAL_HOMEWORK_CTX_SWITCH_H
#define MAL_HOMEWORK_CTX_SWITCH_H
#ifdef __cplusplus
extern "C" {
#endif

/**
 * Switch context between 2 stacks while preserving registry data
 * @param targetStack target SP
 * @param oldStack source SP pointer, current SP will be stored here.
 * @param data arbitrary 16 bit data to pass (ideally a pointer to some data-pool), may be nullptr
 * @return data ptr on the other thread
 */
void* ctx_switch(void* targetStack, void** oldStack, void* data);

/**
 * Start a new thread
 * @param targetStack start of the target stack (highest index)
 * @param sourceStack place to store source SP
 * @param entry entry function pointer
 * @param entry data
 * @return anything that the target stack yields (using ctx_switch or exit_thread)
 */
void* start_thread(void* targetStack, void** sourceStack, void (*entry)(void* data), void* data);

/**
 * Exit from thread (called by thread)
 * @param targetStack go to this stack
 * @param oldStack it should be set back to its initial value. If not, an error has happened somewhere
 * @param data has anything to give back?
 */
[[noreturn]]
void exit_thread(void* targetStack, void** oldStack, void* data);

#ifdef __cplusplus
}
#endif
#endif //MAL_HOMEWORK_CTX_SWITCH_H
