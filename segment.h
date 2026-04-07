/*
 *  segment.h
 *  Kodi Dotterer (hdotte01), James Molloy (jmollo02)
 *  03/3/2026
 *
 *  CS 40 Project 6: um
 *
 *  This module manages the UM’s segmented memory. It is responsible for 
 *  creating, freeing, and accessing memory segments, as well as reusing 
 *  unmapped segment IDs. Each segment is represented as a dynamically allocated
 *  array of 32-bit words together with its length. Segment 0 holds the 
 *  currently executing program, while all other mapped segments act as the UM’s
 *  general memory. This module provides the basic memory operations needed by 
 *  the emulator, including mapping a new segment, unmapping an existing 
 *  segment, loading a word from a segment, storing a word into a segment, and 
 *  duplicating a segment for the load-program instruction.
 * 
 */

#ifndef SEGMENTS_H
#define SEGMENTS_H

#include <stdio.h>
#include <stdint.h>

/* Segment_T
 * Representation: a pointer to a struct containing a uint32_t length
 *                 and a uint32_t *words array.
 * Meaning: represents one mapped UM memory segment, where words points
 *          to a dynamically allocated sequence of 32-bit words and
 *          length gives the number of words in that segment.
 */
typedef struct Segment {
    uint32_t length;
    uint32_t *words;
} *Segment_T;

Segment_T Segment_read_file(FILE *fp);
Segment_T Segment_new(uint32_t length);
void Segment_free(Segment_T *seg);
uint32_t Segment_length(Segment_T seg);
uint32_t Segment_get(Segment_T seg, uint32_t index);
void Segment_put(Segment_T seg, uint32_t index, uint32_t value);
Segment_T Segment_read_file(FILE *fp);

#endif