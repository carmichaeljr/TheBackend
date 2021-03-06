#ifndef TOKENIZER_CLASS
#define TOKENIZER_CLASS

#include <string>
#include <vector>
#include "src/VectorPassThrough.hpp"

class Tokenizer: public VectorPassThrough<std::string> {
	public:
		static const int parseSuccess=0;
		static const int unballancedTokens=1;
	public:
		Tokenizer(void);
		Tokenizer(const Tokenizer &other);
		Tokenizer(const Tokenizer &&other);
		Tokenizer& operator=(const Tokenizer &other);
		Tokenizer& operator=(const Tokenizer &&other);
		void addSplitTokens(const std::string &tokens);
		const std::string& getSplitTokens(void) const;
		void addInclusionTokens(const std::string &tokenPairs);
		const std::vector<std::string>& getInclusionTokens(void) const;
		void addExclusionTokens(const std::string &tokenPairs);
		const std::vector<std::string>& getExclusionTokens(void) const;
		void parse(const std::string &raw, const bool keepTokens=false);
		bool good(void) const;
		int rdstate(void) const;
		void clear(void);
	protected:
		int error=Tokenizer::parseSuccess;
		std::vector<std::string> inclusionTokens;
		std::vector<std::string> exclusionTokens;
		std::string splitTokens;
	private:
		struct ParseData {
			std::vector<std::string> inclusionStack;
			std::vector<std::string> exclusionStack;
			unsigned int curIndex=0;
			unsigned int prevIndex=0;
			bool keepTokens=false;
		};
		void addTokenPairs(std::vector<std::string> &place, const std::string &raw);
		void checkForInclusionToken(const std::string &raw, ParseData &pd);
		void checkForExclusionToken(const std::string &raw, ParseData &pd);
		std::string getPairedToken(const std::vector<std::string> &src, const char openToken) const;
		void addSegmentAndUpdateIndexes(const std::string &raw, ParseData &pd);
		void addSegment(const std::string &raw, const int start, const int end);
		void addToken(const std::string &raw, Tokenizer::ParseData &pd);
		void updateIndexes(Tokenizer::ParseData &pd);
};

#endif
