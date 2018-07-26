#include <string>
#include <iostream>
#include <iterator>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <random>


static const int ORDER = 2;


int read_file (std::string& corpus) {
	std::ifstream source_file ("/usr/local/acct/development/projects/Markov Chain/resources/corpus.txt");
	if (source_file.good ()) {
		corpus.assign ((std::istreambuf_iterator<char>(source_file)), std::istreambuf_iterator<char>());
		source_file.close ();
		
		std::transform(corpus.begin(), corpus.end(), corpus.begin(), ::tolower);
		
		for (char& c : corpus) {
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


int make_paragraph (std::map<std::string, std::vector<std::string>>& markov_chain) {
	std::random_device m_device;
	std::minstd_rand m_generator = std::minstd_rand (m_device ());
	std::uniform_int_distribution<> m_distrobution;
	
	std::map<std::string, std::vector<std::string>>::iterator it = markov_chain.begin ();
	m_distrobution = std::uniform_int_distribution<> (0, markov_chain.size () - 1);
	std::advance (it, m_distrobution (m_generator));
	
	std::vector<std::string> words = {it->first, it->second.at(0)};
	std::string new_suffex;
	
	const int PARAGRAPH_MAX = 10;
	int paragraph_length = 0;
	
	while (paragraph_length < PARAGRAPH_MAX) {
		it = markov_chain.find (words.at (words.size() - 2) + " " + words.at (words.size() - 1));
		
		/*if (it == markov_chain.end ()) {
			std::cout << "iterator at end" << std::endl;
			std::cout << it << " == " << markov_chain.end () << std::endl;
			break;
		}*/
		
		m_distrobution = std::uniform_int_distribution<> (0, it->second.size());
		new_suffex = it->second.at (m_distrobution (m_generator));
		
		words.push_back (new_suffex);
		
		//if (new_suffex.find ('.') != std::string::npos)
			//break;
		paragraph_length += 1;
	}
	
	std::string generated_string = "";
	for (int i = 0; i < words.size (); i += 1) {
		generated_string += (words.at (i) + ' ');
	}
	
	std::cout << generated_string << std::endl;
	
	return 0;
}


void dump_chain (std::map<std::string, std::vector<std::string>>& markov_chain) {
	std::cout << "chain length: " << markov_chain.size () << std::endl;
	
	for (std::map<std::string, std::vector<std::string>>::iterator iter = markov_chain.begin(); iter != markov_chain.end(); ++iter) {
		std::cout << iter->first << " : ";
		
		for (int i = 0; i < iter->second.size (); i += 1)
		{
			
			std::cout << "[" << iter->second.at (i) << "]";
		}
		
		std::cout << std::endl;
	}
}


int main (int argc, char *argv[]) {
	std::string corpus;
	std::map<std::string, std::vector<std::string>> markov_chain;
	
	if (read_file (corpus) != 0) {
		std::cout << "Unable to read corpus!" << std::endl;
		return 1;	
	}
	
	create_markov_chain (corpus, markov_chain);
	
	//dump_chain (markov_chain);
	
	make_paragraph (markov_chain);
	
	return 0;
}