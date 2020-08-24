#include "debug/XMLFileDebug.hpp"
#include "src/Print.hpp"
#include "src/XMLFile.hpp"

XMLFileDebug::XMLFileDebug(void): Debug("XMLFile"),
	debugFile("debug/XMLFileDebug.txt"),
	iterSeq({ "One","Two","Three","Two","Four","Five","Six","Five","One" }){
	//
}

bool XMLFileDebug::debugClassMethods(void){
	return true;
}

bool XMLFileDebug::debugObjectMethods(void){
	return (this->debugConstructor() &&
		this->debugSetSource());
}

bool XMLFileDebug::debugConstructor(void){
	bool rv=true;
	XMLFile test(this->debugFile);
	int i=0;
	for (XMLFile::iterator iter=test.begin(true); iter!=test.end(); iter++, i++){
		rv&=(iter->name==this->iterSeq[i]);
	}

	Print::objectMethodDebug(std::cout,"Constructor",rv);
	return rv;
}

bool XMLFileDebug::debugSetSource(void){
	bool rv=true;
	XMLFile test(this->debugFile);
	int i=0;
	for (XMLFile::const_iterator iter=test.cbegin(true); iter!=test.cend(); iter++, i++){
		rv&=(iter->name==this->iterSeq[i]);
	}

	Print::objectMethodDebug(std::cout,"SetSource",rv);
	return rv;
}
