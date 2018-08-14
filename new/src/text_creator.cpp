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
	
	sentence.append (RandomPrefex (markov_map).AsVector ());
	
	for (int i = ORDER; i < this_sentence_length; i += 1) {
		std::vector<Word> new_prefex;
		for (int j = ORDER; j > 0; j -= 1) {
			new_prefex.push_back (sentence.get_at_index (i - j));
		}
		
		NGram new_key (new_prefex);
		std::map<NGram, NGram>::const_iterator key_find = markov_map.find (new_key);
		
		NGram new_value;
		if (key_find == markov_map.end()) {
			new_value.append (RandomPrefex (markov_map).AsVector ());
		} else {
			new_value.append (key_find->second.get_at_index (RandomInt (0, markov_map.at (new_key).size ())));
		}
		
		sentence.append (new_value.AsVector ());
	}
	
	return sentence.AsString ();
}


NGram TextCreator::RandomPrefex (const std::map<NGram, NGram> &markov_map) {
	NGram new_prefex;
	
	auto random_key = std::next(std::begin(markov_map), RandomInt (0, markov_map.size () - 1));
	for (int i = 0; i < ORDER; i += 1) {
		new_prefex.append (random_key->first.get_at_index (i));
	}
	
	return new_prefex;
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