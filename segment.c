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


// void Segment_put(Segment_T seg, uint32_t index, uint32_t value);

void Segment_put(Segment_T seg, uint32_t index, uint32_t value)
{
        assert(seg != NULL);
        assert(index < seg->length);

        seg->words[index] = value;
}


/****** Segment_new ****
 *
 * Creates a new segment containing the given number of 32-bit words,
 * with every word initialized to 0.
 *
 * Params:
 *      uint32_t length: number of words the segment should contain
 *  
 * Return:
 *      Segment_T seg: a newly allocated segment whose length field is set
 *      to length and whose words array has length elements, all set to 0
 * 
 * Expects:
 *      uint32_t length is a valid length when converted to int.
 * 
 * Notes:
 *      Allocates memory for both the segment struct itself and its words
 *      array.
 *
 *      If length is 0, the segment still exists, but its words array does
 *      not need to store any elements.
 *
 *      This function is useful for creating newly mapped UM segments, since
 *      the UM spec requires that all words in a new segment begin as 0.
 *
 ************************/
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

/****** Segment_read_file ****
 *
 * Takes in the input file and parses it into an array of uint32_t commands
 * stored in the form of a segment_T struct that contains the length of the 
 * wordsd array and also a pointer to the beginning of that words array.
 *
 * Params:
 *      FILE *fp: pointer to the input file
 *  
 * Return:
 *      Segment_T seg: this contians the pointer to an array of words and an
 *                      int that represents the length of the array.
 * 
 * Expects:
 *      Input file is the correct input file and contains a number of bits 
 *      divisible by 32. 
 * 
 * Notes:
 *      Will CRE if EOF is not adjacent to a multiple of 32.
 *
 ************************/
 Segment_T Segment_read_file(FILE *fp)
 {
        // check file nullity
        assert(fp != NULL);

        // malloc size seg and check success
        Segment_T seg = malloc(sizeof(*seg));
        assert(seg != NULL);

        // init values of segment_t
        uint32_t cap = 1;
        seg->words = malloc(cap * sizeof(uint32_t));
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

/****** Segment_length ********
 *
 * Returns the number of words contained in the given segment.
 *
 * Params:
 *      Segment_T seg: the segment whose length is being queried
 *
 * Return:
 *      uint32_t: the number of words in the segment
 *
 * Notes:
 *      The segment must not be NULL.
 *
 ************************/
uint32_t Segment_length(Segment_T seg)
{
        assert(seg != NULL);
        return seg->length;
}

/****** Segment_get ********
 *
 * Return the value held within the given segment at the given index.
 *
 * Params:
 *      Segment_T *seg: address of the segment
 *      uint32_t index: the index of the value we are looking to return
 *
 * Return:
 *      uint32_t which is the word we are indexing for.
 *
 * Expects:
 *       The given index is within range of the words array. 
 *      Expects seg is not null and is a valid Segment_T struct.
 * 
 * Notes: 
 * 
 *       Will CRE if segment is null, if index is not within range.
 *
 ************************/
uint32_t Segment_get(Segment_T seg, uint32_t index)
{
        assert(seg != NULL);
        assert(index < seg->length);
        return seg->words[index];
}

/****** Segment_free ********
 *
 * Frees all memory associated with a segment and sets the caller's
 * pointer to NULL.
 *
 * Params:
 *      Segment_T *seg: address of the segment pointer to free
 *
 * Return:
 *      None
 *
 * Notes:
 *      Frees both the words array inside the segment and the segment
 *      struct itself.
 *
 *      After freeing, *seg is set to NULL to avoid leaving a dangling
 *      pointer.
 *
 ************************/
void Segment_free(Segment_T *seg)
{
        assert(seg != NULL);
        assert(*seg != NULL);

        free((*seg)->words);
        free(*seg);
        *seg = NULL;
}