#include <string>
#include <iostream>
#include <iterator>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>


static const int ORDER = 2;


struct word {
	
	bool natural_start;
	bool natural_end;
	
	std::string text_value;
	
	operator std::string () const { return text_value; }
	
	//TODO: Overload operator to change assigned value to struct `word = ""` assigns to word.text_value.
};


struct markov_prefex {

	std::vector<word> n_gram;
	word suffex;
	
	operator std::string () const {
		std::string prefex;
		prefex.append (n_gram.at (0));
		prefex.append (" ");
		prefex.append (n_gram.at (1));
		return prefex;
	}
};


int read_file (std::string& corpus) {
	std::ifstream source_file ("/usr/local/acct/development/projects/Markov Chain/resources/corpus.txt");
	if (source_file.good ()) {
		corpus.assign ((std::istreambuf_iterator<char>(source_file)), std::istreambuf_iterator<char>());
		source_file.close ();
		
		std::transform(corpus.begin(), corpus.end(), corpus.begin(), ::tolower);
		
		for (char& c : corpus)
		{
			
			if (c == '\n')
				c = ' ';
		}
		
		return 0;
	} else {
		if (source_file.eof ())
			std::cout << "<<End of File>>" << std::endl;
		
		if (source_file.fail ())
			std::cout << "<<Logical Error on I/O Operation>" << std::endl;
		
		if (source_file.bad ())
			std::cout << "Read/Writing Error on I/O Operation" << std::endl;
		
		return 1;
	}
}


int evaluate_string (const std::vector<std::string>& words, std::map<std::string, std::vector<std::string>>& markov_chain) {
	for (int i = 0; i < words.size (); i += 1) {
		if (i > 1) {
			// ***
			
			markov_prefex test;
			test.n_gram.push_back (words.at(i - 2));
			test.n_gram.push_back (words.at(i - 1));
			test.suffex.text_value = words.at(i);
			
			// ***
			
			std::vector<std::string> suffex;
			std::string prefex = words.at(i - 2) + ' ' + words.at(i - 1);
			
			std::cout << prefex << " : " << words.at(i) << std::endl;
			
			std::map<std::string, std::vector<std::string>>::iterator lookup = markov_chain.find (prefex);
			if (lookup != markov_chain.end ()) {
				suffex = lookup->second;
			}
			
			suffex.push_back (words.at(i));
			markov_chain.emplace (prefex, suffex);
		}
	}
	
	return 0;
}


int create_markov_chain (const std::string& corpus, std::map<std::string, std::vector<std::string>>& markov_chain) {
	std::vector<std::string> words;
	
	std::stringstream string_stream (corpus);
	std::string substring;
	
	while (std::getline (string_stream, substring, ' ')) {
		if (substring.empty () == false) {
			words.push_back (substring);
		}
	}
	
	evaluate_string (words, markov_chain);
	
	return 0;
}


int main (int argc, char *argv[]) {
	std::string corpus;
	std::map<std::string, std::vector<std::string>> markov_chain;
	
	if (read_file (corpus) != 0) {
		std::cout << "Unable to read corpus!" << std::endl;
		return 1;	
	}
	
	create_markov_chain (corpus, markov_chain);
	
	return 0;
}