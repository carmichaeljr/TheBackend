#ifndef HELPER_FUNCTION

#include <string>

class HelperFunc {
	public:
		static const std::string whitespace;
	public:
		static void removeTrailingNull(std::string &str);
		static void trimWhitespaceAtEnd(std::string &str);
		static void trimWhitespaceAtStart(std::string &str);
		static void trimWhitespace(std::string &str);
};


#endif
