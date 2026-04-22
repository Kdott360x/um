Names: James Molloy(jmollo02); Henry Dotterer (hdotte01)

Acknowledgements of help:  We received help from the TA's at office hours. This 
                        included help with conceptuallizing how segments
                        and their potential relationships to sequences when 
                        mapping and unmapping segments. Also covered how 
                        segment sizing and sizing of the segments array could 
                        be done.

Identification of correct implementation: 
        We correctly map and unmap segments by saving the id's of the unmapped
        segments and storing them in a sequence for later use. Our 
        implementation correctly stores the pointers according to the spec
        by casting them first as uintptr_ts.

Incorrect Implementations:
        When initially allocating the array to contain the inital program, we 
        use dynamic sizing by multiplying by 2. This could cause a lot of 
        allocated space that is not used. A better method would be to use stat.

Departures from Design:
The main departues from design are the following.
     - We initially thought that our run function would take in the file that
     would be given to us from the user, and that the segment zero would be 
     created inside of our run UM function. We changed this so that segment 0
     was made before calling run, and our run function only took segment zero 
     as a paramater. 
     - We initially thought that the segment.c interface would deal with
     mapping and unmapping implementation. However, as we gained a better
     understanding of how mapping and unmapping works, we found that it made
     more sense to deal with this functionality in the instructions.c 
     interface. We found that using size and capacity variables was crucial
     for our own segment ID system and our mapping implementation.
     - We initially thought that out segments.c function would be 
     comprised of a lot of different sorting functions... one function to 
     differentiate between the different word structures(load value vs. normal),
     one function to send each normal word structure to it's assigned 
     helper function, and then individual helper functions for every command.
     We eventually only had one sorting function that differentiated between
     word structe, sent commands to the proper helper functions, and performed
     the function of "load value" without a helper function.

 Architecture:

- main.c: 	parse args, load program, call run
     Description: Takes in the arguments, which is going to be solely a file, 
     and then it calls um.run. Very simple driver file that sends most of the 
     work onward to um.c. The only secret it knows is that when the um 
     functions are called, the um runs… does not know many secrets. It 
     uses the um struct to call the main um function that does most of the 
     heavy lifting… no Hanson structures used here. Only interacts with um.c, 
     and additionally the segments.c to create segment zero, where it has no 
     clue how segments are implemented (secret).
- um.c: 		overall machine state and run loop
     Description: Create, manage the UM struct and loop through the segment 
     zero program, feeding each uint32_t word command into instructions.c 
     which will complete the necessary actions. We will have the loop go 
     until the halt command is called, which terminates the program. Each time 
     the loop iterates, the program will be set to segment 0 in case that the 
     contents of this segment changed. The UM struct will contain the 8 
     registers, the program controller pointer, an array of memory segments, a 
     segment capacity AND a segment size tracker, and a program pointer that 
     always points to the start of segment 0. It also keeps track of ids of 
     unused memory segments… These ids are values in the array of addresses 
     for segments that do not hold addresses to segments… they point to null. 
     It knows the secret of how the um works, but it does not know how the 
     individual instructions are performed and differentiated besides sending 
     a word to instructions.c… the same follows for segments… it does not know 
     how the segments actually work under the hood. It interacts with these two
     interfaces without knowledge of the “secrets.” Mapping and unmapping are 
     implemented in instructions, but the capacity and size variables necessary
     for these are kept in the UM.
segment.c: 	create, free, load, store segments
     Description: This module manages the UM’s segments that make up its 
     memory. It is responsible for creating, freeing, and accessing memory 
     segments. We are able to create memory segments given a length… it 
     mallocs an array of 32 bit words and returns the address, setting all 
     the values initially to zero. Each segment is represented as a 
     dynamically allocated array of 32-bit words together with its length. 
     This module provides the basic memory operations needed by the emulator, 
     including creating a new segment, freeing an existing segment, loading a 
     word/value from a segment(get), and storing a word into a segment(put). 
     We also have a special function that takes in a file, and using a capacity
      and size variable architecture (basic arraylist logic), creates an array
       that can hold all the commands… This will be used for segment zero 
       mainly. Our segment struct will have the length of the array and the 
       actual array. NO INTERACTION WITH OTHER MODULES. It is only used by 
       other modules… no secrets are kept from segment.c!!!
