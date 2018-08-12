#include "text_creator.hpp"


std::string TextCreator::BuildSentence () {
	Sentence sentence;
	
	const int this_sentence_length = RandomInt (WORDS_PER_SENTENCE_LOWEND, WORDS_PER_SENTENCE_HIGHEND);
	
	return sentence.AsString ();
}


std::string TextCreator::BuildParagraph () {
	Paragraph paragraph;
	
	BuildSentence ();
	
	return paragraph.AsString ();
}


std::string TextCreator::BuildChapter () {
	Chapter chapter;
	
	BuildParagraph ();
	
	return chapter.AsString ();
}


std::string TextCreator::BuildBook () {
	Book book;
	
	BuildParagraph ();
	
	return book.AsString ();
}