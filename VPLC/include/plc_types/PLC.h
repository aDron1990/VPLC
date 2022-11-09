#pragma once

#include "structures/AI.h"
#include "structures/AIL.h"
#include "structures/AQ.h"
#include "structures/AQL.h"
#include "structures/G.h"
#include "structures/GL.h"

#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <json/json.h>

class PLC
{
public:

	std::vector<std::vector<AnalogInput>> AI;
	std::vector<std::vector<AnalogInputLocal>> AIL;
	std::vector<std::vector<AnalogQuit>> AQ;
	std::vector<std::vector<AnalogQuitLocal>> AQL;

	Global G;
	GlobalLocal GL;

	PLC(std::string remanentFilePath)
	{
        std::ifstream settingsFile;
        std::stringstream settingsStream;

        settingsFile.open(remanentFilePath, std::fstream::binary);
        if (settingsFile.is_open())
        {
            settingsStream << settingsFile.rdbuf();
        }
        else
        {
            std::cerr << "Failed to open file" << std::endl;
        }
        settingsFile.close();

        std::string rawJson = settingsStream.str();
        JSONCPP_STRING err;
        Json::Value root;

        Json::Reader reader;
        reader.parse(rawJson, root);
        AI.push_back(std::vector<AnalogInput>{});
        for (int i = 0; i < root["AI"].size(); i++)
        {
            AI[0].push_back(AnalogInput{});
            int a = root["AI"][i]["iSt"].asInt();
            AI[0][i].fiz = root["AI"][i]["iFiz"].asInt();
        }
	}
};