//-----------------------------------------------------------------------------
//	File: Date.cpp
//
//	class: Date
//	methods:
//		Date::Date(short day, short month, short year)
//		bool Date::operator==(const Comparable &other)const
//		bool Date::operator<(const Comparable &other)const
//		void Date::setCurrentDate(void)
//		void Date::setDayOfWeek(void)
//		void Date::setDayOfYear(void)
//		short Date::countLeaps(short year)const
//		void Date::setDayOfMonth(short dayOfMonth)
//		void Date::setMonth(short month)
//		void Date::setYear(short year)
//-----------------------------------------------------------------------------
#include "Date.h"

namespace HJ_DATETIME
{
	//-----------------------------------------------------------------------------
	//    method:		Date(short day, short month, short year) -- constructor
	//
	//    description:	creates a new Date object
	// 
	//    Calls:            setCurrentDate()
	//			daysInMonth(month, year)
	//			setDayOfYear()
	//			setDayOfWeek()
	// 
	//    Called By:	ostream& operator<<(ostream& sout, const CComplex &c)
	// 
	//    Parameters:	short day -- day to set
	//			short month -- month to set
	//			short year -- month to set
	//
	//    History Log:
	//			2/9/08  PB  completed version 1.0
	// ----------------------------------------------------------------------------
	Date::Date(void)
	{
		setCurrentDate();
	}
	Date::Date(short day, short month, short year)
	{
		setYear(year);
		setMonth(month);
		setDayOfMonth(day);
	}
	Date::Date(Date &dateToDate)
	{
		setYear(dateToDate.getYear());
		setMonth(dateToDate.getMonth());
		setDayOfMonth(dateToDate.getDayOfMonth());
	}

	//-----------------------------------------------------------------------------
	//    Class:		Date
	//    method:		operator==(const Comparable& other) const
	//    description:	true if the two objects are exactly the same
	// 
	//    Parameters:	const Comparable &other  -- the other Date to compare
	//    Called By:	main, >=, <=
	//    Returns:      true if the two objects are exactly the same;
	//				    false otherwise
	//    History Log:
	//			5/8/16  PB  completed version 1.1
	//-----------------------------------------------------------------------------
	bool Date::operator==(const Comparable &other) const
	{
		//Comparable must be validated to be date
		//Other operators will be written similarly to this
		bool returnValue = false;
		try
		{
			const Date &otherDate =
				//Should throw exception if types do not match.
				dynamic_cast<const Date&>(other);
			if (m_year == otherDate.m_year && m_dayOfYear ==
				otherDate.m_dayOfYear)
				returnValue = true;
		}
		catch (bad_cast e)
		{
		}
		return returnValue;
	}
	//-----------------------------------------------------------------------------
	//    Class:		Date
	//    method:		operator<(const Comparable& other) const
	//
	//    description:	true if the current object is before other
	// 
	//    Parameters:	const Comparable &other  -- the other Date to compare
	//
	//    Called By:	main, >, <=
	//
	//    Exceptions:	throws bad_cast if other is not a Date
	// 
	//    Returns:		true if the current object is before other;
	//				false otherwise
	//    History Log:
	//			4/25/17 HS	completed version 1.2
	//			5/8/16  PB  completed version 1.1
	// ----------------------------------------------------------------------------
	bool Date::operator<(const Comparable &other) const
	{
		bool returnValue = false;
		try
		{
			const Date &otherDate = dynamic_cast<const Date&>(other);
			if (m_year < otherDate.m_year)
				returnValue = true;
			if (m_year == otherDate.m_year)
			{
				if (m_dayOfYear < otherDate.m_dayOfYear)
					returnValue = true;
			}
		}
		catch (bad_cast e)
		{
		}
		return returnValue;
	}
	//-----------------------------------------------------------------------------
	//    Class:		Date
	//    method:		setCurrentDate()
	//
	//    description:	sets the date from the system clock
	// 
	//    Called By:	constructor, mutators
	//
	//    History Log:
	//			2/9/08  PB  completed version 1.0
	// ----------------------------------------------------------------------------
	void Date::setCurrentDate(void)
	{
		time_t rawtime;
		tm *currentTimePtr;
		time(&rawtime);
		currentTimePtr = localtime(&rawtime);

		m_year = currentTimePtr->tm_year + 1900;
		m_month = currentTimePtr->tm_mon + 1; //Jan is given as 0;
		m_dayOfMonth = currentTimePtr->tm_mday;
		setDayOfYear();
		setDayOfWeek();
	}

	//-----------------------------------------------------------------------------
	//    Class:		Date
	//    method:		setDayOfWeek(void)
	//
	//    description:	validates and sets the proper day of the week
	//
	//    History Log:
	//					4/28/17 HJ completed 4/28/17
	// ----------------------------------------------------------------------------
	void Date::setDayOfWeek(void)
	{
		short year = getYear();
		short month = getMonth();
		short day = getDayOfMonth();
		//Using Sakamoto's method
		static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
		year -= (month < 3);
		m_dayOfWeek = (year + (year / 4) - (year / 100) + (year / 400) + t[month - 1] + day) % 7;
	}

