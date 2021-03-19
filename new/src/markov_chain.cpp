#include "markov_chain.hpp"


const char get_input ()
{

	std::string input;
	
	do
	{
		
		std::cout << std::endl << "Generate another text? (y/n): ";
		std::getline (std::cin, input);
	} while (tolower (input[0]) != 'y' && tolower (input[0]) != 'n');
	
	return tolower (input[0]);
}


int MarkovChain::Start () {
	InputOutput io;
	std::string corpus;
	
	if (io.LoadFile (corpus) != 0) {
		std::cout << "[MarkovChain::Start] Unable to read file!" << std::endl;
		return 1;
	}
	
	if (BuildMap (corpus) != 0) {
		return 1;
	}
	
	TextCreator text_creator;
	
	do
	{
		
		std::cout << std::endl << text_creator.BuildBook (markov_map) << std::endl << std::endl;
		
	} while (get_input () == 'y' ? true : false);
	
	return 0;
}


int MarkovChain::BuildMap (std::string &corpus) {
	RemoveNewLines (corpus);
	std::vector<Word> all_words = SplitStringIntoWords (corpus);
	
	if (LinkWords (all_words) != 0) {
		std::cout << "[MarkovChain::BuildMap] ORDER larger than corpus!" << std::endl;
		return 1;
	}
	
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


int MarkovChain::LinkWords (const std::vector<Word> &all_words) {
	std::map <NGram, NGram>::iterator map_iterator;
	int total_words = all_words.size ();
	if (total_words > ORDER) {
		int index = ORDER;
		while (index < total_words) {
			NGram new_prefex;
			for (int i = ORDER; i > 0; i -= 1) {
				new_prefex.append (all_words.at (index - i));
			}
			
			NGram new_suffex;
			new_suffex.append (all_words.at (index));
		
			std::pair<NGram, NGram> ngram (new_prefex, new_suffex);
			
			const std::pair<std::map<NGram, NGram>::iterator, bool> insert_return = markov_map.insert (ngram);
			if (insert_return.second == false) {
				insert_return.first->second.append (all_words.at (index));
				//std::cout << "Element already exists, now: [" << insert_return.first->first.AsString () << " : " << insert_return.first->second.AsString () << ']' << std::endl;
			}// else {std::cout << "Adding new element: [" << insert_return.first->first.AsString () << " : " << insert_return.first->second.AsString () << ']' << std::endl;}
				
			index += 1;
		}
	} else {
		return 1;
	}
	
	return 0;
}