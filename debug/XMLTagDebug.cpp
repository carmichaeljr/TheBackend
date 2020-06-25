#include "XMLTagDebug.hpp"
#include "src/Print.hpp"

XMLTagDebug::XMLTagDebug(void): Debug("XMLTag") {
	this->correctKey={ "attr0","attr1","attr2" };
	this->correctVal={ "data0","data1","data2" };
}

bool XMLTagDebug::debugClassMethods(void){
	return true;
}

bool XMLTagDebug::debugObjectMethods(void){
	return (this->debugSetGetName() &&
		this->debugSetGetData() &&
		this->debugSetGetAttributes() &&
		this->debugFind() &&
		this->debugCount() &&
		this->debugSwap() &&
		this->debugParseName() &&
		this->debugParseErrors() &&
		this->debugParseAttributes());
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

bool XMLTagDebug::debugSetGetAttributes(void){
	bool rv=true;
	XMLTag test;
	test[this->correctKey[0]]=this->correctVal[0];
	test[this->correctKey[1]]=this->correctVal[1];
	test.emplace(this->correctKey[2],this->correctVal[2]);
	int i=0;
	for (std::map<std::string,std::string>::iterator iter=test.begin(); iter!=test.end(); iter++, i++){
		rv&=(iter->first==correctKey[i] && iter->second==correctVal[i]);
		std::cout << "Pair: " << iter->first << " " << iter->second << std::endl;
	}
	Print::objectMethodDebug(std::cout,"Get/Set Attributes",rv);
	return rv;
}

bool XMLTagDebug::debugFind(void){
	bool rv=true;
	XMLTag test;
	this->initilizeBlankTag(test);
	std::map<std::string,std::string>::iterator iter=test.find(this->correctKey[1]);
	rv&=(iter->first==this->correctKey[1] && iter->second==this->correctVal[1]);
	iter=test.find("attr5");
	rv&=(iter==test.end());
	Print::objectMethodDebug(std::cout,"Find",rv);
	return rv;
}

bool XMLTagDebug::debugCount(void){
	bool rv=true;
	XMLTag test;
	this->initilizeBlankTag(test);
	rv&=(test.count(this->correctKey[0])==1);
	rv&=(test.count("attr5")==0);
	Print::objectMethodDebug(std::cout,"Count",rv);
	return rv;
}

bool XMLTagDebug::debugSwap(void){
	bool rv=true;
	XMLTag test, test2;
	this->initilizeBlankTag(test);
	test2.setName("NameTwo");
	test.swap(test2);

	rv&=(test2.getName()=="Name");
	rv&=(test2.getData()=="Data");
	rv&=(test2[this->correctKey[0]]==this->correctVal[0]);
	rv&=(test2[this->correctKey[1]]==this->correctVal[1]);
	rv&=(test2[this->correctKey[2]]==this->correctVal[2]);

	rv&=(test.getName()=="NameTwo");

	Print::objectMethodDebug(std::cout,"Swap",rv);
	return rv;
}

bool XMLTagDebug::debugParseName(void){
	bool rv=true;
	XMLTag test;
	rv&=(test.parse("<Name>")==XMLTag::parseSuccess);
	rv&=(test.getName()=="Name");

	rv&=(test.parse("<\"<>/' \">")==XMLTag::parseSuccess);
	rv&=(test.getName()=="<>/' ");
	
	Print::objectMethodDebug(std::cout,"ParseName",rv);
	return rv;
}

bool XMLTagDebug::debugParseErrors(void){
	bool rv=true;
	XMLTag test;
	rv&=(test.parse("hello")==XMLTag::invalidTag);
	rv&=(test.getName().size()==0);

	rv&=(test.parse("<'unbalanced>")==(XMLTag::unballancedTag | XMLTag::invalidTag));
	rv&=(test.getName().size()==0);

	rv&=(test.parse("<Name unbalancedAttr=data test/>")==(XMLTag::unballancedAttrs));
	rv&=(test.getName()=="Name");

	Print::objectMethodDebug(std::cout,"ParseErrors",rv);
	return rv;
}

bool XMLTagDebug::debugParseAttributes(void){
	bool rv=true;
	XMLTag test;
	rv&=(test.parse("<Name attr1=data1 attr2=data2/>")==XMLTag::parseSuccess);
	rv&=(test.getName()=="Name");

	Print::objectMethodDebug(std::cout,"ParseAttributes",rv);
	return rv;
}

void XMLTagDebug::initilizeBlankTag(XMLTag &tag) const {
	tag.setName("Name");
	tag.setData("Data");
	for (unsigned int i=0; i<this->correctKey.size(); i++){
		tag[this->correctKey[i]]=this->correctVal[i];
	}
}
