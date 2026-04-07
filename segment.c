/*
 *  segment.c
 *  Kodi Dotterer (hdotte01), James Molloy (jmollo02)
 *  03/3/2026
 *
 *  CS 40 Project 6: um
 *
 *  Implementation of the segment.h file
 * 
 */

#include "segment.h"
#include "assert.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <iso646.h>

// Segment_T Segment_new(uint32_t length);
// void Segment_free(Segment_T *seg);
// uint32_t Segment_length(Segment_T seg);
// uint32_t Segment_get(Segment_T seg, uint32_t index);
// void Segment_put(Segment_T seg, uint32_t index, uint32_t value);
// Segment_T Segment_read_file(FILE *fp);



Segment_T Segment_new(uint32_t length)
{
        Segment_T seg = malloc(sizeof(*seg));
        assert(seg != NULL);

        seg->length = length;
        seg->words = malloc(length * sizeof(uint32_t));
        assert(seg->words != NULL || length == 0);

        for (uint32_t i = 0; i < length; i++) {
                seg->words[i] = 0;
        }

        return seg;
}


 Segment_T Segment_read_file(FILE *fp)
 {
        // check file nullity
        assert(fp != NULL);

        // malloc size seg and check success
        Segment_T seg = malloc(sizeof(*seg));
        assert(seg != NULL);

        // init values of segment_t
        uint32_t cap = 1;
        seg->words = malloc(1 * sizeof(uint32_t));
        assert(seg->words != NULL);
        seg->length = 0;

        // read binary file in 32bit segments
        while(true) {
                int b0 = fgetc(fp);
                if (b0 == EOF) {
                        break;
                }
                int b1 = fgetc(fp);
                int b2 = fgetc(fp);
                int b3 = fgetc(fp);
                assert(b0 != EOF and b1 != EOF and b2 != EOF and b3 != EOF);

                // check capacity for space, if max realloc
                if (cap == seg->length) {
                        cap = cap * 2;
                        seg->words = realloc(seg->words, 
                                                cap * sizeof(uint32_t));
                        assert(seg->words != NULL);
                }

                // create 32bit words in 8bit chunks
                uint32_t word = 0;
                word |= ((uint32_t)b0 << 24);
                word |= ((uint32_t)b1 << 16);
                word |= ((uint32_t)b2 << 8);
                word |= (uint32_t)b3;

                // add words to the segment array
                seg->words[seg->length] = word;
                seg->length++;
        }
        return seg;
 }