#ifndef READ_CFG_H
#define READ_CFG_H

#include <string>
using std::string;

extern bool readConfigFile(const char* cfgfilepath, const string &key, string &value);


#endif // READ_CFG_H
