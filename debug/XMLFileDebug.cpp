#include "debug/XMLFileDebug.hpp"
#include "src/Print.hpp"
#include "src/XMLFile.hpp"

XMLFileDebug::XMLFileDebug(void): Debug("XMLFile"),
	debugFile("debug/XMLFileDebug.txt") {
	//
}

bool XMLFileDebug::debugClassMethods(void){
	return true;
}

bool XMLFileDebug::debugObjectMethods(void){
	return (this->debugConstructor());
}

bool XMLFileDebug::debugConstructor(void){
	bool rv=true;
	XMLFile test(this->debugFile);

	Print::objectMethodDebug(std::cout,"Constructor",rv);
	return rv;
}
