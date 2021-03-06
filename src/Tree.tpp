template <typename T>
Tree<T>::Tree(void){
	//
}

template <typename T>
Tree<T>::Tree(const T &data){
	this->emplace(data);
}

template <typename T>
Tree<T>::Tree(const Tree<T> &other){
	//Don't need to clear, new object is already empty
	this->performDeepCopy(other);
}

template <typename T>
Tree<T>::Tree(Tree<T> &&other){
	*this=std::move(other);
}

template <typename T>
Tree<T>& Tree<T>::operator=(const Tree<T> &other){
	this->clear();
	this->performDeepCopy(other);
	return *this;
}

template <typename T>
Tree<T>& Tree<T>::operator=(Tree<T> &&other){
	if (this!=&other){
		this->clear();
		this->numElem=other.numElem;
		this->headNode=other.headNode;
		other.numElem=0;
		other.headNode=nullptr;
	}
	return *this;
}

template <typename T>
size_t Tree<T>::size(void) const {
	return this->numElem;
}

template <typename T>
bool Tree<T>::empty(void) const {
	return (this->numElem==0);
}

template <typename T>
typename Tree<T>::iterator Tree<T>::begin(bool revisit){
	return Tree<T>::iterator(this->headNode,revisit);
}

template <typename T>
const typename Tree<T>::const_iterator Tree<T>::begin(bool revisit) const {
	return Tree<T>::const_iterator(this->headNode,revisit);
}

template <typename T>
typename Tree<T>::const_iterator Tree<T>::cbegin(bool revisit) const {
	return Tree<T>::const_iterator(this->headNode,revisit);
}

template <typename T>
typename Tree<T>::iterator Tree<T>::end(void){
	return Tree<T>::iterator();
}

template <typename T>
const typename Tree<T>::const_iterator Tree<T>::end(void) const {
	return Tree<T>::const_iterator();
}

template <typename T>
typename Tree<T>::const_iterator Tree<T>::cend(void) const {
	return Tree<T>::const_iterator();
}

template <typename T>
typename Tree<T>::iterator Tree<T>::emplace(const T &data){
	if (this->headNode==nullptr){
		this->setHeadNode(data);
		return this->begin();
	} else {
		return this->emplace(this->begin(),data);
	}
}

template <typename T>
typename Tree<T>::iterator Tree<T>::emplace(const Tree<T>::iterator &sibling, const T &data){
	Tree<T>::Node *end=this->getEndOfSiblings(sibling.node);
	Tree<T>::Node *tmp=this->createNode(data);
	this->appendToSiblings(end,tmp);
	this->numElem++;
	return Tree<T>::iterator(tmp);
}

template <typename T>
typename Tree<T>::iterator Tree<T>::emplaceBelow(const Tree<T>::iterator &parent, const T &data){
	Tree<T>::Node *newChild=this->createNode(data);
	Tree<T>::Node *parNode=parent.node;
	if (parNode->child==nullptr){
		parNode->child=newChild;
		newChild->parent=parNode;
	} else {
		Tree<T>::Node *end=this->getEndOfSiblings(parNode->child);
		this->appendToSiblings(end,newChild);
	}
	this->numElem++;
	return Tree<T>::iterator(newChild);
}

template <typename T>
typename Tree<T>::iterator Tree<T>::find(const T &data){
	return this->find(this->begin(),data);
}

template <typename T>
typename Tree<T>::const_iterator Tree<T>::find(const T &data) const {
	return this->find(this->cbegin(),data);
}

template <typename T>
typename Tree<T>::iterator Tree<T>::find(const typename Tree<T>::iterator &start, const T &data){
	Tree<int>::iterator rv(start.node);
	for(; rv!=this->end() && *rv!=data; rv++);
	return rv;
}

template <typename T>
typename Tree<T>::const_iterator Tree<T>::find(const typename Tree<T>::const_iterator &start, const T &data) const {
	Tree<int>::const_iterator rv(start.node);
	for(; rv!=this->cend() && *rv!=data; rv++);
	return rv;
}

template <typename T>
size_t Tree<T>::count(const T &data) const {
	int rv=0;
	for (Tree<T>::const_iterator iter=this->cbegin(); iter!=this->cend(); iter++){
		(*iter==data)? rv++: 0;
	}
	return rv;
}

