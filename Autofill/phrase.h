#ifndef PHRASE_H
#define PHRASE_H

#include <cmath>
#include <iostream>
#include <list>
#include <algorithm>
#include "dict.h"
#include "element.h"


class Phrase : public Element{
private:
	std::string input_phrase;
	std::vector<std::string> completion;
	std::vector<std::string> checked;
public:
	Phrase (std::string str);
	void complete(const Dict &d);	
	void check(const Dict &d);
	void show();
};

#endif