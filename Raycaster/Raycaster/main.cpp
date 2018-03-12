#include "RenderingLoop.h"
#include "Raycaster.h"
#include <iostream>

int main(int argc, char* argv[])
{
    try
    {
        RenderingLoop loop(std::make_unique<Raycaster>());
        loop.Run();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what();
        getchar();
    }
    
    return 0;
}
