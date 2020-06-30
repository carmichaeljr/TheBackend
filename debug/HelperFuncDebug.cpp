#include <string>
#include "debug/HelperFuncDebug.hpp"
#include "src/Print.hpp"
#include "src/HelperFunctions.hpp"

HelperFuncDebug::HelperFuncDebug(void): Debug("HelperFunc") {
	//
}

bool HelperFuncDebug::debugClassMethods(void){
	return (this->debugTrimWhitespaceAtEnd() &&
		this->debugTrimWhitespaceAtStart());
}

bool HelperFuncDebug::debugTrimWhitespaceAtEnd(void){
	std::string str1="testing   .    ";
	std::string correct="testing   .";
	HelperFunc::trimWhitespaceAtEnd(str1);
	bool rv=(str1==correct);

	std::string str2="testing   .";
	HelperFunc::trimWhitespaceAtEnd(str2);
	rv&=(str2==correct);

	std::string str3="      ";
	HelperFunc::trimWhitespaceAtEnd(str3);
	rv&=(str3.size()==0);

	std::string str4="testing   .\0";
	HelperFunc::trimWhitespaceAtEnd(str2);
	rv&=(str4==correct);
	rv&=(str4[str4.size()-1]!='\0');

	std::string str5;
	HelperFunc::trimWhitespaceAtEnd(str5);
	rv&=(str5.size()==0);

	Print::objectMethodDebug(std::cout,"TrimWhitespaceAtEnd",rv);
	return rv;
}

bool HelperFuncDebug::debugTrimWhitespaceAtStart(void){
	std::string str1="   .   testing";
	std::string correct=".   testing";
	HelperFunc::trimWhitespaceAtStart(str1);
	bool rv=(str1==correct);

	std::string str2=".   testing";
	HelperFunc::trimWhitespaceAtStart(str2);
	rv&=(str2==correct);

	std::string str3="       ";
	HelperFunc::trimWhitespaceAtStart(str3);
	rv&=(str3.size()==0);

	std::string str5;
	HelperFunc::trimWhitespaceAtStart(str5);
	rv&=(str5.size()==0);

	Print::objectMethodDebug(std::cout,"TrimWhitespaceAtStart",rv);
	return rv;
}

bool HelperFuncDebug::debugTrimWhitespace(void){
	std::string str1="   .  testing   .   ";
	std::string correct=".   testing   .";
	HelperFunc::trimWhitespace(str1);
	bool rv=(str1==correct);

	std::string str2="   .   testing";
	HelperFunc::trimWhitespace(str2);
	rv&=(str2==correct);

	std::string str3="        ";
	HelperFunc::trimWhitespace(str3);
	rv&=(str3.size()==0);

	std::string str4;
	HelperFunc::trimWhitespace(str4);
	rv&=(str4.size()==0);

	Print::objectMethodDebug(std::cout,"TrimWhitespace",rv);
	return rv;
}

bool HelperFuncDebug::debugObjectMethods(void){
	return true;
}
