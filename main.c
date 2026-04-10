/*
 *  main.c
 *  Kodi Dotterer (hdotte01), James Molloy (jmollo02)
 *  03/3/2026
 *
 *  CS 40 Project 6: um
 *
 *  Takes in the arguments, which is going to be solely a file, 
 *  and then it calls um.run. Very simple driver file that sends 
 *  most of the work onward to um.c

 */
#include <stdio.h>
#include <stdlib.h>
#include "segment.h"
#include <stdint.h>
#include <inttypes.h>
#include "um.h"

/****** main ********
 *
 * Parses the input args, stores given file as segment0,
 * creates the Universal Machine using segment0, runs the program, and frees all
 * allocated memory for the UM_T before exiting.
 *
 * Params:
 *      int argc: the number of command-line arguments
 *      char *argv[]: the array of command-line argument strings
 *
 * Return:
 *      Returns EXIT_SUCCESS if the program is run successfully.
 *      Returns EXIT_FAILURE if the command line is invalid, if file
 *      cannot be opened, or if program cannot be loaded.
 *
 * Expects:
 *      The program is called with exactly one file argument naming a
 *      valid UM binary.
 *
 * Notes:
 *      Prints an error message to stderr and exits with EXIT_FAILURE if
 *      expectations are not met.
 *
 ************************/
int main(int argc, char *argv[])
{
        if (argc != 2) {
                fprintf(stderr, "Usage: ./um program.um\n");
                return EXIT_FAILURE;
        }

        FILE *fp = fopen(argv[1], "rb");
        if (fp == NULL) {
                fprintf(stderr, "Could not open file: %s\n", argv[1]);
                return EXIT_FAILURE;
        }

        // set segment 0
        Segment_T segment_zero = Segment_read_file(fp);
        fclose(fp);
        if (segment_zero == NULL) {
                fprintf(stderr, "Failed to load program: %s\n", argv[1]);
                return EXIT_FAILURE;
        }

        // create the UM
        UM_T um = UM_new(segment_zero);

        // Run it then free it
        UM_run(um);
        UM_free(&um);

        return EXIT_SUCCESS;
}
