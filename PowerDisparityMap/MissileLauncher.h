#ifndef MISSILELAUNCHER_H
#define MISSILELAUNCHER_H

#include "Weapon.h"

namespace pdm
{
	enum DAMAGE_REDUCTION_FACTOR
	{
		PRECISION_LIGHT, PRECISION_HEAVY, AUTO_TARGETING_LIGHT,
		LIGHT, ROCKET, HEAVY, AUTO_TARGETING_HEAVY, JAVELIN_ROCKET,
		FURY_LIGHT, PRECISION_CRUISE, CRUISE, AUTO_TARGETING_CRUISE,
		RAGE_ROCKET, CITADEL_CRUISE, FURY_HEAVY, HEAVY_ASSAULT,
		JAVELIN_HEAVY_ASSAULT, FURY_CRUISE, RAGE_HEAVY_ASSAULT,
		TORPEDO, JAVELIN_TORPEDO, RAGE_TORPEDO, CITADEL_TORPEDO
	};

	class MissileLauncher
		: public Weapon
	{
	public:
		MissileLauncher(float base_damage, float explosion_radius, float explosion_velocity,
			float rate_of_fire, float max_range, enum DAMAGE_REDUCTION_FACTOR missile_type);
		virtual ~MissileLauncher() = 0;

		virtual float CalcDPS(float range, float transversal, Target* target) override { return 0.0F; };

	protected:
		float _base_damage;
		float _explosion_radius;
		float _explosion_velocity;
		DAMAGE_REDUCTION_FACTOR _missile_type;
		float _rate_of_fire;
		float _maximum_range;
	};
}
#endif // !MISSILELAUNCHER_H