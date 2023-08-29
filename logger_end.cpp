#include "logger_end.h"



    string Logger :: generate_Date_Time() {
        time_t now = time(0);
        tm* timeinfo = std::localtime(&now);
        char buffer[80];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
        string dateTimeString(buffer);
        return dateTimeString;
    }

    void Logger :: open_base(){
        ifstream base_file("base_input.txt");
        if(base_file.is_open()){
            string line;
            while(getline(base_file,line)){
                base_input.push_back(line);
            }
            base_file.close();
        }
        else{
            cout << "Файл с базовыми основами имен не открыт" << endl;
        }

        ifstream base_file2("base_output.txt");
        if(base_file2.is_open()){
            string line2;
            while(getline(base_file2,line2)){
                base_output.push_back(line2);
            }
            base_file2.close();
        }
        else{
            cout << "Файл с базовыми основами имен не открыт" << endl;
        }
    }

    void Logger :: open_log(string massage){
        ofstream file("log.txt", ios::app); 
        if (file.is_open()) {
            file << massage << endl; 
            file.close(); 
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

          void Logger :: Control_file(){
            int n;
            cout << "Введите название директории входных файлов:";
            cin >> name_input_direct;
            cout << "Введите количество входных файлов для одного опыта: ";
            int X,Y;
            cin >> X;
            open_base();


            vector<pair<string,int>> input;
            filesystem::path input_dir = filesystem::current_path() / name_input_direct;
            if (filesystem::exists(input_dir) && filesystem::is_directory(input_dir)) {
            for (const auto& i : filesystem::directory_iterator(input_dir)) {
                int flag = 0;
                n++;
                string file_path = i.path().filename().string();
                if (file_path.find(".json")!=string::npos){
                }
                else{
                    open_log(generate_Date_Time() + " WARNING: Файл " + file_path + " имеет неправильный формат");
                }
                size_t lastUnderscoreIndex = file_path.find_last_of('_');
                string result = file_path.substr(0, lastUnderscoreIndex);
                for(auto i : base_input){
                    if (i == result){
                        name_input.push_back(result);
                        flag = 1;
                    }
                }
                if (flag == 0){
                    open_log(generate_Date_Time() + " WARNING: Файл " + file_path + " имеет неправильное название!");
                }  
            }

            }
            else { 
                cout << "Название директории не соответствует фактическому" << endl;
                exit;
                }
            n = 0;

            name_input = removeDuplicates(name_input);
            count_type_input = size(name_input);

            for(auto i : name_input){
                pair<string,int> a(i,0);
                input.push_back(a);
            }

            for (const auto& i : filesystem::directory_iterator(input_dir)) {
                string file_path = i.path().filename().string();
                size_t lastUnderscoreIndex = file_path.find_last_of('_');
                string result = file_path.substr(0, lastUnderscoreIndex);
                for(int i = 0; i < size(input); i++){
                    if(input[i].first == result){
                        input[i].second++;
                    }
                }                
            }

            for (auto i : input){
                if(i.second != X){
                    open_log(generate_Date_Time() + " WARNING: Не хватает файла с основой " + i.first + " в папке со ВХОДНЫМИ данными!");
                }
            }

            open_log("____________________________________________________________________________");


            cout << "Введите название директории выходных файлов:";
            cin >> name_output_direct;

            cout << "Введите количество выходных файлов для одного опыта: ";
            cin >> Y;
            filesystem::path output_dir = filesystem::current_path() / name_output_direct;
            if (filesystem::exists(output_dir) && filesystem::is_directory(output_dir)) {
            for (const auto& i : filesystem::directory_iterator(output_dir)) {
                int flag = 0;
                n++;
                string file_path = i.path().filename().string();
                if (file_path.find(".json")!=string::npos){
                }
                else{
                    open_log(generate_Date_Time() + " WARNING: Файл " + file_path + " имеет неправильный формат");
                }
                size_t lastUnderscoreIndex2 = file_path.find_last_of('.');
                string result2 = file_path.substr(0, lastUnderscoreIndex2);
                for(auto i : base_output){
                    if (result2.find(i)!=string::npos){
                        flag++;
                    }
                }
                for (auto j : base_input){
                    if(result2.find(j)!=string::npos){
                        flag++;
                    }
                }
                if(flag == 0 || flag ==1){
                    open_log(generate_Date_Time() + " WARNING! Файл " + file_path + " имеет неправильное название!");
                }
                else{
                    name_output.push_back(result2);
                }

            }
            }
            else { 
            cout << "Название директории не соответствует фактическому" << endl;
            exit;
            }
            name_output = removeDuplicates(name_output);
            count_output = size(name_output);
            vector<pair<string,int>> output;
            for(auto i : name_input){
                pair<string,int> b(i,0);
                output.push_back(b);
            }
            for (const auto& i : filesystem::directory_iterator(output_dir)) {
                string file_path = i.path().filename().string();
                size_t lastUnderscoreIndex2 = file_path.find_last_of('.');
                string result2 = file_path.substr(0, lastUnderscoreIndex2);
                for(int i = 0; i<size(output); i++){
                    if(result2.find(output[i].first)!=string::npos){
                        output[i].second++;
                    }
                }
            }

            for(auto i : output){
                if(i.second != Y){
                    open_log(generate_Date_Time() + " WARNING: Не хватает файла с основой " + i.first + " в папке с ВЫХОДНЫМИ данными");
                }
            }

            open_log("____________________________________________________________________________");
        }

        void Logger :: Check_value(){
        filesystem::path input_dir = filesystem::current_path() / name_input_direct;
            if (filesystem::exists(input_dir) && filesystem::is_directory(input_dir)) {
                for (const auto& i : filesystem::directory_iterator(input_dir)) {
                    string file_path = i.path().filename().string();
                    ifstream file(name_input_direct + "/"  + file_path);
                    if (file.peek() == ifstream::traits_type::eof()) {
                        open_log(generate_Date_Time() + " WARNING: Файл " + file_path + " пуст, введите данные и начните программу заново");
                    }
                    if (file.is_open()) {
                        string line1, line2;
                        int number;
                        getline(file, line1); 
                        number = stoi(line1);
                        getline(file, line2);
                        file.close();
                        int num1,num2;
                        stringstream ss(line2);
                        ss >> num1 >> num2;
                        cout << number << " " << num1 << " " << num2 << endl;
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


            filesystem::path output_dir = filesystem::current_path() / name_output_direct;
            if (filesystem::exists(output_dir) && filesystem::is_directory(output_dir)) {
                for (const auto& i : filesystem::directory_iterator(output_dir)) {
                    string file_path = i.path().filename().string();
                    ifstream file(name_output_direct + "/" + file_path);
                    if (file.peek() == ifstream::traits_type::eof()) {
                        open_log(generate_Date_Time() + " WARNING: Файл " + file_path + " пуст, введите данные и начните программу заново");
                    }
                    if (file.is_open()) {
                        string line1, line2;
                        int number;
                        getline(file, line1); 
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


int main(){
    Logger logger;
    logger.Control_file();
    logger.Check_value();
    return 0;
}