#ifndef UTILS_H_
#define UTILS_H_

#include <algorithm> 
#include <cctype>
#include <functional> 
#include <locale>
#include <memory>
#include <string>

#include <unistd.h>

std::string exec(std::string cmd);
void exec_background(std::string cmd);
std::string print(std::string text, std::string color, std::string instance);

bool is_powered();

std::string &trim(std::string &s);

#endif /* UTILS_H_ */
