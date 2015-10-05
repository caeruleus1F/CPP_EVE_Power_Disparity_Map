#include <cstring>
#include "Target.h"

namespace pdm
{
	Target::Target(Hull hull, Weapon* weapon, const char* ship_name)
		: _hull(hull), _weapon(weapon), _ship_name(nullptr)
	{
		int length = strlen(ship_name) + 1;
		_ship_name = new char[length]();
		strcpy_s(_ship_name, length, ship_name);
	}

	Target::~Target()
	{ 
		delete[] _ship_name;
	}

	float Target::CalcDPS(float range, float transversal_or_velocity, Target* target)
	{
		float dps = 0.0F;

		dps = _weapon->CalcDPS(range, transversal_or_velocity, target);

		return dps;
	}

	const char* Target::GetShipName()
	{
		return _ship_name;
	}
}
