#pragma once

#include <vector>
#include <json/json.h>

class NetHelth
{
public:
	
	unsigned int status = 0;
	unsigned int counterOld = 0;
	unsigned int t = 0;
	unsigned int err = 0;

};

class GlobalLocal
{
public:

	unsigned int INIT = 0;
	unsigned int R = 0;
	unsigned int Stations = 0;
	std::vector<unsigned int> AI = { 0 };
	std::vector<unsigned int> DI = { 0 };
	std::vector<unsigned int> AQ = { 0 };
	std::vector<unsigned int> DQ = { 0 };

	unsigned int TS = 0;
	unsigned int C = 0;
	unsigned int DD = 0;
	unsigned int DA = 0;
	unsigned int DAF = 0;
	unsigned int DDF = 0;
	unsigned int T = 0;
	unsigned int AO = 0;
	unsigned int FC = 0;
	unsigned int Rd = 0;
	unsigned int F = 0;

	std::vector<NetHelth> NH;
	unsigned int count10 = 0;
	unsigned int count100 = 0;
	unsigned int oldDay = 0;
	unsigned int oldHour = 0;
	unsigned int oldMinute = 0;
	unsigned int oldSec = 0;
	unsigned int oldSmena = 0;
	int sDA = 0;
	int sDD = 0;

	unsigned int sIO = 0;
	unsigned int VARStep = 0;
	unsigned int uRes1 = 0;
	unsigned int uRes2 = 0;
	int iRes0 = 0;
	int iRes1 = 0;
	int iRes2 = 0;
	float rRes0 = 0;
	float rRes1 = 0;
	float rRes2 = 0;

	GlobalLocal(Json::Value& node)
	{
		R = node["R"].asInt();
		Stations = node["Stations"].asInt();

		AI.resize(node["AI"].size());
		DI.resize(node["DI"].size());
		AQ.resize(node["AQ"].size());
		DQ.resize(node["DQ"].size());

		for (int i = 0; i < node["AI"].size(); i++) AI[i] = node["AI"][i].asInt();
		for (int i = 0; i < node["DI"].size(); i++) DI[i] = node["DI"][i].asInt();
		for (int i = 0; i < node["AQ"].size(); i++)	AQ[i] = node["AQ"][i].asInt();
		for (int i = 0; i < node["DQ"].size(); i++) DQ[i] = node["DQ"][i].asInt();

		TS = node["TS"].asInt();
		C = node["C"].asInt();
		DD = node["DD"].asInt();
		DA = node["DA"].asInt();
		DAF = node["DAF"].asInt();
		DDF = node["DDF"].asInt();
		T = node["T"].asInt();
		AO = node["AO"].asInt();
		FC = node["FC"].asInt();
		Rd = node["Rd"].asInt();
		F = node["F"].asInt();
		sDA = node["sDA"].asInt();
		sDD = node["sDD"].asInt();
		sIO = node["sIO"].asInt();
	}
};