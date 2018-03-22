#include "GameLoop.h"
#include "Raycaster.h"
#include <iostream>

int main(int argc, char* argv[])
{
    try
    {
        GameLoop loop(std::make_unique<Raycaster>());
        loop.Run();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what();
        getchar();
    }
    
    return 0;
}
