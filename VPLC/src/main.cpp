#include "plc_types/PLC.h"
#include "Module.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <Windows.h>
#include <ctime>

int main(int argc, char** argv)
{
	PLC plc{ "res/remanent.json" };

	unsigned long lastUpdate = 0;
	while (1)
	{
		Module moduleAI{ "processAI.dll" };
		Module moduleAQ{ "processAQ.dll" };
		Module moduleDA{ "processDA.dll" };
		Module moduleDD{ "processDD.dll" };
		Module moduleDI{ "processDI.dll" };
		Module moduleDQ{ "processDQ.dll" };
		Module moduleFC{ "processFC.dll" };

		moduleAI.process(plc);
		moduleAQ.process(plc);
		moduleDA.process(plc);
		moduleDD.process(plc);
		moduleDI.process(plc);
		moduleDQ.process(plc);
		moduleFC.process(plc);

		std::cout << std::endl;
		if (clock() - lastUpdate < 2000) Sleep(2000 - (clock() - lastUpdate));
		lastUpdate = clock();
	}

	return 0;
}