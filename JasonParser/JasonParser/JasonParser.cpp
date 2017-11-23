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
		if((document.HasMember("Accuracy")) && 
			(document.HasMember("Airflow")) && 
			(document.HasMember("Nutritions")) && 
			(document.HasMember("LEDTime")))
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
	char json[] = " {  \
									\"LEDTime\":[\
												{ \
													\"StartDate\": \"12:12:2017\",\
													\"EndDate\": \"12:12:2018\",\
													\"StartTime\": \"07:00\",\
													\"EndTime\": \"23:00\"\
												}\
											],\
									\"Nutritions\":[ \
												{ \
													\"StartDate\": \"12:12:2017\",\
													\"EndDate\": \"12:12:2018\",\
													\"StartTime\": \"07:00\",\
													\"EndTime\": \"23:00\"\
												}\
											],\
									\"Accuracy\": 0.5,\
									\"Airflow\": 15\
							} ";

		Document document;
		document.Parse(json);
		
		if(VerifyJason(json))
		{		
			const Value& LedTime = document["LEDTime"];
			assert(LedTime.IsArray());

			for (SizeType i = 0; i < LedTime.Size(); i++) // Uses SizeType instead of size_t
			{
				printf(LedTime[i].);
				for (SizeType j = 0; j < LedTime[i].Size(); j++)
				{
					 
				}
			}
			

			const Value& Nutritions = document["Nutritions"];
			assert(Nutritions.IsArray());

			printf("Accuracy is: %f%\n", document["Accuracy"].GetFloat());
			printf("Airflow is: %d%\n", document["Airflow"].GetInt());
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
