#ifndef TOKENIZER_DEBUG_CLASS
#define TOKENIZER_DEBUG_CLASS

#include <string>
#include <sstream>
#include "debug/Debug.hpp"
#include "src/Tokenizer.hpp"

class TokenizerDebug: public Debug {
	public:
		TokenizerDebug(void);
		bool debugClassMethods(void);
		bool debugObjectMethods(void);
		bool debugAddSplitTokens(void);
		bool debugAddInclusionTokens(void);
		bool debugAddExclusionTokens(void);
		bool debugParse(void);
	private:
		std::string splitTokens;
		std::string inclusionTokens;
		std::string exclusionTokens;
		std::stringstream parseStr;
		std::vector<std::string> parseStrNames;
		void initilizeTokenizer(Tokenizer &test);
};

#endif
