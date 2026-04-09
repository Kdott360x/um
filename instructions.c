/*
 *  instructions.c
 *  Kodi Dotterer (hdotte01), James Molloy (jmollo02)
 *  03/3/2026
 *
 *  CS 40 Project 6: um
 *
 * Implementation of the instructions.h file.
 * 
 */




 // HUGE NOTE!!! For the instruction that jumps to a line of code, jump to the 
 // line of code minus... we are  aware that we are subtracting from
 // zero for unsigned ints, and we are aware this wraps around, but when
 // we add one to the program counter it will work anyway.

#include "instructions.h"
#include "um.h"
#include "segment.h"
#include "assert.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

// all are helpers so all can be static
static inline uint32_t get_opcode(uint32_t word);
static inline uint32_t get_ra(uint32_t word);
static inline uint32_t get_rb(uint32_t word);
static inline uint32_t get_rc(uint32_t word);
static inline uint32_t lv_ra(uint32_t word);
static inline uint32_t lv_value(uint32_t word);

static void conditional_move(UM_T um, uint32_t ra, uint32_t rb, uint32_t rc);
static void segmented_load(UM_T um, uint32_t ra, uint32_t rb, uint32_t rc);
static void segmented_store(UM_T um, uint32_t ra, uint32_t rb, uint32_t rc);
static void add(UM_T um, uint32_t ra, uint32_t rb, uint32_t rc);
static void multiply(UM_T um, uint32_t ra, uint32_t rb, uint32_t rc);
static void divide(UM_T um, uint32_t ra, uint32_t rb, uint32_t rc);
static void nand(UM_T um, uint32_t ra, uint32_t rb, uint32_t rc);
static void map_segment(UM_T um, uint32_t rb, uint32_t rc);
static void unmap_segment(UM_T um, uint32_t rc);
static void output(UM_T um, uint32_t rc);
static void input(UM_T um, uint32_t rc);
static void load_program(UM_T um, uint32_t rb, uint32_t rc);
static void load_value(UM_T um, uint32_t ra, uint32_t value);


bool run_instruction(UM_T um, uint32_t instruction)
{
        assert(um != NULL);

        uint32_t opcode = get_opcode(instruction);

        // check for op 13

        //set the registers vefore getting into the code

        // the rest of hte swtich cases
        switch (opcode) {
        case 0:
                conditional_move(um, ra, rb, rc);
                break;
        case 1:
                segmented_load(um, ra, rb, rc);
                break;
        case 2:
                segmented_store(um, ra, rb, rc);
                break;
        case 3:
                add(um, ra, rb, rc);
                break;
        case 4:
                multiply(um, ra, rb, rc);
                break;
        case 5:
                divide(um, ra, rb, rc);
                break;
        case 6:
                nand(um, ra, rb, rc);
                break;
        case 7:
                return false;
        case 8:
                map_segment(um, rb, rc);
                break;
        case 9:
                unmap_segment(um, rc);
                break;
        case 10:
                output(um, rc);
                break;
        case 11:
                input(um, rc);
                break;
        case 12:
                load_program(um, rb, rc);
                break;
        default:
                assert(false);
        }

        return true;
}

static inline uint32_t get_opcode(uint32_t word)
{
        return word >> 28;
}

static inline uint32_t get_ra(uint32_t word)
{
        return (word >> 6) & 0x7;
}

static void conditional_move(UM_T um, uint32_t ra, uint32_t rb, uint32_t rc)
{
        if (um->regs[rc] != 0) {
                um->regs[ra] = um->regs[rb];
        }
}