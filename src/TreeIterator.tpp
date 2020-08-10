using nodeType=Tree<T>::Node;

template <typename iterVal>
class iteratorBase {
	friend class Tree;
	friend bool operator==(const iteratorBase<iterVal> &a, const iteratorBase<iterVal> &b){
		return (a.node==b.node);
	}
	
	friend bool operator!=(const iteratorBase<iterVal> &a, const iteratorBase<iterVal> &b){
		return (a.node!=b.node);
	}
	
	public:
		bool revisit;
	public:
		iteratorBase(void){
			this->prevAction=Tree::mvDown;
			this->revisit=false;
			this->node=nullptr;
		}

		iteratorBase(nodeType *headNode, bool revisit=false){
			this->prevAction=Tree::mvDown;
			this->revisit=revisit;
			this->node=headNode;
		}

		iteratorBase<iterVal>& operator++(const int num){
			if (this->node==nullptr){
				this->prevAction=-1;
			} else if (this->hasChildren(this->node)){
				if (this->prevAction==Tree::mvDown || this->prevAction==Tree::mvNext){
					this->move(Tree::mvDown);
				} else if (this->hasNext(this->node)){	//prevAction was up
					this->move(Tree::mvNext);
				} else if (!this->hasNext(this->node)){	//prevAction was up
					this->move(Tree::mvUp);
				}
			} else {	//!this->hasChildren(this->node);
				if (this->hasNext(this->node)){
					this->move(Tree::mvNext);
				} else {	//!this->hasNext(this->node)
					this->move(Tree::mvUp);
				}
			}
			return *this;
		}

		iterVal& operator*(void){
			return this->node->data;
		}

		iterVal* operator->(void){
			return (&this->node->data);
		}
	private:
		int prevAction;
		nodeType *node;

		constexpr bool hasChildren(nodeType *node) const{
			return (node->child!=nullptr);
		}

		constexpr bool hasNext(nodeType *node) const{
			return (node->next!=nullptr);
		}

		constexpr bool hasParent(nodeType *node) const{
			return (node->parent!=nullptr);
		}

		void move(const int dir){

			switch(dir){
				case (Tree::mvNext): this->node=this->node->next; 
							this->prevAction=Tree::mvNext; break;
				case (Tree::mvDown): this->node=this->node->child; 
							this->prevAction=Tree::mvDown; break;
				case (Tree::mvUp): this->node=this->node->parent; 
							this->prevAction=Tree::mvUp; break;
				default: break;
			}
			if (!this->revisit && this->prevAction==Tree::mvUp){
				this->operator++(1);
			}
		}
};
