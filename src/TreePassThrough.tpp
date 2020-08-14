template <typename T>
TreePassThrough<T>::TreePassThrough(void){
	//
}

template <typename T>
TreePassThrough<T>::TreePassThrough(const Tree<T> &data):
	ptTree(data) {
	//
}

template <typename T>
size_t TreePassThrough<T>::size(void) const {
	return this->ptTree.size();
}

template <typename T>
bool TreePassThrough<T>::empty(void) const {
	return this->ptTree.empty();
}

template <typename T>
typename Tree<T>::iterator TreePassThrough<T>::begin(bool revisit){
	return this->ptTree.begin(revisit);
}

template <typename T>
typename Tree<T>::const_iterator TreePassThrough<T>::cbegin(bool revisit) const {
	return this->ptTree.cbegin(revisit);
}

template <typename T>
typename Tree<T>::iterator TreePassThrough<T>::end(void){
	return this->ptTree.end();
}

template <typename T>
typename Tree<T>::const_iterator TreePassThrough<T>::cend(void) const {
	return this->ptTree.cend();
}

template <typename T>
typename Tree<T>::iterator TreePassThrough<T>::emplace(const T &data){
	return this->ptTree.emplace(data);
}

template <typename T>
typename Tree<T>::iterator TreePassThrough<T>::emplace(const typename Tree<T>::iterator &sibling, const T &data){
	return this->ptTree.emplace(sibling,data);
}

template <typename T>
typename Tree<T>::iterator TreePassThrough<T>::emplaceBelow(const typename Tree<T>::iterator &parent, const T &data){
	return this->ptTree.emplaceBelow(parent,data);
}

template <typename T>
typename Tree<T>::iterator TreePassThrough<T>::find(const T &data){
	return this->ptTree.find(data);
}

template <typename T>
typename Tree<T>::const_iterator TreePassThrough<T>::find(const T &data) const {
	return this->ptTree.find(data);
}

template <typename T>
typename Tree<T>::iterator TreePassThrough<T>::find(const typename Tree<T>::iterator &start, const T &data){
	return this->ptTree.find(start,data);
}

template <typename T>
typename Tree<T>::const_iterator TreePassThrough<T>::find(const typename Tree<T>::const_iterator &start, const T &data) const {
	return this->ptTree.find(start,data);
}

template <typename T>
size_t TreePassThrough<T>::count(const T &data) const {
	return this->ptTree.count(data);
}

template <typename T>
void TreePassThrough<T>::eraseBelow(const typename Tree<T>::iterator &start){
	return this->ptTree.eraseBelow(start);
}

template <typename T>
typename Tree<T>::iterator TreePassThrough<T>::erase(const typename Tree<T>::iterator &start){
	return this->ptTree.erase(start);
}

template <typename T>
void TreePassThrough<T>::clear(void){
	this->ptTree.clear();
}
