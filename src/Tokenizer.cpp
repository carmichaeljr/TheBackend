#include <algorithm>
#include "src/Tokenizer.hpp"

#include <iostream>	//TODO - remove

Tokenizer::Tokenizer(void){
	//
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
			this->addSegment(raw,prevIndex,i);
			prevIndex=i+1;
			this->error|=((i==std::string::npos)? Tokenizer::unballancedTokens: this->error);
		} else if ((nextTag=this->getPairedToken(this->exclusionTokens,raw[i]))!=0){
			this->addSegment(raw,prevIndex,i);
			i=raw.find_first_of(nextTag,i+1);
			prevIndex=i+1;
			this->error|=((i==std::string::npos)? Tokenizer::unballancedTokens: this->error);
		}
	}
	this->addSegment(raw,prevIndex,raw.size());

	for (int i=0; i<segments.size(); i++){
		std::cout << "Segment: " << i << ": [" << segments[i]  << "]" << std::endl;
	}
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
