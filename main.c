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

        Segment_T segment_zero = Segment_read_file(fp);
        fclose(fp);
        if (segment_zero == NULL) {
                fprintf(stderr, "Failed to load program: %s\n", argv[1]);
                return EXIT_FAILURE;
        }
        // run the UM_run command with the segmentZero
        // NOTE: do we need to free segment zero?  


        // printf("program loaded successfully\n");
        // printf("length: %" PRIu32 "\n", program->length);

        // for (uint32_t i = 0; i < program->length; i++) {
        //         printf("%08" PRIx32 "\n", program->words[i]);
        // }


        UM_T um = UM_new(segment_zero);

        UM_run(um);
        UM_free(&um);

        return EXIT_SUCCESS;
}
