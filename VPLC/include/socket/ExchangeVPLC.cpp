#include "ExchangeVPLC.h"

#pragma warning(disable:4996)

ExchangeVPLC::ExchangeVPLC():port(4381), error_count(0)
{  
   log = new Logger("C:\\proj\\Log\\SendVPLC.log");
   int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
   if (iResult != 0)
   {
      string str_var = "WSAStartup failed: ";
      str_var.append(to_string(iResult));
      log->WriteData(str_var);
      std::cout << str_var << std::endl;

   }
}

ExchangeVPLC::~ExchangeVPLC()
{
    WSACleanup();
    closesocket(serv_fd);
}

bool ExchangeVPLC::Connect()
{
    int valread;
    struct sockaddr_in  serv_addr;
    string ip_adr = "127.0.0.1";
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        log->WriteData("Connect error socket create");
        return false;
    }
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(configure_port1_ptr->port);
    serv_addr.sin_addr.s_addr = inet_addr(configure_port1_ptr->ip.c_str());
    if ((serv_fd = connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) < 0)
    {
      error_string = "Error connect VPLC";
      if( configure_port1_ptr->error_string.compare(error_string) != 0)
      {
        log->WriteData(error_string);
      }

      cout << error_string << endl;
      configure_port1_ptr->error_string = error_string;
      return false;
    }
    else
    {
      configure_port1_ptr->error_string.clear();
      log->WriteData("Connect VPLC");
      cout << "Connect VPLC" << endl;
    }
    return true;
}

void ExchangeVPLC::WriteInitData(vector<device_structure>* device_list)
{
    vector<parametrs_structure>* parametrs_structure_vector_ptr;
    string str_var;
    device_structure* device_structure_ptr;
    parametrs_structure* parametrs_structure_ptr;
    json json_var, json_var1;
    json_var["dest"] = 2;
    json_var["out"] =  json::array();
    json_var["in"] =  json::array();
    for(auto index1 = 0; index1 < device_list->size(); index1 ++)
    {
       device_structure_ptr = &device_list->at(index1);
       parametrs_structure_vector_ptr = &device_structure_ptr->parameters;
       for(auto index2 = 0; index2 < parametrs_structure_vector_ptr->size(); index2 ++)
       {
           parametrs_structure_ptr = &parametrs_structure_vector_ptr->at(index2);
           json_var1["addr"] = parametrs_structure_ptr->plc_address;
           json_var1["count"] = parametrs_structure_ptr->count_reg;
           str_var = device_structure_ptr->label;
           str_var.append(":");
           str_var.append(parametrs_structure_ptr->label);
           json_var1["label"] = str_var;
           if ((parametrs_structure_ptr->fnc == 15) || (parametrs_structure_ptr->fnc == 16)) {json_var["out"].push_back(json_var1);}
           else if ((parametrs_structure_ptr->fnc == 3) || (parametrs_structure_ptr->fnc == 4)){json_var["in"].push_back(json_var1); }
       }
    }
    str_var = json_var.dump();
    cout << str_var << endl;
    WriteString(str_var);
}

void ExchangeVPLC::Proc(vector<device_structure>* device_list, configure_port1_structure *data)
{
    vector<parametrs_structure>* parametrs_structure_vector_ptr;
    string str_var;
    int time_var;
    device_structure* device_structure_ptr;
    parametrs_structure* parametrs_structure_ptr;
    json json_var, json_var1;
    configure_port1_ptr = data;
    while (1)
    {if(Connect()) { break; }
      Sleep(500);
    }
    WriteInitData(device_list);
    while(1)
    {
        auto begin_time = std::chrono::steady_clock::now();
         configure_port1_ptr->error_string.clear();
        json_var1["dest"] = 1;
        json_var1["data"] =  json::array();
        for(auto index = 0; index < device_list->size(); index ++)
        {
            device_structure_ptr = &device_list->at(index);
            parametrs_structure_vector_ptr = &device_structure_ptr->parameters;
            for(auto index1 = 0; index1 < parametrs_structure_vector_ptr->size(); index1 ++)
            {
                parametrs_structure_ptr = &parametrs_structure_vector_ptr->at(index1);
                if(parametrs_structure_ptr->flag_send_in_VPLC == true)
                {
                  json_var["addr"] = parametrs_structure_ptr->plc_address;
                  json_var["regs"] = parametrs_structure_ptr->data;
                  json_var1["data"].push_back(json_var);
                  parametrs_structure_ptr->flag_send_in_VPLC = false;
                }
            }
        }
        str_var = json_var1.dump();
       // cout << str_var << endl;

        if (send(sock, str_var.c_str(), str_var.length()+1,0) < 0)
        {
           error_count ++;
           error_string = "Error send data";
           if( configure_port1_ptr->error_string.compare(error_string) != 0)
           {
               log->WriteData(error_string);
           }
           if (error_count > 5)
           {
               closesocket(serv_fd);
               while(!Connect()){Sleep(50);}
               WriteInitData(device_list);
           }
        }
        else
        {
          error_count = 0;
          error_string.clear();
        }
        configure_port1_ptr->error_string = error_string;
        auto end_time = std::chrono::steady_clock::now();
        time_var = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - begin_time).count() + 11;
        if (time_var < 50){ Sleep(50-time_var); }
        else { warn_string = "Big timeout ";   warn_string.append(to_string(time_var));}
    }
}

bool ExchangeVPLC::Write(parametrs_structure* parametrs_structure_ptr)
{
    string str_var;
    json json_var;
    json_var["addr"] = parametrs_structure_ptr->plc_address;
    json_var["data"] = parametrs_structure_ptr->data;
    str_var = json_var.dump();
    if (send(sock, str_var.c_str(), str_var.length()+1,0) < 0)
    {
       log->WriteData("Error send data write");
       closesocket(serv_fd);
       Connect();
       return false;
    }
    return true;
}

bool ExchangeVPLC::WriteString(string data)
{
   if (send(sock, data.c_str(), data.length()+1,0) < 0)
   {
      log->WriteData("Error send data writestring");
      cout << "Error send data writestring" << endl;
      return false;
   }
   cout << "Send data init" << endl;
   return true;
}

void ExchangeVPLC::CloseConnect() {closesocket(serv_fd);}
