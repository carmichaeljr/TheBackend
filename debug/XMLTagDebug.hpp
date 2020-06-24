#ifndef XML_TAG_DEBUG
#define XML_TAG_DEBUG

#include "Debug.hpp"

class XMLTagDebug: public Debug {
	public:
		XMLTagDebug(void);
		bool debugClassMethods(void);
		bool debugObjectMethods(void);
		bool debugSetGetName(void);
		bool debugSetGetData(void);
		bool debugParseName(void);
};

#endif
