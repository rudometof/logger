#ifndef logger_end_H
#define logger_end_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <ctime>
#include <fstream>
#include <sstream>
#include "single_include/nlohmann/json.hpp"



using namespace std;

class Logger{
    private:
        int number_input = 0;
        int number_output = 0;
        int count_type_input;
        int count_output;
        string name_input_direct;
        string name_output_direct;
        vector<string> name_input;
        vector<string> name_output;

        string generate_Date_Time();

        void open_direct(string name, vector<string> shablon);

        void open_log(string massage);

        vector<string> removeDuplicates(vector<string>& nums);

    public:
        void Control_file();

        void Check_value();

};

#endif
