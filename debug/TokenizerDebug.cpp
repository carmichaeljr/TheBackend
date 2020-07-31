#include "debug/TokenizerDebug.hpp"
#include "src/Print.hpp"

TokenizerDebug::TokenizerDebug(void): Debug("Tokenizer"),
	splitTokens(" .|"),
	inclusionTokens("[]\"\""),
	exclusionTokens("()<>"),
	parseStrNames({"one","two","three","four.four","five","six","seven","eight)eight"}){
	//"one.two| three[four.four]five.\"six\".seven<nothing(nothing>eight)eight"
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
		this->debugParse() &&
		this->debugParseKeepTokens() &&
		this->debugVectorInterface() &&
		this->debugCopyConstructor());
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
	rv&=test.good();
	rv&=(test.rdstate()==Tokenizer::parseSuccess);
	for (unsigned int i=0; i<test.size(); i++){
		rv&=(test[i]==this->parseStrNames[i]);
	}

	test.parse("[Nothing\"Nothing]Nothing\"]");
	rv&=test.good();
	rv&=(test.rdstate()==Tokenizer::parseSuccess);
	rv&=(test[0]=="Nothing\"Nothing]Nothing\"");
	Print::objectMethodDebug(std::cout,"Parse",rv);
	return rv;
}

bool TokenizerDebug::debugParseKeepTokens(void){
	bool rv=true;
	Tokenizer test;
	this->initilizeTokenizer(test);
	test.parse(this->parseStr.str(),true);
	rv&=test.good();
	for (unsigned int i=0; i<test.size(); i++){
		std::cout << i << ": " << test[i] << std::endl;
	}

	Print::objectMethodDebug(std::cout,"ParseKeepTokens",rv);
	return rv;
}

bool TokenizerDebug::debugVectorInterface(void){
	bool rv=true;
	Tokenizer test;
	this->initilizeTokenizer(test);
	test.parse(this->parseStr.str());
	rv&=(test.at(0)==this->parseStrNames[0]);
	rv&=(test[1]==this->parseStrNames[1]);
	rv&=(test.front()==this->parseStrNames[0]);
	rv&=(test.back()==this->parseStrNames.back());
	rv&=(test.size()==this->parseStrNames.size());
	rv&=(!test.empty());
	int i=0;
	for (std::vector<std::string>::iterator iter=test.begin(); iter!=test.end(); iter++, i++){
		rv&=(*iter==this->parseStrNames[i]);
	}
	i=0;
	for (std::vector<std::string>::const_iterator iter=test.begin(); iter!=test.end(); iter++, i++){
		rv&=(*iter==this->parseStrNames[i]);
	}
	test.clear();
	rv&=(test.size()==0);
	Print::objectMethodDebug(std::cout,"VectorInterface",rv);
	return rv;
}

bool TokenizerDebug::debugCopyConstructor(void){
	bool rv=true;
	Tokenizer test;
	this->initilizeTokenizer(test);
	test.parse(this->parseStr.str());
	Tokenizer test2=test;
	for (unsigned int i=0; i<test.size(); i++){
		rv&=(test2[i]==this->parseStrNames[i]);
	}
	Print::objectMethodDebug(std::cout,"CopyConstructor",rv);
	return rv;
}

void TokenizerDebug::initilizeTokenizer(Tokenizer &test){
	test.addSplitTokens(this->splitTokens);
	test.addInclusionTokens(this->inclusionTokens);
	test.addExclusionTokens(this->exclusionTokens);
}
