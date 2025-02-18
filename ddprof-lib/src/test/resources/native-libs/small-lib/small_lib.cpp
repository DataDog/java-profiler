#include <iostream>
#include "small_lib.h"

extern "C" void hello() {
    std::cout << "Hello, World from shared library!" << std::endl;
}
