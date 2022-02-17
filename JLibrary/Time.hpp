// JLibrary
// Time.hpp
// Created on 2022-02-12 by Justyn Durnford
// Last modified on 2022-02-13 by Justyn Durnford
// Header file that includes classes and functions
// dealing with time.

#pragma once

#include "IntegerTypedefs.hpp"

#include <chrono>
#include <compare>
#include <string>

namespace jlib
{
	// Shorthand for std::chrono::time_point<std::chrono::system_clock>.
	typedef std::chrono::time_point<std::chrono::system_clock> TimePoint;
	// Shorthand for std::chrono::duration<float>.
	typedef std::chrono::duration<float> Duration;

	extern const Duration TimeZero;

	///////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////

	// 
	struct Time
	{
		u8 hour;
		u8 minute;
		u8 second;

		// Default constructor.
		Time();

		// Primary constructor.
		Time(u8 new_hour, u8 new_minute, u8 new_second);

		// Returns a std::string representation of the Time.
		std::string toString() const;

		// Returns a std::wstring representation of the Time.
		std::wstring toWideString() const;
	};

	// Overload of binary operator ==
	bool operator == (const Time& A, const Time& B);

	// Overload of binary operator !=
	bool operator != (const Time& A, const Time& B);

	// Overload of binary operator <
	bool operator < (const Time& A, const Time& B);

	// Overload of binary operator <=
	bool operator <= (const Time& A, const Time& B);

	// Overload of binary operator >
	bool operator > (const Time& A, const Time& B);

	// Overload of binary operator >=
	bool operator >= (const Time& A, const Time& B);

	// Overload of binary operator <=>
	std::strong_ordering operator <=> (const Time& A, const Time& B);

	///////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////

	// 
	struct Date
	{
		u8 day;
		u8 month;
		u32 year;

		// Default constructor.
		Date();

		// Primary constructor.
		Date(u8 new_day, u8 new_month, u32 new_year);

		// Returns a std::string representation of the Date.
		std::string toString() const;

		// Returns a std::wstring representation of the Date.
		std::wstring toWideString() const;
	};

	// Overload of binary operator ==
	bool operator == (const Date& A, const Date& B);

	// Overload of binary operator !=
	bool operator != (const Date& A, const Date& B);	

	// Overload of binary operator <
	bool operator < (const Date& A, const Date& B);

	// Overload of binary operator <=
	bool operator <= (const Date& A, const Date& B);

	// Overload of binary operator >
	bool operator > (const Date& A, const Date& B);

	// Overload of binary operator >=
	bool operator >= (const Date& A, const Date& B);

	// Overload of binary operator <=>
	std::strong_ordering operator <=> (const Date& A, const Date& B);

	///////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////

	// 
	class Clock
	{
		TimePoint _start;
		TimePoint _end;
		bool _stopped;

		public:

		// Default constructor.
		//
		Clock();

		// Copy constructor.
		Clock(const Clock& other) = delete;

		// Move constructor.
		Clock(Clock&& other) = delete;

		// Copy assignment operator.
		Clock& operator = (const Clock& other) = delete;

		// Move assignment operator.
		Clock& operator = (Clock&& other) = delete;

		// Destructor.
		~Clock() = default;

		// 
		TimePoint getStartTime() const;

		// 
		TimePoint getEndTime() const;

		// 
		void startTimer();

		// 
		TimePoint getCurrentTimePoint() const;

		// 
		Duration stopTimer();

		// 
		Duration resumeTimer();

		// 
		Duration restartTimer();

		// Returns the total seconds that have passed
		// since the timer was last started.
		Duration getElapsedTime() const;

		// Returns the current second.
		u8 getCurrentSecond() const;

		// Returns the current minute.
		u8 getCurrentMinute() const;

		// Returns the current hour.
		u8 getCurrentHour() const;

		// Returns the current time.
		Time getCurrentTime() const;

		// Returns the current day.
		u8 getCurrentDay() const;

		// Returns the current month.
		u8 getCurrentMonth() const;

		// Returns the current year.
		u32 getCurrentYear() const;

		// Returns the current date.
		Date getCurrentDate() const;
	};
}