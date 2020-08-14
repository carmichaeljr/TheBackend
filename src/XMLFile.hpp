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
#include "src/TreePassThrough.hpp"

class XMLFile: public File, public TreePassThrough<XMLTag> {
	public:
		explicit XMLFile(const std::string &path);
		//void setSource(const std::string &path);
		//void clear(void);
	private:
		void parseFile(void);
		void parseLine(const Tokenizer &tokenizer, Tree<XMLTag>::iterator &iter);
		void addNode(Tree<XMLTag>::iterator &iter, const std::string &rawData, const bool selfClosing);
		void addFirstNode(Tree<XMLTag>::iterator &iter, const std::string &rawData);
		void addNthNode(Tree<XMLTag>::iterator &iter, const std::string &rawData);
		void addData(const Tree<XMLTag>::iterator &iter, const std::string &rawData);
};

#endif
