#include "text_creator.hpp"


/*
	1. Pick random starting prefex
	2. Start crawling
	3. Period and new random if key has no matching value
	4. Stop if EndOfSentence == true || WORDS_PER_SENTENCE_HIGHEND
	5. Store sentence (?) and return as string
*/

NGram TextCreator::BuildSentence (const std::map<NGram, NGram> &markov_map) {
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
		if (key_find == markov_map.end ()) {
			new_value.append (RandomPrefex (markov_map).AsVector ());
			i += (ORDER - 1);
		} else {
			new_value.append (key_find->second.get_at_index (RandomInt (0, markov_map.at (new_key).size ())));
		}
		
		sentence.append (new_value.AsVector ());
	}
	
	return sentence;
}


NGram TextCreator::RandomPrefex (const std::map<NGram, NGram> &markov_map) {
	NGram new_prefex;
	
	auto random_key = std::next (std::begin(markov_map), RandomInt (0, markov_map.size () - 1));
	for (int i = 0; i < ORDER; i += 1) {
		new_prefex.append (random_key->first.get_at_index (i));
	}
	
	return new_prefex;
}


std::string TextCreator::BuildParagraph (const std::map<NGram, NGram> &markov_map) {
	std::string paragraph;
	
	const int number_of_sentences = RandomInt (SENTENCES_PER_PARAGRAPH_LOWEND, SENTENCES_PER_PARAGRAPH_HIGHEND);
	for (int i = 0; i < number_of_sentences; i += 1)
	{
		
		paragraph.append (BuildSentence (markov_map).AsString ());
	}
	
	paragraph.append ("\n\n");
	
	return paragraph;
}


std::string TextCreator::BuildChapter (const std::map<NGram, NGram> &markov_map) {
	std::string chapter;
	
	const int number_of_paragraphs = RandomInt (PARAGRAPHS_PER_CHAPTER_LOWEND, PARAGRAPHS_PER_CHAPTER_HIGHEND);
	for (int i = 0; i < number_of_paragraphs; i += 1)
	{
		
		chapter.append (BuildParagraph (markov_map));
	}
	
	chapter.append ("\n\n");
	
	return chapter;
}


std::string TextCreator::BuildBook (const std::map<NGram, NGram> &markov_map) {
	std::string book;
	
	const int number_of_chapters = RandomInt (CHAPTERS_PER_BOOK_LOWEND, CHAPTERS_PER_BOOK_HIGHEND);
	for (int i = 0; i < number_of_chapters; i += 1)
	{
		
		book.append (BuildChapter (markov_map));
	}
	
	return book;
}