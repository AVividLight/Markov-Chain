#include "markov_chain.hpp"


int MarkovChain::Start () {
	IO_Manager io;
	std::string corpus;
	
	if (io.LoadFile (corpus) != 0) {
		std::cout << "[MarkovChain::Start] Unable to read file!" << std::endl;
		return 1;
	}
	
	if (BuildMap (corpus) != 0) {
		return 1;
	}
	
	return 0;
}


int MarkovChain::BuildMap (std::string &corpus) {
	RemoveNewLines (corpus);
	std::vector<Word> all_words = SplitStringIntoWords (corpus);
	
	return 0;
}


void MarkovChain::RemoveNewLines (std::string &corpus) {
	for (char &c : corpus) {
		if (c == '\n')
			c = ' ';
	}
}


std::vector<Word> MarkovChain::SplitStringIntoWords (const std::string &corpus) {
	std::vector<Word> all_words;
	
	std::stringstream string_stream(corpus);
	std::string item;
	while (std::getline(string_stream, item, ' ')) {
		if (item.empty () != true) {
			all_words.push_back (CreateWord (item));
		}
	}
	
	return all_words;
}


Word MarkovChain::CreateWord (std::string &text) {
	Word new_word;
	
	new_word.DefineTextValue (text);
	AnalyzeWord (new_word);
	
	return new_word;
}


void MarkovChain::AnalyzeWord (Word &word) {
	for (int i = 0; i < word.AsString ().length (); i += 1) {
		const char &c = word.AsString ().at (i);
		
		if (CharIsPunctuation (c)) {
			word.DefinePunctuation (true, c);
		} else {
			word.DefinePunctuation (false);
		}
		
		if (CharIsQuotation (c)) {
			word.DefineQuotation (true, c, i);
		} else {
			word.DefineQuotation (false);
		}
	}
}


bool MarkovChain::CharIsPunctuation (const char &c) {
	switch (c) {
		case '.':
		return true;
		
		case '!':
		return true;
			
		case '?':
		return true;
			
		default:
		return false;
	}
}


bool MarkovChain::CharIsQuotation (const char &c) {
	switch (c) {
		case '\'':
		return true;
		
		case '"':
		return true;
		
		default:
		return false;
	}
}