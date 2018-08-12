#ifndef TEXT_CREATOR
#define TEXT_CREATOR

#include <string>
#include <vector>
#include <random>


const static int ORDER = 2;

//* https://strainindex.wordpress.com/2008/07/28/the-average-sentence-length/
const static int WORDS_PER_SENTENCE_LOWEND = 2;
const static int WORDS_PER_SENTENCE_HIGHEND = 17;

const static int SENTENCES_PER_PARAGRAPH_LOWEND = 1;
const static int SENTENCES_PER_PARAGRAPH_HIGHEND = 9;

const static int PARAGRAPHS_PER_CHAPTER_LOWEND = 3;
const static int PARAGRAPHS_PER_CHAPTER_HIGHEND = 12;

const static int CHAPTERS_PER_BOOK_LOWEND = 1;
const static int CHAPTERS_PER_BOOK_HIGHEND = 18;



class Word {
public:
	
	void DefineTextValue (const std::string v) { text_value = v; }
	void DefinePunctuation (const bool b, const char c = '\0') {
		natural_punctuation = b;
		punctuation_char = c;
	}
	void DefineQuotation (const bool b, const char c = '\0', const int l = 0) {
		natural_quotation = b;
		quotation_char = c;
		quotation_location = l;
	}
	
	bool EndOfSentence () const { return natural_punctuation; }
	char Punctuation () const { return punctuation_char; }
	bool QuoteStart () const { return (quotation_location == 0) ? true : false; }
	bool QuoteEnd () const { return (quotation_location == (text_value.length () - 1)) ? true : false; }
	
	std::string AsString () const { return text_value; }
	
private:
	std::string text_value;
	
	bool natural_punctuation;
	char punctuation_char;
	
	bool natural_quotation;
	char quotation_char;
	int quotation_location;
	
	//std::vector<int> uppercase_locations;
};


class Prefex {
public:
	std::vector<Word> words;
	
	Prefex () {}
	
	Prefex (std::vector<Word> c_words) {
		words = c_words;
	}
	
	std::string AsString () const {
		std::string str;
		for (int i = 0; i < ORDER; i += 1) {
			str.append (words.at (i).AsString ());
			str.push_back (' ');
		}
		str.pop_back ();
		
		return str;
	}
private:
};


namespace std {
	template<> struct less<Prefex> {
		bool operator() (const Prefex &lhs, const Prefex &rhs) const {
			return lhs.AsString ().compare (rhs.AsString ()) < 0;
		}
	};
}


class Suffex {
public:
	std::vector<Word> words;
	
	Suffex () {}
	
	Suffex (std::vector<Word> c_words) {
		words = c_words;
	}
	
	std::string AsString () const {
		std::string str;
		for (int i = 0; i < words.size (); i += 1) {
			str.append (words.at (i).AsString ());
			str.append (", ");
		}
		str.erase (str.size () - 2);
		
		return str;
	}
private:
};


class Sentence {
public:
	
	std::string AsString () const {
		std::string str;
		for (int i = 0; i < words.size (); i += 1) {
			str.append (words.at (i).AsString ());
			str.push_back (' ');
		}
		str.pop_back ();
		
		return str;
	}
private:
	std::vector<Word> words;
};


class Paragraph {
public:
	
	std::string AsString () const {
		std::string str;
		for (int i = 0; i < sentences.size (); i += 1) {
			str.append (sentences.at (i).AsString ());
			str.append (". "); //TODO Return punctuation char
		}
		str.pop_back ();
		
		return str;
	}
private:
	std::vector<Sentence> sentences;
};


class Chapter {
public:
	
	std::string AsString () const {
		std::string str;
		for (int i = 0; i < paragraphs.size (); i += 1) {
			str.append (paragraphs.at (i).AsString ());
			str.append ("\n\n");
		}
		str.pop_back ();
		
		return str;
	}
private:
	std::vector<Paragraph> paragraphs;
};


class Book {
public:
	
	std::string AsString () const {
		std::string str;
		for (int i = 0; i < chapters.size (); i += 1) {
			str.append (chapters.at (i).AsString ());
			str.append ("\n\n***\n");
		}
		str.pop_back ();
		
		return str;
	}
private:
	std::vector<Chapter> chapters;
};


class TextCreator {
public:
	std::string BuildSentence ();
	std::string BuildParagraph ();
	std::string BuildChapter ();
	std::string BuildBook ();
	

private:
	std::random_device rand_device;
	std::minstd_rand rand_generator = std::minstd_rand (rand_device ());
	std::uniform_int_distribution<> rand_distrobution;
	int RandomInt (const int smallest, const int largest)
	{

		rand_distrobution = std::uniform_int_distribution<> (smallest, largest);
		return rand_distrobution (rand_generator);
	}
};

#endif /* end of include guard: TEXT_CREATOR */
