#include <inttypes.h>
#include <stdlib.h>
#include <string>
#include <iostream>
using namespace std;

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
static int const MEM_LEN = 5242880;
static int const BLK_LEN = 400;
static int const SM_BLK_LEN = 20;

class Machine
{
private:
    Machine();
    static string execname;
public:
    unsigned char memory [MEM_LEN];
    int start_addr;

    // These need to be fixed
    int sl = REG_LEN - 2;
    int sb = REG_LEN - 4;
    int fp = REG_LEN - 5;

    /* Special register names */
    int pc = 33; // pcoqh
    int pcoqt = 35; // Next instruction
    int ret0 = 28;
    int sp = 30;

    static Machine& getInstance(string);
    uint32_t registers [REG_LEN];
    int command_shift_unsigned(int, int);
    int command_shift_signed(int, int);
    int command_opcode();
    int command_operand1();
    int command_operand2();
    int command_operand3();
    void incrementpc();
    int getint(int);
    void setint(int, int);
    void command_dump();
    int bit_index(uint64_t, int, int);
    int bit_index(int64_t, int, int);
    int32_t low_sign_ext(int32_t, size_t);
    int32_t sign_ext(int32_t, size_t);
};

