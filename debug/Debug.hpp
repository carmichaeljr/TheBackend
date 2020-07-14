#ifndef DEBUG_CLASS
#define DEBUG_CLASS

#include <string>

class Debug {
	public:
		bool success=true;
		explicit Debug(const std::string &className);
		bool run(void);
		virtual bool debugClassMethods(void)=0;
		virtual bool debugObjectMethods(void)=0;
	protected:
		std::string cName;
};

#endif
