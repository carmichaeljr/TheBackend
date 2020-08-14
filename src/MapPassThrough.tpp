template <typename T, typename U>
MapPassThrough<T,U>::MapPassThrough(void){
	//
}

template <typename T, typename U>
MapPassThrough<T,U>::MapPassThrough(const std::map<T,U> &data):
	ptMap(data) {
	//
}

template <typename T, typename U>
void MapPassThrough<T,U>::emplace(const T &key, const U &val){
	this->ptMap.emplace(key,val);
}

template <typename T, typename U>
U& MapPassThrough<T,U>::operator[](const T &key){
	return this->ptMap[key];
}

template <typename T, typename U>
typename std::map<T,U>::iterator MapPassThrough<T,U>::begin(void){
	return this->ptMap.begin();
}

template <typename T, typename U>
const typename std::map<T,U>::const_iterator MapPassThrough<T,U>::begin(void) const {
	return this->ptMap.begin();
}

template <typename T, typename U>
typename std::map<T,U>::iterator MapPassThrough<T,U>::end(void){
	return this->ptMap.end();
}

template <typename T, typename U>
const typename std::map<T,U>::const_iterator MapPassThrough<T,U>::end(void) const {
	return this->ptMap.end();
}

template <typename T, typename U>
typename std::map<T,U>::const_iterator MapPassThrough<T,U>::cbegin(void) const {
	return this->ptMap.cbegin();
}

template <typename T, typename U>
typename std::map<T,U>::const_iterator MapPassThrough<T,U>::cend(void) const {
	return this->ptMap.cend();
}

template <typename T, typename U>
void MapPassThrough<T,U>::swap(std::map<T,U> &other){
	this->ptMap.swap(other);
}

template <typename T, typename U>
typename std::map<T,U>::iterator MapPassThrough<T,U>::find(const T &key){
	return this->ptMap.find(key);
}

template <typename T, typename U>
typename std::map<T,U>::const_iterator MapPassThrough<T,U>::find(const T &key) const {
	return this->ptMap.find(key);
}

template <typename T, typename U>
size_t MapPassThrough<T,U>::size(void) const {
	return this->ptMap.size();
}

template <typename T, typename U>
size_t MapPassThrough<T,U>::count(const T &key) const {
	return this->ptMap.count(key);
}

template <typename T, typename U>
void MapPassThrough<T,U>::erase(const T &key){
	this->ptMap.erase(key);
}

template <typename T, typename U>
void MapPassThrough<T,U>::clear(void){
	this->ptMap.clear();
}
