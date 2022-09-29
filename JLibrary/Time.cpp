// JLibrary
// Time.cpp
// Created on 2022-02-12 by Justyn Durnford
// Last modified on 2022-09-23 by Justyn Durnford
// Source file that includes classes and functions
// dealing with time.

#include "Time.hpp"

#include <chrono>
using std::chrono::duration;
using std::chrono::milliseconds;
using std::chrono::system_clock;
using std::chrono::time_point;

#include <compare>
using std::strong_ordering;

#include <ctime>
using std::time_t;
using std::tm;
using std::time;

#include <iostream>
using std::cout;

#include <string>
using std::string;
using std::wstring;
using std::to_string;
using std::to_wstring;

namespace jlib
{
	const Duration jlib::TimeZero = Duration(0.0f);

	///////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////

	Time::Time()
	{
		hour = 0;
		minute = 0;
		second = 0;
	}

	Time::Time(u8 new_hour, u8 new_minute, u8 new_second)
	{
		hour = new_hour;
		minute = new_minute;
		second = new_second;
	}

	string Time::toString() const
	{
		string hour_str("00");
		string minute_str("00");
		string second_str("00");

		if (hour < 10)
			hour_str = "0" + to_string(u16(hour));
		else
			hour_str = to_string(u16(hour));

		if (minute < 10)
			minute_str = "0" + to_string(u16(minute));
		else
			minute_str = to_string(u16(minute));

		if (second < 10)
			second_str = "0" + to_string(u16(second));
		else
			second_str = to_string(u16(second));

		return hour_str + ":" + minute_str + ":" + second_str;
	}

	wstring Time::toWideString() const
	{
		wstring hour_wstr(L"00");
		wstring minute_wstr(L"00");
		wstring second_wstr(L"00");

		if (hour < 10)
			hour_wstr = L"0" + to_wstring(u16(hour));
		else
			hour_wstr = to_wstring(u16(hour));

		if (minute < 10)
			minute_wstr = L"0" + to_wstring(u16(minute));
		else
			minute_wstr = to_wstring(u16(minute));

		if (second < 10)
			second_wstr = L"0" + to_wstring(u16(second));
		else
			second_wstr = to_wstring(u16(second));

		return hour_wstr + L":" + minute_wstr + L":" + second_wstr;
	}

	bool operator == (const Time& A, const Time& B)
	{
		return (A.hour == B.hour) && (A.minute == B.minute) && (A.second == B.second);
	}
	
	bool operator != (const Time& A, const Time& B)
	{
		return (A.hour != B.hour) || (A.minute != B.minute) || (A.second != B.second);
	}
	
	bool operator < (const Time& A, const Time& B)
	{
		if (A.hour < B.hour)
			return true;
		if (A.hour > B.hour)
			return false;
		
		if (A.minute < B.minute)
			return true;
		if (A.minute > B.minute)
			return false;

		if (A.second < B.second)
			return true;
		if (A.second > B.second)
			return false;

		return false;
	}
	
	bool operator <= (const Time& A, const Time& B)
	{
		if (A.hour <= B.hour)
			return true;
		if (A.hour > B.hour)
			return false;

		if (A.minute <= B.minute)
			return true;
		if (A.minute > B.minute)
			return false;

		if (A.second <= B.second)
			return true;
		if (A.second > B.second)
			return false;

		return false;
	}
	
	bool operator > (const Time& A, const Time& B)
	{
		if (A.hour > B.hour)
			return true;
		if (A.hour < B.hour)
			return false;

		if (A.minute > B.minute)
			return true;
		if (A.minute < B.minute)
			return false;

		if (A.second > B.second)
			return true;
		if (A.second < B.second)
			return false;

		return false;
	}

	bool operator >= (const Time& A, const Time& B)
	{
		if (A.hour >= B.hour)
			return true;
		if (A.hour < B.hour)
			return false;

		if (A.minute >= B.minute)
			return true;
		if (A.minute < B.minute)
			return false;

		if (A.second >= B.second)
			return true;
		if (A.second < B.second)
			return false;

		return false;
	}

