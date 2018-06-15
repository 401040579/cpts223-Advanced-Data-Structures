/*******************************************************************************************
* Programmer: Ran Tao
* Class: CptS 122, Fall  2016
* Programming Assignment: PA 1
* Date: Sep 20, 2016
* Description: For this project, we will be empirically evaluating bubble sort and comparing it to our own Big­O
analysis. To do this, we will use a range of input values and time how long it takes bubblesort to finish
the sorting of N random values. These timings will be plotted on a Cartesian Coordinate grid to
compare with our expected algorithm behavior. We will also test bubblesort on best and worst case
inputs to see how it runs.
*******************************************************************************************/
#include <iostream>
#include <chrono>
#include <ctime>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;

class mainProgram
{
public:
	float do_bubblesort(std::vector<int> &arr, int n);

	vector<int> randVector(int num);

	vector<int> sortedVector(int num);

	vector<int> sortedReversedVector(int num);

	void run();
};
