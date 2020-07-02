#include <utility>
#include <algorithm>
#include "src/Tokenizer.hpp"

Tokenizer::Tokenizer(void){
	//
}

Tokenizer::Tokenizer(const Tokenizer &other):
	error(other.error),
	segments(other.segments),
	inclusionTokens(other.inclusionTokens),
	exclusionTokens(other.exclusionTokens),
	splitTokens(other.splitTokens) {
	//
}

Tokenizer::Tokenizer(const Tokenizer &&other){
	*this=std::move(other);
}

Tokenizer& Tokenizer::operator=(const Tokenizer &other){
	this->clear();
	this->segments=other.segments;
	this->inclusionTokens=other.inclusionTokens;
	this->exclusionTokens=other.exclusionTokens;
	this->splitTokens=other.splitTokens;
	return *this;
}

Tokenizer& Tokenizer::operator=(const Tokenizer &&other){
	if (this!=&other){
		this->clear();
		this->segments=other.segments;
		this->inclusionTokens=other.inclusionTokens;
		this->exclusionTokens=other.exclusionTokens;
		this->splitTokens=other.splitTokens;
	}
	return *this;
}

void Tokenizer::addSplitTokens(const std::string &tokens){
	for (unsigned int i=0; i<tokens.size(); i++){
		if (this->splitTokens.find_first_of(tokens[i])==std::string::npos){
			this->splitTokens+=tokens;
		}
	}
}

const std::string& Tokenizer::getSplitTokens(void) const {
	return this->splitTokens;
}

void Tokenizer::addInclusionTokens(const std::string &tokenPairs){
	this->addTokenPairs(this->inclusionTokens,tokenPairs);
}

const std::vector<std::string>& Tokenizer::getInclusionTokens(void) const {
	return this->inclusionTokens;
}

void Tokenizer::addExclusionTokens(const std::string &tokenPairs){
	this->addTokenPairs(this->exclusionTokens,tokenPairs);
}

const std::vector<std::string>& Tokenizer::getExclusionTokens(void) const {
	return this->exclusionTokens;
}

void Tokenizer::parse(const std::string &raw){
	char nextTag=0;
	unsigned int prevIndex=0;
	for (unsigned int i=0; i<raw.size(); ((i!=std::string::npos)? i++: i)){
		if (this->splitTokens.find(raw[i])!=std::string::npos){
			this->addSegment(raw,prevIndex,i);
			prevIndex=i+1;
		} else if ((nextTag=this->getPairedToken(this->inclusionTokens,raw[i]))!=0){
			this->addSegment(raw,prevIndex,i);
			prevIndex=i+1;
			i=raw.find_first_of(nextTag,i+1);
			if (i!=std::string::npos){
				this->addSegment(raw,prevIndex,i);
				prevIndex=i+1;
			} else {
				this->error|=Tokenizer::unballancedTokens;
			}
		} else if ((nextTag=this->getPairedToken(this->exclusionTokens,raw[i]))!=0){
			this->addSegment(raw,prevIndex,i);
			i=raw.find_first_of(nextTag,i+1);
			prevIndex=i+1;
			if (i==std::string::npos){
				this->error|=Tokenizer::unballancedTokens;
			}
		}
	}
	if (this->error==Tokenizer::parseSuccess){
		this->addSegment(raw,prevIndex,raw.size());
	}

	//for (int i=0; i<segments.size(); i++){
	//	std::cout << "Segment: " << i << ": [" << segments[i]  << "]" << std::endl;
	//}
}

bool Tokenizer::good(void) const {
	return (this->error==Tokenizer::parseSuccess);
}

int Tokenizer::rdstate(void) const {
	return this->error;
}

std::string& Tokenizer::at(const int index){
	return this->segments.at(index);
}

const std::string& Tokenizer::at(const int index) const {
	return this->segments.at(index);
}

std::string& Tokenizer::operator[](const int index){
	return this->segments[index];
}

const std::string& Tokenizer::operator[](const int index) const {
	return this->segments[index];
}

std::string& Tokenizer::front(void){
	return this->segments.front();
}

const std::string& Tokenizer::front(void) const {
	return this->segments.front();
}

std::string& Tokenizer::back(void){
	return this->segments.back();
}

const std::string& Tokenizer::back(void) const {
	return this->segments.back();
}

std::vector<std::string>::iterator Tokenizer::begin(void){
	return this->segments.begin();
}

const std::vector<std::string>::const_iterator Tokenizer::begin(void) const {
	return this->segments.begin();
}

std::vector<std::string>::iterator Tokenizer::end(void){
	return this->segments.end();
}

const std::vector<std::string>::const_iterator Tokenizer::end(void) const {
	return this->segments.end();
}

std::vector<std::string>::const_iterator Tokenizer::cbegin(void){
	return this->segments.cbegin();
}

std::vector<std::string>::const_iterator Tokenizer::cend(void){
	return this->segments.cend();
}

bool Tokenizer::empty(void) const {
	return this->segments.empty();
}

unsigned int Tokenizer::size(void) const {
	return this->segments.size();
}

void Tokenizer::clear(void){
	this->segments.clear();
	this->error=Tokenizer::parseSuccess;
}

void Tokenizer::addTokenPairs(std::vector<std::string> &place, const std::string &raw){
	for (unsigned int i=0; i<raw.size(); i+=2){
		std::string str=raw.substr(i,2);
		if (std::find(place.begin(),place.end(),str)==place.end()){
			place.push_back(str);
		}
	}
}

char Tokenizer::getPairedToken(const std::vector<std::string> &src, const char openToken) const {
	char rv=0;
	for (unsigned int i=0; i<src.size() && rv==0; i++){
		if (src[i][0]==openToken){
			rv=src[i][1];
		}
	}
	return rv;
}

void Tokenizer::addSegment(const std::string &raw, const int start, const int end){
	if (end-start>1){
		this->segments.push_back(raw.substr(start,end-start));
	}
}