	strong_ordering operator <=> (const Time& A, const Time& B)
	{
		if (A.hour < B.hour)
			return strong_ordering::less;
		if (A.hour > B.hour)
			return strong_ordering::greater;

		if (A.minute < B.minute)
			return strong_ordering::less;
		if (A.minute > B.minute)
			return strong_ordering::greater;

		if (A.second < B.second)
			return strong_ordering::less;
		if (A.second > B.second)
			return strong_ordering::greater;

		return strong_ordering::equivalent;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////

	Date::Date()
	{
		day = 0;
		month = 0;
		year = 0;
	}

	Date::Date(u8 new_day, u8 new_month, u32 new_year)
	{
		day = new_day;
		month = new_month;
		year = new_year;
	}

	string Date::toString() const
	{
		string day_str;
		string month_str;
		string year_str;

		if (day < 10)
			day_str = "0" + to_string(u16(day));
		else
			day_str = to_string(u16(day));

		switch (month)
		{
			case 1:
				month_str = "January";
			break;

			case 2:
				month_str = "February";
			break;

			case 3:
				month_str = "March";
			break;

			case 4:
				month_str = "April";
			break;

			case 5:
				month_str = "May";
			break;

			case 6:
				month_str = "June";
			break;

			case 7:
				month_str = "July";
			break;

			case 8:
				month_str = "August";
			break;

			case 9:
				month_str = "September";
			break;

			case 10:
				month_str = "October";
			break;

			case 11:
				month_str = "November";
			break;

			case 12:
				month_str = "December";
			break;

			default: break;
		}

		year_str = to_string(year);

		return day_str + " " + month_str + " " + year_str;
	}

	wstring Date::toWideString() const
	{
		wstring day_wstr;
		wstring month_wstr;
		wstring year_wstr;

		if (day < 10)
			day_wstr = L"0" + to_wstring(u16(day));
		else
			day_wstr = to_wstring(u16(day));

		switch (month)
		{
			case 1:
				month_wstr = L"January";
				break;

			case 2:
				month_wstr = L"February";
				break;

			case 3:
				month_wstr = L"March";
				break;

			case 4:
				month_wstr = L"April";
				break;

			case 5:
				month_wstr = L"May";
				break;

			case 6:
				month_wstr = L"June";
				break;

			case 7:
				month_wstr = L"July";
				break;

			case 8:
				month_wstr = L"August";
				break;

			case 9:
				month_wstr = L"September";
				break;

			case 10:
				month_wstr = L"October";
				break;

			case 11:
				month_wstr = L"November";
				break;

			case 12:
				month_wstr = L"December";
				break;

			default: break;
		}

		year_wstr = to_wstring(year);

		return day_wstr + L" " + month_wstr + L" " + year_wstr;
	}

	bool operator == (const Date& A, const Date& B)
	{
		return (A.day == B.day) && (A.month == B.month) && (A.year == B.year);
	}

	bool operator != (const Date& A, const Date& B)
	{
		return (A.day != B.day) || (A.month != B.month) || (A.year != B.year);
	}

	bool operator < (const Date& A, const Date& B)
	{
		if (A.year < B.year)
			return true;
		if (A.year > B.year)
			return false;

		if (A.month < B.month)
			return true;
		if (A.month > B.month)
			return false;

		if (A.day < B.day)
			return true;
		if (A.day > B.day)
			return false;

		return false;
	}

	bool operator <= (const Date& A, const Date& B)
	{
		if (A.year <= B.year)
			return true;
		if (A.year > B.year)
			return false;

		if (A.month <= B.month)
			return true;
		if (A.month > B.month)
			return false;

		if (A.day <= B.day)
			return true;
		if (A.day > B.day)
			return false;

		return false;
	}

	bool operator > (const Date& A, const Date& B)
	{
		if (A.year > B.year)
			return true;
		if (A.year < B.year)
			return false;

		if (A.month > B.month)
			return true;
		if (A.month < B.month)
			return false;

		if (A.day > B.day)
			return true;
		if (A.day < B.day)
			return false;

		return false;
	}

	bool operator >= (const Date& A, const Date& B)
	{
		if (A.year >= B.year)
			return true;
		if (A.year < B.year)
			return false;

		if (A.month >= B.month)
			return true;
		if (A.month < B.month)
			return false;

		if (A.day >= B.day)
			return true;
		if (A.day < B.day)
			return false;

		return false;
	}

	strong_ordering operator <=> (const Date& A, const Date& B)
	{
		if (A.year < B.year)
			return strong_ordering::less;
		if (A.year > B.year)
			return strong_ordering::greater;

		if (A.month < B.month)
			return strong_ordering::less;
		if (A.month > B.month)
			return strong_ordering::greater;

		if (A.day < B.day)
			return strong_ordering::less;
		if (A.day > B.day)
			return strong_ordering::greater;

		return strong_ordering::equivalent;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////

	Clock::Clock()
	{
		_start = system_clock::now();
		_end = _start;
		_stopped = true;
	}

	TimePoint Clock::getStartTime() const
	{
		return _start;
	}

	TimePoint Clock::getEndTime() const
	{
		return _end;
	}

	void Clock::startTimer()
	{
		_start = system_clock::now();
		_stopped = false;
	}

	Duration Clock::stopTimer()
	{
		_end = getCurrentTimePoint();
		_stopped = true;
		return _end - _start;
	}

	Duration Clock::resumeTimer()
	{
		_stopped = false;
		return _end - _start;
	}

	Duration Clock::restartTimer()
	{
		TimePoint t_now(getCurrentTimePoint());
		Duration time_elapsed(t_now - _start);
		_start = t_now;
		_stopped = false;
		return time_elapsed;
	}

	TimePoint Clock::getCurrentTimePoint() const
	{
		return system_clock::now();
	}

	Duration Clock::getElapsedTime() const
	{
		if (_stopped)
			return _end - _start;

		return getCurrentTimePoint() - _start;
	}

	u8 Clock::getCurrentSecond()
	{
		return getCurrentTime().second;
	}

	u8 Clock::getCurrentMinute()
	{
		return getCurrentTime().minute;
	}

	u8 Clock::getCurrentHour()
	{
		return getCurrentTime().hour;
	}

	Time Clock::getCurrentTime()
	{
		const time_t now = time(nullptr);
		tm cal_time;
		localtime_s(&cal_time, &now);

		return Time(cal_time.tm_hour, cal_time.tm_min, cal_time.tm_sec);
	}

	u8 Clock::getCurrentDay()
	{
		return getCurrentDate().day;
	}

	u8 Clock::getCurrentMonth()
	{
		return getCurrentDate().month;
	}

	u32 Clock::getCurrentYear()
	{
		return getCurrentDate().year;
	}

	Date Clock::getCurrentDate()
	{
		const time_t now = time(nullptr);
		tm cal_time;
		localtime_s(&cal_time, &now);

		return Date(cal_time.tm_mday, cal_time.tm_mon + 1, cal_time.tm_year + 1900);
	}

	void print(const Time& time)
	{
		cout << time.toString();
	}

	void println(const Time& time)
	{
		cout << time.toString() << '\n';
	}

	void print(const Date& date)
	{
		cout << date.toString();
	}

	void println(const Date& date)
	{
		cout << date.toString() << '\n';
	}
}