#include <iostream>
using namespace std;
#include "machine.h"

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

    try {
        run(argv[1], debug);
    } catch (UnrecognizedInstruction e) {
        cout << e.what();
        return 1;
    } catch (Undefined e) {
        cout << e.what();
        return 2;
    } catch (UnrecognizedIcodeInstruction e) {
        cout << e.what();
        return 3;
    }

    return 0;
}

