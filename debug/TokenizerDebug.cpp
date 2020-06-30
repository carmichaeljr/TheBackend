#include <vector>
#include "debug/TokenizerDebug.hpp"
#include "src/Print.hpp"

TokenizerDebug::TokenizerDebug(void): Debug("Tokenizer"),
	splitTokens(" .|"),
	inclusionTokens("[]\"\""),
	exclusionTokens("()<>"),
	parseStrNames({"one","two","three","four.four","five","six","seven","eight)eight"}){
	//"one.two|.three[four.four]five.\"six\".seven<nothing(nothing>eight)eight"
	this->parseStr << this->parseStrNames[0] << this->splitTokens[1];
	this->parseStr << this->parseStrNames[1] << this->splitTokens[2] << this->splitTokens[0];
	this->parseStr << this->parseStrNames[2] << this->inclusionTokens[0];
	this->parseStr << this->parseStrNames[3] << this->inclusionTokens[1];
	this->parseStr << this->parseStrNames[4] << this->splitTokens[1] << this->inclusionTokens[2];
	this->parseStr << this->parseStrNames[5] << this->inclusionTokens[3] << this->splitTokens[1];
	this->parseStr << this->parseStrNames[6] << this->exclusionTokens[2];
	this->parseStr << "nothing" << this->exclusionTokens[0];
	this->parseStr << "nothing" << this->exclusionTokens[3];
	this->parseStr << this->parseStrNames[7];
}

bool TokenizerDebug::debugClassMethods(void){
	return true;
}

bool TokenizerDebug::debugObjectMethods(void){
	return (this->debugAddSplitTokens() &&
		this->debugAddInclusionTokens() &&
		this->debugAddExclusionTokens() &&
		this->debugParse());
}

bool TokenizerDebug::debugAddSplitTokens(void){
	bool rv=true;
	Tokenizer test;
	this->initilizeTokenizer(test);
	const std::string str=test.getSplitTokens();
	rv&=(str.find_first_of(this->splitTokens[0])!=std::string::npos);
	rv&=(str.find_first_of(this->splitTokens[1])!=std::string::npos);
	rv&=(str.find_first_of(this->splitTokens[2])!=std::string::npos);
	rv&=(str.find_first_of('e')==std::string::npos);
	Print::objectMethodDebug(std::cout,"AddSplitToken",rv);
	return rv;
}

bool TokenizerDebug::debugAddInclusionTokens(void){
	bool rv=true;
	Tokenizer test;
	this->initilizeTokenizer(test);
	const std::vector<std::string> tokens=test.getInclusionTokens();
	rv&=(tokens.size()==(this->inclusionTokens.size()/2));
	rv&=(tokens[0]==this->inclusionTokens.substr(0,2));
	rv&=(tokens[1]==this->inclusionTokens.substr(2,2));
	Print::objectMethodDebug(std::cout,"AddInclusionTokens",rv);
	return rv;
}

bool TokenizerDebug::debugAddExclusionTokens(void){
	bool rv=true;
	Tokenizer test;
	this->initilizeTokenizer(test);
	const std::vector<std::string> tokens=test.getExclusionTokens();
	rv&=(tokens.size()==(this->exclusionTokens.size()/2));
	rv&=(tokens[0]==this->exclusionTokens.substr(0,2));
	rv&=(tokens[1]==this->exclusionTokens.substr(2,2));
	Print::objectMethodDebug(std::cout,"AddExclusionTokens",rv);
	return rv;
}

bool TokenizerDebug::debugParse(void){
	bool rv=true;
	Tokenizer test;
	this->initilizeTokenizer(test);
	test.parse(this->parseStr.str());
	Print::objectMethodDebug(std::cout,"Parse",rv);
	return rv;
}

void TokenizerDebug::initilizeTokenizer(Tokenizer &test){
	test.addSplitTokens(this->splitTokens);
	test.addInclusionTokens(this->inclusionTokens);
	test.addExclusionTokens(this->exclusionTokens);
}
