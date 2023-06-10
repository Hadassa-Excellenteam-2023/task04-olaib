#pragma once
#include "Location.h"
#include "utilties.h"


class CityController {
public:
	// ====================== C-TOR ===========================
	CityController();
	
	void run();
private:
	// ================= PRIVATE MEMBERS ======================
	CityMap m_citiesMap;
	MapX m_mapX;
	MapY m_mapY;
	double m_radius;
	// ================= PRIVATE METHODS ======================
	std::string getCityName()const;
	void printResList(Location mapped, const SquareMap& pairs);
};