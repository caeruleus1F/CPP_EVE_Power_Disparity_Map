#ifndef TARGET_H
#define TARGET_H

#include "Hull.h"
#include "Weapon.h"

namespace pdm
{
	class Weapon;	

	class Target
	{
	private:
		Hull _hull;
		Weapon* _weapon;
		char* _ship_name;

	public:
		Target(Hull hull, Weapon* weapon, const char* ship_name);

		~Target();

		inline Hull& GetHull() { return _hull; }
		const char* GetShipName();
		float CalcDPS(float range, float transversal_or_velocity, Target* target);

	};

}
#endif