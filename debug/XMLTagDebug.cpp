#include "XMLTagDebug.hpp"
#include "src/XMLTag.hpp"
#include "src/Print.hpp"

XMLTagDebug::XMLTagDebug(void): Debug("XMLTag") {
	//
}

bool XMLTagDebug::debugClassMethods(void){
	return true;
}

bool XMLTagDebug::debugObjectMethods(void){
	return (this->debugSetGetName() &&
		this->debugSetGetData() &&
		this->debugParseName());
}

bool XMLTagDebug::debugSetGetName(void){
	bool rv=true;
	XMLTag test;
	test.setName("Testing");
	rv&=(test.getName()=="Testing");
	Print::objectMethodDebug(std::cout,"Get/Set Name",rv);
	return rv;
}

bool XMLTagDebug::debugSetGetData(void){
	bool rv=true;
	XMLTag test;
	test.setData("Testing");
	rv&=(test.getData()=="Testing");
	Print::objectMethodDebug(std::cout,"Get/Set Data",rv);
	return rv;
}

bool XMLTagDebug::debugParseName(void){
	bool rv=true;
	XMLTag test;
	test.parse("<Name>");
	rv&=(test.getName()=="Name");

	//test.parse("<\"<>/' \">");
	//Print::objectMethodDebug(std::cout,"ParseName",rv);
	return rv;
}
