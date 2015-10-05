#ifndef HULL_H
#define HULL_H

namespace pdm
{
	class Hull
	{
	private:
		float _sigrad;

	public:
		Hull(float sigrad)
			: _sigrad(sigrad) {};
		~Hull() {};

		inline float GetSigRad() { return _sigrad; };

	};
}

#endif // !HULL_H