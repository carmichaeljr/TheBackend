#ifndef HELPER_FUNC_DEBUG_CLASS
#define HELPER_FUNC_DEBUG_CLASS

#include "Debug.hpp"

class HelperFuncDebug: public Debug {
	public:
		HelperFuncDebug(void);
		bool debugClassMethods(void);
		bool debugObjectMethods(void);
		bool debugTrimWhitespaceAtEnd(void);
		bool debugTrimWhitespaceAtStart(void);
		bool debugTrimWhitespace(void);
};

#endif
