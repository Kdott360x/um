/*
 *  instructions.c
 *  Kodi Dotterer (hdotte01), James Molloy (jmollo02)
 *  03/3/2026
 *
 *  CS 40 Project 6: um
 *
 * File takes in a uint32_t word from the UM which contains an operation 
 * command and the given register indexes and potential values that we need 
 * to perform the operation. File takes this word and determines what actions
 * to complete.
 * 
 */

#include "instructions.h"
#include "um.h"
#include "segment.h"
#include "assert.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <iso646.h>


/* PARSE CODEWORD HELPERS -> declarations */ 
static inline uint32_t get_opcode(uint32_t word);
static inline uint32_t get_ra(uint32_t word);
static inline uint32_t get_rb(uint32_t word);
static inline uint32_t get_rc(uint32_t word);

/* OPERATION HELPERS -> declarations */
static inline void conditional_move(UM_T um, uint32_t ra, uint32_t rb, uint32_t rc);
static inline void segmented_load(UM_T um, uint32_t ra, uint32_t rb, uint32_t rc);
static inline void segmented_store(UM_T um, uint32_t ra, uint32_t rb, uint32_t rc);
static inline void add(UM_T um, uint32_t ra, uint32_t rb, uint32_t rc);
static inline void multiply(UM_T um, uint32_t ra, uint32_t rb, uint32_t rc);
static inline void divide(UM_T um, uint32_t ra, uint32_t rb, uint32_t rc);
static inline void nand(UM_T um, uint32_t ra, uint32_t rb, uint32_t rc);
static void map_segment(UM_T um, uint32_t rb, uint32_t rc);
static void unmap_segment(UM_T um, uint32_t rc);
static inline void output(UM_T um, uint32_t rc);
static inline void input(UM_T um, uint32_t rc);
static void load_program(UM_T um, uint32_t rb, uint32_t rc);

/****** run_instruction ********
 *
 * Parses the 32bit words to perform the correct operations with the given
 * registers
 *
 * Params:
 *      UM_T um: the Universal Machine, alter the states of the struct
 *      uint32_t instruction: the 32-bit instruction word, contains opcode,
 *                            reg(s), and potentially a value.
 *
 * Return:
 *      Returns true if execution should continue.
 *      Returns false if the instruction is Halt.
 *
 * Expects:
 *      um is not NULL and instruction is a valid UM instruction word.
 *
 * Notes:
 *      If the opcode is 13, the instruction is treated as a Load Value
 *      instruction and decoded using its special format.
 *
 *      For all other opcodes, the instruction is decoded using the
 *      standard three-register format and dispatched to the matching
 *      helper function.
 *
 *      Will CRE if um is NULL or if the opcode is invalid.
 *
 ************************/
