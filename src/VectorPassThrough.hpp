#ifndef VECTOR_PASS_THROUGH
#define VECTOR_PASS_THROUGH

#include <vector>

template <typename T>
class VectorPassThrough {
	public:
		VectorPassThrough(void);
		explicit VectorPassThrough(const std::vector<T> &data);
		T& at(const int index);
		const T& at(const int index) const;
		T& operator[](const int index);
		const T& operator[](const int index) const;
		T& front(void);
		const T& front(void) const;
		T& back(void);
		const T& back(void) const;
		typename std::vector<T>::iterator begin(void);
		const typename std::vector<T>::const_iterator begin(void) const;
		typename std::vector<T>::iterator end(void);
		const typename std::vector<T>::const_iterator end(void) const;
		typename std::vector<T>::const_iterator cbegin(void) const;
		typename std::vector<T>::const_iterator cend(void) const;
		bool empty(void) const;
		size_t size(void) const;
		void clear(void);
	protected:
		std::vector<T> ptVec;
};

#include "src/VectorPassThrough.tpp"

#endif
