#include "HelperFuncDebug.hpp"
#include "FileDebug.hpp"
#include "TreeDebug.hpp"
#include "XMLTagDebug.hpp"

int main(int argc, char **argv){
	bool successful=true;
	successful&=HelperFuncDebug().run();
	successful&=TreeDebug().run();
	successful&=FileDebug().run();
	successful&=XMLTagDebug().run();

	//Print::print(std::cout,"This is a test");
	//Print::incrementIndentLevel(1);
	//Print::print(std::cout,"This is a test");
	//Print::printWithoutIndent(std::cout,"This is a test");
	//Print::incrementIndentLevel(-1);
	//Print::print(std::cout,"This is a test");
	//Print::error(std::cout,"Test error message");
	//Print::objectDebug(std::cout,"Print",true);
	//Print::objectDebug(std::cout,"Print",false);
	//Print::yesOrNoPrompt(std::cout,std::cin,"This is a question");
	return 0;
}
