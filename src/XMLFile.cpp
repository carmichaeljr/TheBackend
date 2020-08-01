#include "src/XMLFile.hpp"
#include "src/HelperFunctions.hpp"

#include <iostream>

XMLFile::XMLFile(const std::string &path):
	File(path) {
	//this->clear();
	this->parseFile();
}

//void XMLFile::setSource(const std::string &path){
//	if (File::fileExists(path)){
//		File::setPath(path);
//		//this->clear();
//		this->parseFile();
//	}
//}

void XMLFile::parseFile(void){
	Tokenizer tokenizer;
	tokenizer.addInclusionTokens("<>");
	int i=0;
	std::cout << File::getPath() << std::endl;
	for (File::const_iterator iter=File::cbegin(); iter!=File::cend(); i++,iter++){
		std::cout << i << ": " << *iter << std::endl;

		std::string line=*iter;
		HelperFunc::trimWhitespace(line);
		tokenizer.clear();
		tokenizer.parse(line);

		for (int i=0; i<tokenizer.size(); i++){
			std::cout << tokenizer[i] << std::endl;
		} 

		////if line starts with '<', its a tag
		////	if first token char is '/', its a closing tag
		////	else if last token char is '/', its a self closing tag
		////	else its a tag
		////else its data for the previous tag
		//if (!line.empty() && line[0]=='<'){
		//	if (!tokenizer.empty() && tokenizer[0][0]=='/'){
		//		//move up in tree
		//	} else if (!tokenizer.empty() && tokenizer[0][tokenizer[0].size()-1]=='/'){
		//		//add tag
		//		//move up in tree
		//	} else {
		//		//add tag
		//	}
		//} else {
		//	//set data at cur node in tree
		//}
	}
}
