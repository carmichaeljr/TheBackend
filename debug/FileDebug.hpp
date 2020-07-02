#ifndef FILE_DEBUG_CLASS
#define FILE_DEBUG_CLASS

#include <vector>
#include <string>
#include <sstream>
#include "debug/Debug.hpp"

class FileDebug: public Debug {
	public:
		FileDebug(void);
		bool debugClassMethods(void);
		bool debugFileExists(void);
		bool debugGetCwd(void);
		bool debugGetPathFromList(void);
		bool debugGetAbsPath(void);
		bool debugObjectMethods(void);
		bool debugSetPath(void);
		bool debugGetDirList(void);
		bool debugGetDrive(void);
		bool debugGetExtension(void);
		bool debugGetName(void);
		bool debugGetNumLines(void);
		bool debugEquals(void);
		bool debugCopy(void);
		bool debugChangeExtension(void);
		bool debugChangeName(void);
		bool debugClear(void);
		bool debugIterator(void);
		bool debugWrite(void);
		bool debugAppend(void);
		bool debugCopyConstructor(void);
		std::stringstream debugFile;
		std::stringstream copyFile;
		std::stringstream equalsFile;
		std::stringstream dirsPath;
		std::vector<std::string> dirs;
};

#endif
