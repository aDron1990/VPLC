#pragma once

#include <array>

class GlobalLocal
{
public:

	unsigned int INIT = 0;
	unsigned int R = 0;
	unsigned int Stations = 0;
	std::array<unsigned int, 4> AI = { 0 };
	std::array<unsigned int, 4> DI = { 0 };
	std::array<unsigned int, 4> AQ = { 0 };
	std::array<unsigned int, 4> DQ = { 0 };

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

	//std::array<NetHelth, 9> NH;
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

};