#include "dict.h"

using namespace std;

Dict::Dict (string v){
	filename=v;
	parse();
};
		
	
void Dict::parse(){
	int window_size, word_count, iter, iter2;
	string temp_sentence;
	string temp_phrase;
	string temp_word;
	vector<string> words_in_sentence;

	ifstream infile;
	infile.open(filename.c_str());
	while(!infile.eof()){
		getline(infile, temp_sentence, '.'); // Saves the sentence in temp.
		replace(temp_sentence.begin(), temp_sentence.end(), '\n', ' ');
		// temp_sentence.erase(remove(temp_sentence.begin(), temp_sentence.end(), '\n'), temp_sentence.end()); // removes \n's

		if (isspace(temp_sentence[0]))
			temp_sentence.erase(0,1); // removes white space in front

		if(find(sentences.begin(), sentences.end(), (temp_sentence + '.')) == sentences.end()) // this is to not add duplicates
			sentences.push_back(temp_sentence + '.');	// this is for sentences

		words_in_sentence.clear();
		word_count = 0;

		stringstream iss;
		iss << temp_sentence;
		while(!iss.eof()){
			getline(iss, temp_word, ' ');

			if(find(words.begin(), words.end(), temp_word) == words.end()) // to not add duplicates
				words.push_back(temp_word); //this is for words

			words_in_sentence.push_back(temp_word); // list of words in sentence now stored in temp_sentence
			word_count++; // this will be used to test whether we have enough words for the phrase loop
		}

		if (word_count > 1){

			if (word_count > 5)
				word_count = 5; // this is so that we make phrases a maximum of 5 words

			for (window_size = 2; window_size <= word_count; window_size++){
				iter = 0;
				while (iter != (words_in_sentence.size() - window_size + 1)){
						//	iter2
					for (iter2 = iter; iter2 < (iter+window_size); iter2++){
						temp_word = words_in_sentence[iter2];
						temp_phrase.append(temp_word);
						temp_phrase.append(1, ' ');
					}
							
					if(find(phrases.begin(), phrases.end(), temp_phrase) == phrases.end()) // to not add duplicates
						phrases.push_back(temp_phrase); // this is for phrases
	
					temp_phrase.clear();
					iter++;
				} 
			} 
		} 
	}

	infile.close();	
};