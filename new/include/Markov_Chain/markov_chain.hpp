#ifndef MARKOV_CHAIN
#define MARKOV_CHAIN

#include "io.hpp"
#include "text_creator.hpp"

#include <map>
//#include <unordered_map> //https://stackoverflow.com/questions/17016175/c-unordered-map-using-a-custom-class-type-as-the-key
#include <vector>
#include <string>
#include <sstream>
#include <iostream>


class MarkovChain {
public:
	int Start ();

private:
	std::map<NGram, NGram> markov_map;
	
	int BuildMap (std::string &corpus);
	void RemoveNewLines (std::string &corpus);
	std::vector<Word> SplitStringIntoWords (const std::string &corpus);
	Word CreateWord (std::string &text);
	void AnalyzeWord (Word &word);
	bool CharIsPunctuation (const char &c);
	bool CharIsQuotation (const char &c);
	int LinkWords (const std::vector<Word> &all_words);
	
	void Lowercase (std::string &str) {
		std::transform (str.begin (), str.end (), str.begin (), ::tolower);
	}
};

#endif /* end of include guard: MARKOV_CHAIN */
