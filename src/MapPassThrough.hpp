#ifndef MAP_PASS_THROUGH_CLASS
#define MAP_PASS_THROUGH_CLASS

#include <map>
#include <utility>

template <typename T, typename U>
class MapPassThrough {
	using iterator=typename std::map<T,U>::iterator;
	using const_iterator=typename std::map<T,U>::const_iterator;
	public:
		MapPassThrough(void);
		explicit MapPassThrough(const std::map<T,U> &data);
		size_t max_size(void) const;
		void emplace(const T &key, const U &val);
		void emplace_hint(const_iterator &pos, const T &key, const U &val);
		std::pair<iterator,bool> insert(const std::pair<const T, U> &val);
		iterator insert(const_iterator &pos, const std::pair<const T, U> &val);
		//Don't have range or initializer list insert methods
		U& at(const T &key);
		const U& at(const T &key) const;
		std::map<T,U>& operator=(const std::map<T,U> &other);
		std::map<T,U>& operator=(const std::map<T,U> &&other);
		U& operator[](const T &key);
		iterator begin(void);
		const const_iterator begin(void) const;
		iterator end(void);
		const const_iterator end(void) const;
		const_iterator cbegin(void) const;
		const_iterator cend(void) const;
		void swap(std::map<T,U> &other);
		iterator find(const T &name);
		const_iterator find(const T &key) const;
		iterator lower_bound(const T &key);
		const_iterator lower_bound(const T &key) const;
		iterator upper_bound(const T &key);
		const_iterator upper_bound(const T &key) const;
		std::pair<iterator, iterator> equal_range(const T &key);
		std::pair<const_iterator, const_iterator> equal_range(const T &key) const;
		size_t size(void) const;
		size_t count(const T &key) const;
		bool empty(void) const;
		void erase(const T &key);
		void clear(void);
	protected:
		std::map<T,U> ptMap;
};

#include "src/MapPassThrough.tpp"

#endif
