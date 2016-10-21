#include "exceptions.h"
#include "opcode.h"
#include <sstream>
using namespace std;

Undefined::Undefined(string instruction)
{
    stringstream st;
    st << "The " << instruction << " instruction was undefined" << endl;
    msg = st.str();
}

const char* Undefined::what() const throw ()
{
    return this->msg.c_str();
}

static string InstructionName(uint8_t opcode)
{
    stringstream st;
    if (opcode == ADD)
        st << "ADD(2)";
    else if (opcode == ADDBF)
        st << "ADDBF(42)";
    else if (opcode == ADDBT)
        st << "ADDBT(40)";
    else if (opcode == ADDI)
        st << "ADDI(45)";
    else if (opcode == ADDIBF)
        st << "ADDIBF(43)";
    else if (opcode == ADDIBT)
        st << "ADDIBT(41)";
    else if (opcode == ADDIL)
        st << "ADDIL(10)";
    else if (opcode == ADDIT)
        st << "ADDIT(44)";
    else if (opcode == BB)
        st << "BB(49)";
    else if (opcode == BE)
        st << "BE(56)";
    else if (opcode == BLE)
        st << "BLE(57)";
    else if (opcode == BREAK)
        st << "BREAK(0)";
    else if (opcode == BVB)
        st << "BVB(48)";
    else if (opcode == CALL)
        st << "CALL(58)";
    else if (opcode == COMBF)
        st << "COMBF(34)";
    else if (opcode == COMBT)
        st << "COMBT(32)";
    else if (opcode == COMIBF)
        st << "COMIBF(35)";
    else if (opcode == COMIBT)
        st << "COMIBT(33)";
    else if (opcode == COMICLR)
        st << "COMICLR(36)";
    else if (opcode == _DEBUG)
        st << "DEBUG(4)";
    else if (opcode == DEP)
        st << "DEP(53)";
    else if (opcode == DIAG)
        st << "DIAG(5)";
    else if (opcode == DXDS)
        st << "DXDS(11)";
    else if (opcode == EXTR)
        st << "EXTR(52)";
    else if (opcode == FC)
        st << "FC(14)";
    else if (opcode == FMPYADD)
        st << "FMPYADD(6)";
    else if (opcode == FMPYSUB)
        st << "FMPYSUB(38)";
    else if (opcode == FTEST)
        st << "FTEST(12)";
    else if (opcode == LDB)
        st << "LDB(16)";
    else if (opcode == LDH)
        st << "LDH(17)";
    else if (opcode == LDIL)
        st << "LDIL(8)";
    else if (opcode == LDO)
        st << "LDO(13)";
    else if (opcode == LDST)
        st << "LDST(3)";
    else if (opcode == LDW)
        st << "LDW(18)";
    else if (opcode == LDWM)
        st << "LDWM(19)";
    else if (opcode == MOVB)
        st << "MOVB(50)";
    else if (opcode == MOVIB)
        st << "MOVIB(51)";
    else if (opcode == PROBE)
        st << "PROBE(1)";
    else if (opcode == STB)
        st << "STB(24)";
    else if (opcode == STH)
        st << "STH(25)";
    else if (opcode == STW)
        st << "STW(26)";
    else if (opcode == STWM)
        st << "STWM(27)";
    else if (opcode == SUBI)
        st << "SUBI(37)";
    else if (opcode == WXWF)
        st << "WXWF(9)";
    else
        st << "UNKNOWN(" << (int)opcode << ")";

    return st.str();
}

UnrecognizedInstruction::UnrecognizedInstruction(uint8_t opcode, uint64_t pc)
{
    stringstream st;
    st << "Unrecognized opcode " << InstructionName(opcode) << " at instruction " << (int)pc << endl;
    msg = st.str();
}

const char* UnrecognizedInstruction::what() const throw ()
{
    return this->msg.c_str();
}

UnrecognizedIcodeInstruction::UnrecognizedIcodeInstruction(uint8_t icode, uint64_t pc)
{
    stringstream st;
    st << "Unrecognized icode " << (int)icode << " at instruction " << (int)pc << endl;
    msg = st.str();
}

const char* UnrecognizedIcodeInstruction::what() const throw ()
{
    return this->msg.c_str();
}