bool run_instruction(UM_T um, uint32_t instruction)
{
        assert(um != NULL);

        // get and store opcode
        uint32_t opcode = (instruction >> 28);

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

        // set regs
        uint32_t ra = get_ra(instruction);
        uint32_t rb = get_rb(instruction);
        uint32_t rc = get_rc(instruction);

        // the rest of the swtich cases
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

/*******
 * PARSE CODEWORD HELPERS *
 * ******/

/****** get_opcode ********
 *
 * Extracts and returns the opcode from the given 32-bit instruction word.
 *
 * Params:
 *      uint32_t word: the instruction word to decode
 *
 * Return:
 *      The 4-bit opcode stored in the most significant bits.
 *
 ************************/
static inline uint32_t get_opcode(uint32_t word)
{
        return word >> 28;
}

/****** get_ra ********
 *
 * Extracts and returns register A from a three-register instruction word.
 *
 * Params:
 *      uint32_t word: the instruction word to decode
 *
 * Return:
 *      The 3-bit register A field from the instruction word.
 *
 ************************/
static inline uint32_t get_ra(uint32_t word)
{
        return (word >> 6) & 0x7;
}

/****** get_rb ********
 *
 * Extracts and returns register B from a three-register instruction word.
 *
 * Params:
 *      uint32_t word: the instruction word to decode
 *
 * Return:
 *      The 3-bit register B field from the instruction word.
 *
 ************************/
static inline uint32_t get_rb(uint32_t word)
{
        return (word >> 3) & 0x7;
}

/****** get_rc ********
 *
 * Extracts and returns register C from a three-register instruction word.
 *
 * Params:
 *      uint32_t word: the instruction word to decode
 *
 * Return:
 *      The 3-bit register C field from the instruction word.
 *
 ************************/
static inline uint32_t get_rc(uint32_t word)
{
        return (word >> 0) & 0x7;
}

/*******
 * OPERATION HELPERS *
 * ******/

/****** conditional_move ********
 *
 * If register C is not zero, copies the value in register B into
 * register A.
 *
 * Params:
 *      UM_T um: the Universal Machine whose registers are updated
 *      uint32_t ra: index of register A
 *      uint32_t rb: index of register B
 *      uint32_t rc: index of register C
 *
 * Return:
 *      None
 *
 ************************/
static inline void conditional_move(UM_T um, uint32_t ra, uint32_t rb, uint32_t rc)
{
        if (um->regs[rc] != 0) {
                um->regs[ra] = um->regs[rb];
        }
}

/****** segmented_load ********
 *
 * Loads into register A the word at offset r[C] in segment m[r[B]].
 *
 * Params:
 *      UM_T um: the Universal Machine whose state is accessed
 *      uint32_t ra: index of register A
 *      uint32_t rb: index of register B
 *      uint32_t rc: index of register C
 *
 * Return:
 *      None
 *
 ************************/
static inline void segmented_load(UM_T um, uint32_t ra, uint32_t rb, uint32_t rc)
{
        Segment_T seg = um->segments[um->regs[rb]];
        um->regs[ra] = seg->words[um->regs[rc]];
}

/****** segmented_store ********
 *
 * Stores the value in register C into offset r[B] of segment m[r[A]].
 *
 * Params:
 *      UM_T um: the Universal Machine whose state is updated
 *      uint32_t ra: index of register A
 *      uint32_t rb: index of register B
 *      uint32_t rc: index of register C
 *
 * Return:
 *      None
 *
 ************************/
static inline void segmented_store(UM_T um, uint32_t ra, uint32_t rb, uint32_t rc)
{
        Segment_T seg = um->segments[um->regs[ra]];
        seg->words[um->regs[rb]] = um->regs[rc];
}

/****** add ********
 *
 * Stores into register A the sum of registers B and C modulo 2^32.
 *
 * Params:
 *      UM_T um: the Universal Machine whose registers are updated
 *      uint32_t ra: index of register A
 *      uint32_t rb: index of register B
 *      uint32_t rc: index of register C
 *
 * Return:
 *      None
 *
 ************************/
static inline void add(UM_T um, uint32_t ra, uint32_t rb, uint32_t rc)
{
        um->regs[ra] = (um->regs[rb] + um->regs[rc]);
}

/****** multiply ********
 *
 * Multiplies the values in registers B and C and stores the result in
 * register A.
 *
 * Params:
 *      UM_T um: the Universal Machine whose registers are updated
 *      uint32_t ra: index of register A
 *      uint32_t rb: index of register B
 *      uint32_t rc: index of register C
 *
 * Return:
 *      None
 *
 ************************/
static inline void multiply(UM_T um, uint32_t ra, uint32_t rb, uint32_t rc)
{
        um->regs[ra] = (um->regs[rb] * um->regs[rc]);
}

/****** divide ********
 *
 * Divides the value in register B by the value in register C and stores
 * the result in register A.
 *
 * Params:
 *      UM_T um: the Universal Machine whose registers are updated
 *      uint32_t ra: index of register A
 *      uint32_t rb: index of register B
 *      uint32_t rc: index of register C
 *
 * Return:
 *      None
 *
 ************************/
static inline void divide(UM_T um, uint32_t ra, uint32_t rb, uint32_t rc)
{
        um->regs[ra] = (um->regs[rb] / um->regs[rc]);
}

/****** nand ********
 *
 * Computes the bitwise NAND of registers B and C and stores the result
 * in register A.
 *
 * Params:
 *      UM_T um: the Universal Machine whose registers are updated
 *      uint32_t ra: index of register A
 *      uint32_t rb: index of register B
 *      uint32_t rc: index of register C
 *
 * Return:
 *      None
 *
 ************************/
static inline void nand(UM_T um, uint32_t ra, uint32_t rb, uint32_t rc)
{
        um->regs[ra] = ~(um->regs[rb] & um->regs[rc]);
}

/****** map_segment ********
 *
 * Creates a new segment of length r[C] and stores its identifier in
 * register B.
 *
 * Params:
 *      UM_T um: the Universal Machine whose memory is updated
 *      uint32_t rb: index of register B
 *      uint32_t rc: index of register C
 *
 * Return:
 *      None
 *
 ************************/
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
                        uint32_t old_capacity = um->seg_capacity;
                        um->seg_capacity *= 2;
                        um->segments = realloc(um->segments, um->seg_capacity *
                                                 sizeof(*um->segments));
                        assert(um->segments != NULL);

                        for (uint32_t i = old_capacity; i < um->seg_capacity;
                                                                        i++) {
                                um->segments[i] = NULL;
                        }
                }
                // handle create new segment case
                id = um->seg_size;
                um->segments[id] = new_seg;
                um->seg_size++;
        }
        // set the value in rb to whatever id we end up with
        um->regs[rb] = id;
}

/****** unmap_segment ********
 *
 * Unmaps the segment whose identifier is stored in register C.
 *
 * Params:
 *      UM_T um: the Universal Machine whose memory is updated
 *      uint32_t rc: index of register C
 *
 * Return:
 *      None
 *
 ************************/
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

/****** output ********
 *
 * Writes the value in register C to standard output as a character.
 *
 * Params:
 *      UM_T um: the Universal Machine whose register is read
 *      uint32_t rc: index of register C
 *
 * Return:
 *      None
 *
 ************************/
static inline void output(UM_T um, uint32_t rc)
{
        putchar((int)um->regs[rc]);
}

/****** input ********
 *
 * Reads one character from standard input and stores it in register C.
 *
 * Params:
 *      UM_T um: the Universal Machine whose register is updated
 *      uint32_t rc: index of register C
 *
 * Return:
 *      None
 *
 ************************/
static inline void input(UM_T um, uint32_t rc)
{
        int32_t current = (int32_t)getchar();
        if (current == EOF) {
                um->regs[rc] = 0xffffffff;
        } else {
                um->regs[rc] = current % 256;
        }
}

/****** load_program ********
 *
 * Replaces segment 0 with a duplicate of segment m[r[B]] and sets the
 * program counter to r[C].
 *
 * Params:
 *      UM_T um: the Universal Machine whose program state is updated
 *      uint32_t rb: index of register B
 *      uint32_t rc: index of register C
 *
 * Return:
 *      None
 *
 ************************/
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
