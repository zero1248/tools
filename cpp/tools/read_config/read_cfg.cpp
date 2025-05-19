#include "read_cfg.h"
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

using std::cout;
using std::endl;
using std::string;

extern bool readConfigFile(const char* cfgfilepath, const string &key, string &value) {
    
    std::fstream cfgFile;

    cfgFile.open(cfgfilepath);
    if( !cfgFile.is_open()) {
        cout<<"can not open cfg file!"<<endl;
        return false;
    }

    char tmp[100];
    
    while(!cfgFile.eof()) {    

        cfgFile.getline(tmp, 100);   
        string line(tmp);
        line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());  // erase whitespace
        size_t pos = line.find('=');     
        if(pos == string::npos) return false;
        string tmpKey = line.substr(0, pos);   // get key before '='
        if(key == tmpKey)         {
            value = line.substr(pos+1);       // get value after '='
            return true;
        }
    }
    cout << "Key " << key << " was not found!" << endl;
    return false;
}


int main() {

    string key_user = "user";
    string key_id = "id";
    string key_age = "age";
    string value;

    const char* cfgfilepath = "./cfg.config"; 

    if(readConfigFile(cfgfilepath, key_user, value))
        cout << "user: " << value << endl;
    if(readConfigFile(cfgfilepath, key_id, value))
        cout << "id: " << value << endl;
    if(readConfigFile(cfgfilepath, key_age, value))
        cout << "age: " << value << endl;
    if(readConfigFile(cfgfilepath, "123", value))
        cout << "123: " << value << endl;


    return 0;
}


