#ifndef XML_TAG_DEBUG
#define XML_TAG_DEBUG

#include <vector>
#include "Debug.hpp"
#include "src/XMLTag.hpp"

class XMLTagDebug: public Debug {
	public:
		XMLTagDebug(void);
		bool debugClassMethods(void);
		bool debugObjectMethods(void);
		bool debugSetGetAttributes(void);
		bool debugFind(void);
		bool debugCount(void);
		bool debugSwap(void);
		bool debugErase(void);
		bool debugClear(void);
		bool debugEquals(void);
		bool debugParseName(void);
		bool debugParseAttributes(void);
		bool debugParseErrors(void);
		bool debugParseBadFormatting(void);
		bool debugGetOpeningTag(void);
		bool debugGetClosingTag(void);
		bool debugCopyConstructor(void);
	private:
		std::vector<std::string> correctKey;
		std::vector<std::string> correctVal;
		void initilizeBlankTag(XMLTag &tag) const;
};

#endif
