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
size_t MapPassThrough<T,U>::max_size(void) const {
	return this->ptMap.max_size();
}

template <typename T, typename U>
void MapPassThrough<T,U>::emplace(const T &key, const U &val){
	this->ptMap.emplace(key,val);
}

template <typename T, typename U>
void MapPassThrough<T,U>::emplace_hint(typename std::map<T,U>::const_iterator &pos, const T &key, const U &val){
	this->ptMap.emplace_hint(pos,key,val);
}

template <typename T, typename U>
std::pair<typename std::map<T,U>::iterator,bool>
	MapPassThrough<T,U>::insert(const std::pair<const T,U> &val){
	return this->ptMap.insert(val);
}

template <typename T, typename U>
typename std::map<T,U>::iterator 
MapPassThrough<T,U>::insert(typename std::map<T,U>::const_iterator &pos, const std::pair<const T,U> &val){
	return this->ptMap.insert(pos,val);
}

template <typename T, typename U>
U& MapPassThrough<T,U>::at(const T &key){
	return this->ptMap.at(key);
}

template <typename T, typename U>
std::map<T,U>& MapPassThrough<T,U>::operator=(const std::map<T,U> &other){
	return this->ptMap.operator=(other);
}

template <typename T, typename U>
std::map<T,U>& MapPassThrough<T,U>::operator=(const std::map<T,U> &&other){
	return this->ptMap.operator=(other);
}

template <typename T, typename U>
const U& MapPassThrough<T,U>::at(const T &key) const {
	return this->ptMap.at(key);
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
typename std::map<T,U>::iterator MapPassThrough<T,U>::lower_bound(const T &key){
	return this->ptMap.lower_bound(key);
}

template <typename T, typename U>
typename std::map<T,U>::const_iterator MapPassThrough<T,U>::lower_bound(const T &key) const{
	return this->ptMap.lower_bound(key);
}

template <typename T, typename U>
typename std::map<T,U>::iterator MapPassThrough<T,U>::upper_bound(const T &key){
	return this->ptMap.upper_bound(key);
}

template <typename T, typename U>
typename std::map<T,U>::const_iterator MapPassThrough<T,U>::upper_bound(const T &key) const{
	return this->ptMap.upper_bound(key);
}

template <typename T, typename U>
std::pair<typename std::map<T,U>::iterator, typename std::map<T,U>::iterator>
MapPassThrough<T,U>::equal_range(const T &key){
	return this->ptMap.equal_range(key);
}

template <typename T, typename U>
std::pair<typename std::map<T,U>::const_iterator, typename std::map<T,U>::const_iterator>
MapPassThrough<T,U>::equal_range(const T &key) const {
	return this->ptMap.equal_range(key);
}

template <typename T, typename U>
bool MapPassThrough<T,U>::empty(void) const {
	return this->ptMap.empty();
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
