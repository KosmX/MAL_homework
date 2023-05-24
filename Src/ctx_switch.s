// -This is definitely not ARM assembly file-
//
// Created by kosmx on 2023-05-24.
//
// C compiler: r0-r3 argument and scratch registers (we can work in it, nobody cares)
// r4-r11 (idk r12) callee save regs, we have to preserve these
// r13-r15, special registers, most notable is lr (link-register) which has to be saved
// saving PSR shouldn't be required 

  .syntax unified
  .cpu cortex-m4
  .thumb

.section    .text.ctx_switch

.macro push_stack
    PUSH {r3-r12, lr}
.endm

.macro pop_stack
    POP {r3-r12, lr}
.endm

/**
 * Switch context between 2 stacks while preserving registry data
 * @param targetStack target SP
 * @param oldStack source SP pointer, current SP will be stored here.
 * @param data arbitrary 16 bit data to pass (ideally a pointer to some data-pool), may be nullptr
 * @return data ptr on the other thread
 */
.global ctx_switch
ctx_switch:
    push_stack

    STR SP, [r1]
    ISB @ Make sure everything is saved before changing the SP
    MOV SP, r0
    ISB @ Make sure SP is changed before reading anything from it

    MOV r0, r2 @ Move data to return

    pop_stack
    BX lr

/**
 * Start a new thread
 * @param targetStack start of the target stack (highest index)
 * @param sourceStack place to store source SP
 * @param entry entry function pointer
 * @param entry data
 * @return anything that the target stack yields (using ctx_switch or exit_thread)
 */
.global start_thread
start_thread:
    push_stack

    STR SP, [r1]
    ISB
    MOV SP, r0

    MOV lr, 0xFFFFFFFF

    MOV r0, r3 // it will pass the data argument to the function... weirdly
    MOV PC, r2


/**
 * Exit from thread (called by thread)
 * @param targetStack go to this stack
 * @param oldStack it should be set back to its initial value. If not, an error has happened somewhere
 * @param data has anything to give back?
 */
.global exit_thread
exit_thread:
    STR SP, [r1]

    MOV SP, r0
    ISB
    pop_stack
    MOV r0, r2
    BX lr

