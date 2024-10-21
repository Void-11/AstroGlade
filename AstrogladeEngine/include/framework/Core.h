#include <iostream>

namespace ly
{
    // Macro
#define LOG(M, ...) std::cout << M << "\n" << ##__VA_ARGS__ << std::endl;
}