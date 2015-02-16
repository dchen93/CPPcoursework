
#ifndef WORD_H
#define WORD_H

#include "element.h"
#include <cmath>
#include "dict.h"
#include <iostream>
#include <list>
#include <algorithm>

class Word : public Element{
	private:
		std::string input_word;
		std::vector<std::string> completion;
		std::vector<std::string> checked;
	public:
		Word(std::string str);
		void complete(const Dict &d);
		void check(const Dict &d);
		void show();

};

#endif