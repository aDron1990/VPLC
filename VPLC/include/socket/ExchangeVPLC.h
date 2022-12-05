#ifndef EXCHANGEVPLC_H
#define EXCHANGEVPLC_H
#include "nlohmann/json.hpp"
#include <iostream>

#include <windows.h>
#include <Winsock2.h>
#include <Ws2tcpip.h>
#include <string>
#include <chrono>
//#include <clocale>
#include "Logger.h"
#include "my_heder.h"

using json = nlohmann::json;
using namespace std;

class ExchangeVPLC
{
    public:
        ExchangeVPLC();
        virtual ~ExchangeVPLC();
        bool Connect();
        void Proc(vector<device_structure>* device_list, configure_port1_structure * data);
        bool Write(parametrs_structure* device_structure_ptr);
        bool WriteString(string data);
        void CloseConnect();
        void WriteInitData(vector<device_structure>* device_list);
    protected:

    private:
        int sock, port, serv_fd, error_count;
        WSADATA wsaData;
        string error_string, warn_string;
        Logger* log;
        //vector<device_structure>* device_list;
        configure_port1_structure *configure_port1_ptr;
};

#endif // EXCHANGEVPLC_H
