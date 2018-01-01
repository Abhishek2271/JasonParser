// SampleParser.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "string"
#include "rapidjson/reader.h"
#include <iostream>
#include "rapidjson/document.h"
#include <vector>
#include "JsonParser.h";

int main() 
{
	try
	{
		char json[] = "{\
							\"LED\":[{\"StartDateTime\": \"12.12.2017T05:45\",\"EndDateTime\": \"12.12.2018T18:45\"}],\
							\"Nutritions\":[{\"StartDate\": \"12:12:2017\",\"EndDate\": \"12:12:2018\",\"ECValue\": 7.89,\"Accuracy\": 0.5}],\
							\"PH\":[{\"StartDate\": \"12:12:2017\",\"EndDate\": \"12:12:2018\",\"PHValue\": 7.89,\"Accuracy\": 0.5}],\
							\"AirflowVent_1\":[{\"Speed\": \"Medium\"}],\
							\"AirflowVent_2\":[{\"StartDateTime\": \"12.12.2017T05:45\",\"EndDateTime\": \"12.12.2018T18:45\",\"Speed\":\"Medium\"}]\
						}";

		ParsedData Data = PopulateData(json);	
		printf("StartDateTime = %s, EndDateTime = %s\n", Data.LedTimes.at(0).LED_StartDateTime, Data.LedTimes.at(0).LED_EndDateTime);
	}
	catch (const std::exception& e)
	{
		 std::cout << e.what();
	}	
		
	return 0;
	
		//MyHandler handler;
		//Reader reader;
		//StringStream ss(json);
		//reader.Parse(ss, handler);
}	  