	//-----------------------------------------------------------------------------
	//    Class:		Date
	//    method:		setDayOfYear(void)
	//
	//    description:	validates and sets the proper day of the year
	//
	//    History Log:
	//			4/24/17 HJ	completed version 1.1
	//			2/9/08  PB  completed version 1.0
	// ----------------------------------------------------------------------------
	void Date::setDayOfYear(void)
	{
		//set day of year to days from current month
		short dayOfYear = getDayOfMonth();
		short month = getMonth();
		short year = getYear();
		//loop and add days from previous month
		for (short i = 1; i < month; i++)
		{
			dayOfYear += daysInMonth(i, year);
		}
		m_dayOfYear = dayOfYear;
	}
	//-----------------------------------------------------------------------------
	//    Class:			Date
	//    method:			countLeaps(short year)const
	//
	//    description:	returns the number of leap years from 1760 to year
	// 
	//    Calls:            isLeapYear(short)
	// 
	//    Returns:          the number of leap years from 1760 to year 
	//
	//    History Log:
	//                           2/9/08  PB  completed version 1.0
	//-----------------------------------------------------------------------------
	short Date::countLeaps(short year)const
	{
		short leaps = 0;
		for (short i = LOWYEAR; i < year; i++)
			if (isLeapYear(i))
				leaps++;
		return leaps;
	}

	//-----------------------------------------------------------------------------
	//    Class:		Date
	//    method:		setDayOfMonth(short dayOfMonth)
	//
	//    description:	mutator for m_dayOfMonth
	// 
	//    Calls:            daysInMonth(short, short)
	//			setDayOfYear()
	//			setDayOfWeek()
	// 
	//    Parameters:	dayOfMonth --  day of month to set
	//
	//    History Log:
	//			2/9/08  PB  completed version 1.0
	//-----------------------------------------------------------------------------
	void Date::setDayOfMonth(short dayOfMonth)
	{
		m_dayOfMonth = dayOfMonth;
		setDayOfYear();
		setDayOfWeek();
	}

