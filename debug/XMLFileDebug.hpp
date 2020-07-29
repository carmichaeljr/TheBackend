#ifndef XML_FILE_DEBUG
#define XML_FILE_DEBUG

#include "debug/Debug.hpp"

class XMLFileDebug: public Debug {
	public:
		XMLFileDebug(void);
		bool debugClassMethods(void);
		bool debugObjectMethods(void);
};

#endif
