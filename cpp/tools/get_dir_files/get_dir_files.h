#ifndef GET_DIR_FILES_H
#define GET_DIR_FILES_H

#include <string>
#include <vector>

extern void getAllFile(std::string filepath, std::vector<std::string>& files); 
extern void getAllFile(std::string filepath, std::vector<std::string>& files, std::string fileType); 

#endif // GET_DIR_FILES_H
