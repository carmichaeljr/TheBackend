#include <sstream>
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
	return (this->debugSetGetAttributes() &&
		this->debugFind() &&
		this->debugCount() &&
		this->debugSwap() &&
		this->debugErase() &&
		this->debugClear() &&
		this->debugEquals() &&
		this->debugParseName() &&
		this->debugParseAttributes() &&
		this->debugParseErrors() &&
		this->debugParseBadFormatting() &&
		this->debugGetOpeningTag() &&
		this->debugGetClosingTag() &&
		this->debugCopyConstructor());
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
	test2.name="NameTwo";
	test.swap(test2);

	rv&=(test2.name=="Name");
	rv&=(test2.data=="Data");
	rv&=(test2[this->correctKey[0]]==this->correctVal[0]);
	rv&=(test2[this->correctKey[1]]==this->correctVal[1]);
	rv&=(test2[this->correctKey[2]]==this->correctVal[2]);

	rv&=(test.name=="NameTwo");

	Print::objectMethodDebug(std::cout,"Swap",rv);
	return rv;
}

bool XMLTagDebug::debugErase(void){
	bool rv=true;
	XMLTag test;
	this->initilizeBlankTag(test);
	test.erase(this->correctKey[0]);
	test.erase(this->correctKey[2]);
	rv&=(test.size()==1);
	rv&=(test[this->correctKey[1]]==this->correctVal[1]);
	rv&=(test.find(this->correctKey[0])==test.end());
	rv&=(test.find(this->correctKey[2])==test.end());

	Print::objectMethodDebug(std::cout,"Erase",rv);
	return rv;
}

bool XMLTagDebug::debugClear(void){
	bool rv=true;
	XMLTag test;
	this->initilizeBlankTag(test);
	test.clear();
	rv&=(test.size()==0);
	rv&=(test.name.size()==0);
	rv&=(test.data.size()==0);

	Print::objectMethodDebug(std::cout,"Clear",rv);
	return rv;
}

bool XMLTagDebug::debugEquals(void){
	bool rv=true;
	XMLTag test, test2;
	this->initilizeBlankTag(test);
	rv&=(test!=test2);
	this->initilizeBlankTag(test2);
	rv&=(test==test2);
	Print::objectMethodDebug(std::cout,"Equals",rv);
	return rv;
}

bool XMLTagDebug::debugParseName(void){
	bool rv=true;
	XMLTag test;
	rv&=(test.parse("<Name>")==XMLTag::parseSuccess);
	rv&=(test.name=="Name");

	rv&=(test.parse("<\"<>/' \">")==XMLTag::parseSuccess);
	rv&=(test.name=="<>/' ");
	
	Print::objectMethodDebug(std::cout,"ParseName",rv);
	return rv;
}

bool XMLTagDebug::debugParseAttributes(void){
	bool rv=true;
	std::stringstream str;
	str << "<Name " << this->correctKey[0] << "=" << this->correctVal[0] << " ";
	str << this->correctKey[1] << "=" << this->correctVal[1] << " ";
	str << this->correctKey[2] << "=" << this->correctVal[2] << "/>";
	XMLTag test;
	rv&=(test.parse(str.str())==XMLTag::parseSuccess);
	rv&=(test.name=="Name");
	rv&=(test[this->correctKey[0]]==this->correctVal[0]);
	rv&=(test[this->correctKey[1]]==this->correctVal[1]);
	rv&=(test[this->correctKey[2]]==this->correctVal[2]);

	Print::objectMethodDebug(std::cout,"ParseAttributes",rv);
	return rv;
}

bool XMLTagDebug::debugParseErrors(void){
	bool rv=true;
	XMLTag test;
	rv&=(test.parse("hello")==XMLTag::invalidTag);
	rv&=(test.name.size()==0);

	rv&=(test.parse("<'unbalanced>")==(XMLTag::unballancedTag | XMLTag::invalidTag));
	rv&=(test.name.size()==0);

	rv&=(test.parse("<Name unbalancedAttr=data test/>")==(XMLTag::unballancedAttrs));
	rv&=(test.name=="Name");

	Print::objectMethodDebug(std::cout,"ParseErrors",rv);
	return rv;
}

bool XMLTagDebug::debugParseBadFormatting(void){
	bool rv=true;
	std::stringstream str;
	str << "<   Name    " << this->correctKey[0] << " =  " << this->correctVal[0] << "  ";
	str << this->correctKey[1] << "  = " << this->correctVal[1] << "    ";
	str << this->correctKey[2] << "    =" << this->correctVal[2] << "  /   >   ";
	XMLTag test;
	rv&=(test.parse(str.str())==XMLTag::parseSuccess);

	Print::objectMethodDebug(std::cout,"BadFormatting",rv);
	return rv;
}

bool XMLTagDebug::debugGetOpeningTag(void){
	bool rv=true;
	XMLTag test;
	this->initilizeBlankTag(test);
	rv&=(test.getOpeningTag()=="<Name attr0=data0 attr1=data1 attr2=data2>");
	rv&=(test.getOpeningTag(true)=="<Name attr0=data0 attr1=data1 attr2=data2/>");
	Print::objectMethodDebug(std::cout,"GetOpeningTag",rv);
	return rv;
}

bool XMLTagDebug::debugGetClosingTag(void){
	bool rv=true;
	XMLTag test;
	this->initilizeBlankTag(test);
	rv&=(test.getClosingTag()=="<Name/>");
	Print::objectMethodDebug(std::cout,"GetClosingTag",rv);
	return rv;
}

bool XMLTagDebug::debugCopyConstructor(void){
	bool rv=true;
	XMLTag test, test2;
	this->initilizeBlankTag(test);
	test2=test;
	rv&=(test==test2);
	Print::objectMethodDebug(std::cout,"CopyConstructor",rv);
	return rv;
}

void XMLTagDebug::initilizeBlankTag(XMLTag &tag) const {
	tag.name="Name";
	tag.data="Data";
	for (unsigned int i=0; i<this->correctKey.size(); i++){
		tag[this->correctKey[i]]=this->correctVal[i];
	}
}
