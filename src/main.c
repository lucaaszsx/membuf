#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

/*
 * memory unit stores binary data in groups of bits called words
 * in the memory, there is 2^l locations, that starts from 0 to 2^l - 1
 * N = 2^l, where N is the number of bytes of the memory and "l" is the number of address buses
 * 
 */

uint8_t MEM_BUF[64 * 1024]; // 64KB

void mem_write(uint16_t addr, uint8_t data) {
    MEM_BUF[addr] = data;
}

uint8_t mem_read(uint16_t addr) {
    return MEM_BUF[addr];
}

int main() {
    // writes a simple program
    // based on Intel 8080 instruction set
    // see: https://en.wikipedia.org/wiki/Intel_8080
    const uint8_t program[] = {
        0x3E, 0x05, // MVI A, 05H
        0x06, 0x03, // MVI B, 03H
        0x80, // ADD B
        0x32, 0x00, 0x02, // STA 0200H
        0x76 // HTL
    };
    for (size_t i = 0; i < sizeof(program); i++) mem_write(i, program[i]);

    // reads the program with PC (program counter)
    uint16_t PC = 0x0000;
    uint8_t opcode;
    
    while ((opcode = mem_read(PC++))) printf("reading opcode: %x\n", opcode);
    printf("program ended.\n");
    
    return 0;
}