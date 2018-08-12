#include "text_creator.hpp"


std::string TextCreator::BuildSentence () {
	Sentence sentence;
	
	return sentence.AsString ();
}


std::string TextCreator::BuildParagraph () {
	Paragraph paragraph;
	
	BuildSentence ();
	
	return paragraph.AsString ();
}


std::string TextCreator::BuildBook () {
	Book book;
	
	BuildParagraph ();
	
	return book.AsString ();
}