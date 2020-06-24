#ifndef TREE_DEBUG_CLASS
#define TREE_DEBUG_CLASS

#include <string>
#include "Debug.hpp"
#include "src/Tree.hpp"

class TreeDebug: public Debug {
	public:
		TreeDebug(void);
		bool debugClassMethods(void);
		bool debugObjectMethods(void);
		bool debugConstructor(void);
		bool debugEmplace(void);
		bool debugEmplaceBelow(void);
		bool debugIterator(void);
		bool debugEraseBelow(void);
		bool debugErase(void);
		bool debugClear(void);
		bool debugCopyConstructor(void);
		bool debugFind(void);
		bool debugCount(void);
	private:
		Tree<int> createDebugTestTree(void) const;
		bool debugEraseHelp(Tree<int> &test, std::vector<int> &correct, int delNum, int next);
};

#endif
