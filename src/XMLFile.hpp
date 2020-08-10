#ifndef XML_FILE_CLASS
#define XML_FILE_CLASS

//setSource
//write
//iter access
//GT "pass-through" functions

#include <string>
#include "src/File.hpp"
#include "src/Tree.hpp"
#include "src/XMLTag.hpp"
#include "src/Tokenizer.hpp"

class XMLFile: public File {
	public:
		explicit XMLFile(const std::string &path);
		//void setSource(const std::string &path);
		//void clear(void);
	protected:
		Tree<XMLTag> data;
	private:
		void parseFile(void);
		void parseLine(const Tokenizer &tokenizer, Tree<XMLTag>::iterator &iter);
};

#endif