template <typename T>
void Tree<T>::eraseBelow(const Tree<T>::iterator &start){
	if (start.node->child!=nullptr){
		Tree<T>::Node *tmp=nullptr;
		Tree<T>::iterator iter(start.node,true);
		iter++;
		while (iter!=this->end() && iter!=start){
			tmp=(iter.prevAction==Tree<T>::mvUp || iter.node->child==nullptr)? iter.node: nullptr;
			iter++;
			if (tmp!=nullptr){
				this->deleteNode(tmp);
			}
		}
		start.node->child=nullptr;
	}
}

template <typename T>
typename Tree<T>::iterator Tree<T>::erase(const Tree<T>::iterator &start){
	Tree<T>::iterator rv(start.node->next);
	this->eraseBelow(start);
	Tree<T>::Node *cur=start.node;
	Tree<T>::Node *par=this->getParentNode(start.node);
	Tree<T>::Node *prev=this->getPrevNode(start.node);
	this->unlinkNode(par,prev,cur);
	return rv;
}

template <typename T>
void Tree<T>::clear(void){
	while (this->headNode!=nullptr){
		this->erase(this->begin());
	}
}

template <typename T>
Tree<T>::~Tree(void){
	this->clear();
}

//Private Methods===============================================================
template <typename T>
void Tree<T>::setHeadNode(const T &data){
	this->headNode=this->createNode(data);
	this->numElem++;
}

template <typename T>
constexpr typename Tree<T>::Node* Tree<T>::createNode(const T &data) const {
	return (new Tree<T>::Node(data));
}

template <typename T>
void Tree<T>::deleteNode(Tree<T>::Node *node) {
	delete node;
	this->numElem--;
}

template <typename T>
typename Tree<T>::Node* Tree<T>::getEndOfSiblings(typename Tree<T>::Node *node) const {
	Tree<T>::Node *rv=node;
	for (; rv!=nullptr && rv->next!=nullptr; rv=rv->next);
	return rv;
}

template <typename T>
void Tree<T>::appendToSiblings(typename Tree<T>::Node *end, typename Tree<T>::Node *newEnd){
	end->next=newEnd;
	newEnd->parent=end->parent;
	end->parent=nullptr;
}

template <typename T>
typename Tree<T>::Node* Tree<T>::getParentNode(typename Tree<T>::Node *node) const {
	Tree<T>::Node *rv=this->getEndOfSiblings(node);
	return (rv->parent);
}

template <typename T>
typename Tree<T>::Node* Tree<T>::getPrevNode(typename Tree<T>::Node *node) const {
	Tree<T>::Node *par=this->getParentNode(node);
	Tree<T>::Node *siblingStart=(par!=nullptr)? par->child: this->headNode;
	Tree<T>::Node *rv=nullptr;
	for (; siblingStart!=nullptr && siblingStart!=node; 
		rv=siblingStart, siblingStart=siblingStart->next);
	return rv;
}

template <typename T>
void Tree<T>::unlinkNode(typename Tree<T>::Node *par, typename Tree<T>::Node *prev, typename Tree<T>::Node *cur){
	if (prev!=nullptr){
		prev->next=cur->next;
		prev->parent=cur->parent;
	}
	(par!=nullptr && prev==nullptr && par->child==cur)? par->child=cur->next: nullptr;
	(cur==this->headNode)? this->headNode=cur->next: nullptr;
	this->deleteNode(cur);
}

template <typename T>
void Tree<T>::performDeepCopy(const Tree<T> &other){
	Tree<T>::const_iterator otherIter=other.cbegin();
	this->emplace(*otherIter);
	otherIter++;
	Tree<T>::iterator thisIter=this->begin();
	for (; otherIter!=other.cend(); otherIter++, thisIter++){
		if (otherIter.prevAction==Tree<T>::mvDown){
			this->emplaceBelow(thisIter,*otherIter);
		} else if (otherIter.prevAction==Tree<T>::mvNext){
			this->emplace(*otherIter);
		}
	}
}

//=============================================================================
//Inner Node Class
template <typename T>
Tree<T>::Node::Node(void){
	//
}

template <typename T>
Tree<T>::Node::Node(const T &ndata): 
	data(ndata) {
	//
}
