#ifndef MARKOV_CHAIN
#define MARKOV_CHAIN

#include "io.hpp"

#include <map>
#include <vector>
#include <string>
#include <iostream>


class Word {
public:
	
	void SetTextValue (const std::string v) { text_value = v; }
	void SetPunctuation (const bool b, const char c = '\0') {
		natural_punctuation = b;
		punctuation_char = c;
	}
	void SetQuotation (const bool b, const char c = '\0', const int l = 0) {
		natural_quotation = b;
		quotation_char = c;
		quotation_location = l;
	}
	
	bool EndOfSentence () { return natural_punctuation; }
	
private:
	std::string text_value;
	
	bool natural_punctuation;
	char punctuation_char;
	
	bool natural_quotation;
	char quotation_char;
	int quotation_location;
};


class MarkovChain {
public:
	int Start ();

private:
	std::string corpus;
	std::map<Word, std::vector<Word>> markov_map;
};

#endif /* end of include guard: MARKOV_CHAIN */
