#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <exception>
#include "CTime.h"

using namespace PB_DATETIME;

int main() {
	CTime current_Time;

	cout << current_Time.print;

	return EXIT_SUCCESS;
}