instructions.c: 	Execute all operations given solely a word
     Description: This part of the code will take in a word as input. It will
     distinguish between normal commands and the loadVal command. It will then 
     use the “switch case statement” structure in C to send the appropriate 
     amount of registers to the appropriate function for each of the 14 
     instructions. Its functions will need a pointer to the UM struct… it 
     will not know the secret of how the UM stores memory, it will just know 
     how to use the registers and memory to perform instructions. It keeps 
     the secret from UM of how instructions are decoded and performed. It 
     interacts with both the UM and segment interfaces, because it needs to 
     create new segments and it needs to use values from the given um struct 
     in the parameters. Mapping and unmapping is mainly dealt with here.
       
     

– Explains how long it takes your UM to execute 50 million instructions, and 
how you know


Our UM executes 50 million instructions in about 0.59 seconds. We
measured this by running cpu-limited 120 /usr/bin/time ./um um-lab/loop50m.um >
 /dev/null. We know it executes exactly 50,000,000 instructions because
we built the test as a fixed loop with a known count. There are 3 setup
instructions before the loop, 4 instructions in each loop iteration, and
1 final halt instruction, so the total number of instructions is 4N + 4.
We set N to 12,499,999, so 4(12,499,999) + 4 = 50,000,000.


– Mentions each UM unit test (from UMTESTS) by name, explaining what each one 
tests and how


– How many hours you have spent analyzing the assignment: 3
– How many hours you have spent preparing your design: 11
– How many hours you have spent solving the problems after your analysis: 11


Descriptions of the UMTESTS

halt.um
Tests the Halt instruction alone. The program immediately halts and
produces no output.


halt-verbose.um
Tests Halt more. The first instruction is Halt, so correct
behavior is still no output. If Halt were broken, the later
instructions would print "Bad!\n", which helps detect a failure to
stop execution.


add-halt.um
Tests Add instruction by performing an addition, then halting. 
This test doesn’t check printed output, but it helps make sure that 
the instruction stream is formed correctly and that Add can 
execute without crashing.


print-six.um
Tests Load Value, Add, Output, Halt. Program loads 48
into one register, 6 into another, adds them to produce the ASCII
value for '6', outputs that character, and halts. ‘6’ = 54 ASCII


input-output.um
Tests Input, Output, Halt. Makes sure input and output are both Q.


cmov-zero.um
Tests Conditional Move when condition register contains 0.
Program loads 'A' and 'B' in registers, uses zero condition
register, outputs the destination register. B/c the
condition is zero, the move shouldn’t happen, so expected output
is "A".


cmov-nonzero.um
Tests Conditional Move when condition register is !=0. The
program loads 'A' and 'B' into registers, uses nonzero condition
register, performs conditional move, outputs the destination
register. Because nonzero, the move should happen, so
expected output is "B".


mult-six.um
Tests Multiplication, Load Value, Add, Output. The program
multiplies 3 by 2 to get 6, adds 48 to convert it to the ASCII code
for '6', outputs that character, and halts. Expected output is "6".
Also known as 54 in ascii.


div-four.um
Tests Division, Load Value, Add, Output. The program divides
8 / 2 = 4, adds 48 to convert it to the ascii code for '4',
outputs that character, and halts. Expected output is "4".


nand-zero.um
Tests Bitwise NAND, Output, Halt. The program chooses values so
that low byte of NAND result is 48, which is the ascii code
for '0'. It outputs this character. Expected output is "0".


seg-store-load-zero.um
Tests seg store and seg load on seg 0. Program stores 'Z' 
into already-used location in segment 0,then loads value 
back from that same location, outputs it. Expected output "Z".


map-store-load-unmap.um
Tests map seg, seg store, seg load, unmap seg, output, halt. 
Program maps a new segment of length 1, stores 'M' into offset 
0 of that mapped segment, loads the value back, outputs it, 
unmaps the segment, and halts. Expected output is "M".


loadval-six.um
 Tests load value, output, and halt. Program loads the value 54,
 which is the ASCII code for '6', into a register, outputs it,
 and then halts. Expected output is "6".