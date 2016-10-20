#include <iostream>
using namespace std;
#include <string.h>
#include <stdio.h>
#include "machine.h"
#include "opcode.h"

#define LOG(opcode) { printf("%s:\t", opcode); machine.command_dump(); }

int main (int argc, char *argv[])
{
    if (argc < 2) {
        cout << argv[0] << " {binary} [-d]" << endl;
        return 1;
    }
    bool debug = false;
    if (argc > 2) {
        debug = true;
    }
    
    Machine machine = Machine::getInstance(argv[1]);
    
    while (true) {
        int opcode = machine.command_opcode();
        if (opcode == ADD) {
            if (debug) LOG("ADD")
            machine.reg[machine.command_shift_unsigned(27, 32)] = machine.reg[machine.command_operand1()] + machine.reg[machine.command_operand2()];
            machine.incrementpc();
        } else if (opcode == LDIL) {
            if (debug) LOG("LDIL")
            int answer;
            int first = machine.command_shift_signed(11, 16) << 13;
            int second = machine.command_shift_unsigned(18, 31);
            if (first < 0)
                answer = first - second;
            else
                answer = first + second;
            machine.reg[machine.command_operand1()] = answer;
            machine.incrementpc();
        } else if (opcode == LDO) {
            if (debug) LOG("LDO")
            machine.reg[machine.command_operand2()] = machine.reg[machine.command_operand1()] + machine.command_operand3();
            machine.incrementpc();
        } else if (opcode == LDW) {
            if (debug) LOG("LDW")
            machine.reg[machine.command_operand2()] = machine.getint(machine.reg[machine.command_operand1()] + machine.command_operand3());
            machine.incrementpc();
        } else if (opcode == STW) {
            if (debug) LOG("STW")
            machine.setint(machine.reg[machine.command_operand1()] + machine.command_operand3(), machine.reg[machine.command_operand2()]);
            machine.incrementpc();
        } else if (opcode == DEP) {
            if (debug) LOG("DEP")
            uint32_t icode = machine.command_shift_unsigned(19, 22);
            uint32_t len = 32 - machine.command_shift_unsigned(27, 32);
            uint32_t p = 31 - machine.command_shift_unsigned(22, 27);
            uint32_t condition = machine.command_shift_unsigned(16, 19);
            printf("icode: %d, len: %d, p: %d, condition: %d\n", icode, len, p, condition);
            if (icode == 2) {
                if (p >= len-1) {
                    // GR[t] ← cat(0{0..p-len},GR[r]{32-len..31},0{p+1..31});
                    //if (cond_satisfied) PSW[N] ← 1;
                }
            } else if (icode == 7) { // DEPOSIT IMMEDIATE pg. 219
                int32_t ival = machine.low_sign_ext(machine.command_operand2(), 5);
                if (p >= len-1) {
                    uint32_t t = machine.command_operand1();
                    machine.reg[machine.command_operand1()] = ((machine.reg[t] << p-len) >> p-len) | ((ival << 32-len) >> 32-len) | ((machine.reg[t] << p+1) >> p+1);
                    // if (cond_satisfied) PSW[N] ← 1;
                } else {
                    LOG("UNDEF")
                    exit(-1);
                }
            } else {
                printf("Unrecognized icode %d at instruction 0x%02x: ", icode, machine.reg[machine.pc()]);
                machine.command_dump();
                exit(-1);
            }
        } else {
            printf("Unrecognized opcode %d at instruction 0x%02x: ", opcode, machine.reg[machine.pc()]);
            machine.command_dump();
            exit(-1);
        }
        /* This isn't working right now
        // Check for Stack Overflow (local then global)
        if (machine.reg[machine.sl] > machine.reg[machine.sp] || machine.sl > machine.reg[machine.sp]) {
            cout << "Stack overflow";
            throw 10;
        } */
    }
    
    return 0;
}
