/*
 *  instructions.h
 *  Kodi Dotterer (hdotte01), James Molloy (jmollo02)
 *  03/3/2026
 *
 *  CS 40 Project 6: um
 *
 * This part of the code will take in a word as input. It will distinguish
 * between normal commands and the loadVal command. It will then use the 
 * “switch case statement” structure in C to send the appropriate amount of 
 * registers to the appropriate function for each of the 14 instructions. Its 
 * functions will need a pointer to the registers and a pointer to our array of 
 * segmented memory.
 * 
 */

#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <stdint.h>
#include <stdbool.h>
#include "um.h"

bool run_instruction(UM_T um, uint32_t instruction);

#endif