#include "Functions.h"
#include "IOManager.h"

namespace
{
	//func options
	enum functions :int {
		L2, Linf, L1
	};

	// this function calculating: |x0 - x1|
	double manhatanDistance(const Location& currCityLocation, const Location& otherCityLoc)
	{
		return std::max(abs(currCityLocation.x - otherCityLoc.x), abs(currCityLocation.y - otherCityLoc.y));
	}

	// this function calculating: max(|x0 - x1|, |y0 - y2|
	double infiniteDistance(const Location& currCityLocation, const Location& otherCityLoc)
	{
		return std::max(abs(currCityLocation.x - otherCityLoc.x), abs(currCityLocation.y - otherCityLoc.y));
	}

	// this function calculating:  ?((??0 ? ??1)² + (??0 ? ??1)²).
	double euclidianDistance(const Location& currCityLocation, const Location& otherCityLoc)
	{
		return sqrt(pow(currCityLocation.x - otherCityLoc.y, 2) + pow(currCityLocation.y - otherCityLoc.y, 2));
	}

	FunMap initFunctionsMap()
	{
		auto map = FunMap();

		map[L1] = &manhatanDistance;
		map[Linf] = &infiniteDistance;
		map[L1] = &manhatanDistance;

		return map;
	}

}

FunctionPtr getFunction(const char& c)
{
	static auto funcMap = initFunctionsMap();

	auto mapEntry = funcMap.find(c);

	if (mapEntry == funcMap.end())
		return nullptr;

	return mapEntry->second;
}

FunctionPtr getDistFunction()
{
	FunctionPtr distanceFunc;
	int funcNorm;

	do {
		std::cout << ENTER_NORM;
		std::cin >> funcNorm;
		if (std::cin.fail() || !std::cin.good()) {
			throw std::invalid_argument(INVALID_INPUT);
		}

		distanceFunc = getFunction(funcNorm);
		if (!distanceFunc) {
			std::cout << FUNC_DOESNT_EXIST;
			clearInput();
		}
	} while (!distanceFunc);

	return distanceFunc;
}
