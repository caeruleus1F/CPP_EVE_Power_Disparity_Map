#ifndef GENERICTURRET_H
#define GENERICTURRET_H

#include "Turret.h"
#include "Target.h"
//using pdm::Target;

namespace pdm
{
	class GenericTurret :
		public Turret
	{
	public:
		GenericTurret(float sigres, float tracking, float optimal, float falloff,
			float base_damage, float rate_of_fire)
			: Turret(sigres, tracking, optimal, falloff, base_damage, rate_of_fire) {};
		virtual ~GenericTurret() {};

		virtual float CalcDPS(float range, float transversal, Target* target) override;

	private:
		float TurretHitChance(float transversal, float range, float sigres, float tracking,
			float sigrad, float optimal, float falloff);
		float EffectiveDPS(float base_damage, float chance_to_hit);

	};
}

#endif