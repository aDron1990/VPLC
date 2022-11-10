#pragma once

#include <json/json.h>

struct AnalogInputLocal
{
public:

	float in = 0;
	float in_min = 0;
	float in_max = 0;
	float mA_min = 0;
	float mA_max = 0;
	float fiz_notFiltr = 0;
	float fiz_min = 0;
	float fiz_max = 0;
	unsigned int filtr = 0;
	unsigned int iTyp = 0;

	AnalogInputLocal(Json::Value& node)
	{
		in_min = node["in_min"].asFloat();
		in_max = node["in_max"].asFloat();
		mA_min = node["mA_min"].asFloat();
		mA_max = node["mA_max"].asFloat();
		fiz_min = node["fiz_min"].asFloat();
		fiz_max = node["fiz_max"].asFloat();
		filtr = node["filtr"].asInt();
		iTyp = node["iTyp"].asInt();
	}
};