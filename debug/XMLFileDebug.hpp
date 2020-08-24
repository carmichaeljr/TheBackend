#ifndef XML_FILE_DEBUG
#define XML_FILE_DEBUG

#include <vector>
#include <string>
#include "debug/Debug.hpp"

class XMLFileDebug: public Debug {
	public:
		XMLFileDebug(void);
		bool debugClassMethods(void);
		bool debugObjectMethods(void);
		bool debugConstructor(void);
		bool debugSetSource(void);
	protected:
		std::string debugFile;
		std::vector<std::string> iterSeq;
};

#endif
