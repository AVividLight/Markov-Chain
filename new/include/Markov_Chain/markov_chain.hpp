#ifndef MARKOV_CHAIN
#define MARKOV_CHAIN

#include "io.hpp"

#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <random>

//DELETE ME **************************************************************************************************************************************************************************
#include <iostream>
//DELETE ME **************************************************************************************************************************************************************************


class Word {
public:
	
	void DefineTextValue (const std::string v) { text_value = v; }
	void DefinePunctuation (const bool b, const char c = '\0') {
		natural_punctuation = b;
		punctuation_char = c;
	}
	void DefineQuotation (const bool b, const char c = '\0', const int l = 0) {
		natural_quotation = b;
		quotation_char = c;
		quotation_location = l;
	}
	
	bool EndOfSentence () const { return natural_punctuation; }
	bool QuoteStart () const { return (quotation_location == 0) ? true : false; }
	bool QuoteEnd () const { return (quotation_location == (text_value.length () - 1)) ? true : false; }
	
	std::string AsString () const { return text_value; }
	
private:
	std::string text_value;
	
	bool natural_punctuation;
	char punctuation_char;
	
	bool natural_quotation;
	char quotation_char;
	int quotation_location;
	
	std::vector<int> uppercase_locations;
};


class Prefex {
public:
	std::vector<Word> words;
	
	Prefex (std::vector<Word> c_words) {
		words = c_words;
	}
private:
};


class Suffex {
public:
	std::vector<Word> words;
private:
};


class MarkovChain {
public:
	int Start ();

private:
	const int ORDER = 2;
	
	std::map<Prefex, Suffex> markov_map;
	
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
	
	std::random_device rand_device;
	std::minstd_rand rand_generator = std::minstd_rand (rand_device ());
	std::uniform_int_distribution<> rand_distrobution;
	int RandomInt (const int smallest, const int largest)
	{

		rand_distrobution = std::uniform_int_distribution<> (smallest, largest);
		return rand_distrobution (rand_generator);
	}
};

#endif /* end of include guard: MARKOV_CHAIN */
