#include "single_include/nlohmann/json.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <windows.h>
#include <random>

using namespace std;

void create_input(){
    int count_type;
    cout << "Укажи сколько типов данных хочешь создать: ";
    cin >> count_type;
    vector<string> type;
    for (int i = 0; i<count_type; i++){
        string new_type = "";
        cout << "Введи название типа: ";
        cin >> new_type;
        type.push_back(new_type);
    }

    vector<int> number_type;
    for (int i = 0; i<count_type; i++){
        cout << "Укажи, сколько файлов будет для " << type[i] << " : ";
        int new_number = 0;
        cin >> new_number;
        number_type.push_back(new_number);
    }

    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<int> distribution_middle(1, 100);
    uniform_int_distribution<int> distribution_left(1, 50);
    uniform_int_distribution<int> distribution_right(51, 100);
    string folderName = "input";
    if (system(("mkdir " + folderName).c_str()) == 0) {
        for (int i = 0; i<count_type;i++){
            for (int j = 0; j<number_type[i]; j++){
                ofstream file(folderName + "\\" + type[i] + "_" + to_string(j+1) + ".json");
                if (file.is_open()) {
                int randomNumber1 = distribution_middle(rng);
                int randomNumber2 = distribution_left(rng);
                int randomNumber3 = distribution_right(rng);
                file << randomNumber1 << endl;
                file << randomNumber2 << " " << randomNumber3;
                file.close();
                }
            }
        }

    }

    int count_output;
    cout << "Укажи, сколько выходных файлов для каждого из типов: ";
    cin >> count_output;
    vector<string> output_type;
    for (int i = 0; i<count_output; i++){
        cout << "Укажи название выходного файла № " << i+1 << " : ";
        string new_name;
        cin >> new_name;
        output_type.push_back(new_name);
    }

    folderName = "output";
    if (system(("mkdir " + folderName).c_str()) == 0) {
        for (int i = 0; i<count_output;i++){
            for(int j = 0; j<count_type; j++){
                ofstream file(folderName + "\\" + output_type[i] + "_" + type[j]  + ".json");
                if (file.is_open()) {
                int randomNumber1 = distribution_middle(rng);
                int randomNumber2 = distribution_left(rng);
                int randomNumber3 = distribution_right(rng);
                file << randomNumber1 << endl;
                file << randomNumber2 << " " << randomNumber3;
                file.close();
                }
            }
        }
    }


}


int main(){
    create_input();
    return 0;
}