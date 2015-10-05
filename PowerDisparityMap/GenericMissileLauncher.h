#ifndef GENERICMISSILELAUNCHER_H
#define GENERICMISSILELAUNCHER_H

#include "MissileLauncher.h"

namespace pdm
{
	class GenericMissileLauncher :
		public MissileLauncher
	{
	public:
		GenericMissileLauncher(float base_damage, float explosion_radius, float explosion_velocity,
			float rate_of_fire, float max_range, enum DAMAGE_REDUCTION_FACTOR missile_type) 
			: MissileLauncher(base_damage, explosion_radius, explosion_velocity, rate_of_fire, max_range, missile_type)
		{};
		virtual ~GenericMissileLauncher() {};

		//inline float GetBaseDamage() { return _base_damage; }
		//inline float GetExplosionRadius() { return _explosion_radius; }
		//inline float GetExplosionVelocity() { return _explosion_velocity; }
		//inline enum DAMAGE_REDUCTION_FACTOR GetMissileType() { return _missile_type; }
		//inline float GetRateOfFire() { return _rate_of_fire; }
		//inline float GetMaxRange() { return _maximum_range; }

		virtual float CalcDPS(float range, float velocity, Target* target) override;
	
	};

}

#endif