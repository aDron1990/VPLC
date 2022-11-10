#pragma once

#include <array>
#include <json/json.h>

class Global
{
public:

	std::array<unsigned short, 4> NHmodule = { 0 };

	unsigned int NoPart = 0;
	unsigned int PLCConnectCounter = 0;

	unsigned int curDay = 0;
	unsigned int curHour = 0;
	unsigned int curMinute = 0;
	unsigned int curSec = 0;

	unsigned short NHhmi = 0;
	unsigned short NHioScanner = 0;
	unsigned short NHplc = 0;
	
	unsigned int uRes = 0;
	int iRes = 0;
	float rRes = 0;

	Global(Json::Value& node)
	{
		NoPart = node["NoPart"].asInt();
	}
};