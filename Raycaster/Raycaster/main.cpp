#include "RenderingLoop.h"
#include <iostream>

int main(int argc, char* argv[])
{
    try
    {
        RenderingLoop loop;
        loop.Run();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what();
    }
    
    return 0;
}
