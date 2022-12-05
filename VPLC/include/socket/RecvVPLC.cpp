#include "RecvVPLC.h"

#pragma warning(disable:4996)

RecvVPLC::RecvVPLC():port(4380)
{
   log = new Logger("C:\\proj\\Log\\RecvVPLC.log");
   log->WriteData("Start");
   int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
   if (iResult != 0)
    {
        error_string = "WSAStartup failed: ";
        error_string.append(to_string(iResult));
        log->WriteData(error_string);
        std::cout << error_string << std::endl;
    }
}

RecvVPLC::~RecvVPLC()
{
    WSACleanup();
    shutdown(sock, 2);
    log->CloseFile();
}

void RecvVPLC::Proc(vector<device_structure>* dev_list, configure_port2_structure *data )
{
   device_list = dev_list;
   configure_port2_ptr = data;
   configure_port2_ptr->col_client = 0;
   sockaddr_in clientInfo;
   ZeroMemory(&clientInfo, sizeof(clientInfo));
   int clientInfo_size = sizeof(clientInfo);
   log->WriteData("Connect");
   while(1)
   {
     if (!Connect()) { log->WriteData(error_string); configure_port2_ptr->error_string = error_string;}
     else
     {
         error_string = " Start server";
         configure_port2_ptr->error_string = error_string;
         log->WriteData(error_string);
         break;
     }
     Sleep(1000);
   }


   while(1)
   {
     configure_port2_ptr->error_string.clear();
     SOCKET ClientSock = accept(sock, (sockaddr*)&clientInfo, &clientInfo_size);
     if(ClientSock == INVALID_SOCKET)
     {
         closesocket(ClientSock);
         log->WriteData("Client sock error connect");
         configure_port2_ptr->error_string = "Client sock error connect";
         cout << "close client sock" << endl;
         /*closesocket(sock);
         Connect();*/
     }
     else
     {
        log->WriteData("Connect client sock");
        thread thread_read_data(&RecvVPLC::Read, this, &ClientSock);
        thread_read_data.detach();
     }
   }
}

