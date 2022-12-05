

#include "plc_types/PLC.h"
#include "Module.h"
#include "tools/bits.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <Windows.h>
#include <ctime>
#include <thread>

void SocketProc() {}
void ModbasProc() {}
void MQTTProc() {}

int main(int argc, char** argv)
{
	PLC plc{ "res/remanent.json" };

	std::thread SocketThread{ SocketProc };
	std::thread ModbasThread{ ModbasProc };
	std::thread MQTTThread{ MQTTProc };

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

		moduleAI.~Module();
		moduleAQ.~Module();
		moduleDA.~Module();
		moduleDD.~Module();
		moduleDI.~Module();
		moduleDQ.~Module();
		moduleFC.~Module();

		std::cout << std::endl;
		if (clock() - lastUpdate < 1000) Sleep(1000 - (clock() - lastUpdate));
		lastUpdate = clock();
	}

	SocketThread.join();
	ModbasThread.join();
	MQTTThread.join();

	return 0;
}