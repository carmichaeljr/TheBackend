#include <utility>
#include <sstream>
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
	this->parse(raw);
}

XMLTag::XMLTag(const std::string &nName, const std::string &nData): 
	name(nName),
	data(nData) {
	//
}

//copy constructor
//move constructor

XMLTag& XMLTag::operator=(const XMLTag &other){
	this->clear();
	this->name=other.name;
	this->data=other.data;
	this->attributes=other.attributes;
	return *this;
}

//move assignment operator

void XMLTag::emplace(const std::string &key, const std::string &val){
	this->attributes.emplace(key,val);
}

std::string& XMLTag::operator[](const std::string &attrName){
	return this->attributes[attrName];
}

int XMLTag::size(void) const {
	return this->attributes.size();
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
	std::swap(other.name,this->name);
	std::swap(other.data,this->data);
	this->attributes.swap(other.attributes);
}

void XMLTag::erase(const std::string &attr){
	this->attributes.erase(attr);	
}

void XMLTag::clear(void){
	this->attributes.clear();
	this->data="";
	this->name="";
}

int XMLTag::parse(const std::string &raw){
	std::vector<std::string> segments;
	int rv=this->populateSegments(segments,raw);
	//std::cout << "rv populate segments: " << rv << std::endl;
	rv|=((rv!=XMLTag::invalidTag)? this->setDataFromSegments(segments): rv);
	//std::cout << "rv set data: " << rv << std::endl;
	return rv;
}

std::string XMLTag::getOpeningTag(bool selfClosing) const {
	std::string buf;
	std::stringstream rv;
	this->getParseableSegment(buf,this->name);
	rv << "<" << buf << " ";
	for (std::map<std::string,std::string>::const_iterator iter=this->attributes.cbegin();
		iter!=this->attributes.cend(); iter++){
		this->getParseableSegment(buf,iter->first);
		rv << iter->first << "=";
		this->getParseableSegment(buf,iter->second);
		rv << iter->second << " ";
	}
	rv.seekp(-1,rv.cur);
	rv << ((selfClosing)? "/": "") << ">";
	return rv.str();
}

std::string XMLTag::getClosingTag(void) const {
	std::string buf;
	std::stringstream rv;
	this->getParseableSegment(buf,this->name);
	rv << "<" << buf << "/>";
	return rv.str();
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

void XMLTag::getParseableSegment(std::string &buf, const std::string &data) const {
	buf.clear();
	std::stringstream str;
	if (this->containsTag(data)){
		str << "\"" << data << "\"";
	} else {
		str << data;
	}
	buf=str.str();
}

bool XMLTag::containsTag(const std::string &data) const {
	bool rv=(data.find_first_of(XMLTag::splitTags)!=std::string::npos);
	for (unsigned int i=0; i<XMLTag::inclusionTags.size() && !rv; i++){
		rv&=(data.find_first_of(XMLTag::inclusionTags[i])!=std::string::npos);
	}
	for (unsigned int i=0; i<XMLTag::exclusionTags.size() && !rv; i++){
		rv&=(data.find_first_of(XMLTag::exclusionTags[i])!=std::string::npos);
	}
	return rv;
}

bool operator==(const XMLTag &rhs, const XMLTag &lhs){
	return (rhs.name==lhs.name && rhs.data==lhs.data &&
		rhs.attributes==lhs.attributes);
}

bool operator!=(const XMLTag &rhs, const XMLTag &lhs){
	return !(rhs==lhs);
}
