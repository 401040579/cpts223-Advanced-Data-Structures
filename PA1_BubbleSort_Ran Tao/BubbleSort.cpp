#include "BubbleSort.h"
/*************************************************************
* Function: do_bubblesort(std::vector<int> &arr, int n)
* Date Created:9/20/2016
* Description: sorts the vector of n elements passed in
	and returns # of seconds to accomplish the sorting
* Input parameters: std::vector<int>, int
* Returns: float
*************************************************************/
float mainProgram::do_bubblesort(std::vector<int> &arr, int n)
{
	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();
	//start
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n - i - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
	//end
	end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	return elapsed_seconds.count();
}
/*************************************************************
* Function: randVector(int num)
* Date Created:9/20/2016
* Description: enter the num you want to the vector have and 
	got a non-repeat array.
* Input parameters: int
* Returns: vector<int>
*************************************************************/
vector<int> mainProgram::randVector(int num)
{
	//got non-repeat array
	vector<int> vec, vec1;
	for (int i = 0;i < num;++i)
	{
	vec.push_back(i);
	}
	for (int j = 0;j < num;j++) {
	int randNum = rand() % (num - j);
	vec1.push_back(vec[randNum]);
	vec[randNum] = vec[num - j - 1];
	vec.pop_back();
	}
	return vec1;
}
/*************************************************************
* Function: sortedVector(int num)
* Date Created:9/20/2016
* Description: got sorted array
* Input parameters: int
* Returns: vector<int>
*************************************************************/
vector<int> mainProgram::sortedVector(int num)
{
	vector<int> vec;
	for (int i = 0; i < num; ++i)
	{	
		vec.push_back(i);
	}
	return vec;
}
/*************************************************************
* Function: sortedVector(int num)
* Date Created:9/20/2016
* Description: got Reversed sorted array
* Input parameters: int
* Returns: vector<int>
*************************************************************/
vector<int> mainProgram::sortedReversedVector(int num)
{
	vector<int> vec;
	for (int i = 0; i < num; ++i)
	{
		vec.push_back(num - i - 1);
	}
	return vec;
}
/*************************************************************
* Function: run()
* Date Created:9/20/2016
* Description: run main program
* Input parameters: NONE
* Returns: void
*************************************************************/
void mainProgram::run()
{
	//write out a file called BSStats.csv
	ofstream outFile("BSStats.csv");

	//first line
	outFile << "N Size,Optimal time,Worst case time,Average sort time,Run #1,Run #2,Run #3,Run #4,Run #5" << endl;
	//using for loop to make code short.
	int size = 5;
	for (int i = 0; i < 9; i++) {// make size be 10, 50, 100, 500, 1000, 5000, 10000, 50000, 100000.
		if (i % 2)
			size = size * 5;
		else
			size = size * 2;

		vector<int> vec;
		float optTime = 0.0, worstTime = 0.0, aveTime = 0.0, r1 = 0.0, r2 = 0.0, r3 = 0.0, r4 = 0.0, r5 = 0.0;
		//got rand arr
		vec = randVector(size);
		r1 = do_bubblesort(vec, size);
		vec = randVector(size);
		r2 = do_bubblesort(vec, size);
		vec = randVector(size);
		r3 = do_bubblesort(vec, size);
		vec = randVector(size);
		r4 = do_bubblesort(vec, size);
		vec = randVector(size);
		r5 = do_bubblesort(vec, size);
		aveTime = (r1 + r2 + r3 + r4 + r5) / 5;

		//Best case
		vec = sortedVector(size);
		for (int j = 0; j < 5; j++)
			optTime += do_bubblesort(vec, size);
		optTime = optTime / 5;

		//Worst case
		for (int j = 0; j < 5; j++) {
			vec = sortedReversedVector(size);
			worstTime += do_bubblesort(vec, size);
		}
		worstTime = worstTime / 5;

		outFile << setprecision(6) << fixed << size
			<< "," << optTime
			<< "," << worstTime
			<< "," << aveTime
			<< "," << r1
			<< "," << r2
			<< "," << r3
			<< "," << r4
			<< "," << r5 << endl;
		cout << "N=" << size << " Done" << endl;
	}
	outFile.close();
}
