#include "plc_types/PLC.h"

#include <iostream>

extern "C" __declspec(dllexport) void process(PLC & plc)
{
	std::cout << "processDQ" << std::endl;
}
