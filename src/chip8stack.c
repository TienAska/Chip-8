#include "chip8stack.h"
#include "chip8.h"
#include <assert.h>
static void  chip8_is_stack_in_bound(struct chip8* chip8, unsigned char SP){
    assert(SP < CHIP8_TOTAL_STACK_DEPTH);
}

void chip8_stack_push(struct chip8* chip8, unsigned short val){
    chip8_is_stack_in_bound(chip8, chip8->registers.SP);
    chip8->stack.stack[chip8->registers.SP] = val;
    chip8->registers.SP++;
}

unsigned short chip8_stack_pop(struct chip8* chip8){
    chip8_is_stack_in_bound(chip8, --chip8->registers.SP);
    unsigned short val = chip8->stack.stack[chip8->registers.SP];
    return val;
}