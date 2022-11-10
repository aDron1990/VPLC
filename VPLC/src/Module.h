#pragma once

#include <plc_types/PLC.h>
#include <string>
#include <Windows.h>

typedef void(*module_process_t)(PLC& plc);

class Module
{
private:

	HMODULE module_;
	module_process_t process_;

public:

	Module(std::string moduleFileName, std::string moduleFileDir = "./modules/")
	{
		module_ = LoadLibrary((moduleFileDir + moduleFileName).c_str());
		if (module_ == 0) throw;
		process_ = (module_process_t)GetProcAddress(module_, "process");
		if (process_ == 0) throw;
	}

	~Module()
	{
		FreeLibrary(module_);
	}

	void process(PLC& plc)
	{
		process_(plc);
	}
};

