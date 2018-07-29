#include "markov_chain.hpp"

int MarkovChain::Start () {
	
	IO_Manager io;
	if (io.LoadFile (corpus) != 0) {
		std::cout << "[MarkovChain::Start] Unable to read file!" << std::endl;
		return 1;
	}
	
	return 0;
}