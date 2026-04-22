/*
 *  um.c
 *  Kodi Dotterer (hdotte01), James Molloy (jmollo02)
 *  03/3/2026
 *
 *  CS 40 Project 6: um
 *
 *  Implementaion of the um.h file
 * 
 */

#include "um.h"
#include <stdbool.h>

// Helper functions for the run_um loop

static void map_segment(UM_T um, uint32_t rb, uint32_t rc);
static void unmap_segment(UM_T um, uint32_t rc);
static void load_program(UM_T um, uint32_t rb, uint32_t rc);


 /****** UM_new ****
 *
 * Creates a new UM struct.
 *
 * Params:
 *      Segment_T segmentZero: This is the segment containing all of the 
 *      commands
 *  
 * Return:
 *      Returns a pointer to a UM_T struct that will be used for the run command
 * 
 * Expects:
 *      Segment_T is not null and is a pointer to a valid Segment_T
 * 
 * Notes:
 *      Will CRE if the Segment is Null or invalid 
 *
 ************************/
UM_T UM_new(Segment_T seg_zero) 
{
        assert(seg_zero != NULL);

        // get space for the um pointer
        UM_T um = malloc(sizeof(*um));
        assert(um != NULL);

        // init registers
        for (int i = 0; i < 8; i++) {
                um->regs[i] = 0;
        }

        //init the counter
        um->program_counter = 0;    		

        // allocate array of 1 Segment_T pointer
        um->segments = malloc(sizeof(*um->segments) * 1);
        assert(um->segments != NULL);

        // store segment 0
        um->segments[0] = seg_zero;

        // init segment capacity to 1
        um->seg_size = 1;	
        um->seg_capacity = 1;	
        // NOTE: Can do individual add ns if time is inefficient

        // initialize the unmapped sequence
        um->unmapped = Seq_new(1000);	

        // return the pointer
        return um;	           			
}


 /****** UM_run ****
 *
 * Runs the UM struct through the UM program.
 *
 * Params:
 *      UM_T um: This is the UM containing the commands and registers that will
 *      be used to run our program.
 *  
 * Return:
 *      nothing
 * 
 * Expects:
 *      UM_T is not null or invalid
 * 
 * Notes:
 *      Will CRE if the UM is Null or invalid 
 *
 ************************/
void UM_run(UM_T um)
{
        assert(um != NULL);
        assert(um->segments[0] != NULL);

        // set the local vars for hot mem
        uint32_t *regs = um->regs;
        Segment_T *segments = um->segments;

        // index local var to track
        uint32_t pc = um->program_counter;

        while (true) {
                Segment_T program = segments[0];
                uint32_t instruction = program->words[pc++];
                uint32_t opcode = instruction >> 28;

                // check for op 13
                if (opcode == 13) {
                        // find register
                        uint32_t regA_13 = (instruction >> 25) & 0x7;

                        // find value
                        uint32_t val_13 = instruction & 0x01FFFFFF;

                        // put val in register
                        regs[regA_13] = val_13;

                        continue;
                }

                // set regs
                uint32_t ra = (instruction >> 6) & 0x7;
                uint32_t rb = (instruction >> 3) & 0x7;
                uint32_t rc = instruction & 0x7;

                // the rest of the switch cases
                switch (opcode) {
                case 0:
                        // cond move
                        if (regs[rc] != 0) {
                                regs[ra] = regs[rb];
                        }
                        break;

                case 1: {
                        // seg load
                        Segment_T seg = segments[regs[rb]];
                        regs[ra] = seg->words[regs[rc]];
                        break;
                }

                case 2: {
                        // seg_store
                        Segment_T seg = segments[regs[ra]];
                        seg->words[regs[rb]] = regs[rc];
                        break;
                }

                case 3:
                        // add
                        regs[ra] = regs[rb] + regs[rc];
                        break;

                case 4:
                        // mult
                        regs[ra] = regs[rb] * regs[rc];
                        break;

                case 5:
                        // div
                        regs[ra] = regs[rb] / regs[rc];
                        break;

                case 6:
                        // and
                        regs[ra] = ~(regs[rb] & regs[rc]);
                        break;

                case 7:
                        // exit program, but reset pc first
                        um->program_counter = pc;
                        return;

                case 8:
                        // map
                        um->program_counter = pc;
                        map_segment(um, rb, rc);
                        segments = um->segments;
                        pc = um->program_counter;
                        break;

                case 9:
                        // unmap
                        um->program_counter = pc;
                        unmap_segment(um, rc);
                        segments = um->segments;
                        pc = um->program_counter;
                        break;

                case 10:
                        // output
                        putchar((int)regs[rc]);
                        break;

                case 11: {
                        // input
                        int in = getchar();
                        if (in == EOF) {
                                regs[rc] = 0xFFFFFFFF;
                        } else {
                                regs[rc] = (uint32_t)in;
                        }
                        break;
                }

                case 12:
                        // load program
                        um->program_counter = pc;
                        load_program(um, rb, rc);
                        segments = um->segments;
                        pc = um->program_counter;
                        break;

                default:
                        assert(false);
                }
        }
}


 /****** UM_free ****
 *
 * Frees the UM struct.
 *
 * Params:
 *      UM_T um: This is the UM containing the commands and registers that will
 *      be used to run our program.
 *  
 * Return:
 *      nothing
 * 
 * Expects:
 *      UM_T is not null or invalid
 * 
 * Notes:
 *      Will CRE if the UM is Null or invalid 
 *
 ************************/
void UM_free(UM_T *um) 
{
        assert(um != NULL);
        assert(*um != NULL);

        for (uint32_t i = 0; i < (*um)->seg_capacity; i++) {
                if ((*um)->segments[i] != NULL) {
                        Segment_free(&((*um)->segments[i]));
                }
        }

        free((*um)->segments);
        Seq_free(&((*um)->unmapped));

        free(*um);
        *um = NULL;
}




// HELPER FUNCTIONS FOR THE RUN_INSTRUCTIONS LOOP



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