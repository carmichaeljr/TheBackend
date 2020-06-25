//#include <utility>
#include "XMLTag.hpp"
#include "HelperFunctions.hpp"

#include <iostream>	//TODO - remove later

const std::vector<std::string> XMLTag::inclusionTags={ "\"\"","''" };
const std::vector<std::string> XMLTag::exclusionTags={ "/>" };
const std::string XMLTag::splitTags=" <>=";

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

std::string& XMLTag::getName(void){
	return this->name;
}

void XMLTag::setData(const std::string &nData){
	this->data=nData;
}

std::string& XMLTag::getData(void){
	return this->data;
}

void XMLTag::emplace(const std::string &key, const std::string &val){
	this->attributes.emplace(key,val);
}

std::string& XMLTag::operator[](const std::string &attrName){
	return this->attributes[attrName];
}

std::map<std::string,std::string>::iterator XMLTag::begin(void){
	return this->attributes.begin();
}

std::map<std::string,std::string>::iterator XMLTag::end(void){
	return this->attributes.end();
}

std::map<std::string,std::string>::iterator XMLTag::find(const std::string &name){
	return this->attributes.find(name);
}

int XMLTag::count(const std::string &key) const {
	return this->attributes.count(key);
}

void XMLTag::swap(XMLTag &other){
	//std::swap(other.getName(),this->name);
	//std::swap(other.getData(),this->data);
	std::string otherName=other.getName();
	std::string otherData=other.getData();
	other.setName(this->name);
	other.setData(this->data);
	this->setName(otherName);
	this->setData(otherData);
	this->attributes.swap(other);
}

//void XMLTag::erase(const std::string &attr){
//	this->attributes.erase(attr);	
//}

int XMLTag::parse(const std::string &raw){
	std::vector<std::string> segments;
	int rv=this->populateSegments(segments,raw);
	//std::cout << "rv populate segments: " << rv << std::endl;
	rv|=((rv!=XMLTag::invalidTag)? this->setDataFromSegments(segments): rv);
	//std::cout << "rv set data: " << rv << std::endl;
	return rv;
}

int XMLTag::populateSegments(std::vector<std::string> &segments, const std::string &raw) const {
	int rv=XMLTag::parseSuccess;
	char nextTag=0;
	unsigned int prevIndex=0;
	for (unsigned int i=0; i<raw.size(); ((i!=std::string::npos)? i++: i)){
		if (XMLTag::splitTags.find(raw[i])!=std::string::npos){
			this->addSegment(segments,raw,prevIndex,i);
			prevIndex=i+1;
		} else if ((nextTag=this->getPairedInclusionTag(raw[i]))!=0){
			this->addSegment(segments,raw,prevIndex,i);
			prevIndex=i+1;
			i=raw.find_first_of(nextTag,i+1);
			this->addSegment(segments,raw,prevIndex,i);
			prevIndex=i+1;
			rv|=((i==std::string::npos)? XMLTag::unballancedTag: rv);
		} else if ((nextTag=this->getPairedExclusionTag(raw[i]))!=0){
			this->addSegment(segments,raw,prevIndex,i);
			i=raw.find_first_of(nextTag,i+1);
			prevIndex=i+1;
			rv|=((i==std::string::npos)? XMLTag::unballancedTag: rv);
		}
	}
	rv|=((segments.size()==0)? XMLTag::invalidTag: rv);

	for (int i=0; i<segments.size(); i++){
		std::cout << "Segment: " << i << ": [" << segments[i]  << "]" << std::endl;
	}
	return rv;
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
	for (unsigned int i=0; i<XMLTag::exclusionTags.size() && rv==0; i++){
		if (XMLTag::exclusionTags[i][0]==openTag){
			rv=XMLTag::exclusionTags[i][1];
		}
	}
	return rv;
}

//start inclusive, end exclusive
void XMLTag::addSegment(std::vector<std::string> &segments, const std::string &raw, const int start, const int end) const {
	if (end-start>1){
		segments.push_back(raw.substr(start,end-start));
	}
}

int XMLTag::setDataFromSegments(const std::vector<std::string> &segments){
	if (segments.size()>0){
		this->name=segments[0];
	}
	for (unsigned int i=2; i<segments.size(); i+=2){
		this->attributes[segments[i-1]]=segments[i];
	}
	return ((segments.size()>1 && segments.size()%2==0)? XMLTag::unballancedAttrs: XMLTag::parseSuccess);
}
