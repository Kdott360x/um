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
#include "instructions.h"



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

        // set the program pointer to seg_zero
        um->program = seg_zero;

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
        assert(um->program != NULL);

        bool program_is_running = true;

        while (program_is_running) {
                uint32_t curr_instruction =
                        Segment_get(um->program, um->program_counter);

                um->program_counter++;

                program_is_running = run_instruction(um, curr_instruction);

                um->program = um->segments[0];
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