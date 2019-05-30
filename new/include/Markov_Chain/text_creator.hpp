#ifndef TEXT_CREATOR
#define TEXT_CREATOR

#include <string>
#include <vector>
#include <random>
#include <map>
//include <unordered_map>

#include <iostream>


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


class NGram {
public:
	NGram () {}
	
	NGram (Word new_word) {
		words.push_back (new_word);
	}
	
	NGram (std::vector<Word> c_words) {
		words = c_words;
	}
	
	void append (const Word word) {
		words.push_back (word);
	}
	
	void append (const std::vector<Word> new_words) {
		for (int i = 0; i < new_words.size (); i += 1) {
			words.push_back (new_words.at (i));
		}
	}
	
	Word get_at_index (const int i) const {
		/*if (i >= words.size () || words.empty () == true)
			return nanl;*/
		
		return words.at (i); //TODO Only return `i` if in range.
	}
	
	const int size () const { return words.size () - 1; }
	
	std::vector<Word> AsVector () const {
		return words;
	}
	
	std::string AsString () const {
			std::string str;
			for (int i = 0; i < words.size (); i += 1) {
				str.append (words.at (i).AsString ());
				str.push_back (' '); // *** TODO: Change character based on context (sentence: ' ', paragraph: ". ", chapter: "\n\n", book: "\n\n***\n")
			}
			//str.pop_back ();
		
			return str;
		}
private:
	std::vector<Word> words;
};


namespace std {
	template<> struct less<NGram> {
		bool operator() (const NGram &lhs, const NGram &rhs) const {
			return lhs.AsString ().compare (rhs.AsString ()) < 0;
		}
	};
}


class TextCreator {
public:
	NGram BuildSentence (const std::map<NGram, NGram> &markov_map);
	std::string BuildParagraph (const std::map<NGram, NGram> &markov_map);
	std::string BuildChapter (const std::map<NGram, NGram> &markov_map);
	std::string BuildBook (const std::map<NGram, NGram> &markov_map);
	

private:
	NGram RandomPrefex (const std::map<NGram, NGram> &markov_map);
	
	std::random_device rand_device;
	std::minstd_rand rand_generator = std::minstd_rand (rand_device ());
	std::uniform_int_distribution<> rand_distrobution;
	int RandomInt (const int smallest, const int largest) {
		if (smallest == largest) {
			return smallest;
		}
		
		rand_distrobution = std::uniform_int_distribution<> (smallest, largest);
		return rand_distrobution (rand_generator);
	}
};

#endif /* end of include guard: TEXT_CREATOR */
