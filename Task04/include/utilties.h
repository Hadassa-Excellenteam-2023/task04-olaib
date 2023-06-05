#pragma once

#include <map>
#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <unordered_map>
#include <sstream>
#include "Location.h"


using LocationStrPair = std::pair<const Location&, const std::string&>;
using CityMap = std::unordered_map<std::string, Location>;
using MapX = std::multimap<Location, std::string, LessX>;
using MapY = std::multimap<Location, std::string, LessY>;
using SquareMap = std::multimap<double, std::string>;
using lessXMap = std::multimap<Location, std::string, LessX>;

constexpr auto ENTER_CITY_NAME = "Please enter selected city name(with line break after it) :";
constexpr auto ENTER_RADIUS = "Please enter the wanted radius:";
constexpr auto ENTER_NORM = "Please enter the wanted norm (0. L2, Euclidean distance, 1. Linf, Chebyshev distance, 2. L1, Manhattandistance):\n";
constexpr auto RESULT = "Search result:";
constexpr auto CITIES_FOUND_IN_RADIUS = " city/cities found in the given radius.";
constexpr auto NORTH_CITIES = " cities are to the north of the selected city.";
constexpr auto CLOSEST_CITIES = "City list:\n";
constexpr auto DATA_FILE_NAME = "data.txt";
constexpr auto FUNC_DOESNT_EXIST = "No such function.";
constexpr auto BYE = "Bye";
constexpr auto END = "0";
constexpr auto TAB_SPACE = '\t';



inline const char* FILE_OPEN_ERR = "Cannot open file: ";
inline const char* FILE_READ_ERR = "Cannot read file: ";
inline const char* INVALID_INPUT = "Invalid input";

constexpr auto UNKNOWN_ERROR = "Unknown error";
constexpr auto NEGATIVE_RADIUS = "Radius must be positive value";
constexpr auto ERROR_OCCURRED = "An error occurred : ";