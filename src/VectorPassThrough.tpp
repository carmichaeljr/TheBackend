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
size_t VectorPassThrough<T>::max_size(void) const {
	return this->ptVec.max_size();
}

template <typename T>
void VectorPassThrough<T>::assign(typename std::vector<T>::iterator &first, typename std::vector<T>::iterator &last){
	this->ptVec.assign(first,last);
}

template <typename T>
void VectorPassThrough<T>::assign(size_t n, const T &val){
	this->ptVec.assign(n,val);
}

template <typename T>
typename std::vector<T>::iterator 
VectorPassThrough<T>::emplace(typename std::vector<T>::iterator &pos, const T &data){
	return this->ptVec.emplace(pos,data);
}

template <typename T>
typename std::vector<T>::iterator 
VectorPassThrough<T>::emplace(typename std::vector<T>::const_iterator &pos, const T &data){
	return this->ptVec.emplace(pos,data);
}

template <typename T>
typename std::vector<T>::iterator VectorPassThrough<T>::emplace_back(const T &data){
	return this->ptVec.emplace_back(data);
}

template <typename T>
typename std::vector<T>::iterator 
VectorPassThrough<T>::insert(typename std::vector<T>::const_iterator &pos, const T &val){
	return this->ptVec.insert(pos,val);
}

template <typename T>
typename std::vector<T>::iterator
VectorPassThrough<T>::insert(typename std::vector<T>::const_iterator &pos, size_t n, const T &val){
	return this->ptVec.insert(pos,n,val);
}

template <typename T>
void VectorPassThrough<T>::push_back(const T &data){
	this->ptVec.push_back(data);
}

template <typename T>
void VectorPassThrough<T>::push_back(const T &&data){
	this->ptVec.push_back(data);
}

template <typename T>
void VectorPassThrough<T>::reserve(size_t n){
	this->ptVec.reserve(n);
}

template <typename T>
void VectorPassThrough<T>::resize(size_t n){
	this->ptVec.resize(n);
}

template <typename T>
void VectorPassThrough<T>::resize(size_t n, const T &val){
	this->ptVec.resize(n,val);
}

template <typename T>
size_t VectorPassThrough<T>::capacity(void) const {
	return this->ptVec.capacity();
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
T* VectorPassThrough<T>::data(void){
	return this->ptVec.data();
}

template <typename T>
const T* VectorPassThrough<T>::data(void) const {
	return this->ptVec.data();
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
void VectorPassThrough<T>::swap(std::vector<T> &other){
	this->ptVec.swap(other);
}

template <typename T>
typename std::vector<T>::iterator 
VectorPassThrough<T>::erase(typename std::vector<T>::iterator &pos){
	this->ptVec.erase(pos);
}

template <typename T>
typename std::vector<T>::iterator
VectorPassThrough<T>::erase(typename std::vector<T>::iterator &first, typename std::vector<T>::iterator &last){
	this->ptVec.erase(first,last);
}

template <typename T>
void VectorPassThrough<T>::pop_back(void){
	return this->ptVec.pop_back();
}

template <typename T>
void VectorPassThrough<T>::shrink_to_fit(void){
	return this->shrink_to_fit();
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
