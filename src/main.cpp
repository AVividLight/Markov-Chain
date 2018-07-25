#include <string>
#include <iostream>
#include <iterator>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>


static const int ORDER = 2;


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
			std::cout << "<<Read/Writing Error on I/O Operation>>" << std::endl;
		
		return 1;
	}
}


int evaluate_string (const std::vector<std::string>& words, std::map<std::string, std::vector<std::string>>& markov_chain) {
	for (int i = 0; i < words.size (); i += 1) {
		if (i > 1) {
			std::string prefex = words.at(i - 2) + ' ' + words.at(i - 1);
			
			std::map<std::string, std::vector<std::string>>::iterator lookup = markov_chain.find (prefex);
			if (lookup != markov_chain.end ()) {
				lookup->second.push_back (words.at (i));
				
				//std::cout << "adding `" << words.at (i) << "` to `" << lookup->first << "`" << std::endl;
			} else {
				std::vector<std::string> suffex (1, words.at (i));
				markov_chain.emplace (prefex, suffex);
				
				//std::cout << "creating `" << prefex << " : " << suffex.at(0) << "`" << std::endl;
			}
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
	
	std::cout << "chain length: " << markov_chain.size () << std::endl;
	
	for (std::map<std::string, std::vector<std::string>>::iterator iter = markov_chain.begin(); iter != markov_chain.end(); ++iter) {
		std::cout << iter->first << " : ";
		
		for (int i = 0; i < iter->second.size (); i += 1)
		{
			
			std::cout << "[" << iter->second.at (i) << "]";
		}
		
		std::cout << std::endl;
	}
	
	return 0;
}