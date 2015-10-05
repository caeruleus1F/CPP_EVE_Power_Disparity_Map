#include "MissileLauncher.h"

namespace pdm
{
	MissileLauncher::MissileLauncher(float base_damage, float explosion_radius, float explosion_velocity,
		float rate_of_fire, float max_range, enum DAMAGE_REDUCTION_FACTOR missile_type)
		: _base_damage(base_damage), _explosion_radius(explosion_radius), _explosion_velocity(explosion_velocity),
		_rate_of_fire(rate_of_fire), _maximum_range(max_range), _missile_type(missile_type)
	{}

	MissileLauncher::~MissileLauncher()
	{

	}
}
