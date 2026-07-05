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
    printf("writing address %x\n", addr);
    MEM_BUF[addr] = data;
}

uint8_t mem_read(uint16_t addr) {
    printf("reading address %x\n", addr);
    return MEM_BUF[addr];
}

int main() {
    // writes a simple program
    // based on Intel 8080 instruction set
    // see: https://en.wikipedia.org/wiki/Intel_8080
    const uint8_t program[] = {
        0x3E, 0x06, // MVI A, 06H
        0x06, 0x07, // MVI B, 07H
        0x80, // ADD B
        0x06, 0x0A, // MVI B, 10H
        0x80, // ADD B
        0x32, 0x00, 0x02, // STA 0200H
        0x76, // HTL
    };
    for (size_t i = 0; i < sizeof(program); i++) mem_write(i, program[i]);

    // reads the program with PC (program counter) and run
    uint16_t PC = 0x0000;
    uint8_t A_REG = 0x00;
    uint8_t B_REG = 0x00;
    uint8_t opcode;
    
    uint8_t running = 1;
    while (running) {
        opcode = mem_read(PC++);
        
        switch (opcode) {
            case 0x3E: // MVI A
                A_REG = mem_read(PC++);
                break;
            case 0x06: // MVI B
                B_REG = mem_read(PC++);
                break;
            case 0x80: // ADD B
                A_REG = A_REG + B_REG;
                break;
            case 0x32:{ // STA
                uint8_t low = mem_read(PC++);
                uint8_t high = mem_read(PC++);
                mem_write((uint16_t)((high << 8) | low), A_REG);
                break;
            }
            case 0x76: // HTL
                running = 0;
                break;
        }
    }
    
    printf("A_REG: 0x%x\n", A_REG);
    printf("B_REG: 0x%x\n", B_REG);
    printf("0200H in MEM_BUF: 0x%x\n", mem_read(0x200));
    printf("program ended.\n");
    
    return 0;
}