#include "CityController.h"
#include "IOManager.h"
#include "Functions.h"


//todo: check how this will work well - the it - equal range??
namespace {
    void squareByRadius(const Location& cityLoc, SquareMap& sqaureMape, const MapX& mapX, const MapY& mapy, const double& radius)
    {
        static const auto ComapreFunc = [](const LocationStrPair& p1, const LocationStrPair& p2)
        {
            return p1.first.x < p2.first.x;
        };
        auto x = cityLoc.x;
        auto y = cityLoc.y;
        auto itRangeX = mapX.equal_range(Location(x - radius, y));
        auto itRangeY = mapy.equal_range(Location(x, y - radius));

        auto subMmapY = lessXMap();
        for (auto it = itRangeY.first; it != itRangeY.second; ++it) {
            if (it->first.y <= y + radius) {
                subMmapY.insert(*it);
            }
            else {
                break;
            }
        }

        std::set_intersection(itRangeX.first, itRangeX.second, subMmapY.begin(), subMmapY.end(),
            std::inserter(sqaureMape, sqaureMape.begin()), ComapreFunc);
    }

    void sortedSquare(const Location& cityLoc, FunctionPtr distFuncPtr, const SquareMap& squareMap, lessXMap& sortedSquare)
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
        readCityInfo(DATA_FILE_NAME,m_mapX,m_mapY,m_citiesMap);
        initCitiesMap();
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

    try
    {
        while ((city = getCityName()) != END)
        {
            readRadiusInput(m_radius);
            // get distance function
            auto distanceFunc = getDistFunction();

            auto& cityLoc = m_citiesMap.at(city);
            auto sortedSquareMap = lessXMap();
            auto squareMap = SquareMap();

            // create square radius
            squareByRadius(cityLoc, squareMap, m_mapX, m_mapY, m_radius);
            // create sorted square
            sortedSquare(cityLoc, distanceFunc, squareMap, sortedSquareMap);

            // print the result list
            printResList(cityLoc, sortedSquareMap);
            clearInput();
        }
    }
    catch(std::invalid_argument& e)
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

void CityController::printResList(Location cityLoc, const lessXMap& sortedSquare)
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


