#include <string>
#include <iostream>
#include <iterator>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <random>
#include <algorithm>


static const int ORDER = 2;


class Markov_Prefix {
	std::string first_word;
	std::string second_word;
	
	std::string concat () {
		return first_word + " " + second_word;
	}
} prefix;


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


int evaluate_string (const std::vector<std::string>& all_words, std::map<std::string, std::vector<std::string>>& markov_chain) {
	for (int i = 0; i < all_words.size (); i += 1) {
		if (i > 1) {
			std::string prefex = all_words[i - 2] + ' ' + all_words[i - 1];
			
			std::map<std::string, std::vector<std::string>>::iterator lookup = markov_chain.find (prefex);
			if (lookup != markov_chain.end ()) {
				//TODO: Check to see if suffex already exists and ignore if true
				lookup->second.emplace_back (all_words[i]);
				
				//std::cout << "adding `" << words.at (i) << "` to `" << lookup->first << "`" << std::endl;
			} else {
				std::vector<std::string> suffex (1, all_words[i]);
				markov_chain.emplace (prefex, suffex);
				
				//std::cout << "creating `" << prefex << " : " << suffex.at(0) << "`" << std::endl;
			}
		}
	}
	
	return 0;
}


int create_markov_chain (const std::string& corpus, std::map<std::string, std::vector<std::string>>& markov_chain) {
	std::vector<std::string> all_words;
	std::stringstream string_stream (corpus);
	std::string substring;
	
	while (std::getline (string_stream, substring, ' ')) {
		if (substring.empty () == false) {
			all_words.emplace_back (substring);
		}
	}
	
	evaluate_string (all_words, markov_chain);
	
	return 0;
}


int make_paragraph (std::map<std::string, std::vector<std::string>>& markov_chain) {
	std::random_device m_device;
	std::minstd_rand m_generator = std::minstd_rand (m_device ());
	std::uniform_int_distribution<> m_distrobution = std::uniform_int_distribution<> (0, markov_chain.size () - 1);
	
	std::map<std::string, std::vector<std::string>>::iterator it = markov_chain.begin ();
	std::advance (it, m_distrobution (m_generator));
	
	
	std::vector<std::string> generated_string;
	
	std::stringstream ss(it->first);
	std::string item;
	while (getline(ss, item, ' ')) {
		generated_string.emplace_back(item);
	}

	
	const int PARAGRAPH_MAX = 100;
	int paragraph_length = 0;
	
	int max = 0;
	
	while (paragraph_length < PARAGRAPH_MAX) {
		std::string debug_string = (generated_string[generated_string.size() - 2] + " " + generated_string[generated_string.size() - 1]);
		
		it = markov_chain.find (debug_string);
		if (it == markov_chain.end ()) {
			std::cout << "unable to find '" << debug_string << "'" << std::endl << std::endl;
			break;
		}
		
		max = it->second.size ();
		
		if (max != 0) {
			m_distrobution = std::uniform_int_distribution<> (0, max);
			max = m_distrobution (m_generator);
		} else {
			max = 0;
		}
		generated_string.emplace_back (it->second[max]);

		paragraph_length += 1;
	}
	
	std::string concatenated_string = "";
	for (int i = 0; i < generated_string.size (); i += 1) {
		concatenated_string += (generated_string[i] + ' ');
	}
	
	std::cout << "<*> " << concatenated_string << "<*>" << std::endl;
	
	return 0;
}


void dump_chain (std::map<std::string, std::vector<std::string>>& markov_chain) {
	std::cout << "chain length: " << markov_chain.size () << std::endl;
	
	for (std::map<std::string, std::vector<std::string>>::iterator iter = markov_chain.begin(); iter != markov_chain.end(); ++iter) {
		std::cout << iter->first << " : ";
		
		for (int i = 0; i < iter->second.size (); i += 1)
		{
			
			std::cout << "[" << iter->second[i] << "]";
		}
		
		std::cout << std::endl;
	}
}


int main (int argc, char *argv[]) {
	std::string corpus;
	std::map<std::string, std::vector<std::string>> markov_chain;
	std::map<Markov_Prefix, std::vector<std::string>> test;
	
	if (read_file (corpus) != 0) {
		std::cout << "Unable to read corpus!" << std::endl;
		return 1;	
	}
	
	create_markov_chain (corpus, markov_chain);
	
	//dump_chain (markov_chain);
	
	make_paragraph (markov_chain);
	
	return 0;
}