#include "src/HelperFunctions.hpp"

const std::string HelperFunc::whitespace=" \t\n\r";

void HelperFunc::removeTrailingNull(std::string &str){
	if (str.size()>0 && str[str.size()-1]=='\0'){
		str.erase(str.begin()+(str.size()-1));
	}
}

void HelperFunc::trimWhitespaceAtEnd(std::string &str){
	std::size_t startIndex=str.find_last_not_of(HelperFunc::whitespace);
	std::size_t endIndex=str.find_last_of(HelperFunc::whitespace);
	if (startIndex!=std::string::npos){
		str.erase(str.begin()+startIndex+1,str.end());
	} else if (endIndex==str.size()-1){	//startIndex==std::string::npos 
		str.clear();
	}
	HelperFunc::removeTrailingNull(str);
}

void HelperFunc::trimWhitespaceAtStart(std::string &str){
	std::size_t endIndex=str.find_first_not_of(HelperFunc::whitespace);
	std::size_t startIndex=str.find_first_of(HelperFunc::whitespace);
	if (endIndex!=std::string::npos){
		str.erase(str.begin(),str.begin()+endIndex);
	} else if (startIndex==0){
		str.clear();
	}
}

void HelperFunc::trimWhitespace(std::string &str){
	HelperFunc::trimWhitespaceAtEnd(str);
	HelperFunc::trimWhitespaceAtStart(str);
}
