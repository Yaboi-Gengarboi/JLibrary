module;

#include "Arithmetic.hpp"

export module Point2;

export namespace jlib
{
	template <std_arithmetic T> class Point2
	{
		public:

		T x;
		T y;

		Point2()
		{
			x = static_cast<T>(0);
			y = static_cast<T>(0);
		}

		Point2(T X, T Y)
		{
			x = X;
			y = Y;
		}
	};
}