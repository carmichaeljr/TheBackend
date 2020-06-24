#include "XMLTag.hpp"
#include "HelperFunctions.hpp"

#include <iostream>	//TODO - remove later

XMLTag::XMLTag(void){
	//
}

XMLTag::XMLTag(const std::string &raw){
	//
}

XMLTag::XMLTag(const std::string &nName, const std::string &nData): 
	name(nName),
	data(nData) {
	//
}

void XMLTag::setName(const std::string &nName){
	this->name=nName;
}

std::string XMLTag::getName(void) const {
	return this->name;
}

void XMLTag::setData(const std::string &nData){
	this->data=nData;
}

std::string XMLTag::getData(void) const {
	return this->data;
}

//Idea:: token pairs
void XMLTag::parse(const std::string &raw){
	char tagType='s';
	unsigned int prevIndex=0;
	std::vector<std::string> segments;
	for (unsigned int i=0; i<raw.size(); i++){
		if (XMLTag::splitTokens.find(raw[i])!=std::string::npos && tagType=='s'){
			segments.push_back(raw.substr(prevIndex+1,i));
			prevIndex=i;
		} else if (this->isOpeningInclusionTag(raw[i]) && tagType=='s'){
			prevIndex=i;
			tagType='i';
		} else if (this->isOpeningExclusionTag(raw[i]) && tagType=='s'){
			tagType='e';
		} else if (this->isClosingInclusionTag(raw[i]) && tagType=='i'){
			segment.push_back(raw.substr(prevIndex+1,i));
			prevIndex=i;
			tagType='s';
		} else if (this->isClosingExclusionTag(raw[i]) && tagType=='e'){
			prevIndex=i;
			tagType='s';
		}
	}
	//std::vector<int> tokenIndexes;
	//this->populateTokenList(tokenIndexes,raw);
	//for (int i=0; i<tokenIndexes.size(); i++){
	//	std::cout << tokenIndexes[i] << ", ";
	//}
	//std::cout << std::endl;

	//std::vector<std::string> strs;
	//this->populateSubstings(strs,tokenIndexes);
}

//void XMLTag::populateTokenList(std::vector<int> &tokenIndexes, const std::string &raw){
//	bool insideQuotes=false;
//	const std::string tokens=" \"'<>/=";
//	for (unsigned int i=0; i<raw.size(); i++){
//		if (tokens.find(raw[i])!=std::string::npos){
//			if (!insideQuotes){
//				tokenIndexes.push_back(i);
//				insideQuotes=(raw[i]=='"' || raw[i]=='\'');
//			} else if (raw[tokenIndexes.size()-1]==raw[i]){
//				tokenIndexes.push_back(i);
//				insideQuotes=false;
//			}
//		}
//	}
//}
//
//void XMLTag::populateSubstings(std::vector<std::string> &strs, std::vector<int> &tokenIndexes){
//
//}
