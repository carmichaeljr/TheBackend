#include "debug/Debug.hpp"
#include "src/Print.hpp"

Debug::Debug(const std::string &className): cName(className) {
	//
}

bool Debug::run(void){
	this->success=(this->debugClassMethods() && this->debugObjectMethods());
	Print::objectDebug(std::cout,this->cName,this->success);
	return this->success;
}
