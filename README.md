---
## Hipotetical Computer no. 2

#### Overview

This is my second study about computer organization and their respective architecture. In this version, I improved the hypothetical computer created on the first study. Unfortunately, I deleted the first code when I was trying to write a readme file for the repository. To put both version in perspective, I'll briefly describe how the first machine was implemented.

### The first version

The first version was implemented using the C programming language, and it was much more like a calculator than a Turing's machine. It had only two general purpose registers (AX and BX), each one with 16 bits, and an especific purpose register called AUX. It's instruction set architecture had only seven statments: ADD, SUB, MUL, DIV, SHW, HLT and MOV. In general, it didn't have a full fetch-decode-execute cycle, since it didn't have a primary memory. So, this is the reason why it's difficult to call the machine a "computer" (what, in fact, it wasn't). It's important to mention the absent of the RAM, since it implies in the absent of other components such as the implementation of byte code to represent programs, in the presence of jump or memory access statments and even conditional instructions. Some of these problems were solved on the second version, which is very similiar to a primitive Turing's machine.

### The second version

The second machine, altought it's built over the first one, it didn't emerge from any process of refactoring, in contrast, it emerged from a process of rewrite of the code starting from scratch.

Now I'll describe the new features implemented on this version. Firstly, more registers were created: it has four general purpose registers (AX, BX, CX and DX, each one with 16 bits, divided into MSB and LSB) and four especific purpose registers (SP, IP, BP and EFLAGS). The EFLAGS register is composed by two bits, where the first one represents the zero flag, and the second represents the sign flag. The registers SP, BP and IP are pointers of eight bits address to the, now implemented, primary memory. SP, stands for stack pointer (the names were inspired in the x86 architecture), and it points to the top of the stack. In addition, BP (base pointer) points to the bottom of the stack and the IP (instruction pointer, it has the behavior of a PC register) points to the current statment which will be executed. It's relevant to mention that the machine doesn't has any types of segmentation registers or pipeline suport.

The primary memory consists in a 64 KiB RAM (unfortunately, it can not be fully addressed, since the especific purpose registers points to only one byte of addressing. To point to all the memory area they had to point to two bytes and not to only one byte). Again, the fetch-decode-execute cycle isn't fully implemented, however, it's steps is much more visible and defined. Moreover, the programs must be coded in byte codes to be executed, which allowed a huge jump in the size and quality of the instruction set architecture.

Now ISA has eighteen instructions, which can be accounted with the use variations, resulting in 83 variations of the statments. The ISA has memory access statments (LDA and STA), conditional and inconditional jumps statments (JMP, JMZ and JMS). The eighteen instructions are described in sequence (for a full complete table of variations, consult the .ods file):

| Assembly |  Opcode | Action
|---------|----------|---------
|  HLT  | 0x0A | Halt the system
| SHW | 0x0B | Show the register's states
| MOV | 0x2A | Move data
| LDA | 0x2B | Write a data from the memory into a register
| STA | 0x2C | Write a data from the register into the memory
| ADD | 0x1A | Add two values
| SUB | 0x1B | Subtract two values
| MUL | 0x1C | Multiplies two values
| DIV | 0x1D | Divides two values
| CMP | 0x3A | Compares two values
| CMZ | 0x3B | Checks if the value is zero
| CMS | 0x3C | Checks if the value is negative
| JMP | 0x4A | Jumps inconditionally
| JMZ | 0x4B | Jumps if the value is zero
| JMS | 0x4C | Jump if the value is a negative number
| PSH | 0x5A | Push into stack
| POP | 0x5B | Pop from stack
| WRT | 0x6A | Writes a character into the stdout file descriptor of the system

The programs, always in bytecode, are loaded into the 0x3E8 address of the memory. The IP register reads every statement in a finite cycle. Since I didn't write an assembler, it's mandatory to write a program in bytecode and that can be done with the auxiliary code "write_program.c". The code on "write_program.c" helps to write the program, because it creates a binary file, with the bytecodes, and this file can be loaded into the memory. Since it's very difficult to write a code using bytecodes, I developed an app, using React Native, which permits to code, line per line, a program in assembly. The app works as an assembler, it assembles and sends the program, to an endpoint, wrote using Node.js, which executes the machine with the program translated.

You can find the app code on the "interface_hypothetical_computer_V2" repository. The endpoint can be found at "backend_interface_hypothetical_computer_V2" repository.

### For the future

I believe this version can be considered a kind of Turing's machine, since it can write, read and take decisions over a "tape". However, when I finished this project, I figure out some insights which could improve this version, like solve the addressing problem of the specific purpose registers, create memory segmentation registers, implement a kind of pipeline for the fetch step, etc. 

In conclusion, the next version will have some of these features (I'm thinking about creating DI and SI registers and to move from 16 bits to 32 bits architecture, maybe I could implement indirect addressing and a real assembler too). I believe this serie of studies will remain for a while, since my main goal is to create a real CPU using only logic gates, and, some day it could be implemented using integrated circuits or some kind of FPGA).

### How to run

To run the machine, first you need to compile it (it only runs in *nix systems). To compile you can run the following command on the terminal:
```make all```
This command will produce an ELF file, called machine, which you can execute with the command:
```./machine file_of_your_program.f```
The ```file_of_your_program.f``` is the file in which you created the programming which will be executed in the machine. To help you create the program file you can you the ```write_program.c``` file. You can write your code in the array which represents the byte code as follow:

```
uint16_t programa[100] = {
        LDA, BX, 0x01, 0x64,
        MOV, AX, BX,
        SUB, BX, AX,
        SUB, BX, AX,
        MOV, AX, BX,
        WRT, 'H',
        WRT, 'E',
        WRT, 'L',
        WRT, 'L',
        WRT, 'O',
        WRT, ' ',
        WRT, 'W',
        WRT, 'O',
        WRT, 'R',
        WRT, 'L',
        WRT, 'D',
        WRT, '!',
        WRT, '\n',
        ADD, AX, 0x01,
        JMS, 0x1F,
        HLT
    };
```
In conclusion you can compile it: 
```make write_program```
And finally, to create the program file you just need to run:
```./write_program```

You can use the app made with React Native and Expo to write your program if you prefer. To do this, go to their respective repositories (interface_hypothetical_computer_V2 and backend_interface_hypothetical_computer_V2) and see the instructions of how to set up they.
