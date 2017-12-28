// SampleParser.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "string"
#include "rapidjson/reader.h"
#include <iostream>
#include "rapidjson/document.h"



using namespace rapidjson;
using namespace std;

bool VerifyJason(char json[])
{
	//TODO: Remove document parsing from here;
	Document document;
	document.Parse(json);

	try
	{
		if((document.HasMember("AirflowVent_1")) && 
			(document.HasMember("AirflowVent_2"))	&& 
			(document.HasMember("PH")) && 
			(document.HasMember("Nutritions")) && 
			(document.HasMember("LED")))
		{
			return true;
		}		
		else
		{
			return false;			
		}
	}
	catch(const char *str)
	{		
		printf("Error occured while verifying the jason string: %s%\n", str);
		return false;
	}
}


struct MyHandler {
    bool Null() { cout << "Null()" << endl; return true; }
    bool Bool(bool b) { cout << "Bool(" << boolalpha << b << ")" << endl; return true; }
    bool Int(int i) { cout << "Int(" << i << ")" << endl; return true; }
    bool Uint(unsigned u) { cout << "Uint(" << u << ")" << endl; return true; }
    bool Int64(int64_t i) { cout << "Int64(" << i << ")" << endl; return true; }
    bool Uint64(uint64_t u) { cout << "Uint64(" << u << ")" << endl; return true; }
    bool Double(double d) { cout << "Double(" << d << ")" << endl; return true; }
    bool RawNumber(const char* str, SizeType length, bool copy) { 
        cout << "Number(" << str << ", " << length << ", " << boolalpha << copy << ")" << endl;
        return true;
    }
    bool String(const char* str, SizeType length, bool copy) { 
        cout << "String(" << str << ", " << length << ", " << boolalpha << copy << ")" << endl;
        return true;
    }
    bool StartObject() { cout << "StartObject()" << endl; return true; }
    bool Key(const char* str, SizeType length, bool copy) {
        cout << "Key(" << str << ", " << length << ", " << boolalpha << copy << ")" << endl;
        return true;
    }
    bool EndObject(SizeType memberCount) { cout << "EndObject(" << memberCount << ")" << endl; return true; }
    bool StartArray() { cout << "StartArray()" << endl; return true; }
    bool EndArray(SizeType elementCount) { cout << "EndArray(" << elementCount << ")" << endl; return true; }
};

int main() {
	char json[] = "{\
						\"LED\":[{\"StartDateTime\": \"12.12.2017T05:45\",\"EndDateTime\": \"12.12.2018T18:45\"}],\
						\"Nutritions\":[{\"StartDate\": \"12:12:2017\",\"EndDate\": \"12:12:2018\",\"ECValue\": 7.89,\"Accuracy\": 0.5}],\
						\"PH\":[{\"StartDate\": \"12:12:2017\",\"EndDate\": \"12:12:2018\",\"PHValue\": 7.89,\"Accuracy\": 0.5}],\
						\"AirflowVent_1\":[{\"Speed\": \"Medium\"}],\
						\"AirflowVent_2\":[{\"StartDateTime\": \"12.12.2017T05:45\",\"EndDateTime\": \"12.12.2018T18:45\",\"Speed\":\"Medium\"}]\
					}";

		Document document;
		document.Parse(json);
		if(VerifyJason(json))
		{		
			const Value& LedTime = document["LED"];
			assert(LedTime.IsArray());

			for (SizeType i = 0; i < LedTime.Size(); i++) // Uses SizeType instead of size_t
			{
				printf("StartDateTime = %s, EndDateTime = %s \n", document["LED"][i]["StartDateTime"].GetString(), document["LED"][i]["EndDateTime"].GetString());
			}
			const Value& Nutritions = document["Nutritions"];
			assert(Nutritions.IsArray());
			for (SizeType i = 0; i < Nutritions.Size(); i++) // Uses SizeType instead of size_t
			{
				printf("StartDate = %s, EndDate = %s, ECValue = %f, Accuracy = %f \n", document["Nutritions"][i]["StartDate"].GetString(), document["Nutritions"][i]["EndDate"].GetString(), document["Nutritions"][i]["ECValue"].GetFloat(), document["Nutritions"][i]["Accuracy"].GetFloat());
			}
			const Value& PH = document["PH"];
			assert(PH.IsArray());
			for (SizeType i = 0; i < PH.Size(); i++) // Uses SizeType instead of size_t
			{
				printf("StartDate = %s, EndDate = %s, PHValue = %f, Accuracy = %f \n", document["PH"][i]["StartDate"].GetString(), document["PH"][i]["EndDate"].GetString(), document["PH"][i]["PHValue"].GetFloat(), document["PH"][i]["Accuracy"].GetFloat());
			}

			printf("AirflowVent 1 speed is = %s \n", document["AirflowVent_1"][0]["Speed"].GetString());

			const Value& AirflowVent_2 = document["AirflowVent_2"];
			assert(AirflowVent_2.IsArray());
			for (SizeType i = 0; i < AirflowVent_2.Size(); i++) // Uses SizeType instead of size_t
			{
				printf("StartDateTime = %s, EndDateTime = %s, Speed = %s \n", document["AirflowVent_2"][i]["StartDateTime"].GetString(), document["AirflowVent_2"][i]["EndDateTime"].GetString(), document["AirflowVent_2"][i]["Speed"].GetString());
			}
		}
		else
		{
			printf("Malformed jason\n");
		}
		//MyHandler handler;
		//Reader reader;
		//StringStream ss(json);
		//reader.Parse(ss, handler);

    return 0;
}	  
