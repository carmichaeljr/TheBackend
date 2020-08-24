#ifndef TREE_PASS_THROUGH_CLASS
#define TREE_PASS_THROUGH_CLASS

#include "src/Tree.hpp"

template <typename T>
class TreePassThrough {
	using iterator=typename Tree<T>::iterator;
	using const_iterator=typename Tree<T>::const_iterator;
	public:
		TreePassThrough(void);
		explicit TreePassThrough(const Tree<T> &data);
		size_t size(void) const;
		bool empty(void) const;
		iterator begin(bool revisit=false);
		const const_iterator begin(bool revisit=false) const;
		const_iterator cbegin(bool revisit=false) const;
		iterator end(void);
		const const_iterator end(void) const;
		const_iterator cend(void) const;
		iterator emplace(const T &data);
		iterator emplace(const iterator &sibling, const T &data);
		iterator emplaceBelow(const iterator &parent, const T &data);
		iterator find(const T &data);
		const_iterator find(const T &data) const;
		iterator find(const iterator &start, const T &data);
		const_iterator find(const const_iterator &start, const T &data) const;
		size_t count(const T &data) const;
		void eraseBelow(const iterator &start);
		iterator erase(const iterator &start);
		void clear(void);
	protected:
		Tree<T> ptTree;
};

#include "src/TreePassThrough.tpp"

#endif
