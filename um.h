/*
 *  um.h
 *  Kodi Dotterer (hdotte01), James Molloy (jmollo02)
 *  03/3/2026
 *
 *  CS 40 Project 6: um
 *
 *  Create, manage the UM struct and loop through the segment zero program, 
 *  feeding each uint32_t word command into instructions.c which will complete 
 *  the necessary actions. We will have the loop go until the halt command is 
 *  called, in which terminates the program.
 * 
 */

#ifndef UM_H
#define UM_H

#include "segment.h"
#include "assert.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <iso646.h>
#include "seq.h"


typedef struct UM {
        uint32_t regs[8];			// 8 registers
        uint32_t program_counter;    		// program controller

        Segment_T *segments;		        // mapped segments
        uint32_t seg_size;		
        uint32_t seg_capacity;		

        Seq_T unmapped;		                // unmapped 			

} *UM_T;


UM_T UM_new(Segment_T segmentZero);
void UM_run(UM_T um);
void UM_free(UM_T *um);

#endif