#ifndef GENERIC_TREE_CLASS
#define GENERIC_TREE_CLASS

#include <string>
#include <vector>
#include <utility>

template <typename T>
class Tree {
	friend bool operator==(const Tree<T> &rhs, const Tree<T> &lhs){
		bool rv=(rhs.size()==lhs.size());
		Tree<T>::const_iterator rhsIter=rhs.cbegin();
		Tree<T>::const_iterator lhsIter=lhs.cbegin();
		for (; rv && rhsIter!=rhs.cend() && lhsIter!=lhs.cend();
			rv=(*rhsIter==*lhsIter), rhsIter++, lhsIter++);
		return rv;
	}
	friend bool operator!=(const Tree<T> &rhs, const Tree<T> &lhs){
		return !(rhs==lhs);
	}

	private:	//Needs to be placed at top for reference later in class
		class Node {
			public:
				Node(void);
				explicit Node(const T &data);
				T data;
				Tree<T>::Node *parent=nullptr;
				Tree<T>::Node *child=nullptr;
				Tree<T>::Node *next=nullptr;
		};
	public:
		static const int mvUp=0;
		static const int mvDown=1;
		static const int mvNext=2;
	public:
#include "TreeIterator.tpp"
		typedef iteratorBase<T> iterator;
		typedef iteratorBase<const T> const_iterator;

		Tree(void);
		explicit Tree(const T &data);
		Tree(const Tree<T> &other);
		Tree(Tree<T> &&other);
		Tree<T>& operator=(const Tree<T> &other);
		Tree<T>& operator=(Tree<T> &&other);
		size_t size(void) const;
		bool empty(void) const;
		Tree<T>::iterator begin(bool revisit=false);
		Tree<T>::const_iterator cbegin(bool revisit=false) const;
		Tree<T>::iterator end(void);
		Tree<T>::const_iterator cend(void) const;
		Tree<T>::iterator emplace(const T &data);
		Tree<T>::iterator emplace(const Tree<T>::iterator &sibling, const T &data);
		Tree<T>::iterator emplaceBelow(const Tree<T>::iterator &parent, const T &data);
		Tree<T>::iterator find(const T &data);
		Tree<T>::const_iterator find(const T &data) const;
		Tree<T>::iterator find(const Tree<T>::iterator &start, const T &data);
		Tree<T>::const_iterator find(const Tree<T>::const_iterator &start, const T &data) const;
		size_t count(const T &data) const;
		void eraseBelow(const Tree<T>::iterator &start);
		Tree<T>::iterator erase(const Tree<T>::iterator &start);
		void clear(void);
		~Tree(void);
	protected:
		int numElem=0;
		Tree<T>::Node *headNode=nullptr;
	private:
		void setHeadNode(const T &data);
		constexpr Tree<T>::Node* createNode(const T &data) const;
		void deleteNode(Tree<T>::Node *node);
		Tree<T>::Node* getEndOfSiblings(Tree<T>::Node *node) const;
		void appendToSiblings(Tree<T>::Node *end, Tree<T>::Node *newEnd);
		Tree<T>::Node* getParentNode(Tree<T>::Node *node) const;
		Tree<T>::Node* getPrevNode(Tree<T>::Node *node) const;
		void unlinkNode(Tree<T>::Node *par, Tree<T>::Node *prev, Tree<T>::Node *cur);
		void performDeepCopy(const Tree<T> &other);
};

#include "Tree.tpp"

#endif
