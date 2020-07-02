#ifndef GENERIC_TREE_CLASS
#define GENERIC_TREE_CLASS

#include <string>
#include <vector>
#include <utility>

template <typename T>
class Tree {
	private:	//Needs to be placed at top for reference later in class
		class Node {
			public:
				Node(void);
				explicit Node(const T &data);
				T data;
				Tree<T>::Node *parent;
				Tree<T>::Node *child;
				Tree<T>::Node *next;
		};
	public:
		static const int mvUp=0;
		static const int mvDown=1;
		static const int mvNext=2;
	public:
		class iterator {
			friend class Tree;
			friend bool operator==(const Tree<T>::iterator &a, const Tree<T>::iterator &b){
				return (a.node==b.node);
			}
			friend bool operator!=(const Tree<T>::iterator &a, const Tree<T>::iterator &b){
				return (a.node!=b.node);
			}
			public:
				iterator(void);
				iterator(Tree<T>::Node *headNode, bool revisit=false);
				Tree<T>::iterator& operator++(const int num);
				T& operator*(void);
				T& operator*(void) const;
				T* operator->(void);
				T* operator->(void) const;
			private:
				bool revisit;
				int prevAction;
				Tree<T>::Node *node;
				constexpr bool hasChildren(Tree<T>::Node *node) const;
				constexpr bool hasNext(Tree<T>::Node *node) const;
				constexpr bool hasParent(Tree<T>::Node *node) const;
				void move(const int dir);
		};

		Tree(void);
		explicit Tree(const T &data);
		Tree(const Tree<T> &other);
		Tree(Tree<T> &&other);
		Tree<T>& operator=(const Tree<T> &other);
		Tree<T>& operator=(Tree<T> &&other);
		int size(void) const;
		bool empty(void) const;
		Tree<T>::iterator begin(bool revisit=false) const;
		Tree<T>::iterator end(void) const;
		void emplace(const T &data);
		void emplace(const Tree<T>::iterator &sibling, const T &data);
		void emplaceBelow(const Tree<T>::iterator &parent, const T &data);
		Tree<T>::iterator find(const T &data) const;
		Tree<T>::iterator find(const Tree<T>::iterator &start, const T &data) const;
		int count(const T &data) const;
		void eraseBelow(const Tree<T>::iterator &start);
		Tree<T>::iterator erase(const Tree<T>::iterator &start);
		void clear(void);
		~Tree(void);
	private:
		int numElem=0;
		Tree<T>::Node *headNode=nullptr;
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
#include "TreeIterator.tpp"

#endif
