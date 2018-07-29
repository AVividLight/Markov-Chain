#include "io.hpp"


int IO_Manager::LoadFile (std::string &corpus) {
	std::ifstream source_file ("/usr/local/acct/development/projects/Markov Chain/new/resources/corpus.txt");
	
	if (source_file.good () != true) {
		return 1;
	}
	
	corpus.assign ((std::istreambuf_iterator<char>(source_file)), std::istreambuf_iterator<char>());
	return 0;
}