/*#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <ctime>
#include <fstream>
#include <sstream>



using namespace std;*/

#include "logger_end.h"

//class Logger{
    //private:
        /*int number_input = 0;
        int number_output = 0;
        int count_type_input;
        int count_output;
        string name_input_direct;
        string name_output_direct;
        vector<string> name_input;
        vector<string> name_output;*/

    string Logger :: generate_Date_Time() {
        time_t now = time(0);
        tm* timeinfo = std::localtime(&now);
        char buffer[80];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
        string dateTimeString(buffer);
        return dateTimeString;
    }

    void Logger :: open_direct(string name, vector<string> shablon){
        int n = 0;
        int count = 0;
        filesystem::path input_dir = filesystem::current_path() / name;  // Получение пути к папке "input"
        // Проверка, существует ли папка "input"
        if (filesystem::exists(input_dir) && filesystem::is_directory(input_dir)) {
            // Перебор всех файлов в папке "input"
            for (const auto& i : filesystem::directory_iterator(input_dir)) {
                string file_path = i.path().filename().string();
                if (name == name_output_direct){
                    count++;
                    string massage = generate_Date_Time() + "  WARNING " + file_path + " не соответствует заданному названию выходных файлов";
                    for (auto f: shablon){
                        for (auto g:name_input){
                        if (file_path.find(f)!=string::npos && file_path.find(g)!=string::npos){
                            massage = "";
                            n++;
                        }

                    }
                    }
                    open_log(massage);
                    number_output++;
                }

                else{
                count++;
                string massage = generate_Date_Time() + "  WARNING " + file_path + " не соответствует заданному названию входных файлов";
                for(auto j : shablon){

                    if (file_path.find(j)!=string::npos){
                        massage = "";
                        n++;
                    }
            
                } 
                open_log(massage);
                number_input++;              
            }
            }
                if (n == count && name == name_output_direct){
                    open_log(generate_Date_Time() + " INFO: Названия всех выходных файлов удовлетворяют заданным параметрам");
            }
            
                if (n == count && name == name_input_direct){
                    open_log(generate_Date_Time() + " INFO: Названия всех входных файлов удовлетворяют заданным параметрам");
            }
            

        } else {
            cout << "Папка " << name << " не найдена." << endl;
        }
    }

    void Logger :: open_log(string massage){
        ofstream file("log.txt", ios::app); // открываем файл для записи
        if (file.is_open()) { // проверяем, удалось ли открыть файл
            file << massage << endl; // записываем текст в файл
            file.close(); // закрываем файл
        } 
        else {
            cout << "Не удалось открыть файл" << endl;
        }
    }

    vector<string> Logger :: removeDuplicates(vector<string>& nums) {
        vector<string> result;
        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size(); i++) {
            if (i == 0 || nums[i] != nums[i - 1]) {
                result.push_back(nums[i]);
            }
        }
        return result;
    }

    //public:
          void Logger :: Control_file(){
            int n;
            cout << "Введите название директории входных файлов:";
            cin >> name_input_direct;
            filesystem::path input_dir = filesystem::current_path() / name_input_direct;
            if (filesystem::exists(input_dir) && filesystem::is_directory(input_dir)) {
            // Перебор всех файлов в папке "input"
            for (const auto& i : filesystem::directory_iterator(input_dir)) {
                n++;
                string file_path = i.path().filename().string();
                size_t lastUnderscoreIndex = file_path.find_last_of('_');
                string result = file_path.substr(0, lastUnderscoreIndex);
                if (n == 1){
                    name_input.push_back(result);
                }
                int g = size(name_input);
                for (int i = 0; i<g; i++){
                    if(name_input[i] == result){
                    }
                    else{
                        name_input.push_back(result);
                    }
                }
            }
            }
            n = 0;

            name_input = removeDuplicates(name_input);
            count_type_input = size(name_input);

            cout << "Введите название директории выходных файлов:";
            cin >> name_output_direct;

            filesystem::path output_dir = filesystem::current_path() / name_output_direct;
            if (filesystem::exists(output_dir) && filesystem::is_directory(output_dir)) {
            // Перебор всех файлов в папке "input"
            for (const auto& i : filesystem::directory_iterator(output_dir)) {
                n++;
                string file_path = i.path().filename().string();
                size_t firstUnderscoreIndex = file_path.find_first_of('_');
                string result2 = file_path.substr(0, firstUnderscoreIndex);
                if (n == 1){
                    name_output.push_back(result2);
                }
                int g = size(name_output);
                for (int i = 0; i<g; i++){
                    if(name_output[i] == result2){
                    }
                    else{
                        name_output.push_back(result2);
                    }
                }
            }
            }

            name_output = removeDuplicates(name_output);
            count_output = size(name_output);

            for (auto i: name_input){
                cout << i << endl;
            }

            cout << endl;

            for(auto i:name_output){
                cout << i << endl;
            }

            string all_output;
            open_direct(name_input_direct, name_input);
            open_direct(name_output_direct, name_output);  
            open_log("____________________________________________________________________________");
            if (number_input*count_output == number_output){
                open_log( generate_Date_Time() + " INFO: ВСЕ ОК, У КАЖДОГО ВХОДНОГО ФАЙЛА ПО " + to_string(count_output) + " ВЫХОДНЫХ");
            }
            else{
                filesystem::path output_dir = filesystem::current_path() / name_output_direct;  // Получение пути к папке "input"
        // Проверка, существует ли папка "input"
                if (filesystem::exists(output_dir) && filesystem::is_directory(output_dir)) {
            // Перебор всех файлов в папке "input"
                for (const auto& i : filesystem::directory_iterator(output_dir)) {
                    string file_path = i.path().filename().string();
                    all_output+=file_path;
            }
            }

            filesystem::path input_dir = filesystem::current_path() / name_input_direct;  // Получение пути к папке "input"
        // Проверка, существует ли папка "input"
                if (filesystem::exists(input_dir) && filesystem::is_directory(input_dir)) {
            // Перебор всех файлов в папке "input"
                for (const auto& i : filesystem::directory_iterator(input_dir)) {
                    string file_path = i.path().filename().string();
                    for(auto j:name_output){
                        string now = j + "_" + file_path;
                        if(all_output.find(now)!=string::npos){
                        }
                        else{
                            open_log (generate_Date_Time() + " WARNING: НЕ ХВАТАЕТ ФАЙЛА " + j + "_" + file_path);
                        }
                    }
                    
            }
            }
            }
            open_log("____________________________________________________________________________");
        }

        void Logger :: Check_value(){
            filesystem::path input_dir = filesystem::current_path() / name_input_direct;
            if (filesystem::exists(input_dir) && filesystem::is_directory(input_dir)) {
                for (const auto& i : filesystem::directory_iterator(input_dir)) {
                    string file_path = i.path().filename().string();
                    ifstream file("input/"+file_path);
                    if (file.is_open()) { // проверка, удалось ли открыть файл
                        string line1, line2;
                        int number;
                        getline(file, line1); // чтение первой строки из файла
                        number = stoi(line1);
                        getline(file, line2);
                        file.close();
                        int num1,num2;
                        stringstream ss(line2);
                        ss >> num1 >> num2;
                        if (number>num1 && number<num2){ 
                        }
                        else{
                            open_log(generate_Date_Time()+ " WARNING: В файле " + file_path + " значение не находится в нужном диапазоне");
                        }
                    }
                    else{
                        cout << "Файл не открылся" << endl;
                    } 

                }
                open_log(" ");
            }
        }





//};

int main(){
    Logger logger;

    //автоматически должна опрределять количество типов входных файлов и из названия (ок)
    //N входных файлов на X выходных (это указать нужно) 


    logger.Control_file();
    logger.Check_value();


    //Завести git репозиторий, где этот код будет одной  веткой, а исправленный уже другой
    //Разбить на h файл (ок)
    //ошибки, которые есть внутри directory_iterator записывать в лог файл
    //процесс считывания данных из файла
    //переделать txt на json
    //написать генератор входных файлов(файл, подготавливающий json файл с тестовыми значениями переменными), используя рандом
    return 0;
}