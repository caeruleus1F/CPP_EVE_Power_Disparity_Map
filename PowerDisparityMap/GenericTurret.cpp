#include "GenericTurret.h"
#include <math.h>

namespace pdm
{
	float GenericTurret::CalcDPS(float range, float transversal, Target* target)
	{
		float dps = 0.0F;
		float my_hit_chance = 0.0F;
		my_hit_chance = TurretHitChance(transversal, range, _sigres, _tracking,
			target->GetHull().GetSigRad(), _optimal, _falloff);
		dps = EffectiveDPS(_base_damage, my_hit_chance) / _rof;
		return dps;
	}

	float GenericTurret::TurretHitChance(float transversal, float range, float sigres, float tracking,
		float sigrad, float optimal, float falloff)
	{
		float chance = 0.0F;
		float exponent = 0.0F;

		float first_term = transversal * sigres / (range * tracking * sigrad);
		float second_term = fmax(0.0F, range - optimal) / falloff;

		exponent = pow(first_term, 2) + pow(second_term, 2);

		chance = pow(0.5F, exponent);

		return chance;
	}

	// at some point modify to include target's resistances
	float GenericTurret::EffectiveDPS(float base_damage, float chance_to_hit)
	{
		float dps = 0.0F;

		if (chance_to_hit >= 0.01)
		{
			dps = static_cast<float>(base_damage * (pow(chance_to_hit, 2) + chance_to_hit + 0.0499) / 2);
		}
		else
		{
			dps = base_damage * 3 * chance_to_hit;
		}

		return dps;
	}
}