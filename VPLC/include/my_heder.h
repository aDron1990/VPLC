#ifndef MY_HEDER_H_INCLUDED
#define MY_HEDER_H_INCLUDED
#include <string>
#include <vector>
using namespace std;
typedef struct
        {
          bool enabled;
          string                label;
          unsigned int          device_address;
          unsigned int          fnc;
          unsigned int          read_fnc;
          unsigned int          register_address;
          unsigned int          count_reg;
          string                plc_type;
          unsigned int          plc_address;
          string                byte_order;
          string                type;
          unsigned int          skip_turns;
          string                comment;
          bool                  trigger;
          unsigned int          skip;
          vector<uint16_t>      data;
          vector<uint16_t>      data_write;
          long unsigned int     count_good_seans;
          long unsigned int     count_bad_seans;
          unsigned int          skip_count;
          bool                  flag_send_in_VPLC;
          bool                  flag_allow_send_in_device;
          int                   error_cod;
          string                error_string;
        } parametrs_structure;

typedef struct
        {
          string ip;
          string label;
          string protocol;
          int port;
          unsigned int polling_pause;
          unsigned int timeout;
          bool enabled;
          string interface_protocol;
          string mode;
          vector<parametrs_structure> parameters;
          string warn_string;
          string error_string;
          int error_cod;
        } device_structure;

/*typedef struct
        {
          string ip_vplc;
          int port_read_vplc;
          int port_write_vplc;
          int timeout_write_vpls;
          int timeout_read_modbus;
        } configure_tool_structure;*/

typedef struct
        {
          string ip;
          int port;
          std::string error_string;
        } configure_port1_structure;    //порт передачи данных в VPLC
typedef struct
        {
          string ip;
          int port;
          std::string error_string;
          int col_client;
        } configure_port2_structure;   //порт чтения данных из VPLC и обмен с терминалом
typedef struct
        {
          configure_port1_structure configure_port1;
          configure_port2_structure configure_port2;
        } configure_tool_structure;  //Общие настройки

#endif // MY_HEDER_H_INCLUDED
