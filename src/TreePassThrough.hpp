#ifndef TREE_PASS_THROUGH_CLASS
#define TREE_PASS_THROUGH_CLASS

#include "src/Tree.hpp"

template <typename T>
class TreePassThrough {
	public:
		TreePassThrough(void);
		explicit TreePassThrough(const Tree<T> &data);
		size_t size(void) const;
		bool empty(void) const;
		typename Tree<T>::iterator begin(bool revisit=false);
		typename Tree<T>::const_iterator cbegin(bool revisit=false) const;
		typename Tree<T>::iterator end(void);
		typename Tree<T>::const_iterator cend(void) const;
		typename Tree<T>::iterator emplace(const T &data);
		typename Tree<T>::iterator emplace(const typename Tree<T>::iterator &sibling, const T &data);
		typename Tree<T>::iterator emplaceBelow(const typename Tree<T>::iterator &parent, const T &data);
		typename Tree<T>::iterator find(const T &data);
		typename Tree<T>::const_iterator find(const T &data) const;
		typename Tree<T>::iterator find(const typename Tree<T>::iterator &start, const T &data);
		typename Tree<T>::const_iterator find(const typename Tree<T>::const_iterator &start, const T &data) const;
		size_t count(const T &data) const;
		void eraseBelow(const typename Tree<T>::iterator &start);
		typename Tree<T>::iterator erase(const typename Tree<T>::iterator &start);
		void clear(void);
	protected:
		Tree<T> ptTree;
};

#include "src/TreePassThrough.tpp"

#endif
