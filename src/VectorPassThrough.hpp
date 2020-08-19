#ifndef VECTOR_PASS_THROUGH
#define VECTOR_PASS_THROUGH

#include <vector>

template <typename T>
class VectorPassThrough {
	//using iterator=std::vector<T>::iterator;
	//using const_iterator=std::vector<T>::const_iterator;
	public:
		VectorPassThrough(void);
		explicit VectorPassThrough(const std::vector<T> &data);
		size_t max_size(void) const;
		void assign(typename std::vector<T>::iterator &first, typename std::vector<T>::iterator &last);
		void assign(size_t n, const T &val);
		typename std::vector<T>::iterator emplace(typename std::vector<T>::iterator &pos, const T &data);
		typename std::vector<T>::iterator emplace(typename std::vector<T>::const_iterator &pos, const T &data);
		typename std::vector<T>::iterator emplace_back(const T &data);
		typename std::vector<T>::iterator insert(typename std::vector<T>::const_iterator &pos, const T &val);
		typename std::vector<T>::iterator insert(typename std::vector<T>::const_iterator &pos, size_t n, const T &val);
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
		typename std::vector<T>::iterator begin(void);
		const typename std::vector<T>::const_iterator begin(void) const;
		typename std::vector<T>::iterator end(void);
		const typename std::vector<T>::const_iterator end(void) const;
		typename std::vector<T>::const_iterator cbegin(void) const;
		typename std::vector<T>::const_iterator cend(void) const;
		void swap(std::vector<T> &other);
		typename std::vector<T>::iterator erase(typename std::vector<T>::iterator &pos);
		typename std::vector<T>::iterator erase(typename std::vector<T>::iterator &first, typename std::vector<T>::iterator &last);
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
