#include <inttypes.h>
#include <stdlib.h>
#include <string>
#include <iostream>
using namespace std;

void hexDump (char*, void*, int);

static int const REG_LEN = 64;
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
    int registers [REG_LEN];
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
    int32_t low_sign_ext(uint32_t, size_t);
    uint32_t cat(uint32_t, uint32_t, size_t);
    int32_t sign_ext(uint32_t, size_t);
};

