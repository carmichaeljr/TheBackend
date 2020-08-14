#ifndef MAP_PASS_THROUGH_CLASS
#define MAP_PASS_THROUGH_CLASS

#include <map>

template <typename T, typename U>
class MapPassThrough {
	public:
		MapPassThrough(void);
		explicit MapPassThrough(const std::map<T,U> &data);
		//size_t max_size(void) const;
		void emplace(const T &key, const U &val);
		//void emplace_hint(typename std::map<T,U>::const_iterator pos, const T &key, const U &val);
		//std::pair<typename std::map<T,U>::iterator,bool> insert(const std::pair<const T, U> &val);
		//typename std::map<T,U>::iterator insert(typename std::map<T,U>::const_iterator &pos, const std::pair<const T, U> &val);
		////Don't have range or initializer list insert methods
		//U& at(const T &key);
		//const U& at(const T &key) const;
		U& operator[](const T &key);
		typename std::map<T,U>::iterator begin(void);
		const typename std::map<T,U>::const_iterator begin(void) const;
		typename std::map<T,U>::iterator end(void);
		const typename std::map<T,U>::const_iterator end(void) const;
		typename std::map<T,U>::const_iterator cbegin(void) const;
		typename std::map<T,U>::const_iterator cend(void) const;
		void swap(std::map<T,U> &other);
		typename std::map<T,U>::iterator find(const T &name);
		typename std::map<T,U>::const_iterator find(const T &key) const;
		//typename std::map<T,U>::iterator lower_bound(const T &key);
		//typename std::map<T,U>::const_iterator lower_bound(const T &key) const;
		//typename std::map<T,U>::iterator upper_bound(const T &key);
		//typename std::map<T,U>::const_iterator upper_bound(const T &key) const;
		//std::pair<typename std::map<T,U>::iterator, typename std::map<T,U>::iterator> equal_range(const T &key);
		//std::pair<typename std::map<T,U>::const_iterator, typename std::map<T,U>::const_iterator> equal_range(const T &key) const;
		size_t size(void) const;
		size_t count(const T &key) const;
		//bool empty(void) const;
		void erase(const T &key);
		void clear(void);
	protected:
		std::map<T,U> ptMap;
};

#include "src/MapPassThrough.tpp"

#endif
