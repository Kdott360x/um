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