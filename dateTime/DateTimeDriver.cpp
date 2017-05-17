//-----------------------------------------------------------------------------
//	File:		DateTimeDriver.cpp
//
//	Function:	main()
//-----------------------------------------------------------------------------
#include <iostream>
#include <cstdlib>
#include <exception>
#include "ArraySort.h"
//-----------------------------------------------------------------------------
//
//	Function:	main()
//	Title:		Making a date, marking time
//	Description:This file contains function main()
//				which tests the date,time,datetime classes
//				and arraySort()
//	Programmer:	Han Jung 
//	Date:		4/28/2017
//	Version:	1.0
//	Environment:Hardware: Dell Inspirion
//				Software: MS Windows 10
//				Compiles under Microsoft Visual C++.Net 2017
//	Input:		Datetime objects, Date objects
//	Output:		Date and Time informations
//	Calls:		DateTime()
//				Date()
//				safeRead()
//				printArray()
//				quickSort()
//	Called By:	n/a
//	Parameters:	None
//	Returns:	EXIT_SUCCESS  = successful 
//	History Log:
//			
//			4/28/17 HJ Completed 1.0
//-----------------------------------------------------------------------------
using namespace HJ_ARRAYSORT;
int main() {
	char c = ' ';
	int arraySize = 0;
	int otherArraySize = 0;
	Comparable** entries = nullptr;
	Comparable** otherEntries = nullptr;
	DateTime current;
	CTime time;
	cout << "Date Time program by Han S. Jung" << endl;
	cout << "v_20170501_7" << endl; //version name to keep track of compile
	cout << "The current day and time is" << endl << current << endl;
	cout << "Enter a time (hh:mm:ss): ";
	cin >> time;
	while (!(cin))
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid entry." << endl;
		cout << "Enter NUMBERS in hh:mm:ss format: ";
		cin >> time;
	}
	cout << time << endl;
	cout << "Enter number of date/times to be stored" << endl;
	cin >> arraySize;
	while (arraySize < 1 || !(cin))
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Enter a number greater than 1: ";
		cin >> arraySize;
	}
	entries = new Comparable*[arraySize];
	for (short i = 0; i < arraySize; i++)
		entries[i] = nullptr;
	//take in array of date/time
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	for (short i = 0; i < arraySize; i++) {
		DateTime tempDateTime;
		Comparable * tempDateTimeComparable = &tempDateTime;
		cout << "DateTime " << i + 1 << " [mm/dd/yyyy hh:mm:ss]: ";
		safeRead(cin, tempDateTimeComparable, 
			"Make sure the year is between 1700 and 9999: ");
		entries[i] = new DateTime(dynamic_cast<DateTime&>(*tempDateTimeComparable));
	}
	cout << "Date/Time you've entered: " << endl;
	//print entered date/times
	printArray(cout, entries, arraySize);
	cout << "Sorted date/time: " << endl;
	quickSort(entries, 0 , arraySize-1);
	//prints sorted array
	printArray(cout, entries, arraySize);
	cout << "Enter number of dates to be entered: ";
	cin >> otherArraySize;
	while (otherArraySize < 1 ||!(cin))
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Enter a NUMBER greater than 1: ";
		cin >> otherArraySize;
	}
	otherEntries = new Comparable*[otherArraySize];
	for (short i = 0; i < otherArraySize; i++)
		otherEntries[i] = nullptr;
	//Take in array of dates
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	for (short i = 0; i < otherArraySize; i++) {
		Date tempDate;
		Comparable * tempDateComparable = &tempDate;
		cout << "Date " << i+1 << " [mm/dd/yyyy]: ";
		safeRead(cin, tempDateComparable, 
			"Makes sure date exist and is between 1700 to 9999: ");
		otherEntries[i] = new Date(dynamic_cast<Date&>(*tempDateComparable));
		cout << tempDate.getMonth();
	}
	cout << "Date you've entered: " << endl;
	
	printArray(cout, otherEntries, otherArraySize);
	cout << "Sorted date " << endl;
	quickSort(otherEntries, 0, otherArraySize-1);
	printArray(cout, otherEntries, otherArraySize);

	Date *firstDate = dynamic_cast<Date*>(otherEntries[0]);
	Date *lastDate = dynamic_cast<Date*>(otherEntries[otherArraySize - 1]);
	Date Date1 = firstDate->yesterday();
	Date Date2 = lastDate->tomorrow();
	cout << "Day before earliest date: " << Date1 << endl;
	cout << "Day after most recent date: " << Date2 << endl;
	for (int i = 0; i < arraySize; i++)
	{
		delete entries[i];
	}
	for (int i = 0; i < otherArraySize; i++)
	{
		delete otherEntries[i];
	}
	
	delete[] entries;
	delete[] otherEntries;
	while (cin.get() != '\n') { ; }

	return EXIT_SUCCESS;
}
