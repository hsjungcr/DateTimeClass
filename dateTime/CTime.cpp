//-----------------------------------------------------------------------------
//	File: CTime.cpp
//
//	class: CTime
//	methods:
//		void CTime::setCurrentTime()
//
//
//-----------------------------------------------------------------------------
#include "CTime.h"
namespace HJ_DATETIME
{
	//-----------------------------------------------------------------------------
	//    Class:		CTime
	//			method:		setCurrentTime()
	//
	//    description:	sets the time from the system clock
	//
	//    Called By:	constructor, mutators
	//
	//    History Log:
	//			2/9/08  PB  completed version 1.0
	// ----------------------------------------------------------------------------
	void CTime::setCurrentTime()
	{
		time_t rawtime;
		tm *currentTimePtr;
		time(&rawtime);
		currentTimePtr = localtime(&rawtime);

		m_hour = currentTimePtr->tm_hour;
		m_minute = currentTimePtr->tm_min;
		m_second = currentTimePtr->tm_sec;
	}
	//Default Constructor
	CTime::CTime(void)
	{
		setCurrentTime();
	}
	//Constructor with parameters
	CTime::CTime(int hour, int minute, int second) {
		if (hour < MAXHOUR && minute < MAXMINSEC && second < MAXMINSEC &&
			hour >= 0 && minute >= 0 && second >= 0)
		{
			setHour(hour);
			setMinute(minute);
			setSecond(second);
		}
		else
		{
			//If invalid arguments are passed then set the time to current time
			setCurrentTime();
		}
	}
	CTime::CTime(CTime &TimetoTime)
	{
		setHour(TimetoTime.getHour());
		setMinute(TimetoTime.getMinute());
		setSecond(TimetoTime.getSecond());
	}
	//-----------------------------------------------------------------------------
	//    Class:		CTime
	//	  method:       void CTime::setHour(short hour)
	//    description:	assign hour to hour property
	//    Called By:	constructor
	//
	//    History Log:
	//			4/28/17 HJ completed version 1.0
	// ----------------------------------------------------------------------------
	void CTime::setHour(short hour)
	{
		m_hour = hour;
	}
	//-----------------------------------------------------------------------------
	//    Class:		CTime
	//	  method:       void CTime::setMinute(short minute)
	//    description:	assign minute to minute property
	//    Called By:	constructor
	//
	//    History Log:
	//			4/28/17 HJ completed version 1.0
	// ----------------------------------------------------------------------------
	void CTime::setMinute(short minute)
	{
		m_minute = minute;
	}
	//-----------------------------------------------------------------------------
	//    Class:		CTime
	//	  method:       void CTime::setSecond(short second)
	//    description:	assign minute to minute property
	//    Called By:	constructor
	//
	//    History Log:
	//			4/28/17 HJ completed version 1.0
	// ----------------------------------------------------------------------------
	void CTime::setSecond(short second)
	{
		m_second = second;
	}
	//-----------------------------------------------------------------------------
	//    Class:		CTime
	//	  method:       void CTime::input(istream& sin)
	//    description:	Takes input for CTime class in correct format
	//    Called By:	operator >>
	//	  Calls:		setHour(hour);
	//					setMinute(minute);
	//					setSecond(second);
	//    History Log:
	//			4/28/17 HJ completed version 1.0
	// ----------------------------------------------------------------------------
	void CTime::input(istream& sin)
	{
		short second = 0; short minute = 0; short hour = 0;
		bool isOkay = true;
		char c = ' ';
		sin.get(c);
		if (c != '\n')
		{
			sin.putback(c);
			sin >> hour;
			if (hour > MAXHOUR || hour < 0)
				isOkay = false;
			if (hour == MAXHOUR)
				hour = 0;
			sin.get(c);
			if (c == ':') {
				sin >> minute;
				if (minute < 0 || minute >= MAXMINSEC)
					isOkay = false;
				
				sin.get(c);
				if (c == ':') {
					sin >> second;
					if (second < 0 || second >= MAXMINSEC)
						isOkay = false;
					
				}
			}
		}
		if (!isOkay)
			sin.setstate(ios::failbit);
		setHour(hour);
		setMinute(minute);
		setSecond(second);
	}
	//-----------------------------------------------------------------------------
	//    Class:		CTime
	//	  method:       void CTime::print(istream& sin)
	//    description:	Prints time in hh:mm:ss format
	//    Called By:	operator <<
	//	  Calls:		getHour(hour);
	//					getMinute(minute);
	//					getSecond(second);
	//    History Log:
	//			4/28/17 HJ completed version 1.0
	// ----------------------------------------------------------------------------
	void CTime::print(ostream& sout) const
	{
		if (getHour() < 10)
		{
			sout << "0" << getHour() << ":";
		}
		else
		{
			sout << getHour() << ":";
		}
		if (getMinute() < 10)
		{
			sout << "0" << getMinute() << ":";
		}
		else
		{
			sout << getMinute() << ":";
		}
		if (getSecond() < 10)
		{
			sout << "0" << getSecond();
		}
		else
		{
			sout << getSecond();
		}
	}
	//-----------------------------------------------------------------------------
	//    Class:			CTime
	//	  Method:			bool CTime::operator==(const Comparable &other)const
	//	  Description:		The equals to operator for CTime objects   
	//    Called By:		>,<,<=,>=,!= operators
	//    Parameters:		const Comparable &other
	//    Returns:          true or false
	//    History Log:
	//			4/28/17 HJ completed version 1.0
	// ----------------------------------------------------------------------------
	bool CTime::operator==(const Comparable &other)const
	{
		bool returnValue = false;
		try
		{
			const CTime &otherTime =
				//Should throw exception if types do not match.
				dynamic_cast<const CTime&>(other);
			if (m_hour == otherTime.m_hour && m_minute ==
				otherTime.m_minute && m_second == otherTime.m_second)
				returnValue = true;
		}
		catch (bad_cast e)
		{
		}
		return returnValue;
	}
	//-----------------------------------------------------------------------------
	//    Class:			CTime
	//	  Method:			bool CTime::operator<(const Comparable &other)const
	//	  Description:		The equals to operator for CTime objects   
	//    Called By:		>,<=,>= operators
	//    Parameters:		const Comparable &other
	//    Returns:          true or false
	//    History Log:
	//			4/28/17 HJ completed version 1.0
	// ----------------------------------------------------------------------------
	bool CTime::operator<(const Comparable &other)const
	{
		bool returnValue = false;
		try
		{
			const CTime &otherTime = dynamic_cast<const CTime&>(other);
			if (m_hour < otherTime.m_hour)
				returnValue = true;
			if (m_hour == otherTime.m_hour)
			{
				if (m_minute < otherTime.m_minute)
					returnValue = true;
				if (m_minute == otherTime.m_minute)
				{
					if (m_second < otherTime.m_minute)
						returnValue = true;
				}
			}
		}
		catch (bad_cast e)
		{
		}
		return returnValue;
	}
	//-----------------------------------------------------------------------------
	//   
	//	  Method:			ostream& operator<<(ostream& sout, const CTime& time)
	//	  Description:		output operator for CTime objects
	//	  Output:			sout
	//	  Calls:			time.print()
	//    Called By:		main()
	//    Parameters:		ostream& sout, const CTime& time
	//    Returns:          sout - output ostream
	//    History Log:
	//						4/28/17 HJ completed version 1.0
	// ----------------------------------------------------------------------------
	ostream& operator<<(ostream& sout, const CTime& time)
	{
		time.print(sout);
		return sout;
	}
	//-----------------------------------------------------------------------------
	//   
	//	  Method:			ostream& operator>>(ostream& sout, const CTime& time)
	//	  Description:		input operator for CTime objects
	//	  Output:			sin
	//	  Calls:			time.input()
	//    Called By:		main()
	//    Parameters:		ostream& sout, const CTime& time
	//    Returns:          istream
	//    History Log:
	//						4/28/17 HJ completed version 1.0
	// ----------------------------------------------------------------------------
	istream& operator>>(istream& sin, CTime& time)
	{
		time.input(sin);
		return sin;
	}
}