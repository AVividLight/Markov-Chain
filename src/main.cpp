#include <string>
#include <iostream>
#include <iterator>
#include <fstream>
#include <sstream>
#include <map>

class markov_string
{

	bool natural_start;
	bool natural_end;

	std::string value;
};


int read_file (std::string& corpus)
{
	
	std::ifstream source_file ("/usr/local/acct/development/projects/Markov Chain/resources/corpus.txt");
	if (source_file.good ())
	{
		corpus.assign ((std::istreambuf_iterator<char>(source_file)), std::istreambuf_iterator<char>());
		source_file.close ();
		return 0;
	} else {
		return 1;
	}
}


int evaluate_string (const std::string& str)
{
	
	return 0;
}


int create_markov_chain (const std::string& corpus, std::map<std::string, std::string>& markov_chain)
{
	
	std::stringstream string_stream (corpus);
	std::string substring;
	
	while (std::getline (string_stream, substring, ' '))
	{
		
		evaluate_string (substring);
		
		std::cout << substring << std::endl;
	}
	
	return 0;
}


int main (int argc, char *argv[])
{	
	
	std::string corpus;
	std::map<std::string, std::string> markov_chain;
	
	if (read_file (corpus) != 0)
	{
		std::cout << "Unable to read corpus!" << std::endl;
		return 1;	
	}
	
	std::cout << "Corpus: " << corpus << std::endl;
	
	create_markov_chain (corpus, markov_chain);
	
	return 0;
}