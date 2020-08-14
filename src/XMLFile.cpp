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

//void XMLFile::clear(void){
//	this->data.clear();
//	File::clear();
//	std::cout << "Clearing file?????" << std::endl;
//}

void XMLFile::parseFile(void){
	Tokenizer tokenizer;
	tokenizer.addInclusionTokens("\"\"");
	tokenizer.addSplitTokens("<>/");
	Tree<XMLTag>::iterator tagIter=TreePassThrough::end(); //Will need to place at start upon adding first node
	for (File::const_iterator iter=File::cbegin(); iter!=File::cend(); iter++){
		std::string line=*iter;
		HelperFunc::trimWhitespace(line);
		tokenizer.clear();
		tokenizer.parse(line,true);
		this->parseLine(tokenizer,tagIter);
	}

	std::cout << TreePassThrough::size() << std::endl;
	for (Tree<XMLTag>::iterator iter=TreePassThrough::begin(true); iter!=TreePassThrough::end(); iter++){
		std::cout << iter->name << std::endl;
	}
}

void XMLFile::parseLine(const Tokenizer &tokenizer, Tree<XMLTag>::iterator &iter){
	for (unsigned int i=2; i<tokenizer.size(); i++){
		if (tokenizer[i-2]=="<" && tokenizer[i]==">"){
			//open node, add node
			this->addNode(iter,tokenizer[i-1],false);
		} else if (tokenizer[i-2]==">" && tokenizer[i]=="<"){
			//data
			this->addData(iter,tokenizer[i-1]);
		} else if (i>2 && tokenizer[i-3]=="<" && tokenizer[i-1]=="/" && tokenizer[i]==">"){
			//self closing node
			this->addNode(iter,tokenizer[i-2],true);
		} else if (i>2 && tokenizer[i-3]=="<" && tokenizer[i-2]=="/" && tokenizer[i]==">"){
			//closing node, move up
			iter++;
		} 
	}
}

void XMLFile::addNode(Tree<XMLTag>::iterator &iter, const std::string &rawData, const bool selfClosing){
	if (TreePassThrough::size()==0){
		this->addFirstNode(iter,rawData);
	} else {
		this->addNthNode(iter,rawData);
		if (selfClosing){
			iter++;
		}
	}
}

void XMLFile::addFirstNode(Tree<XMLTag>::iterator &iter, const std::string &rawData){
	iter=TreePassThrough::emplace(XMLTag(rawData));
	iter.revisit=true;
}

void XMLFile::addNthNode(Tree<XMLTag>::iterator &iter, const std::string &rawData){
	iter=TreePassThrough::emplaceBelow(iter,XMLTag(rawData));
	iter.revisit=true;
}

void XMLFile::addData(const Tree<XMLTag>::iterator &iter, const std::string &rawData){
	iter->data=rawData;
}
