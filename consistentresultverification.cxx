#include <iostream>
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;
int main(int argc, char **argv)
{
   
	if(argc !=3){
		printf("Usage: consistentresultverification file1.json file2.json\n");
		return -1;
	}
	std::ifstream ifs1(argv[1]);
	json input1=json::object();
	ifs1 >> input1;
	
	std::ifstream ifs2(argv[2]);
	json input2=json::object();
	ifs2 >> input2;
	
	int flag=0;
	json file1=json::object();
	file1.push_back({"arraySize",input1["metadata"]["arraySize"]});
	file1.push_back({"name",argv[1]});
	file1.push_back({"numSamples",input1["metadata"]["numSamples"]});
	
	json file2=json::object();
	file2.push_back({"arraySize",input2["metadata"]["arraySize"]});
	file2.push_back({"name",argv[2]});
	file2.push_back({"numSamples",input2["metadata"]["numSamples"]});
	
	json metadata=json::object();
	metadata.push_back({"File1",file1});
	metadata.push_back({"File2",file2});
	int len=input1["metadata"]["arraySize"];
	int numSamples=input1["metadata"]["numSamples"];
	std::string sample="Sample";
	json data = json::object();
    int inversions=0;
	for(int i=1;i<=numSamples;i++){
		std::string arrayName=sample + std::to_string(i);
		for(int j=0;j<len;j++){
			if(input1[arrayName][j] != input2[arrayName][j]) {
				flag=1;
				break;
			}
		}
		if(flag==1){
			json sampleInfo=json::object();
			sampleInfo.push_back({argv[2],input2[arrayName]});
			json mismatch=json::object();
			for(int j=0;j<len;j++){
				json tempArray=json::array();
				if(input1[arrayName][j] != input2[arrayName][j]){
					tempArray.push_back(input1[arrayName][j]);
					tempArray.push_back(input2[arrayName][j]);
					mismatch.push_back({std::to_string(j),tempArray});
				}
			}
			sampleInfo.push_back({"Mismatches",mismatch});
			sampleInfo.push_back({argv[1],input1[arrayName]});
			data.push_back({arrayName,sampleInfo});
			inversions++;
		}
        flag=0;
	}
	metadata.push_back({"samplesWithConflictingResults",inversions});
	data.push_back({"metadata",metadata});
    std::cout<<data.dump(2)<<std::endl;
	return 0;
}