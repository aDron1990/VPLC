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

	Global* G;
	GlobalLocal* GL;

    PLC(std::string remanentFilePath)
    {
        std::ifstream settingsFile;
        std::stringstream settingsStream;

        settingsFile.open(remanentFilePath, std::fstream::binary);
        if (settingsFile.is_open())
        {
            settingsStream << settingsFile.rdbuf();
            std::cerr << "Start reading remanent file" << std::endl;
        }
        else
        {
            std::cerr << "Failed to open file" << std::endl;
        }
        settingsFile.close();

        try
        {
            std::string rawJson = settingsStream.str();
            JSONCPP_STRING err;
            Json::Value root;

            Json::Reader reader;
            reader.parse(rawJson, root);

            G = new Global{ root["G"] };
            GL = new GlobalLocal{ root["GL"] };

            AI.resize(GL->Stations);
            AIL.resize(GL->Stations);
            AQ.resize(GL->Stations);
            AQL.resize(GL->Stations);
            for (int i = 0; i < GL->Stations; i++)
            {
                AI[i] = std::vector<AnalogInput>();
                AIL[i] = std::vector<AnalogInputLocal>();
                AQ[i] = std::vector<AnalogQuit>();
                AQL[i] = std::vector<AnalogQuitLocal>();
            }
            for (int i = 0; i < root["AI"].size(); i++)
            {
                AI[root["AI"][i]["iSt"].asInt()].push_back(AnalogInput{ root["AI"][i] });
                AIL[root["AI"][i]["iSt"].asInt()].push_back(AnalogInputLocal{ root["AI"][i] });
            }
            for (int i = 0; i < root["AQ"].size(); i++)
            {
                AQ[root["AQ"][i]["iSt"].asInt()].push_back(AnalogQuit{ root["AQ"][i] });
                AQL[root["AQ"][i]["iSt"].asInt()].push_back(AnalogQuitLocal{ root["AQ"][i] });
            }
        }
        catch(...)
        {
            std::cerr << "Json file read error" << std::endl;
        }
	}

    ~PLC()
    {
        delete G;
        delete GL;
    }
};

typedef int(*subProgram_process)(PLC* plc);