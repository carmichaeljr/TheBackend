#ifndef TOKENIZER_CLASS
#define TOKENIZER_CLASS

#include <string>
#include <vector>

class Tokenizer {
	public:
		static const int parseSuccess=0;
		static const int unballancedTokens=1;
	public:
		Tokenizer(void);
		void addSplitTokens(const std::string &tokens);
		const std::string& getSplitTokens(void) const;
		void addInclusionTokens(const std::string &tokenPairs);
		const std::vector<std::string>& getInclusionTokens(void) const;
		void addExclusionTokens(const std::string &tokenPairs);
		const std::vector<std::string>& getExclusionTokens(void) const;
		void parse(const std::string &raw);
	private:
		int error=Tokenizer::parseSuccess;
		std::vector<std::string> segments;
		std::vector<std::string> inclusionTokens;
		std::vector<std::string> exclusionTokens;
		std::string splitTokens;
		void addTokenPairs(std::vector<std::string> &place, const std::string &raw);
		char getPairedToken(const std::vector<std::string> &src, const char openToken) const;
		void addSegment(const std::string &raw, const int start, const int end);
};

#endif
