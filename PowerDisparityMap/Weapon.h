#ifndef WEAPON_H
#define WEAPON_H
#include "Target.h"

namespace pdm
{
	class Target;

	class Weapon
	{
	private:

	protected:

	public:
		Weapon() {};
		virtual ~Weapon() = 0;
		virtual float CalcDPS(float range, float transversal, Target* target) { return 0.0F; };

	};

}

#endif