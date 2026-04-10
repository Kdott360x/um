/*
 * umlab.c
 *
 * Functions to generate UM unit tests. Once complete, this module
 * should be augmented and then linked against umlabwrite.c to produce
 * a unit test writing program.
 *  
 * A unit test is a stream of UM instructions, represented as a Hanson
 * Seq_T of 32-bit words adhering to the UM's instruction format.  
 * 
 * Any additional functions and unit tests written for the lab go
 * here. 
 *  
 */


#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include <seq.h>
#include <bitpack.h>
#include <inttypes.h>


typedef uint32_t Um_instruction;
typedef enum Um_opcode {
        CMOV = 0, SLOAD, SSTORE, ADD, MUL, DIV,
        NAND, HALT, ACTIVATE, INACTIVATE, OUT, IN, LOADP, LV
} Um_opcode;


/* Functions that return the two instruction types */

Um_instruction three_register(Um_opcode op, int ra, int rb, int rc);
Um_instruction loadval(unsigned ra, unsigned val);


/* Wrapper functions for each of the instructions */

static inline Um_instruction halt(void) 
{
        return three_register(HALT, 0, 0, 0);
}

typedef enum Um_register { r0 = 0, r1, r2, r3, r4, r5, r6, r7 } Um_register;

static inline Um_instruction add(Um_register a, Um_register b, Um_register c) 
{
        return three_register(ADD, a, b, c);
}

static inline Um_instruction input(Um_register c)
{
        return three_register(IN, 0, 0, c);
}

static inline Um_instruction output(Um_register c)
{
        return three_register(OUT, 0, 0, c);
}

static inline Um_instruction cmov(Um_register a, Um_register b, Um_register c)
{
        return three_register(CMOV, a, b, c);
}

static inline Um_instruction sload(Um_register a, Um_register b, Um_register c)
{
        return three_register(SLOAD, a, b, c);
}

static inline Um_instruction sstore(Um_register a, Um_register b, Um_register c)
{
        return three_register(SSTORE, a, b, c);
}

static inline Um_instruction multiply(Um_register a, Um_register b, Um_register c)
{
        return three_register(MUL, a, b, c);
}

static inline Um_instruction divide(Um_register a, Um_register b, Um_register c)
{
        return three_register(DIV, a, b, c);
}

static inline Um_instruction nand(Um_register a, Um_register b, Um_register c)
{
        return three_register(NAND, a, b, c);
}

static inline Um_instruction map_segment(Um_register b, Um_register c)
{
        return three_register(ACTIVATE, 0, b, c);
}

static inline Um_instruction unmap_segment(Um_register c)
{
        return three_register(INACTIVATE, 0, 0, c);
}

/* END Wrapper functions for each of the instructions */

/* Functions for working with streams */

static inline void append(Seq_T stream, Um_instruction inst)
{
        assert(sizeof(inst) <= sizeof(uintptr_t));
        Seq_addhi(stream, (void *)(uintptr_t)inst);
}

const uint32_t Um_word_width = 32;

void Um_write_sequence(FILE *output, Seq_T stream)
{
        assert(output != NULL && stream != NULL);
        int stream_length = Seq_length(stream);
        for (int i = 0; i < stream_length; i++) {
                Um_instruction inst = (uintptr_t)Seq_remlo(stream);
                for (int lsb = Um_word_width - 8; lsb >= 0; lsb -= 8) {
                        fputc(Bitpack_getu(inst, 8, lsb), output);
                }
        }
      
}


/* Unit tests for the UM */

void build_halt_test(Seq_T stream)
{
        append(stream, halt());
}

void build_verbose_halt_test(Seq_T stream)
{
        append(stream, halt());
        append(stream, loadval(r1, 'B'));
        append(stream, output(r1));
        append(stream, loadval(r1, 'a'));
        append(stream, output(r1));
        append(stream, loadval(r1, 'd'));
        append(stream, output(r1));
        append(stream, loadval(r1, '!'));
        append(stream, output(r1));
        append(stream, loadval(r1, '\n'));
        append(stream, output(r1));
}

