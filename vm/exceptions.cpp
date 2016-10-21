#include "exceptions.h"
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

UnrecognizedInstruction::UnrecognizedInstruction(uint8_t opcode, uint64_t pc)
{
    stringstream st;
    st << "Unrecognized opcode " << (int)opcode << " at instruction " << (int)pc << endl;
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

