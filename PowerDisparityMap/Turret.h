#ifndef TURRET_H
#define TURRET_H
#include "Weapon.h"

namespace pdm
{
	class Turret
		: public Weapon
	{
	public:
		Turret(float sigres, float tracking, float optimal, float falloff, 
			float base_damage, float rate_of_fire)
		: _sigres(sigres), _tracking(tracking), _optimal(optimal), _falloff(falloff),
		_base_damage(base_damage), _rof(rate_of_fire) {};
		virtual ~Turret() = 0;

		//inline float& GetSigRes() { return _sigres; };
		//inline float& GetTracking() { return _tracking; };
		//inline float& GetOptimal() { return _optimal; };
		//inline float& GetFalloff() { return _falloff; };
		//inline float& GetBaseDamage() { return _base_damage; };
		//inline float& GetROF() { return _rof; };

		virtual float CalcDPS(float range, float transversal, Target* target) override { return 0.0F; };

	protected:

		float _sigres;
		float _tracking;
		float _optimal;
		float _falloff;
		float _base_damage;
		float _rof;

	};
}

#endif