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
#include <iso646.h>


// static helper declarations
static inline uint32_t get_opcode(uint32_t word);
static inline uint32_t get_ra(uint32_t word);
static inline uint32_t get_rb(uint32_t word);
static inline uint32_t get_rc(uint32_t word);

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


bool run_instruction(UM_T um, uint32_t instruction)
{
        assert(um != NULL);

        uint32_t opcode = get_opcode(instruction);

        // check for op 13
        if (opcode == 13) {
                // find register
                uint32_t regA_13 = (instruction >> 25) & 0x7;

                // find value
                uint32_t val_13 = instruction & 0x01FFFFFF;

                // put val in register
                um->regs[regA_13] = val_13;

                return true;
        }


        //set the registers vefore getting into the code: note use um->regs[reg]
        // to access the actual value stored, i.e. what is below is the index
        uint32_t ra = get_ra(instruction);
        uint32_t rb = get_rb(instruction);
        uint32_t rc = get_rc(instruction);



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


// bit functions
static inline uint32_t get_opcode(uint32_t word)
{
        return word >> 28;
}

static inline uint32_t get_ra(uint32_t word)
{
        return (word >> 6) & 0x7;
}
static inline uint32_t get_rb(uint32_t word)
{
        return (word >> 3) & 0x7;
}
static inline uint32_t get_rc(uint32_t word)
{
        return (word >> 0) & 0x7;
}

// command functions
static void conditional_move(UM_T um, uint32_t ra, uint32_t rb, uint32_t rc)
{
        if (um->regs[rc] != 0) {
                um->regs[ra] = um->regs[rb];
        }
}

static void segmented_load(UM_T um, uint32_t ra, uint32_t rb, uint32_t rc)
{
        um->regs[ra] = Segment_get(um->segments[um->regs[rb]], um->regs[rc]);
}

static void segmented_store(UM_T um, uint32_t ra, uint32_t rb, uint32_t rc)
{
        Segment_put(um->segments[um->regs[ra]], um->regs[rb], um->regs[rc]);
}

static void add(UM_T um, uint32_t ra, uint32_t rb, uint32_t rc)
{
        um->regs[ra] = (um->regs[rb] + um->regs[rc]);
}

static void multiply(UM_T um, uint32_t ra, uint32_t rb, uint32_t rc)
{
        um->regs[ra] = (um->regs[rb] * um->regs[rc]);
}

static void divide(UM_T um, uint32_t ra, uint32_t rb, uint32_t rc)
{
        um->regs[ra] = (um->regs[rb] / um->regs[rc]);
}

static void nand(UM_T um, uint32_t ra, uint32_t rb, uint32_t rc)
{
        um->regs[ra] = ~(um->regs[rb] & um->regs[rc]);
}

static void map_segment(UM_T um, uint32_t rb, uint32_t rc)
{
        assert(um != NULL);

        uint32_t length = um->regs[rc];
        Segment_T new_seg = Segment_new(length);
        uint32_t id;

        if (Seq_length(um->unmapped) > 0) {
                id = (uint32_t)(uintptr_t)Seq_remlo(um->unmapped);
                um->segments[id] = new_seg;
        } else {
                if (um->seg_size == um->seg_capacity) {
                        um->seg_capacity *= 2;
                        um->segments = realloc(um->segments, um->seg_capacity *
                                                 sizeof(*um->segments));
                        assert(um->segments != NULL);
                }
                // handle create new segment case
                id = um->seg_size;
                um->segments[id] = new_seg;
                um->seg_size++;
        }
        // set the value in rb to whatever id we end up with
        um->regs[rb] = id;
}

static void unmap_segment(UM_T um, uint32_t rc)
{
        assert(um != NULL);

        // set id equal to what is in rc
        uint32_t id = um->regs[rc];

        // free the segment at the id
        Segment_free(&(um->segments[id]));
        assert(um->segments[id] == NULL);

        // add the id to the sequence
        Seq_addlo(um->unmapped, (void *)(uintptr_t)id);
}

static void output(UM_T um, uint32_t rc)
{
        uint32_t value = um->regs[rc];
        putchar((char)value);
}

static void input(UM_T um, uint32_t rc)
{
        int32_t current = (int32_t)getchar();
        if (current == EOF) {
                um->regs[rc] = 0xffffffff;
        } else {
                um->regs[rc] = current % 256;
        }
}

static void load_program(UM_T um, uint32_t rb, uint32_t rc)
{      
        assert(um != NULL);
        if (um->regs[rb] == 0) {
                um->program_counter = um->regs[rc];
                return;
        }
        Segment_T source = um->segments[um->regs[rb]];

        Segment_free(&(um->segments[0]));
        assert(um->segments[0] == NULL);

        // creating new id
        uint32_t length = Segment_length(source);
        Segment_T new_seg = Segment_new(length);

        // copying over 
        for (uint32_t i = 0; i < length; i++) {
                uint32_t word = Segment_get(source, i);
                Segment_put(new_seg, i, word);
        }
        um->segments[0] = new_seg;
        um->program_counter = um->regs[rc];
}
