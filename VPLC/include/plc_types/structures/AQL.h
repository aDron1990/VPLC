#pragma once

struct AnalogQuitLocal
{
public:

	float out = 0;
	float out_min = 0;
	float out_max = 0;
	float mA_min = 0;
	float mA_max = 0;
	float fiz_min = 0;
	float fiz_max = 0;
	unsigned int iDA = 0;
	int iRes = 0;

	AnalogQuitLocal(Json::Value& node)
	{
		out_min = node["out_min"].asFloat();
		out_max = node["out_max"].asFloat();
		mA_min = node["mA_min"].asFloat();
		mA_max = node["mA_max"].asFloat();
		fiz_min = node["fiz_min"].asFloat();
		fiz_max = node["fiz_max"].asFloat();
		iDA = node["iDA"].asInt();
		iRes = node["iRes"].asInt();
	}
};