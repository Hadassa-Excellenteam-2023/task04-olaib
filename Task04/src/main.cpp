#include <iostream>
#include "CityController.h"

int main()
{
    try
    {
        CityController().run();
    }
    catch (const std::exception& ex)
    {
        std::cerr << ERROR_OCCURRED << ex.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << UNKNOWN_ERROR << std::endl;
    }

    std::cout << BYE << std::endl;

    return EXIT_SUCCESS;
}