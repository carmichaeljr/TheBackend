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
	Tree<XMLTag>::iterator dataIter=this->data.end(); 
	//Will need to place at start upon adding first node
	int i=0;
	//std::cout << File::getPath() << std::endl;
	for (File::const_iterator iter=File::cbegin(); iter!=File::cend(); i++,iter++){
		std::cout << i << ": " << *iter << std::endl;

		std::string line=*iter;
		HelperFunc::trimWhitespace(line);
		tokenizer.clear();
		tokenizer.parse(line,true);

		//for (int i=0; i<tokenizer.size(); i++){
		//	std::cout << tokenizer[i] << std::endl;
		//} 
		this->parseLine(tokenizer,dataIter);
	}
}

void XMLFile::parseLine(const Tokenizer &tokenizer, Tree<XMLTag>::iterator &iter){
	for (unsigned int i=2; i<tokenizer.size(); i++){
		if (tokenizer[i-2]=="<" && tokenizer[i]==">"){
			//open node, add node

			std::cout << "Adding node: " << tokenizer[i-1] << std::endl;
			if (iter==this->data.end()){
				std::cout << "END???" << std::endl;
			}
			XMLTag temp(tokenizer[i-1]);
			if (this->data.size()==0){
				this->data.emplace(temp);
				iter=this->data.begin(true);
			} else {
				iter=this->data.emplaceBelow(iter,temp);
				iter.revisit=true;
			}

		} else if (tokenizer[i-2]==">" && tokenizer[i]=="<"){
			//data

			std::cout << "Adding data: " << tokenizer[i-1] << std::endl;
			iter->data=tokenizer[i-1];

		} else if (i>2 && tokenizer[i-3]=="<" && tokenizer[i-1]=="/" && tokenizer[i]==">"){
			//self closing node, add as child

			std::cout << "Adding self closing node: " << tokenizer[i-2] << std::endl;
			XMLTag temp(tokenizer[i-2]);
			if (this->data.size()==0){
				this->data.emplace(temp);
				iter=this->data.begin(true);
			} else {
				iter=this->data.emplaceBelow(iter,temp);
				iter.revisit=true;
				iter++;
			}


		} else if (i>2 && tokenizer[i-3]=="<" && tokenizer[i-2]=="/" && tokenizer[i]==">"){
			//closing node, move up
			std::cout << "Moving Up: " << tokenizer[i-1] << std::endl;

			iter++;
		} 
	}

	std::cout << this->data.size() << std::endl;
	for (Tree<XMLTag>::iterator iter=this->data.begin(true); iter!=this->data.end(); iter++){
		std::cout << iter->name << std::endl;
	}
}
