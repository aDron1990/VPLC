#include "Logger.h"

#include <sstream>

#pragma warning(disable:4996)

Logger::Logger():count_write(0)
{
    //ctor
}

Logger::Logger(string file_name_data)
{
   OpenFile(file_name_data);
   Logger();
}

Logger::~Logger()
{
    CloseFile();
}
bool Logger::OpenFile(string file_name_data)
{
   path_file =  file_name_data;
   return OpenFile();
}

bool Logger::OpenFile()
{
   log_file.open(path_file, ofstream::app);
   if(!log_file.is_open())
   {
       string_error = "Error open config file";  //test
       cout << string_error << endl;
       return false;
   }
   return true;
}

bool Logger::WriteData(string data)
{
    string str_var;
    time_t rawtime;
    struct tm * timeinfo;
    time( &rawtime );
     char s[40];                        
    timeinfo = localtime( &rawtime );
    int length = strftime(s, 40, "%d.%m.%Y %H:%M:%S   ", timeinfo);
    str_var.assign(s, length);
    log_file << str_var << data << endl;
    count_write ++;
    if (count_write > 25)
    {
       log_file.seekp(0, ios::end);
       if(log_file.tellp() > 10000)
       {
          log_file.close();
          log_file.open(path_file,std::ofstream::out | std::ofstream::trunc);
       }
       count_write = 0;
    }
    return true;
}

void Logger::CloseFile()
{
    if (log_file.is_open()){log_file.close();}
}

void Logger::ResizeFile()
{
    CloseFile();
    ifstream read_file;
    ofstream write_file;
    string str_var, str_var1;
    read_file.open(path_file, ofstream::in);
    read_file.seekg(0,ios::end);
    auto pos = read_file.tellg();
    pos = pos / 10;
    read_file.seekg(-pos,ios::end);
    while (read_file)
    {
        getline(read_file, str_var);
        str_var1.append(str_var);
    }
    read_file.close();
    write_file.open(path_file, ios::trunc);
    write_file << str_var1;
    write_file.close();
    OpenFile();

}

