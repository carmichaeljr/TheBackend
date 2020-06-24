#include "XMLTag.hpp"
#include "HelperFunctions.hpp"

#include <iostream>	//TODO - remove later

const std::vector<std::string> inclusionTags={ "\"\"","''" };
const std::vector<std::string> exclusionTags={ "/>" };
const std::string splitTokens=" <>=";

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

void XMLTag::parse(const std::string &raw){
	unsigned int prevIndex=0;
	std::vector<std::string> segments;
	for (unsigned int i=0; i<raw.size(); i++){
		if (XMLTag::splitTokens.find(raw[i])!=std::string::npos){
			segments.push_back(raw.substr(prevIndex,i));
			prevIndex=i+1;
		} else if ((char nextTag=this->getPairedInclusionTag(raw[i]))!=0){
			i=raw.find_first_of(nextTag,i);
			segment.push_back(raw.substr(prevIndex,i));
			prevIndex=i+1;
		} else if ((char nextTag=this->getPairedExclusionTag(raw[i]))!=0){
			i=raw.find_first_of(nextTag,i);
			prevIndex=i+1;
		}

		//if (XMLTag::splitTokens.find(raw[i])!=std::string::npos && tagType=='s'){
		//	segments.push_back(raw.substr(prevIndex,i));
		//	prevIndex=i+1;
		//} else if ((nextTag=this->isOpeningInclusionTag(raw[i])) && tagType=='s'){
		//	prevIndex=i+1;
		//	tagType='i';
		//} else if (this->isOpeningExclusionTag(raw[i]) && tagType=='s'){
		//	tagType='e';
		//} else if (this->isClosingInclusionTag(raw[i]) && tagType=='i'){
		//	segment.push_back(raw.substr(prevIndex+1,i));
		//	prevIndex=i+1;
		//	tagType='s';
		//} else if (this->isClosingExclusionTag(raw[i]) && tagType=='e'){
		//	prevIndex=i+1;
		//	tagType='s';
		//}
	}
}

char XMLTag::getPairedInclusionTag(const char openTag) const {
	char rv=0;
	for (unsigned int i=0; i<XMLTag::inclusionTags.size() && rv==0; i++){
		if (XMLTag::inclusionTags[i][0]==openTag){
			rv=XMLTag::inclusionTags[i][1];
		}
	}
	return rv;
}

char XMLTag::getPairedExclusionTag(const char openTag) const {
	char rv=0;
	for (unsigned int i=0; i<XMLTag::inclusionTags.size() && rv==0; i++){
		if (XMLTag::exclusionTags[i][0]==openTag){
			rv=XMLTag::exclusionTags[i][1];
		}
	}
	return rv;
}
