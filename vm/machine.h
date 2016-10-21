#include <inttypes.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <cmath>
#include <string>
#include <iostream>
#include <memory>
using namespace std;
#include "exceptions.h"
#include "opcode.h"

void hexDump (char*, void*, int);

/* http://www.robelle.com/smugbook/register.html
R0  =   bit bucket and source of zero value
R1  =   target of ADDIL (Add Immediate Literal)
R2  =   RP Return Pointer where BL places address and where BV gets it
R23 =   fourth parameter of a procedure call
R24 =   third parameter of a procedure call
R25 =   second parameter of a procedure call
R26 =   first parameter of a procedure call
R27 =   DP Data Pointer to base of global data
R28-29 = function result in R28 if 32-bits, both if 64-bits
R30 =   SP Stack Pointer to parameters and exit data
R31 =   receives target branch address in BLE instruction
*/
static int const REG_LEN = 32;
static int const SP_REG_LEN = 8;
static int const BLK_LEN = 400;
static int const SM_BLK_LEN = 20;
static int const STACK_HEAP_LEN = 5242880;

class Machine
{
private:
    Machine();
    static string execname;
    uint64_t pcoqh = 0; // Program Counter
    uint64_t pcoqt = 0; // Next instruction
public:
    uint8_t *memory;
    int start_addr;

    // These need to be fixed
    //int sl = REG_LEN - 2;
    //int sb = REG_LEN - 4;
    //int fp = REG_LEN - 5;
    uint64_t sb;

    /* Special register names */
    int sp = 30;

    static Machine& getInstance(string);
    uint32_t reg[REG_LEN];
    uint32_t sp_reg[SP_REG_LEN];
    uint32_t command_shift_unsigned(int, int);
    int command_shift_signed(int, int);
    uint8_t command_opcode();
    uint8_t command_operand1();
    uint8_t command_operand2();
    int command_operand3();
    void incrementpc();
    uint32_t getint(int);
    void setint(int, int);
    void command_dump();
    uint32_t bit_index(uint32_t, int, int);
    int32_t low_sign_ext(int32_t, size_t);
    int32_t sign_ext(int32_t, size_t);
    uint64_t pc();
};

#define LOG(opcode) { printf("%s:\t", opcode); machine.command_dump(); }

void run(string binary, bool debug);

