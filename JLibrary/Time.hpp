// JLibrary
// Time.hpp
// Created on 2022-02-12 by Justyn Durnford
// Last modified on 2022-09-23 by Justyn Durnford
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

	// Simple structure that represents a point in time accurate to 1 second.
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

	// Simple structure that represents a date of a year.
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

	// Class that provides functions to observe the date and time
	// as well as provide stopwatch-timer functionality.
	class Clock
	{
		TimePoint _start;
		TimePoint _end;
		bool _stopped;

		public:

		// Default constructor.
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

		// Returns the starting point of the timer.
		TimePoint getStartTime() const;

		// Returns the ending point of the timer.
		TimePoint getEndTime() const;

		// Starts the timer.
		void startTimer();

		// Stops the timer and returns the total 
		// seconds that have passed since the timer 
		// was last started.
		Duration stopTimer();

		// Resumes the timer if it has been stopped.
		Duration resumeTimer();

		// Restarts the timer.
		Duration restartTimer();

		// Returns the current point in time.
		TimePoint getCurrentTimePoint() const;

		// Returns the total seconds that have passed
		// since the timer was last started.
		Duration getElapsedTime() const;

	///////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////

		// Returns the current second.
		static u8 getCurrentSecond();

		// Returns the current minute.
		static u8 getCurrentMinute();

		// Returns the current hour.
		static u8 getCurrentHour();

		// Returns the current time.
		static Time getCurrentTime();

		// Returns the current day.
		static u8 getCurrentDay();

		// Returns the current month.
		static u8 getCurrentMonth();

		// Returns the current year.
		static u32 getCurrentYear();

		// Returns the current date.
		static Date getCurrentDate();
	};

	///////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////

	// Prints the given time to the standard output stream.
	void print(const Time& time);

	// Prints the given time to the standard output stream with a newline.
	void println(const Time& time);

	// Prints the given date to the standard output stream.
	void print(const Date& date);

	// Prints the given date to the standard output stream with a newline.
	void println(const Date& date);
}