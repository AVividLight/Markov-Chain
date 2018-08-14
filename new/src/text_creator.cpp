#include "text_creator.hpp"


/*
	1. Pick random starting prefex
	2. Start crawling
	3. Period and new random if key has no matching value
	4. Stop if EndOfSentence == true || WORDS_PER_SENTENCE_HIGHEND
	5. Store sentence (?) and return as string
*/

std::string TextCreator::BuildSentence (const std::map<NGram, NGram> &markov_map) {
	NGram sentence;
	const int this_sentence_length = RandomInt (WORDS_PER_SENTENCE_LOWEND, WORDS_PER_SENTENCE_HIGHEND);
	
	//***
	auto random_key = std::next(std::begin(markov_map), RandomInt (0, markov_map.size () - 1));
	for (int i = 0; i < ORDER; i += 1) {
		sentence.append (random_key->first.get_at_index (i));
	}
	//***
	
	for (int i = ORDER; i < this_sentence_length; i += 1) {
		std::vector<Word> prefex;
		for (int j = 0; j < ORDER; j += 1) {
			//prefex.push_back (sentence.AsVector.)
		}
		
		NGram new_key (sentence.AsVector ());
		
		sentence.append (markov_map.at (new_key).get_at_index (RandomInt (0, markov_map.at (new_key).size ())));
	}
	
	return sentence.AsString ();
}


std::string TextCreator::BuildParagraph (const std::map<NGram, NGram> &markov_map) {
	NGram paragraph;
	
	BuildSentence (markov_map);
	
	return paragraph.AsString ();
}


std::string TextCreator::BuildChapter (const std::map<NGram, NGram> &markov_map) {
	NGram chapter;
	
	BuildParagraph (markov_map);
	
	return chapter.AsString ();
}


std::string TextCreator::BuildBook (const std::map<NGram, NGram> &markov_map) {
	NGram book;
	
	BuildParagraph (markov_map);
	
	return book.AsString ();
}