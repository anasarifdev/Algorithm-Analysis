// Libraries to be added

#include <iostream>
#include <math.h>
#include <iomanip>
#include <cstdlib>
#include <chrono>
#include <time.h>
#include <fstream>

using namespace std;
// We use this record to be returned by the function  that finds
// the maximum sub-array.
struct MaxSubArrayRecord
{
	// Holds the starting index of the sub-array.
	int startIndex = 0;
	// Holds the ending index of the sub-array.
	int endIndex = 0;
	// Holds the sum of all the elements within  the  sub-array.
	int maxSum = 0;
};
//ProtoTypes of functions used in the Program
void RandomArray(int array[], int size);
MaxSubArrayRecord FindMaxSubArrayRecursive(int A[], int start, int end);
MaxSubArrayRecord CrossSum(int A[], int start, int mid, int end);


int main()
{


	MaxSubArrayRecord obj;
	ofstream outputFile;
	int SIZE;
	cout << "Enter number of integers" << endl;
	cin >> SIZE;
	int* array = new int[SIZE];

	//Generating Random integers
	RandomArray(array, SIZE);

	auto start = chrono::high_resolution_clock::now(); //Variable to store starting time

	obj = FindMaxSubArrayRecursive(array, 0, SIZE-1); //Finding max suub array using Recursive function
	
	auto end = chrono::high_resolution_clock::now(); 
	double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
	time_taken *= 1e-9;
	cout << "Time taken by program is : " << fixed << time_taken << setprecision(10)<<endl; //Calculation time taken by the algorithm

	//storing the sorted array in the file
	outputFile.open("FindMaxSubArrayRecursive.csv");
	for (int i = 0; i < SIZE; i++) {
		outputFile << array[i] << endl;

	}
	outputFile.close();



	cout << "Start Index " << obj.startIndex << endl;
	cout << "End Index " << obj.endIndex << endl;
	cout << "Sum of max sub array " << obj.maxSum<<endl;
	//deleting the dynamically allocated array

	system("pause");
	return 0;
}


//function to generate random array
void RandomArray(int array[], int size) {
	srand(time(0));
	int var;
	for (int i = 0; i < size; ++i) {
		var = rand() % 1000000;
		if ((var % 2) != 0) { //Storing negative numbers in the array
			var = var * (-1);
		}
		array[i] = var;
	}
}

//Function to find max sub array using recursive technique
MaxSubArrayRecord FindMaxSubArrayRecursive(int A[], int start, int end)
{
	MaxSubArrayRecord obj1, obj2, obj3;
	if (start!=end) { //when there are more then one elements in the array
		int mid = floor((start + end) / 2);
		obj1 = FindMaxSubArrayRecursive(A, start, mid);
		obj2 = FindMaxSubArrayRecursive(A, mid + 1, end);
		obj3 = CrossSum(A, start, mid, end);
		if ((obj1.maxSum >= obj2.maxSum) && (obj1.maxSum >= obj3.maxSum)) {
			return obj1;
		}

		if ((obj2.maxSum >= obj1.maxSum) && (obj2.maxSum >= obj3.maxSum)) {
			return obj2;
		}

		if ((obj3.maxSum >= obj1.maxSum) && (obj3.maxSum >= obj2.maxSum)) {
			return obj3;
		}
	}
	else {
		MaxSubArrayRecord result;
		result.startIndex = start;
		result.endIndex = end;
		result.maxSum = A[start];
		return result;
	}
}

//Function to calculate sum of divided arrays
MaxSubArrayRecord CrossSum(int A[], int start, int mid, int end) 
{
	
	int leftSum = 0;
	int rightSum = 0;
	int leftMax = 0;
	int rightMax = 0;
	int startInd=0;
	int endInd=0;

	for (int i = mid; i >= start; i--)
	{
		leftSum = leftSum + A[i];
		if (leftSum > leftMax) 
		{
			leftMax = leftSum;
			startInd = i;
			
		}
	}
	for (int i = mid + 1; i <= end; i++)
	{
		rightSum = rightSum + A[i];
		if (rightSum > rightMax)
		{
			rightMax = rightSum;
			endInd = i;
		}

	}

	MaxSubArrayRecord obj;
	obj.startIndex = startInd;
	obj.endIndex = endInd;
	obj.maxSum = rightMax + leftMax;

	return obj;
}
