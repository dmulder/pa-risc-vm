#include <exception>
#include <string>
using namespace std;

class Undefined : exception
{
    private:
    string msg;

    public:
    Undefined(string instruction);
    const char* what() const throw ();
};

class UnrecognizedInstruction : exception
{
    private:
    string msg;

    public:
    UnrecognizedInstruction(uint8_t opcode, uint64_t pc);
    const char* what() const throw ();
};

class UnrecognizedIcodeInstruction : exception
{
    private:
    string msg;

    public:
    UnrecognizedIcodeInstruction(uint8_t opcode, uint64_t pc);
    const char* what() const throw ();
};

class NotImplemented : exception
{
    const char* what() const throw ()
    {
        return "The request instruction is not implemented";
    }
};

class ExeNotFound : exception
{
    const char* what() const throw ()
    {
        return "The specified executable was not found";
    }
};

class StackOverflow : exception
{
    const char* what() const throw ()
    {
        return "A stack overflow was detected";
    }
};

