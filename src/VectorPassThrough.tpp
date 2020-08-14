template <typename T>
VectorPassThrough<T>::VectorPassThrough(void){
	//
}

template <typename T>
VectorPassThrough<T>::VectorPassThrough(const std::vector<T> &data):
	ptVec(data) {
	//
}

template <typename T>
T& VectorPassThrough<T>::at(const int index){
	return this->ptVec.at(index);
}

template <typename T>
const T& VectorPassThrough<T>::at(const int index) const {
	return this->ptVec.at(index);
}

template <typename T>
T& VectorPassThrough<T>::operator[](const int index){
	return this->ptVec[index];
}

template <typename T>
const T& VectorPassThrough<T>::operator[](const int index) const {
	return this->ptVec[index];
}

template <typename T>
T& VectorPassThrough<T>::front(void){
	return this->ptVec.front();
}

template <typename T>
const T& VectorPassThrough<T>::front(void) const {
	return this->ptVec.front();
}

template <typename T>
T& VectorPassThrough<T>::back(void){
	return this->ptVec.back();
}

template <typename T>
const T& VectorPassThrough<T>::back(void) const {
	return this->ptVec.back();
}

template <typename T>
typename std::vector<T>::iterator VectorPassThrough<T>::begin(void){
	return this->ptVec.begin();
}

template <typename T>
const typename std::vector<T>::const_iterator VectorPassThrough<T>::begin(void) const {
	return this->ptVec.begin();
}

template <typename T>
typename std::vector<T>::iterator VectorPassThrough<T>::end(void){
	return this->ptVec.end();
}

template <typename T>
const typename std::vector<T>::const_iterator VectorPassThrough<T>::end(void) const {
	return this->ptVec.end();
}

template <typename T>
typename std::vector<T>::const_iterator VectorPassThrough<T>::cbegin(void) const {
	return this->ptVec.cbegin();
}

template <typename T>
typename std::vector<T>::const_iterator VectorPassThrough<T>::cend(void) const {
	return this->ptVec.cend();
}

template <typename T>
bool VectorPassThrough<T>::empty(void) const {
	return this->ptVec.empty();
}

template <typename T>
size_t VectorPassThrough<T>::size(void) const {
	return this->ptVec.size();
}

template <typename T>
void VectorPassThrough<T>::clear(void){
	this->ptVec.clear();
}
