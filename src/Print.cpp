#include <iomanip>
#include <sstream>
#include <limits>
#include "src/Print.hpp"

int Print::indentLevel=0;
int Print::spacesPerIndent=4;

void Print::init(void){
	Print::indentLevel=0;
	Print::spacesPerIndent=4;
}

void Print::incrementIndentLevel(const int increment){
	(Print::indentLevel+increment>=0)? Print::indentLevel+=increment: Print::indentLevel=0;
}

void Print::setSpacesPerIndent(const int numSpaces){
	if (numSpaces>=0){
		Print::spacesPerIndent=numSpaces;
	}
}

void Print::print(std::ostream &os, const std::string &str, const bool addEndl){
	for (int i=0; i<Print::indentLevel*Print::spacesPerIndent; i++){
		os << " ";
	}
	os << str;
	if (addEndl){
		os << std::endl;
	}
}

void Print::printWithoutIndent(std::ostream &os, const std::string &str, const bool addEndl){
	os << str;
	if (addEndl){
		os << std::endl;
	}
}

void Print::error(std::ostream &os, const std::string &errMsg){
	os << "!Error!: " << errMsg << std::endl;
}

void Print::objectDebug(std::ostream &os, const std::string &className, const bool success){
	std::stringstream str;
	str << "[" << std::left << std::setw(5) << ((success)? "OK": "Error") << std::setw(0);
	str << "]: " << className << " class";
	Print::print(os,str.str());
}

void Print::objectMethodDebug(std::ostream &os, const std::string &methodName, const bool success){
	if (!success){
		Print::error(os,methodName);
	}
}

bool Print::yesOrNoPrompt(std::ostream &os, std::istream &is, const std::string &question){
	std::stringstream str;
	str << question << "? (y/n) ";
	char input=' ';
	while (tolower(input)!='y' && tolower(input)!='n'){
		Print::print(os,str.str(),false);
		is >> input;
		is.clear();
		is.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
	}
	return (tolower(input)=='y');
}
