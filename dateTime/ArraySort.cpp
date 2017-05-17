#include "ArraySort.h"
namespace HJ_ARRAYSORT
{
	//-----------------------------------------------------------------------------
	//    function:		safeRead(istream& sin, Comparable* d, const char* re)
	//    description:	safely reads in a DateTime (d) from sin.
	//				Re-prompts and re-enters if input is invalid
	//    
	//    Input:		Comparable* d from sin
	// 
	//    Called By:	main
	// 
	//    Parameters:	istream& sin  -- the input stream
	//			Comparable* d -- pointer to the object input
	//			const char* prompt  -- prompt, if necessary
	// 
	//    Returns:          void 
	//
	//    History Log:
	//			2/9/08  PB  completed version 1.0
	// ----------------------------------------------------------------------------	
	void safeRead(istream& sin, Comparable* d, const char* prompt)
	{
		const int BUFFERSIZE = 256;
		d->input(sin);
		while (!sin)
		{	// read in number--enter loop if fail
			sin.clear();		// clear fail
			sin.ignore(BUFFERSIZE, '\n');	// read past newline
			cout << prompt;  // re-prompt
			d->input(sin);
		}
		// read past newline once input succeeds
		sin.ignore(BUFFERSIZE, '\n');
	}

	//-----------------------------------------------------------------------------
	//    function:	void printArray(ostream & sout, Comparable **a, int size)
	//    description:	can print out an array of DateTime *
	// 
	//    Output:		Comparable* d sout
	//
	//    Called By:	main
	// 
	//    Parameters:	ostream& sout  -- the output stream
	//			Comparable** a -- array of pointers to the objects
	//			int size  -- number of elements in the array
	// 
	//    Returns:          void 
	//
	//    History Log:
	//			2/9/08  PB  completed version 1.0
	// ----------------------------------------------------------------------------	
	void printArray(ostream & sout, Comparable **a, int size)
	{
		for (int i = 0; i < size; i++)
		{
			a[i]->print(sout);
			sout << endl;
		}
		sout << endl;
	}
	//-----------------------------------------------------------------------------
	//    function:		void quickSort(Comparable** arr, int from, int to)
	//    description:	sorts given array from Comparable class within given 
	//					indices
	// 
	//    Called By:	main
	// 
	//    Parameters:	Comparable** arr -- given array of object
	//					int from -- starting index
	//					int to -- end index
	// 
	//    Returns:      void 
	//
	//    History Log:
	//			4/28/17 HJ completed version 1.0
	// ----------------------------------------------------------------------------	
	void quickSort(Comparable** arr, int from, int to)
	{
		int size = to - from;
		if (size <= 3)
			insertionSort(arr, from, to);
		else
		{
			int mid = partition(arr, from, to);
			quickSort(arr, from, mid);
			quickSort(arr, mid, to);
		}
	}
	//-----------------------------------------------------------------------------
	//    function:		void partition(Comparable** arr, int from, int to)
	//    description:	finds the median value so that quicksort can deal with
	//					array of half size
	//    
	//	  Calls:		sortFirstMiddleLast()
	//					swap()
	//    Called By:	quicksort()
	// 
	//    Parameters:	Comparable** arr -- given array of object
	//					int from -- starting index
	//					int to -- end index
	// 
	//    Returns:      void 
	//
	//    History Log:
	//			4/28/17 HJ completed version 1.0
	// ----------------------------------------------------------------------------	
	int partition(Comparable** arr, int from, int to)
	{
		//Comparable* from =  arr // to = arr+to ?
		int arrSize = to-from;
		int begin, end;
		int pivotPoint = static_cast<int>(arrSize / 2);
		SortFirstMiddleLast(arr, from, pivotPoint, to);
		swap(arr[pivotPoint], arr[to - 1]);
		begin = from + 1; //arr[0] was found line 114, start with next one.
		end = to - 2;
		pivotPoint = to - 1;
		while (begin <= end)
		{
			while (*arr[begin] < *arr[pivotPoint])
				begin++;
			while (*arr[pivotPoint] < *arr[end])
				end--;
			swap(arr[begin], arr[end]);
			begin++;
			end--;
		}
		return begin; //begin should == end;
	}
	//-----------------------------------------------------------------------------
	//    function:		void SortFirstMiddleLast(Comparable** arr, int from,
	//					int mid, int to)
	//    description:	Sort the array so within indices that begin, is halfpoint 
	//					and end.
	//    
	//    Input:		n/a
	// 
	//    Called By:	main
	// 
	//    Parameters:	Comparable** arr -- given array of object
	//					int from -- starting index
	//					int to -- end index
	// 
	//    Returns:      void 
	//
	//    History Log:
	//			4/28/17 HJ completed version 1.0
	// ----------------------------------------------------------------------------	
	void SortFirstMiddleLast(Comparable** arr, int from, int mid, int to)
	{
		if (*arr[mid] < *arr[from]) //with no index *(*(arr+mid)) < *(*arr+from))
			swap(arr[mid], arr[from]);
		if (*arr[to] < *arr[mid])
			swap(arr[to], arr[mid]);
		if (*arr[mid] < *arr[from])
			swap(arr[mid], arr[from]);
	}
	//-----------------------------------------------------------------------------
	//    function:		void insertionSort(Comparable** arr, int from, int to)
	//    description:	sort the array with insertion sort algorithm.
	//    
	//    Input:		n/a
	// 
	//    Called By:	quicksorts()
	//    Parameters:	Comparable** arr -- given array of object
	//					int from -- starting index
	//					int to -- end index
	// 
	//    Returns:      void 
	//
	//    History Log:
	//			4/28/17 HJ completed version 1.0
	// ----------------------------------------------------------------------------	
	void insertionSort(Comparable** arr, int from, int to)
	{

		Comparable *temp = arr[from]; // *(arr+from)
		Comparable *value = arr[from];    // i.e. {5,3,4,1,2}
		for (int i = from + 1; i <= to; i++)  
		{
			temp = arr[i]; //3
			int j = i;
			for (j = i; j > 0; j--)
			{
				value = arr[j - 1]; //5 
				if (*temp < *value)   //3<5
					arr[j] = arr[j-1];  
				else break;
			}
			arr[j] = temp;
		}
	}
	//-----------------------------------------------------------------------------
	//    function:		void swap(Comparable*& a, Comparable* &b)
	//    description:	swaps two elements in the array/
	//    
	//    Input:		n/a
	// 
	//    Called By:	firstMiddleLast()
	//					partition()
	//    Parameters:	Comparable*& a, Comparable* &b -- two swapping elemets
	// 
	//    Returns:      void 
	//    History Log:
	//			4/28/17 HJ completed version 1.0
	// ----------------------------------------------------------------------------	
	void swap(Comparable*& a, Comparable* &b)
	{
		Comparable* temp = a;
		a = b;
		b = temp;
	}
}
