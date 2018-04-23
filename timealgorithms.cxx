#include <fstream>
#include <iostream>
#include <chrono>
#include <ctime>
#include "json.hpp"
#include "insertionsort.h"
#include "quicksort.h"
#include "mergesort.h"

int main(int argc, char** argv) {
    double InsertionSortTime;
    double MergeSortTime;
    double QuickSortTime;
	if(argc !=2){
		std::cout<<"Usage: timealgorithms file.json"<<std::endl;
		return -1;
	}
	std::ifstream ifs(argv[1]);	
	nlohmann::json input;
	ifs >> input;
	
	std::string sample="Sample";
	int numSamples = input["metadata"]["numSamples"];
	int arraySize  = input["metadata"]["arraySize"];
    std::cout<<"sampleName," \
				"InsertionSortTime," \
				"InsertionSortCompares," \
				"InsertionSortMemaccess," \
				"MergeSortTime," \
				"MergeSortCompares," \
				"MergeSortMemaccess," \
				"QuickSortTime," \
				"QuickSortCompares," \
				"QuickSortMemaccess"<<std::endl;
	for(int i=1;i<=numSamples;i++){
		std::string sampleName=sample + std::to_string(i);
		std::vector<int>array;
		for(int j=0;j<arraySize;j++){
			array.push_back(input[sampleName][j]);
		}
		
		InsertionSortTime=0.0;
		InsertionSortCompares=0;
		InsertionSortMemaccess=0;
		MergeSortTime=0.0;
		MergeSortCompares=0;
		MergeSortMemaccess=0;
		QuickSortTime=0.0;
		QuickSortCompares=0;
		QuickSortMemaccess=0;
		
		clock_t tStart = clock();
		InsertionSort(&array);
		InsertionSortTime=(((double)(clock() - tStart))/CLOCKS_PER_SEC);
		
		tStart = clock();
		MergeSort(&array);
		MergeSortTime=(((double)(clock() - tStart))/CLOCKS_PER_SEC);
		
		tStart = clock();
		QuickSort(&array);
		QuickSortTime=(((double)(clock() - tStart))/CLOCKS_PER_SEC);
		std::cout<<sampleName<<"," \
					<<InsertionSortTime<<"," \
					<<InsertionSortCompares<<"," \
					<<InsertionSortMemaccess<<"," \
					<<MergeSortTime<<"," \
					<<MergeSortCompares<<"," \
					<<MergeSortMemaccess<<"," \
					<<QuickSortTime<<"," \
					<<QuickSortCompares<<"," \
					<<QuickSortMemaccess<<std::endl;
	}
	return 0;
}