#include "GenericMissileLauncher.h"
#include <math.h>

namespace pdm
{

	float GenericMissileLauncher::CalcDPS(float range, float velocity, Target* target)
	{
		float dps = 0.0F;

		float first_term = 1.0F;
		float second_term = 0.0F;
		float third_term = 0.0F;
		float exponent = 0.0F;
		float drf = 0.0;		

		switch (_missile_type)
		{
		case pdm::PRECISION_LIGHT: drf = 2.6F; break;
		case pdm::PRECISION_HEAVY: drf = 2.7F; break;
		case pdm::AUTO_TARGETING_LIGHT: drf = 2.8F; break;
		case pdm::LIGHT: drf = 2.8F; break;
		case pdm::ROCKET: drf = 3.0F; break;
		case pdm::HEAVY: drf = 3.2F; break;
		case pdm::AUTO_TARGETING_HEAVY: drf = 3.2F; break;
		case pdm::JAVELIN_ROCKET: drf = 3.2F; break;
		case pdm::FURY_LIGHT: drf = 3.2F; break;
		case pdm::PRECISION_CRUISE: drf = 3.5F; break;
		case pdm::CRUISE: drf = 4.5F; break;
		case pdm::AUTO_TARGETING_CRUISE: drf = 4.5F; break;
		case pdm::RAGE_ROCKET: drf = 4.5F; break;
		case pdm::CITADEL_CRUISE: drf = 4.5F; break;
		case pdm::FURY_HEAVY: drf = 4.5F; break;
		case pdm::HEAVY_ASSAULT: drf = 4.5F; break;
		case pdm::JAVELIN_HEAVY_ASSAULT: drf = 4.6F; break;
		case pdm::FURY_CRUISE: drf = 4.7F; break;
		case pdm::RAGE_HEAVY_ASSAULT: drf = 4.8F; break;
		case pdm::TORPEDO: drf = 5.0F; break;
		case pdm::JAVELIN_TORPEDO: drf = 5.2F; break;
		case pdm::RAGE_TORPEDO: drf = 5.2F; break;
		case pdm::CITADEL_TORPEDO: drf = 5.5F; break;
		}

		if (_explosion_radius != 0)
		{
			second_term = target->GetHull().GetSigRad() / _explosion_radius;
		}

		if (_explosion_radius != 0 && velocity != 0)
		{
			exponent = (float)(log(drf) / log(5.5));
			third_term = (float)(pow(target->GetHull().GetSigRad() * _explosion_velocity / (_explosion_radius * velocity), exponent));
		}

		if (range <= _maximum_range)
		{
			dps = _base_damage * fmin(first_term, fmin(second_term, third_term) / _rate_of_fire);
		}

		return dps;
	}
}
