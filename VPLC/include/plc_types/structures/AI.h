#pragma once

#include <json/json.h>

struct AnalogInput
{
	float val = 0;
	float fiz = 0;
	float SP = 0;
	float SPoor = 0;
	unsigned short SW = 0;
	unsigned int addr = 0;

	AnalogInput(Json::Value& node)
	{
		fiz = node["iFiz"].asInt();
		SW = node["SW"].asInt();
		addr = node["addr"].asInt();
	}
};