#pragma once
#include <fstream>

typedef struct Location
{
	double x,
		y;

	Location(double x = 0, double y = 0) :x(x), y(y) {}
	~Location() = default;
}Location;

bool operator<(const Location& loc1, const Location& loc2);
std::ostream& operator<<(std::ostream & os, const Location & loc);

// ======================================================================

typedef struct LessX
{
	bool operator()(const Location& loc1, const Location& loc2)const
	{
		return loc1.x < loc2.x;
	}
}lessX;

// ======================================================================

typedef struct LessY
{
	bool operator()(const Location& loc1, const Location& loc2)const
	{
		return loc1.y < loc2.y;
	}
}lessY;

