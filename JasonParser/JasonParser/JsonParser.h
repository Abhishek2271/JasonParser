// SampleParser.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "string"
#include "rapidjson/reader.h"
#include <iostream>
#include "rapidjson/document.h"
#include <vector>


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

struct LEDTimings
{
	const char* LED_StartDateTime;
	const char* LED_EndDateTime;
};

struct NutritionDefs
{
	const char* N_StartDate;
	const char* N_EndDate;
	float EC_Value;
	float N_Accuracy;
};

struct PHDefs
{
	const char* PhStartDate;
	const char* PhEndDate;
	float Ph_Value;
	float ph_Accuracy;
};


struct AirVent_2
{
	const char* Vent_StartDateTime;
	const char* Vent_EndDateTime;
	int VentSpeed;
};

class ParsedData
{	
	public: vector<LEDTimings> LedTimes;
	public: vector<NutritionDefs> N_Defs;
	public: vector<PHDefs> P_Defs;
	public:	int AirVent_1;
	public: vector<AirVent_2> AirVent_2;

	public:	int getVentSpeed(const char* Speed)
	{  
		if (strcmp(Speed, "Off") == 0)
		{
			return 0;
		}
		else if (strcmp(Speed, "Low") == 0)
		{
			return 1;
		}
		else if (strcmp(Speed, "Medium") == 0)
		{
			return 2;
		}
		else if (strcmp(Speed, "High") == 0)
		{
			return 3;
		}
	};
};


ParsedData PopulateData( char JsonInput[])
{
	ParsedData Data;
	Document document;
	document.Parse(JsonInput);
	if(VerifyJason(JsonInput))
	{		
		const Value& LedTime = document["LED"];
		assert(LedTime.IsArray());
		
		for (SizeType i = 0; i < LedTime.Size(); i++) // Uses SizeType instead of size_t
		{
			LEDTimings LT;
			LT.LED_StartDateTime = document["LED"][i]["StartDateTime"].GetString();
			LT.LED_EndDateTime = document["LED"][i]["EndDateTime"].GetString();
			Data.LedTimes.push_back(LT);
			
			printf("StartDateTime = %s, EndDateTime = %s \n", LT.LED_StartDateTime, LT.LED_EndDateTime);
		}
		const Value& Nutritions = document["Nutritions"];
		assert(Nutritions.IsArray());
		for (SizeType i = 0; i < Nutritions.Size(); i++) // Uses SizeType instead of size_t
		{
			NutritionDefs ND;
			ND.N_StartDate = document["Nutritions"][i]["StartDate"].GetString();
			ND.N_EndDate = document["Nutritions"][i]["EndDate"].GetString();
			ND.EC_Value = document["Nutritions"][i]["ECValue"].GetFloat();
			ND.N_Accuracy = document["Nutritions"][i]["Accuracy"].GetFloat();
			Data.N_Defs.push_back(ND);
			
			printf("StartDate = %s, EndDate = %s, ECValue = %f, Accuracy = %f \n", ND.N_StartDate, ND.N_EndDate, ND.EC_Value, ND.N_Accuracy);
		}
		const Value& PH = document["PH"];
		assert(PH.IsArray());
		for (SizeType i = 0; i < PH.Size(); i++) // Uses SizeType instead of size_t
		{
			PHDefs PDef;
			PDef.PhStartDate = document["PH"][i]  ["StartDate"].GetString();
			PDef.PhEndDate = document["PH"][i]["EndDate"].GetString();
			PDef.Ph_Value = document["PH"][i]["PHValue"].GetFloat();
			PDef.ph_Accuracy = document["PH"][i]["Accuracy"].GetFloat();
			Data.P_Defs.push_back(PDef);
			printf("StartDate = %s, EndDate = %s, PHValue = %f, Accuracy = %f \n", PDef.PhStartDate, PDef.PhEndDate, PDef.Ph_Value, PDef.ph_Accuracy);
		}
		
		int VentSpeed = Data.getVentSpeed(document["AirflowVent_1"][0]["Speed"].GetString());
		Data.AirVent_1 = VentSpeed;
		printf("AirflowVent 1 speed is = %s \n", document["AirflowVent_1"][0]["Speed"].GetString());
		
		//int VentSpeed = getVentSpeed(document["AirflowVent_1"][0]["Speed"].GetString());
		const Value& AirflowVent_2 = document["AirflowVent_2"];
		assert(AirflowVent_2.IsArray());
		for (SizeType i = 0; i < AirflowVent_2.Size(); i++) // Uses SizeType instead of size_t
		{
			AirVent_2 Vent2;
			Vent2.Vent_StartDateTime = document["AirflowVent_2"][i]["StartDateTime"].GetString();
			Vent2.Vent_EndDateTime = document["AirflowVent_2"][i]["EndDateTime"].GetString();
			int VentSpeed = Data.getVentSpeed(document["AirflowVent_2"][i]["Speed"].GetString());
			Vent2.VentSpeed = VentSpeed;
			Data.AirVent_2.push_back(Vent2);
			printf("StartDateTime = %s, EndDateTime = %s, Speed = %s \n", Vent2.Vent_StartDateTime, Vent2.Vent_EndDateTime, document["AirflowVent_1"][0]["Speed"].GetString());
		}		
		//_Data.ParsedData::ParsedData(Data);
		return Data;
	}
	else
	{
		printf("Malformed jason\n");
	}	
}