#include "Location.h"

bool operator<(const Location& loc1, const Location& loc2)
{
	return loc1.x < loc2.x;
}

std::ostream& operator<<(std::ostream& os, const Location& loc)
{
	os << "[" << loc.x << ", " << loc.y << ")";
	return os;
}
