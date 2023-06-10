#include "CityController.h"
#include "IOManager.h"
#include "Functions.h"


//todo: check how this will work well - the it - equal range??
namespace {
    // Calculate the square within the given radius
    void squareByRadius(const Location& cityLoc, lessXMap& sqaureMap, const MapX& mapX, const MapY& mapY, const double& radius)
    {
       static const auto ComapreFunc = [](const LocationStrPair& pair1, const LocationStrPair& pair2)
        {
            return pair1.first.x < pair2.first.x;
        };
       auto minX = cityLoc.x - radius;
       auto maxX = cityLoc.x + radius;
       auto maxY = cityLoc.y + radius;
       auto minY = cityLoc.y - radius;

       auto itBeginX = mapX.lower_bound(Location(minX, cityLoc.y));
       auto itEndX = mapX.upper_bound(Location(maxX, cityLoc.y));
       //
       const auto subMapY = lessXMap(
           mapY.lower_bound(Location(cityLoc.x, minY)),//itBeginY
           mapY.upper_bound(Location(cityLoc.x, maxY))//itEndY
       );

       std::set_intersection(
           itBeginX, itEndX,
           subMapY.begin(), subMapY.end(),
           std::inserter(sqaureMap, sqaureMap.begin()), ComapreFunc
       );

    }
    // Sort the square map based on distance
    void sortedSquare(const Location& cityLoc, FunctionPtr distFuncPtr, const lessXMap& squareMap, SquareMap& sortedSquare)
    {
        const auto DistClacFunc = [&sortedSquare, distFuncPtr, cityLoc](const LocationStrPair& locStrP)
        {
            sortedSquare.emplace(distFuncPtr(cityLoc, locStrP.first), locStrP.second);
        };

        std::ranges::for_each(squareMap, DistClacFunc);
    }
}



CityController::CityController()
{
    try {
        readCityInfo(DATA_FILE_NAME, m_mapX, m_mapY, m_citiesMap);
    }
    catch (const std::exception& e)
    {
        throw e;
    }
    catch (...)
    {
        throw;
    }
}

// ==================================================================

void CityController::run()
{
    std::string city;

    try {
        while ((city = getCityName()) != END)
        {
            readRadiusInput(m_radius);
            // get distance function
            auto distanceFunc = getDistFunction();

            auto& cityLoc = m_citiesMap.at(city);
            auto squareMap = lessXMap();
            auto sortedSquareMap = SquareMap();

            // create square by given radius
            squareByRadius(cityLoc, squareMap, m_mapX, m_mapY, m_radius);
            // create sorted square
            sortedSquare(cityLoc, distanceFunc, squareMap, sortedSquareMap);

            // print the result list
            printResList(cityLoc, sortedSquareMap);
            clearInput();
        }

    }
    catch (std::invalid_argument& e)
    {
        std::cout << e.what() << std::endl;
        throw e;
    }
    catch (const std::exception& e)
    {
        throw e;
    }
}

// =============================================================================

std::string CityController::getCityName() const
{
    std::string city;
    // read until city is valid
    do {
        try {
            std::cout << ENTER_CITY_NAME;
            if (!std::getline(std::cin, city) || city == END)
                break;
            if (m_citiesMap.find(city) == m_citiesMap.end())
                throw std::out_of_range("ERROR: '" + city + " 'isn't found in the city list. Please try again.");
            else
                break; // valid city, exit the loop
        }
        catch (const std::out_of_range& e) {
            std::cout << e.what() << std::endl;
        }
    } while (true);

    return city;

}

// =============================================================================

void CityController::printResList(Location cityLoc, const SquareMap& sortedSquare)
{
    auto nearestCities = ++sortedSquare.cbegin();
    auto farestCities = sortedSquare.upper_bound(m_radius);// circle

    const auto northCitiesByRadius = [cityLoc, this](const LocationStrPair& p)->bool
    {
        return m_citiesMap[p.second].y < cityLoc.y;
    };

    std::cout << std::endl << TAB_SPACE << RESULT << std::endl;
    std::cout << std::distance(nearestCities, farestCities) << NORTH_CITIES << std::endl << std::endl;

    std::cout << std::endl << TAB_SPACE << CLOSEST_CITIES << std::endl;
    for (auto it = nearestCities; it != farestCities; ++it)
        std::cout << it->second << std::endl;

}


