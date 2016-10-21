#include "machine.h"
#include <sys/stat.h>

string Machine::execname;

Machine& Machine::getInstance(string filename) {
    Machine::execname = filename;
    static Machine instance;
    return instance;
}

Machine::Machine()
{
    // Load the file into memory and set start, stack limit, and base
    FILE *exe;
    const char * c_filename = Machine::execname.c_str();
    struct stat finfo;
    if (stat(c_filename, &finfo) != 0) {
        throw ExeNotFound();
    }
    unsigned int mem_len = finfo.st_size + STACK_HEAP_LEN;
    memory = (uint8_t*)malloc(mem_len);

    exe = fopen(c_filename, "r");

    int i = 0;
    unsigned char buff [168];
    int result = getc(exe);
    while (result != EOF && i < 168) {
        buff[i] = (unsigned char) result;
        result = getc(exe);
        i++;
    }
    /* Get the entry point */
    unsigned char *start = &buff[164];
    pcoqh = (start[0] << 24) + (start[1] << 16) + (start[2] << 8) + start[3];

    /* Get the text memory offset */
    unsigned char *offset = &buff[140];
    int ofs = (offset[0] << 24) + (offset[1] << 16) + (offset[2] << 8) + offset[3];
    while (result != EOF && i < ofs) {
        result = getc(exe);
        i++;
    }

    i = 0;
    while (result != EOF) {
        memory[i] = (unsigned char) result;
        result = getc(exe);
        i++;
        if (i >= mem_len) {
            cout << "Stack Overflow while loading binary into memory!";
            throw 10;
        }
    }
    
    fclose(exe);

    pcoqt = pcoqh+4;
    start_addr = pcoqh;
    int stack_base = mem_len - 4;
    
    //reg[sl] = ((stack_base-i)/2)+i; // stack_limit
    reg[sp] = stack_base;
    sb = stack_base;
}

int Machine::command_shift_unsigned(int s_bit, int e_bit)
{
    return bit_index((uint64_t)getint(pcoqh), s_bit, e_bit);
}

int Machine::command_shift_signed(int s_bit, int e_bit)
{
    return bit_index((int64_t)getint(pcoqh), s_bit, e_bit);
}

int Machine::bit_index(uint64_t command, int s_bit, int e_bit)
{
    s_bit = s_bit + 32;
    e_bit = 32 - e_bit;
    command = command << s_bit;
    command = command >> e_bit+s_bit;
    return command;
}

int Machine::bit_index(int64_t command, int s_bit, int e_bit)
{
    s_bit = s_bit + 32;
    e_bit = 32 - e_bit;
    command = command << s_bit;
    command = command >> e_bit+s_bit;
    return command;
}

uint8_t Machine::command_opcode()
{
    return command_shift_unsigned(0, 6);
}

uint8_t Machine::command_operand1()
{
    return command_shift_unsigned(6, 11);
}

uint8_t Machine::command_operand2()
{
    return command_shift_unsigned(11, 16);
}

int Machine::command_operand3()
{
    return (int) command_shift_signed(18, 31);
}

void Machine::incrementpc()
{
    pcoqh += 4;
    pcoqt += 4;
    /* Check for stack overflow */
    if (reg[sp] < sb-(STACK_HEAP_LEN/2))
        throw StackOverflow();
}

int Machine::getint(int index)
{
    return (memory[index] << 24) + (memory[index+1] << 16) + (memory[index+2] << 8) + memory[index+3];
}

void Machine::setint(int index, int data)
{
    int shift = 24;
    for (int i = 0; i < 4; i++) {
        memory[index+i] = data >> shift;
        shift -= 8;
    }
}

int32_t Machine::sign_ext(int32_t x, size_t len)
{
    /* Bit shift left so that our sign is in the far left bit, then
     * bit shift back to the right to sign extend the integer */
    return (x << 32-len) >> 32-len;
}

int32_t Machine::low_sign_ext(int32_t x, size_t len)
{
    /* Remove the rightmost bit, then sign extend to the left assuming
     * the left most bit is len-1 */
    return sign_ext(x >> 1, len-1);
}

uint64_t Machine::pc()
{
    return pcoqh;
}

void print_binary(unsigned char);

void Machine::command_dump()
{
    for (int i = 0; i < 4; i++)
        print_binary(memory[pcoqh+i]);
    cout << endl;
}

void print_binary(unsigned char c)
{
    unsigned char i1 = (1 << (sizeof(c)*8-1));
    for(; i1; i1 >>= 1)
        printf("%d",(c&i1)!=0);
}

/* Testing code */
void hexDump (char *desc, void *addr, int len) {
    int i;
    unsigned char buff[17];
    unsigned char *pc = (unsigned char*)addr;

    // Output description if given.
    if (desc != NULL)
        printf ("%s:\n", desc);

    // Process every byte in the data.
    for (i = 0; i < len; i++) {
        // Multiple of 16 means new line (with line offset).

        if ((i % 16) == 0) {
            // Just don't print ASCII for the zeroth line.
            if (i != 0)
                printf ("  %s\n", buff);

            // Output the offset.
            printf ("  %04x ", i);
        }

        // Now the hex code for the specific character.
        printf (" %02x", pc[i]);

        // And store a printable ASCII character for later.
        if ((pc[i] < 0x20) || (pc[i] > 0x7e))
            buff[i % 16] = '.';
        else
            buff[i % 16] = pc[i];
        buff[(i % 16) + 1] = '\0';
    }

    // Pad out last line if not exactly 16 characters.
    while ((i % 16) != 0) {
        printf ("   ");
        i++;
    }

    // And print the final ASCII bit.
    printf ("  %s\n", buff);
}

void run(string binary, bool debug)
{    
    Machine machine = Machine::getInstance(binary);
    
    while (true) {
        uint8_t opcode = machine.command_opcode();
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
            uint32_t c = machine.command_shift_unsigned(16, 19);
            if (icode == 2) { // ZERO AND DEPOSIT
                if (p >= len-1) {
                    uint32_t t = machine.command_operand1();
                    uint32_t r = machine.command_operand2();
                    machine.reg[t] = 0 | ((machine.reg[r] << 32-len) >> 32-len);
                    if (c != 0)
                        throw NotImplemented();
                } else
                    throw Undefined("ZERO AND DEPOSIT");
            } else if (icode == 7) { // DEPOSIT IMMEDIATE
                int32_t ival = machine.low_sign_ext(machine.command_operand2(), 5);
                if (p >= len-1) {
                    uint32_t t = machine.command_operand1();
                    machine.reg[t] = ((machine.reg[t] << p-len) >> p-len) | ((ival << 32-len) >> 32-len) | ((machine.reg[t] << p+1) >> p+1);
                    if (c != 0)
                        throw NotImplemented();
                } else
                    throw Undefined("DEPOSIT IMMEDIATE");
            } else
                throw UnrecognizedIcodeInstruction(icode, machine.pc());
            machine.incrementpc();
        } else
            throw UnrecognizedInstruction(opcode, machine.pc());
    }
}

