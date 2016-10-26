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
    public:
    const char* what() const throw ()
    {
        return "The requested instruction is not implemented\n";
    }
};

class ExeNotFound : exception
{
    public:
    const char* what() const throw ()
    {
        return "The specified executable was not found\n";
    }
};

class StackOverflow : exception
{
    public:
    const char* what() const throw ()
    {
        return "A stack overflow was detected\n";
    }
};

