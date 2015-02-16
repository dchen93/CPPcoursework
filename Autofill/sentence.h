#ifndef SENTENCE_H
#define SENTENCE_H

#include <cmath>
#include <iostream>
#include <list>
#include <algorithm>
#include "dict.h"
#include "element.h"

class Sentence : public Element{
	private:
		std::string input_sentence;
		std::vector<std::string> completion;
		std::vector<std::string> checked;
	public:
		Sentence(std::string str);
		void complete(const Dict &d);
		void check(const Dict &d);
		void show();

};

#endif