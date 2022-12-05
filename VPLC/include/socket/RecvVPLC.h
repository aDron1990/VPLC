#ifndef RECVVPLC_H
#define RECVVPLC_H
#include "nlohmann/json.hpp"
#include <iostream>
#include <thread>
#include <Windows.h>

#include <Winsock2.h>
#include <Ws2tcpip.h>
#include <string>
#include "my_heder.h"
#include <fstream>
#include "Logger.h"
//#include "ExchangeProtocolServer.h"
using json = nlohmann::json;
using namespace std;

#define BUFF_SIZE 1024

class RecvVPLC
{
    public:
        RecvVPLC();
        virtual ~RecvVPLC();
        void Proc(vector<device_structure>* dev_list, configure_port2_structure *data );
        void Read(SOCKET* socket_read);
        bool Connect();
    protected:

    private:
        int port, listen_fd, sock;
        string error_string;
        WSADATA wsaData;
        vector<device_structure>* device_list;
        Logger* log;
        configure_port2_structure* configure_port2_ptr;
        //ExchangeProtocolServer* ExchangeProtocolSrv;
};


#endif // RECVVPLC_H
