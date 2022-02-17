// JLibrary
// IDClass.ixx
// Created on 2022-02-09 by Justyn Durnford
// Last modified on 2022-02-09 by Justyn Durnford
// Module file for the IDClass template class.

module;

#include <compare>
#include <concepts>

export module IDClass;

export namespace jlib
{
	// This serves as a base class for any type
	// that needs an ID. This way the code can
	// be re-used and any two objects can simply
	// be compared by their IDs.
	template <std::unsigned_integral T> class IDClass
	{
		public:

		using id_type = T;

		protected:

		id_type _id;

		public:

		// Default constructor.
		// Sets the ID to 0.
		IDClass()
		{
			_id = static_cast<id_type>(0);
		}

		// id_type constructor.
		// Sets the ID to new_id.
		IDClass(id_type new_id)
		{
			_id = new_id;
		}

		// Virtual destructor.
		virtual ~IDClass() = default;

		// Returns the ID of the IDClass.
		id_type getID() const
		{
			return _id;
		}

		// Sets the ID of the IDClass to new_id.
		void setID(id_type new_id)
		{
			_id = new_id;
		}
	};

	// Overload of binary operator ==
	template <std::unsigned_integral T>
	bool operator == (const IDClass<T>& A, const IDClass<T>& B)
	{
		return A.getID() == B.getID();
	}

	// Overload of binary operator !=
	template <std::unsigned_integral T>
	bool operator != (const IDClass<T>& A, const IDClass<T>& B)
	{
		return A.getID() != B.getID();
	}

	// Overload of binary operator <
	template <std::unsigned_integral T>
	bool operator < (const IDClass<T>& A, const IDClass<T>& B)
	{
		return A.getID() < B.getID();
	}

	// Overload of binary operator <=
	template <std::unsigned_integral T>
	bool operator <= (const IDClass<T>& A, const IDClass<T>& B)
	{
		return A.getID() <= B.getID();
	}

	// Overload of binary operator >
	template <std::unsigned_integral T>
	bool operator > (const IDClass<T>& A, const IDClass<T>& B)
	{
		return A.getID() > B.getID();
	}

	// Overload of binary operator >=
	template <std::unsigned_integral T>
	bool operator >= (const IDClass<T>& A, const IDClass<T>& B)
	{
		return A.getID() >= B.getID();
	}

	// Overload of binary operator <=>
	template <std::unsigned_integral T>
	std::strong_ordering operator <=> (const IDClass<T>& A, const IDClass<T>& B)
	{
		return A.getID() <=> B.getID();
	}
}