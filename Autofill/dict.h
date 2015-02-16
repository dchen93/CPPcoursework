#ifndef DICT_H
#define DICT_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>

class Dict{
private:
	std::string filename;
public:
	std::vector<std::string> words;
	std::vector<std::string> sentences;
	std::vector<std::string> phrases;
		
	Dict (std::string v);
	void parse();
};

#endif