	//-----------------------------------------------------------------------------
	//    Class:	Date
	//    method:		setMonth(short dmonth)
	//
	//    description:	mutator for m_month
	// 
	//    Calls:            daysInMonth(short, short)
	//			setDayOfYear()
	//			setDayOfWeek()
	// 
	//    Parameters:	month --  month to set
	//
	//    History Log:
	//			4/28/17  HJ  completed version 1.0
	//-----------------------------------------------------------------------------
	void Date::setMonth(short month)
	{
		m_month = month;
	}
	//-----------------------------------------------------------------------------
	//    Class:		Date
	//    method:		setYear(short year)
	//
	//    description:	mutator for m_year
	// 
	//    Calls:            isLeapYear(short)
	//			setDayOfYear()
	//			setDayOfWeek()
	// 
	//    Parameters:	year --  year to set
	//
	//    History Log:
	//			 4/28/17 HJ  completed version 1.0
	//-----------------------------------------------------------------------------
	void Date::setYear(short year)
	{
		m_year = year;
	}
	//-----------------------------------------------------------------------------
	//    Class:		Date
	//    method:		tomorrow() const
	//
	//    description:	returns Date after date in object
	// 
	//    Calls:        daysInMonth()
	//    Parameters:	n/a
	//
	//    History Log:
	//			 4/28/17 HJ  completed version 1.0
	//-----------------------------------------------------------------------------
	Date Date::tomorrow() const
	{
		short day = getDayOfMonth();
		short month = getMonth();
		short year = getYear();
		if (day + 1 > daysInMonth(month, year))
		{
			day = 1;

			if (month + 1 > MONTHSINYEAR)
			{
				month = 1;
				year++;
			}
			else {
				month++;
			}
		}
		else {
			day++;
		}
		return Date(day, month, year);
	}
	//-----------------------------------------------------------------------------
	//    Class:		Date
	//    method:		yesterday() const
	//
	//    description:	returns Date before date in object
	// 
	//    Calls:        daysInMonth()
	//    Parameters:	n/a
	//
	//    History Log:
	//			 4/28/17 HJ  completed version 1.0
	//-----------------------------------------------------------------------------
	Date Date::yesterday()const
	{
		short day = getDayOfMonth();
		short month = getMonth();
		short year = getYear();
		if (day - 1 < 1)
		{
			if (month - 1 < 1)
			{
				--year;
				month = 12;
				day = daysInMonth(month, year);
			}
			else {
				--month;
				day = daysInMonth(month, year);
			}
		}
		else {
			--day;
		}
		return Date(day, month, year);
	}
	//-----------------------------------------------------------------------------
	//    Class:		Date
	//    method:		isLeapYear(short year)
	//
	//    description:	return true if year for parameter is leap year
	//    Parameters:	short year -- year to calculate
	//	  Called By:	daysInMonth()
	//    History Log:
	//			 4/28/17 HJ  completed version 1.0
	//-----------------------------------------------------------------------------
	bool Date::isLeapYear(short year)
	{
		if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
			return true;
		return false;
	}
	//-----------------------------------------------------------------------------
	//    Class:		Date
	//    method:		daysInMonth(short month, short year)
	//
	//    description:	returns how many days are in given month at given year
	//    Parameters:	short year -- year to calculate
	//	  Called By:	input()
	//    History Log:
	//			 4/28/17 HJ  completed version 1.0
	//-----------------------------------------------------------------------------
	short Date::daysInMonth(short month, short year)
	{
		short days;
		if (month < 8 && month % 2 == 0)
		{
			days = 30;
		}
		else if (month < 8 && month % 2 == 1)
			days = 31;
		else if (month > 8 && month % 2 == 0)
			days = 31;
		else if (month > 8 && month % 2 == 1)
			days = 30;
		if (month == 2)
		{
			if (isLeapYear)
				days = 29;
			else
				days = 28;
		}
		return days;
	}
	//-----------------------------------------------------------------------------
	//    Class:		Date
	//    method:		void input(istream& sin)
	//
	//    description:	takes input from istream with correct format
	//    Parameters:	istream& sin
	//	  Called By:	<< operator
	//	  Calls:        setDayOfMonth();
	//					setMonth();
	//					setYear();
	//					daysInMonth();
	//    History Log:
	//			 4/28/17 HJ  completed version 1.0
	//-----------------------------------------------------------------------------
	void Date::input(istream& sin)
	{
		short year = 0; short month = 1; short day = 1;
		bool isOkay = true;
		char c = ' ';
		sin.get(c);
		if (c != '\n')
		{
			sin.putback(c);
			sin >> month;
			if (month <= 0 || month > MONTHSINYEAR)
				isOkay = false;
			sin.get(c);
			if (c == '/') {
				sin >> day;
				if (day<=0)
					isOkay = false;
				sin.get(c);
				if (c == '/') {
					sin >> year;
					if (year <LOWYEAR || year > MAXYEAR)
						isOkay = false;
				}
			}
		}
		if (day > daysInMonth(month, year))
			isOkay = false;
		if (!isOkay)
			sin.setstate(ios::failbit);
		setDayOfMonth(day);
		setMonth(month);
		setYear(year);
	}
	//-----------------------------------------------------------------------------
	//    Class:		Date
	//    method:		void print(ostream& oin)
	//
	//    description:	give output to ostream with correct format
	//    Parameters:	istream& sin
	//	  Called By:	>> operator
	//    History Log:
	//			 4/28/17 HJ  completed version 1.0
	//-----------------------------------------------------------------------------
	void Date::print(ostream& sout)const
	{
		sout << weekdayName(getDayOfWeek()) << ", " << monthName(getMonth()) << ' '
			<< getDayOfMonth() << ", " << getYear() << " ";
	}
	//-----------------------------------------------------------------------------
	//    Class:		Date
	//    method:		monthName(int monthNum)
	//    description:	takes month by number and give name in string
	//    Parameters:	int monthNum
	//
	//    History Log:
	//			 4/28/17 HJ  completed version 1.0
	//-----------------------------------------------------------------------------
	const char* Date::monthName(int monthNum)
	{
		char* month = "Invalid Month";
		switch (monthNum) {
		case 1:
			month = "January";
			break;
		case 2:
			month = "February";
			break;
		case 3:
			month = "March";
			break;
		case 4:
			month = "April";
			break;
		case 5:
			month = "May";
			break;
		case 6:
			month = "June";
			break;
		case 7:
			month = "July";
			break;
		case 8:
			month = "August";
			break;
		case 9:
			month = "September";
			break;
		case 10:
			month = "October";
			break;
		case 11:
			month = "November";
			break;
		case 12:
			month = "December";
			break;
		}
		return month;
	}
	//-----------------------------------------------------------------------------
	//    Class:		Date
	//    method:		weekdayName(int weekdayNum)
	//    description:	takes day in week by number and give name in string
	//    Parameters:	int weekdayNum
	//
	//    History Log:
	//			 4/28/17 HJ  completed version 1.0
	//-----------------------------------------------------------------------------
	const char* Date::weekdayName(int weekdayNum)
	{
		char* day = "Invalid day";
		switch (weekdayNum) {
		case 0:
			day = "Sunday";
			break;
		case 1:
			day = "Monday";
			break;
		case 2:
			day = "Tuesday";
			break;
		case 3:
			day = "Wednesday";
			break;
		case 4:
			day = "Thursday";
			break;
		case 5:
			day = "Friday";
			break;
		case 6:
			day = "Saturday";
			break;
		}
		return day;
	}
	ostream & operator<<(ostream & sout, const Date & date)
	{
		date.print(sout);
		return sout;
	}
	istream & operator>>(istream & sin, Date & date)
	{
		date.input(sin);
		return sin;
	}
}