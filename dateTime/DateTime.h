//-----------------------------------------------------------------------------
//	File: DateTime.h
//
//	class: DateTime
//-----------------------------------------------------------------------------
#ifndef DATETIME_H
#define DATETIME_H

//-----------------------------------------------------------------------------
//    Class:		DateTime
//
//    File:         DateTime.cpp
//
//    Title:        DateTime Class
//    Description:	This file contains the class definition for Date
//
//    Programmer:	Paul Bladek
//					Han Jung
//   
//    Date:         4/28/2017
// 
//    Version:          1.0
//  
//    Environment:   Hardware: IBM Pentium  
//                   Software:  WinXP or later or .NET for execution;
//
//    Compiles under Microsoft C++ 2005
// 
//	  class Date:
//
//	  Properties:
//		short m_year;		// full year, i.e., 2006
//		short m_month;		// 0 - 11
//		short m_dayOfMonth; // 1 - days in that month
//		short m_dayOfYear;  // 1 - 365 or 366
//		short m_dayOfWeek;	// 0 - 6
//
//	  Methods:
//		Inline:
//		Static:
//			static bool isLeapYear(short year) 
//				true if year is a leap year; false otherwise
//			static short daysInMonth(short month, short year) 
//				returns the number of days in month for that year
//			static const char* monthName(int monthNum) 
//				returns a string representation of monthNum
//			static const char* weekdayName(int weekdayNum) 
//				returns a string representation of weekdayNum
//		Non-Static:
//			short getDayOfWeek() const
//			short getDayOfMonth() const
//			short getMonth() const
//			short getYear() const
//			short getDayOfYear() const
//
//		Non-inline:
//					
//			virtual bool equals(const Comparable &other)const
//			virtual lessthan(const Comparable &other)const
//			virtual void input(istream& sin)
//			virtual void print(ostream& sout)const
//
//			void setMonth(short monthIn)
//			void setYear(short yearIn)
//			void setCurrentDate(void)
//			void setDayOfYear(void)
//			void setDayOfWeek(void)
//			void setDayOfMonth(short dayOfMonth)
//			Date tomorrow()const
//			Date yesterday()const
//			short countLeaps(short year)const
//			void print(ostream& sout)const;
//
//    History Log:
//                      4/7/08  PB  completed version 1.0
// ----------------------------------------------------------------------------
#include "Date.h"
#include "CTime.h"
namespace HJ_DATETIME
{
	class DateTime : public Date, public CTime
	{
	public:
		DateTime();
		DateTime(short day, short month = 0, short year = 0, short hour = 0, short min = 0, short sec = 0);
		DateTime(const Date& date, const CTime& time);
		virtual ~DateTime(void) {}
		virtual bool operator==(const Comparable &other)const;
		virtual bool operator!=(const Comparable &other)const
		{
			return !((*this) == other);
		}
		virtual bool operator<(const Comparable &other)const;
		virtual bool operator>(const Comparable &other)const
		{
			return !((*this) < other) && !((*this) == other);
		}
		virtual bool operator<=(const Comparable &other)const
		{
			return !((*this) > other);
		}
		virtual bool operator>=(const Comparable &other)const
		{
			return !((*this) < other);
		}

		virtual void input(istream& sin);
		virtual void print(ostream& sout)const;
	};
	ostream& operator<<(ostream& sout, const DateTime& dateTime);
	istream& operator>>(istream& sin, DateTime& dateTime);
}

#endif