#include "debug/HelperFuncDebug.hpp"
#include "debug/TokenizerDebug.hpp"
#include "debug/FileDebug.hpp"
#include "debug/TreeDebug.hpp"
#include "debug/XMLTagDebug.hpp"
#include "debug/XMLFileDebug.hpp"

int main(int argc, char **argv){
	bool successful=true;
	successful&=HelperFuncDebug().run();
	successful&=TokenizerDebug().run();
	successful&=TreeDebug().run();
	successful&=FileDebug().run();
	successful&=XMLTagDebug().run();
	successful&=XMLFileDebug().run();

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
