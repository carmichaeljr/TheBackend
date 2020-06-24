#ifndef PRINT
#define PRINT

#include <iostream>
#include <string>

class Print {
	public:
		static void init(void);
		static void incrementIndentLevel(const int increment);
		static void setSpacesPerIndent(const int numSpaces);
		static void print(std::ostream &os, const std::string &str, const bool addEndl=true);
		static void printWithoutIndent(std::ostream &os, const std::string &str, const bool addEndl=true);
		static void error(std::ostream &os, const std::string &errMsg);
		static void objectDebug(std::ostream &os, const std::string &className, const bool success);
		static void objectMethodDebug(std::ostream &os, const std::string &methodName, const bool success);
		static bool yesOrNoPrompt(std::ostream &os, std::istream &is, const std::string &question);
	private:
		static int indentLevel;
		static int spacesPerIndent;
};

#endif
