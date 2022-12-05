#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;
class Logger
{
    public:
        Logger();
        Logger(string file_name_data);
        virtual ~Logger();
        bool OpenFile(string file_name_data);
        bool OpenFile();
        bool WriteData(string data);
        void CloseFile();
        void ResizeFile();

    protected:

    private:
         ofstream log_file;
         string file_name, string_error;
         int count_write;
         string path_file;

};

#endif // LOGGER_H
