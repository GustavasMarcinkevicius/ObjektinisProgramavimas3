#ifndef INCLUDES_H
#define INCLUDES_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <set>
#include <regex>
#include <algorithm>
#include <cctype>


std::string to_lower(std::string s);
bool is_lithuanian_letter(char c);
std::string clean_word(const std::string& word);

#endif