void RecvVPLC::Read(SOCKET* socket_read)
{

  vector <char> read_data_buff(BUFF_SIZE);
  string read_data_string, write_data_string;
  int adr_plc;
  //ExchangeProtocolSrv = new ExchangeProtocolServer();
  vector<uint16_t> regs_vector;
  json json_var, json_var1, json_var2;
  int  read_count_byte, write_count_byte;
  device_structure* device_structure_ptr;
  vector<parametrs_structure>* parametrs_structure_vector_ptr;
  parametrs_structure* parametrs_structure_ptr;
  configure_port2_ptr->col_client ++;
  while(1)
  {
      read_count_byte = recv(*socket_read, read_data_buff.data(), read_data_buff.size(), 0);
      if(!read_count_byte)
      {
         log->WriteData("Error read data");
        break;
      }
      else
      {
          read_data_string.clear();
          read_data_string.assign(&read_data_buff[0], read_count_byte);

          try
          {
            json_var = json::parse(read_data_string);
          }
          catch(const std::exception& e)
          {
            log->WriteData("Error parse json data");
            closesocket(*socket_read);
            return;
          }

          if (json_var["dest"] == 1)
          {
            for (const auto& element : json_var["data"])
            {
                adr_plc = element["addr"];
                regs_vector.clear();
                for (const auto& element1 : element["regs"]) { regs_vector.push_back(element1); }
                for(auto index = 0; index < device_list->size(); index ++)
                {
                  device_structure_ptr = &device_list->at(index);
                  parametrs_structure_vector_ptr = &device_structure_ptr->parameters;
                  for(auto index1 = 0; index1 < parametrs_structure_vector_ptr->size(); index1 ++)
                  {
                    parametrs_structure_ptr = &parametrs_structure_vector_ptr->at(index1);
                    if(parametrs_structure_ptr->plc_address == adr_plc)
                    {
                      parametrs_structure_ptr->flag_allow_send_in_device = 0;
                      parametrs_structure_ptr->data_write = regs_vector;
                      parametrs_structure_ptr->flag_allow_send_in_device = 1;
                    }
                 }
               }
            }
          }
          else if(json_var["dest"] == 1000)
          {
            json_var.clear();
            json_var["dest"] = 2000;
            json_var["data"] = json::array();
            for(auto index1 = 0; index1 < device_list->size(); index1 ++)
            {
              device_structure_ptr = &device_list->at(index1);
              parametrs_structure_vector_ptr = &device_structure_ptr->parameters;
              json_var1["enabled"]              = device_structure_ptr->enabled;
              json_var1["label"]                = device_structure_ptr->label;
              json_var1["ip"]                   = device_structure_ptr->ip;
              json_var1["interface_protocol"]   = device_structure_ptr->interface_protocol;
              json_var1["mode"]                 = device_structure_ptr->mode;
              json_var1["polling_pause"]        = device_structure_ptr->polling_pause;
              json_var1["port"]                 = device_structure_ptr->port;
              json_var1["protocol"]             = device_structure_ptr->protocol;
              json_var1["timeout"]              = device_structure_ptr->timeout;
              json_var1["parametrs"]            = json::array();
              for(auto index2 = 0; index2 < parametrs_structure_vector_ptr->size(); index2 ++)
              {
                parametrs_structure_ptr = &parametrs_structure_vector_ptr->at(index2);
                json_var2["enabled"]            = parametrs_structure_ptr->enabled;
                json_var2["byte_order"]         = parametrs_structure_ptr->byte_order;
                json_var2["comment"]            = parametrs_structure_ptr->comment;
                json_var2["count_reg"]          = parametrs_structure_ptr->count_reg;
                json_var2["device_address"]     = parametrs_structure_ptr->device_address;
                json_var2["label"]              = parametrs_structure_ptr->label;
                json_var2["plc_address"]        = parametrs_structure_ptr->plc_address;
                json_var2["read_fnc"]           = parametrs_structure_ptr->read_fnc;
                json_var2["register_address"]   = parametrs_structure_ptr->register_address;
                json_var2["skip"]               = parametrs_structure_ptr->skip;
                json_var2["skip_turns"]         = parametrs_structure_ptr->skip_turns;
                json_var2["trigger"]            = parametrs_structure_ptr->trigger;
                json_var2["type"]               = parametrs_structure_ptr->type;
                json_var1["parametrs"].push_back(json_var2);
              }
               json_var["data"].push_back(json_var1);
             }
             write_data_string = json_var.dump();
             if ((write_count_byte = send(*socket_read, write_data_string.c_str(), write_data_string.size(), 0)) > 0)
             {
             }else { log->WriteData("Error write init data dest=1000");}
           }
           else if (json_var["dest"] == 1002)
           {
            while(1)
            {

            }
          }
      }

  }
  closesocket(*socket_read);
  configure_port2_ptr->col_client --;
}

bool RecvVPLC::Connect()
{
    struct sockaddr_in  serv_addr;
    string ip_adr = "127.0.0.1";
    //int erStat;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
       error_string = "Socket creation error";

       return false;
    }
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(configure_port2_ptr->port);
    serv_addr.sin_addr.s_addr = inet_addr(configure_port2_ptr->ip.c_str());
    //erStat = bind(sock, (sockaddr*)&serv_addr, sizeof(serv_addr));
    if (0)
    {
      error_string =  "Error Socket binding. Error ";
      error_string.append(to_string(WSAGetLastError()));      
      cout << error_string  << endl;
      closesocket(sock);
      return false;
    }
    if (listen(sock, 5) != 0)
    {
        error_string =  "Error Socket listen. Error ";
        error_string.append(to_string(WSAGetLastError()));
        cout << error_string  << endl;
        closesocket(sock);
        return false;
    }
    return true;
}
