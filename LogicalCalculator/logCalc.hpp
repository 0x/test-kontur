#pragma once
#include <iostream>                                     
#include <fstream>
#include <unordered_map>
#include <sstream>
#include <string>
#include <memory>



std::unordered_map<std::string, int> SimpleExprMap;
std::unordered_map<std::string, std::string> CompoundExprMap;
std::string StrToExprStr(std::stringstream& compExprSStr);