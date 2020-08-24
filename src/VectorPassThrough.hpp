#ifndef VECTOR_PASS_THROUGH
#define VECTOR_PASS_THROUGH

#include <vector>

template <typename T>
class VectorPassThrough {
	using iterator=typename std::vector<T>::iterator;
	using const_iterator=typename std::vector<T>::const_iterator;
	public:
		VectorPassThrough(void);
		explicit VectorPassThrough(const std::vector<T> &data);
		size_t max_size(void) const;
		void assign(iterator &first, iterator &last);
		void assign(size_t n, const T &val);
		iterator emplace(iterator &pos, const T &data);
		iterator emplace(const_iterator &pos, const T &data);
		iterator emplace_back(const T &data);
		iterator insert(const_iterator &pos, const T &val);
		iterator insert(const_iterator &pos, size_t n, const T &val);
		//Does not have range, move, or initializer list insert methods
		void push_back(const T &val);
		void push_back(const T &&val);
		void reserve(size_t n);
		void resize(size_t n);
		void resize(size_t n, const T &val);
		size_t capacity(void) const;
		T& at(const int index);
		const T& at(const int index) const;
		T& operator[](const int index);
		const T& operator[](const int index) const;
		T& front(void);
		const T& front(void) const;
		T& back(void);
		const T& back(void) const;
		T* data(void);
		const T* data(void) const;
		iterator begin(void);
		const const_iterator begin(void) const;
		iterator end(void);
		const const_iterator end(void) const;
		const_iterator cbegin(void) const;
		const_iterator cend(void) const;
		void swap(std::vector<T> &other);
		iterator erase(iterator &pos);
		iterator erase(iterator &first, iterator &last);
		void pop_back(void);
		void shrink_to_fit(void);
		bool empty(void) const;
		size_t size(void) const;
		void clear(void);
	protected:
		std::vector<T> ptVec;
};

#include "src/VectorPassThrough.tpp"

#endif
