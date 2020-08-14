#include <utility>
#include <sstream>
#include <algorithm>
#include "src/Tokenizer.hpp"

Tokenizer::Tokenizer(void){
	//
}

Tokenizer::Tokenizer(const Tokenizer &other):
	VectorPassThrough(other.ptVec),
	error(other.error),
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
	VectorPassThrough::ptVec=other.ptVec;
	this->inclusionTokens=other.inclusionTokens;
	this->exclusionTokens=other.exclusionTokens;
	this->splitTokens=other.splitTokens;
	return *this;
}

Tokenizer& Tokenizer::operator=(const Tokenizer &&other){
	if (this!=&other){
		this->clear();
		VectorPassThrough::ptVec=other.ptVec;
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

void Tokenizer::parse(const std::string &raw, const bool keepTokens){
	this->clear();
	Tokenizer::ParseData pd={ .keepTokens=keepTokens };
	for (; pd.curIndex<raw.size(); pd.curIndex++){
		if (pd.exclusionStack.empty() && pd.inclusionStack.empty() && 
			this->splitTokens.find(raw[pd.curIndex])!=std::string::npos){
			this->addSegmentAndUpdateIndexes(raw,pd);
		} else {
			if (pd.exclusionStack.empty()){
				this->checkForInclusionToken(raw,pd);
			}
			if (pd.inclusionStack.empty()){
				this->checkForExclusionToken(raw,pd);
			}
		}
	}
	if (!pd.inclusionStack.empty() || !pd.exclusionStack.empty()){
		this->error|=Tokenizer::unballancedTokens;
	}
	if (this->error==Tokenizer::parseSuccess){
		pd.curIndex=raw.size();
		this->addSegmentAndUpdateIndexes(raw,pd);
	}
}

bool Tokenizer::good(void) const {
	return (this->error==Tokenizer::parseSuccess);
}

int Tokenizer::rdstate(void) const {
	return this->error;
}

void Tokenizer::clear(void){
	VectorPassThrough::clear();
	this->error=Tokenizer::parseSuccess;
}

//Private Methods===============================================================
void Tokenizer::addTokenPairs(std::vector<std::string> &place, const std::string &raw){
	for (unsigned int i=0; i<raw.size(); i+=2){
		std::string str=raw.substr(i,2);
		if (std::find(place.begin(),place.end(),str)==place.end()){
			place.push_back(str);
		}
	}
}

void Tokenizer::checkForInclusionToken(const std::string &raw, Tokenizer::ParseData &pd){
	std::string nextTag=this->getPairedToken(this->inclusionTokens,raw[pd.curIndex]);
	if (!pd.inclusionStack.empty() && pd.inclusionStack.back().find(raw[pd.curIndex])!=std::string::npos){
		pd.inclusionStack.pop_back();
		if (pd.inclusionStack.empty()){
			this->addSegmentAndUpdateIndexes(raw,pd);
		}
	} else if (nextTag.size()>0){
		if (pd.inclusionStack.empty()){
			this->addSegmentAndUpdateIndexes(raw,pd);
		}
		pd.inclusionStack.push_back(nextTag);
	}
}

void Tokenizer::checkForExclusionToken(const std::string &raw, Tokenizer::ParseData &pd){
	std::string nextTag=this->getPairedToken(this->exclusionTokens,raw[pd.curIndex]);
	if (!pd.exclusionStack.empty() && pd.exclusionStack.back().find(raw[pd.curIndex])!=std::string::npos){
		pd.exclusionStack.pop_back();
		this->addToken(raw,pd);
		this->updateIndexes(pd);
	} else if (nextTag.size()>0 && pd.exclusionStack.empty()){
		pd.exclusionStack.push_back(nextTag);
		this->addSegmentAndUpdateIndexes(raw,pd);
	}
}

std::string Tokenizer::getPairedToken(const std::vector<std::string> &src, const char openToken) const {
	std::stringstream rv;
	for (unsigned int i=0; i<src.size(); i++){
		if (src[i][0]==openToken){
			rv << src[i][1];
		}
	}
	return rv.str();
}

void Tokenizer::addSegmentAndUpdateIndexes(const std::string &raw, Tokenizer::ParseData &pd){
	this->addToken(raw,pd);
	this->addSegment(raw,pd.prevIndex,pd.curIndex);
	this->updateIndexes(pd);
}

void Tokenizer::addSegment(const std::string &raw, const int start, const int end){
	if (end-start>1){
		VectorPassThrough::ptVec.push_back(raw.substr(start,end-start));
	}
}

void Tokenizer::addToken(const std::string &raw, Tokenizer::ParseData &pd){
	int index=pd.prevIndex-1;
	if (pd.keepTokens && index>=0){
		std::string temp(1,raw[index]);
		VectorPassThrough::ptVec.push_back(temp);
	}
}

void Tokenizer::updateIndexes(Tokenizer::ParseData &pd){
	pd.prevIndex=pd.curIndex+1;
}
