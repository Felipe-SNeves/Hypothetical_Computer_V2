#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Opcodes
#define HLT 0x0A
#define SHW 0x0B
#define MOV 0x2A
#define LDA 0x2B
#define STA 0x2C
#define ADD 0x1A
#define SUB 0x1B
#define MUL 0x1C
#define DIV 0x1D
#define CMP 0x3A
#define CMZ 0x3B
#define CMS 0x3C
#define JMP 0x4A
#define JMZ 0x4B
#define JMS 0x4C
#define PSH 0x5A
#define POP 0x5B
#define WRT 0x6A

// General registers
#define AX 0xF0
#define BX 0xF1
#define CX 0xF2
#define DX 0xF3

int main () {

    FILE * program = fopen ("programa.f", "wb+");
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
    uint16_t * parser = programa;

    do {
        fwrite (parser, 1, 1, program);
        parser++;
    } while (*parser);

    return 0;
}
