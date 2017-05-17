//-----------------------------------------------------------------------------
//	File: DateTime.cpp
//
//	class: DateTime
//	methods:
//		bool DateTime::operator==(const Comparable &other) const
//		bool DateTime::operator<(const Comparable &other)const
//		void DateTime::input(istream& sin)
//		void DateTime::print(ostream& sout) const
//		ostream& operator<<(ostream& sout, const DateTime& dateTime)
//		ostream& operator<<(ostream& sout, const DateTime& dateTime)
//		
//-----------------------------------------------------------------------------
#include "DateTime.h"
namespace HJ_DATETIME
{
	//constructors
	DateTime::DateTime() 
	{
		CTime();
		Date();
	}
	DateTime::DateTime(short day, short month, short year, short hour,
		short min, short sec )
	{
		Date(day, month, year);
		CTime(hour, min, sec);
	}
	DateTime::DateTime(const Date &date, const CTime &time)
	{
		Date(date.getYear(), date.getMonth(), date.getDayOfMonth());
		CTime(time.getHour(), time.getMinute(), time.getSecond());
	}
	//-----------------------------------------------------------------------------
	//    Class:			DateTime
	//	  Method:			bool DateTime::operator==(const Comparable &other)const
	//	  Description:		The equals to operator for DateTime objects   
	//    Called By:		>,<,<=,>=,!= operators
	//    Parameters:		const Comparable &other
	//    Returns:          true or false
	//    History Log:
	//			4/28/17 HJ completed version 1.0
	// ----------------------------------------------------------------------------
	bool DateTime::operator==(const Comparable &other) const
	{
		bool returnValue = false;
		try
		{
			const DateTime &otherDateTime = dynamic_cast<const DateTime&>(other);
			if (m_year == otherDateTime.m_year && m_dayOfYear == 
				otherDateTime.m_dayOfYear && m_hour == otherDateTime.m_hour && 
				m_minute == otherDateTime.m_minute && m_second == 
				otherDateTime.m_second)	
				returnValue = true;
		}
		catch (bad_cast e)
		{}
		return returnValue;
	}
	//-----------------------------------------------------------------------------
	//    Class:			DateTime
	//	  Method:			bool DateTime::operator<(const Comparable &other)const
	//	  Description:		The equals to operator for DateTime objects   
	//    Called By:		>,<=,>= operators
	//    Parameters:		const Comparable &other
	//    Returns:          true or false
	//    History Log:
	//			4/28/17 HJ completed version 1.0
	// ----------------------------------------------------------------------------
	bool DateTime::operator<(const Comparable &other)const
	{
		bool returnValue = false;
		try
		{
			const DateTime &otherDateTime = dynamic_cast<const DateTime&>(other);
			if (m_year < otherDateTime.m_year)
				returnValue = true;
			else if (m_year == otherDateTime.m_year)
			{
				if (m_dayOfYear < otherDateTime.m_dayOfYear)
					returnValue = true;
				else if (m_dayOfYear == otherDateTime.m_dayOfYear)
				{
					if (m_hour < otherDateTime.m_hour)
						returnValue = true;
					else if (m_hour == otherDateTime.m_hour)
					{
						if (m_minute < otherDateTime.m_minute)
							returnValue = true;
						else if (m_minute == otherDateTime.m_minute && m_second < 
							otherDateTime.m_second)
							returnValue = true;
					}
				}
			}
		}
		catch (bad_cast e)
		{}
		return returnValue;
	}
	//-----------------------------------------------------------------------------
	//    Class:		DateTime
	//	  method:       void DateTime::input(istream& sin)
	//    description:	Takes input for Date/Time inputs
	//    Called By:	operator >>
	//	  Calls:		setHour(hour);
	//					setMinute(minute);
	//					setSecond(second);
	//    History Log:
	//			4/28/17 HJ completed version 1.0
	// ----------------------------------------------------------------------------
	void DateTime::input(istream& sin)
	{
		Date::input(sin);
		CTime::input(sin);
	}
	//-----------------------------------------------------------------------------
	//    Class:		DateTime
	//	  method:       void DateTime::print(ostream& sout) const
	//    description:	Prints Date and Time
	//    Called By:	operator <<
	//	  Calls:		getHour(hour);
	//					getMinute(minute);
	//					getSecond(second);
	//    History Log:
	//			4/28/17 HJ completed version 1.0
	// ----------------------------------------------------------------------------
	void DateTime::print(ostream& sout) const
	{
		Date::print(sout);
		CTime::print(sout);
	}
	//-----------------------------------------------------------------------------
	//	  Method:			ostream& operator<<(ostream& sout,
	//						const DateTime& time)
	//	  Description:		output operator for DateTime objects
	//	  Output:			sout
	//	  Calls:			dateTime.print()
	//    Called By:		main()
	//    Parameters:		ostream& sout, const DateTime& time
	//    Returns:          sout - output ostream
	//    History Log:
	//						4/28/17 HJ completed version 1.0
	// ----------------------------------------------------------------------------
	ostream& operator<<(ostream& sout, const DateTime& dateTime)
	{
		dateTime.print(sout);
		return sout;
	}
	//-----------------------------------------------------------------------------
	//	  Method:			ostream& operator>>(ostream& sout, 
	//						const DateTime& time)
	//	  Description:		input operator for DateTime objects
	//	  Output:			sin
	//	  Calls:			dateTime.input()
	//    Called By:		main()
	//    Parameters:		ostream& sout, const DateTime& time
	//    Returns:          istream
	//    History Log:
	//						4/28/17 HJ completed version 1.0
	// ----------------------------------------------------------------------------
	istream& operator>>(istream& sin, DateTime& dateTime)
	{
		dateTime.input(sin);
		return sin;
	}
}
