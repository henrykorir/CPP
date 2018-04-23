#include <iostream>
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;
int main(int argc, char**argv)
{
   if(argc !=2){
		std::cout<<"Usage: "<<argv[0]<<" file.json"<<std::endl;
		return -1;
   }
   json input;
   std::ifstream ifs(argv[1]);
   ifs >> input;
   int arraySize=0, numSamples=0;
   std::string sample="Sample";
   numSamples=input["metadata"]["numSamples"];
   arraySize=input["metadata"]["arraySize"];
   json data=json::object();
   int i=0,j=0,k=0,inversions=0;
   for(i=1;i<=numSamples;i++){
      std::string array_name=sample + std::to_string(i);
      int count=0;
	  json CI=json::object();
       for(j=0,k=j+1;j<arraySize-1 && k<arraySize;j++,k++){
           if(input[array_name][j]>input[array_name][k]){
               count++;
			   json array=json::array();
               array.push_back(input[array_name][j]);
               array.push_back(input[array_name][k]);
               CI.push_back({std::to_string(count),array});
           }
       }
	   if(count>0){
			inversions++;
			json sample_info=json::object();
			sample_info.push_back({"ConsecutiveInversions",CI});
			sample_info.push_back({sample,input[array_name]});
			data.push_back({array_name,sample_info});
	   }
   }
   json metadata=json::object();
   metadata.push_back({"arraySize",arraySize});
   metadata.push_back({"file","SampleExample.json"});
   metadata.push_back({"numSamples",numSamples});
   metadata.push_back({"samplesWithInversions",inversions});
   
   data.push_back({"metadata",metadata});
   std::cout<<data.dump(2)<<std::endl;
  return 0;
}
   