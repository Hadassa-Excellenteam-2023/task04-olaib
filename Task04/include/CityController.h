#pragma once
#include "Location.h"
#include "utilties.h"


class CityController {
public:
	CityController();
	std::string getCityName()const;
	void printResList(Location mapped, const lessXMap& pairs);
	void run();
private:
	CityMap m_citiesMap;
	MapX m_mapX;
	MapY m_mapY;

	double m_radius;

	void initCitiesMap();
};