void build_add_halt_test(Seq_T stream)
{
        append(stream, add(r1, r2, r3));
        append(stream, halt());
}

void build_print_six_test(Seq_T stream)
{
        append(stream, loadval(r1, 48));
        append(stream, loadval(r2, 6));
        append(stream, add(r3, r1, r2));
        append(stream, output(r3));
        append(stream, halt());
}

Um_instruction three_register(Um_opcode op, int ra, int rb, int rc)
{
        // create codeword
        Um_instruction myInstruction = 0;
        
        // pack opcode into first 4 bits
        myInstruction = (Um_instruction) op; 

        // pad bits 27-9 with nothing (19 bits!!)
        myInstruction = myInstruction << 19;
        
        int intArray[ ] = {ra, rb, rc};

        for (int i = 0; i < 3; i++){
                myInstruction = myInstruction << 3;
                myInstruction = myInstruction | intArray[i];
        }

        return myInstruction;
}

Um_instruction loadval(unsigned ra, unsigned val)
{
        // create codeword
        Um_instruction myInstruction = 0;
        
        // pack opcode into first 4 bits
        myInstruction = (Um_instruction)13;
        myInstruction = myInstruction << 3;
        myInstruction = myInstruction | ((Um_instruction)ra); 

        // pad bits 27-9 with nothing
        myInstruction = myInstruction << 25;
        myInstruction = myInstruction | ((Um_instruction)val);

        return myInstruction;
}

void build_input_output_test(Seq_T stream)
{
        append(stream, input(r1));
        append(stream, output(r1));
        append(stream, halt());
}

void build_cmov_zero_test(Seq_T stream)
{
        append(stream, loadval(r1, 'A'));
        append(stream, loadval(r2, 'B'));
        append(stream, loadval(r3, 0));
        append(stream, cmov(r1, r2, r3));
        append(stream, output(r1));
        append(stream, halt());
}

void build_cmov_nonzero_test(Seq_T stream)
{
        append(stream, loadval(r1, 'A'));
        append(stream, loadval(r2, 'B'));
        append(stream, loadval(r3, 1));
        append(stream, cmov(r1, r2, r3));
        append(stream, output(r1));
        append(stream, halt());
}

void build_mult_test(Seq_T stream)
{
        append(stream, loadval(r1, 3));
        append(stream, loadval(r2, 2));
        append(stream, multiply(r3, r1, r2)); 
        append(stream, loadval(r4, 48));
        append(stream, add(r5, r3, r4));
        append(stream, output(r5));
        append(stream, halt());
}

void build_div_test(Seq_T stream)
{
        append(stream, loadval(r1, 8));
        append(stream, loadval(r2, 2));
        append(stream, divide(r3, r1, r2));
        append(stream, loadval(r4, 48));
        append(stream, add(r5, r3, r4));
        append(stream, output(r5));
        append(stream, halt());
}

void build_nand_test(Seq_T stream)
{
        append(stream, loadval(r1, 255));
        append(stream, loadval(r2, 207));
        append(stream, nand(r3, r1, r2));
        append(stream, output(r3));
        append(stream, halt());
}

void build_seg_store_load_zero_test(Seq_T stream)
{
        append(stream, loadval(r1, 0));
        append(stream, loadval(r2, 0));
        append(stream, loadval(r3, 'Z'));

        append(stream, sstore(r1, r2, r3));
        append(stream, sload(r4, r1, r2));
        append(stream, output(r4));
        append(stream, halt());
}

void build_map_store_load_unmap_test(Seq_T stream)
{
        append(stream, loadval(r1, 1));
        append(stream, map_segment(r2, r1));

        append(stream, loadval(r3, 0));
        append(stream, loadval(r4, 'M'));

        append(stream, sstore(r2, r3, r4));
        append(stream, sload(r5, r2, r3));
        append(stream, output(r5));
        append(stream, unmap_segment(r2));
        append(stream, halt());
}