#include <utility>
#include <sstream>
#include "src/XMLTag.hpp"
#include "src/HelperFunctions.hpp"

const std::string XMLTag::inclusionTokens="\"\"''";
const std::string XMLTag::exclusionTokens="/>";
const std::string XMLTag::splitTokens=" <>=";

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

XMLTag::XMLTag(const XMLTag &other):
	name(other.name),
	data(other.data),
	attributes(other.attributes) {
	//
}

XMLTag::XMLTag(const XMLTag &&other){
	*this=std::move(other);
}

XMLTag& XMLTag::operator=(const XMLTag &other){
	this->clear();
	this->name=other.name;
	this->data=other.data;
	this->attributes=other.attributes;
	return *this;
}

XMLTag& XMLTag::operator=(const XMLTag &&other){
	if (this!=&other){
		this->clear();
		this->name=other.name;
		this->data=other.data;
		this->attributes=other.attributes;
	}
	return *this;
}

int XMLTag::parse(const std::string &raw){
	Tokenizer tokenizer;
	tokenizer.addSplitTokens(XMLTag::splitTokens);
	tokenizer.addInclusionTokens(XMLTag::inclusionTokens);
	tokenizer.addExclusionTokens(XMLTag::exclusionTokens);
	tokenizer.parse(raw);
	int rv=this->setDataFromTokens(tokenizer);
	rv|=tokenizer.rdstate();
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

const std::map<std::string,std::string>::const_iterator XMLTag::begin(void) const {
	return this->attributes.begin();
}

std::map<std::string,std::string>::iterator XMLTag::end(void){
	return this->attributes.end();
}

const std::map<std::string,std::string>::const_iterator XMLTag::end(void) const {
	return this->attributes.end();
}

std::map<std::string,std::string>::const_iterator XMLTag::cbegin(void){
	return this->attributes.cbegin();
}

std::map<std::string,std::string>::const_iterator XMLTag::cend(void){
	return this->attributes.cend();
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

int XMLTag::setDataFromTokens(const Tokenizer &tokens){
	if (tokens.size()>0){
		this->name=tokens[0];
	}
	for (unsigned int i=2; i<tokens.size(); i+=2){
		this->attributes[tokens[i-1]]=tokens[i];
	}
	return ((tokens.size()>1 && tokens.size()%2==0)? XMLTag::unballancedAttrs: XMLTag::parseSuccess);
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
	bool rv=(data.find_first_of(XMLTag::splitTokens)!=std::string::npos);
	for (unsigned int i=0; i<XMLTag::inclusionTokens.size() && !rv; i+=2){
		rv&=(data.find_first_of(XMLTag::inclusionTokens[i])!=std::string::npos);
	}
	for (unsigned int i=0; i<XMLTag::exclusionTokens.size() && !rv; i+=2){
		rv&=(data.find_first_of(XMLTag::exclusionTokens[i])!=std::string::npos);
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
