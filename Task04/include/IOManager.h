#pragma once
#include "MyException.h"
#include "Location.h"
#include "utilties.h"

namespace {

    bool isFileEmpty(std::ifstream& file)
    {
        return file.peek() == std::ifstream::traits_type::eof();
    }

    // ======================================================================

    std::ifstream openFile(std::string fileName)
    {
        auto file = std::ifstream(fileName);
        if (!file.is_open())
            throw std::exception(FILE_OPEN_ERR);

        if (isFileEmpty(file))

            return file;
    }

    // ======================================================================

    void readCityInfo(const std::string& fileName, MapX& mapX,MapY& mapY, CityMap& citiesMap)
    {

        auto file = std::ifstream(fileName);
        if (isFileEmpty(file))
        {
            throw std::runtime_error("File is empty");
        }
        for (auto city = std::string(); std::getline(file, city);)
        {
            auto x_coordinate = std::string();
            auto y_coordinate = std::string();
            std::getline(file, x_coordinate, '-');
            if (x_coordinate.empty())
                throw std::runtime_error("Faulty data");
            std::getline(file, y_coordinate);
            if (y_coordinate.empty())
                throw std::runtime_error("Faulty data");
            const auto coordinates = Location(std::stod(x_coordinate), std::stod(y_coordinate));
            mapX.emplace(coordinates, city);
            mapY.emplace(coordinates, city);
            citiesMap.emplace(city, coordinates);
        }



        /*auto file = openFile(fileName);

        std::string city,
            separator, // '-'
            eol, //End of line
            fileContents; // String to hold the file contents

        auto strLocation = std::pair<std::string, std::string>();

        // Read the file contents into a string
        fileContents.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
        file.close();

        std::istringstream iss(fileContents);

        while (std::getline(iss, city))
        {
            if (city.empty())
                break;

            if (!(iss >> strLocation.first >> separator >> strLocation.second))
                throw FileError(FILE_READ_ERR);

            Location location;
            if (!strLocation.first.empty() && !strLocation.second.empty()) {
                location.x = std::stod(strLocation.first);
                location.y = std::stod(strLocation.second);
            }

            citiesMap.emplace(city, location);

            mapX.emplace(location, city); // city map sorted by coordinate x
            mapY.emplace(location, city); // city map sorted by coordinate y

            if (!std::getline(iss, eol))
                throw FileError(FILE_READ_ERR);
        }
        for (auto city : citiesMap)
            std::cout << city.second << std::endl;*/
    }

    // ======================================================================

    void clearInput()
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    // ======================================================================

    void readRadiusInput(double& radiusVar)
    {
        double radius;
        do {
            std::cout << ENTER_RADIUS;

            std::cin >> radius;

            if (std::cin.fail()) 
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::invalid_argument(INVALID_INPUT);
            }
            if (radius < 0) {
                std::cout << NEGATIVE_RADIUS << std::endl;
                clearInput();
            }
        } while (radius < 0);

        radiusVar = radius;
    }
   
}