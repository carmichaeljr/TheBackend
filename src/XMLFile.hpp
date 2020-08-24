#ifndef XML_FILE_CLASS
#define XML_FILE_CLASS

//setSource
//write
//clear
//equals

#include <string>
#include "src/File.hpp"
#include "src/Tree.hpp"
#include "src/XMLTag.hpp"
#include "src/Tokenizer.hpp"
#include "src/TreePassThrough.hpp"

class XMLFile: public File, public TreePassThrough<XMLTag> {
	public:
		typedef Tree<XMLTag>::iterator iterator;
		typedef Tree<XMLTag>::const_iterator const_iterator;
	public:
		explicit XMLFile(const std::string &path);
		void setSource(const std::string &path);
		//begin/end methods are declared here to resolve inheritance ambiguity
		iterator begin(bool revisit=false);
		const const_iterator begin(bool revisit=false) const;
		const_iterator cbegin(bool revisit=false) const;
		iterator end(void);
		const const_iterator end(void) const;
		const_iterator cend(void) const;
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
