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
        (void) um;
        bool program_is_running = true;
        while (program_is_running) {
                // find the value that the program counter points to
                uint32_t curr_instruction = segment_get(um->segments[0], 
                                                um->program_counter);

                // pass this value (u_int32) into our instruction function
                program_is_running = run_instruction(um, curr_instruction);

                // increment the program counter
                um->program_counter++;
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
// void UM_free(UM_T um) 
// {
//         assert(um != NULL);
//         um->program = NULL;

//         for (int i = 0; i < 8; i++) {
//                 regs[i] = 0;
//         }

//         for (int i = 0; i < (um->segments.size()); i++) {
//                 Segment_free(*(um->segments[i]));
//                 *(um->segments[i]) = NULL;
//         }
//         free(um->segments);

//         Seq_free(um->unmapped);	

//         free(*um);	
//         um = NULL;           			
// }