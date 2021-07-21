// to do finish vector functions
// make classes templates
// fix copy constructor and assignment operator

#pragma once
#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

class NodeT
{
public:
	int data;
	NodeT* left;
	NodeT* right;
    NodeT* parent;
    bool isBlack;
    NodeT(const int &v, NodeT* l = nullptr, NodeT* r = nullptr, NodeT* p = nullptr):
    data(v), isBlack(false), left(l), right(r), parent(p){}
};

class RedBlackTree{
    NodeT* root;
    NodeT* extNode;
    int numOfValues;
    void left_rotate (NodeT* &rt, NodeT*);
    void right_rotate(NodeT* &rt, NodeT*);
    NodeT* insert_bst(NodeT* &p, NodeT* &r, const int &v);
    NodeT* my_search(NodeT* r, int val, bool& truth);
    NodeT* uncle(NodeT* v) const;
    NodeT* grand(NodeT* v) const;
    NodeT* find_val(int it)const;
    void makeEmpty(NodeT*);
    bool placeAtLeaf(NodeT* );
    bool isLeftChild(NodeT* )const;
    void insertFix(NodeT*&, NodeT*);
    void swap(NodeT*, NodeT*);
	void my_remove(NodeT* &, NodeT*);
	void removeFixUp(NodeT*&, NodeT*, NodeT*);
	NodeT* minimum(NodeT* node);
	NodeT* maximum(NodeT* node);
	void myCopy(NodeT*, NodeT*);
    
public:
    RedBlackTree();
    RedBlackTree(const RedBlackTree&);
    RedBlackTree& operator=(const RedBlackTree&);
    ~RedBlackTree();
    bool insert(const int&);
    void my_insert(NodeT*&, NodeT*);
    bool remove(int data);
    bool search(int data);
    vector<int> search(int data, int data2);
    int closestLess(int data);
    int closestGreater(int data);
    vector<int> values();
    int size() const; 
    void print();
    void print(NodeT*)const;
    // template <class Tjwme>
    // friend NodeT<Tjwme>* JWMEgetRoot(const RedBlackTree<Tjwme> & rbt);
};

NodeT* RedBlackTree::find_val(int it) const{
    NodeT* v = root;
    bool absent = false;
    while(!absent && it != v->data){
        if(it < v->data && v->left != nullptr)
            v = v->left;
        else if(it > v->data && v->right!= nullptr)
            v = v->right;
        else
            absent = true;
    }
    return v;
}

void RedBlackTree::makeEmpty(NodeT* t){
    if(t == nullptr)
        return;
    makeEmpty(t->left);
    makeEmpty(t->right);
    delete t;
}

RedBlackTree::RedBlackTree(){
    extNode = nullptr;
    root = extNode;
    numOfValues = 0;
}


RedBlackTree::RedBlackTree(const RedBlackTree& rbt){
	if(rbt.root == nullptr){
		root = nullptr;
		return;
	}
	root = new NodeT(rbt.root->data);
	numOfValues = rbt.numOfValues;
	myCopy(root, rbt.root);
}

RedBlackTree::~RedBlackTree(){
    makeEmpty(root);
}

void RedBlackTree::myCopy(NodeT* nd, NodeT* rb){
	if(rb!=nullptr){
		nd->data = rb->data;
		nd->isBlack = rb->isBlack;
		if(rb->left != nullptr){
			nd->left = new NodeT(rb->left->data);
			nd->left->isBlack = rb->left->isBlack;
			nd->left->parent = nd;
			myCopy(nd->left, rb->left);
		}
		else{
			nd->left = nullptr;
		}
		if(rb->right != nullptr){
			nd ->right = new NodeT(rb->right->data);
			nd ->right->isBlack = rb->right->isBlack;
			nd->right->parent = nd;

			myCopy(nd->right, rb->right);
		}
		else{
			nd->right = nullptr;
		}
	}
}

RedBlackTree& RedBlackTree::operator=(const RedBlackTree& rbt){
    if(this != &rbt){
        makeEmpty(root);
        if(rbt.root == nullptr){
			root = nullptr;
			return *this;
		}
		root = new NodeT(rbt.root->data);
		numOfValues = rbt.numOfValues;
    }
    return *this;
}

vector<int> RedBlackTree::search(int data, int data2){
	
}

vector<int> RedBlackTree::values(){
    
}

bool RedBlackTree::search(int data){
    bool truth = false;
    my_search(root, data, truth);
    return truth;
}

NodeT* RedBlackTree::my_search(NodeT* node, int data, bool& truth){
	if(node == nullptr){
		truth = false;
		return node;
	}
	else if(node->data == data){
		truth = true;
		return node;
	}
	else{
		if(data > node->data)
			return my_search(node->right, data, truth);
		else
			return my_search(node->left, data, truth);
	}


}


// bool RedBlackTree:: insert(const int& v){
//     NodeT* x = new NodeT(v);
//     x->left = extNode;
//     x->right = extNode;
//     if(!placeAtLeaf(x))
//         return false;
//     cout<<"inserting "<<v<<endl;
//     x->isBlack = false;
//     while(x != root && x->parent->isBlack == false){
//         NodeT* y = uncle(x);
//         if(y != nullptr && y ->isBlack == false){ //move red up tree
//             x->parent->isBlack = true;
//             y->isBlack = true;
//             grand(x)->isBlack = false;
//             x = grand(x);
//         }
//         else{   // uncle is black, fix with rotations
//             bool parentWasLeft = isLeftChild(x->parent);
//             bool xIsLeft = isLeftChild(x);
//             //first rotation
//             if(parentWasLeft && !xIsLeft){
//                 x = x->parent;
//                 left_rotate(x);
//             }
//             else if(!parentWasLeft && xIsLeft){
//                 x = x->parent;
//                 right_rotate(x);
//             }
//             // Finish with rotation
//             x->parent->isBlack = true;
//             grand(x)->isBlack = false;
//             if(parentWasLeft)
//                 right_rotate(grand(x));
//             else
//                 left_rotate(grand(x));
//         }
//     }
//     root->isBlack = true;
//     return true;
// }

bool RedBlackTree:: remove(int data){
	bool truth = false;

	cout<<"before my search"<<endl;
	NodeT* deleteNode = my_search(root, data, truth);

	cout<<"after my search"<<endl;
	if(!truth)
		return false;
	
	if(deleteNode != nullptr)
		my_remove(root, deleteNode);
	return true;

}
void RedBlackTree::my_remove(NodeT* &root, NodeT* node){
	NodeT* child, *parent;
	bool tempBlack;
	numOfValues--;
	// The node left and right of the node isn't empty
	if(node->left != nullptr && node ->right != nullptr){
		NodeT* replace = node;
		replace = node->right;
		while(replace->left != nullptr){
			replace = replace->left;
		}

		// deleted node is not the root
		if(node->parent != nullptr){
			if(node->parent->left == node)
				node->parent->left = replace;
			else
				node->parent->right = replace;
		}
		// root node situation
		else
			root = replace;
		//child is the right node of the replacement node, which is the node that needs subsequent adjustment.
		child = replace->right;
		parent = replace -> parent;
		tempBlack = replace->isBlack;

		// Node is replaced by the parent node of the replace
		if(parent == node)
			parent = replace;
		else
		{
			//Children's node exists
			if (child != nullptr)
				child->parent = parent;
			
			parent->left = child;

			replace->right = node->right;
			node->right->parent = replace;
		}
		replace->parent = node->parent;
		replace->isBlack = node->isBlack;
		replace->left = node->left;
		node->left->parent = replace;
		if (tempBlack == true)
			removeFixUp(root, child, parent);

		delete node;
		return;
	}
	// When the deleted node has only the left (right) node is empty, find the child node of the deleted node
	if(node->left != nullptr)
		child = node->left;
	else
		child = node->right;
	
	parent = node->parent;
	tempBlack = node->isBlack;
	if (child) 
	{
		child->parent = parent;
	}
	//The deleted node is not the root node
	if(parent){
		if(node == parent->left)
			parent->left = child;
		else
			parent->right = child;
	}
	// deleted node is the root node
	else
		this->root = child;

	if (tempBlack == true){
		removeFixUp(root, child, parent);
	}
	delete node;


}

void RedBlackTree::removeFixUp(NodeT* &root, NodeT* node, NodeT* parent){
	NodeT* othernode;
	while((!node) || node->isBlack == true && node != this->root){
		if(parent->left == node){
			othernode = parent->right;
			if (othernode->isBlack == false)
			{
				othernode->isBlack = true;
				parent->isBlack = false;
				left_rotate(root, parent);
				othernode = parent->right;
			}
			else{
				if (!(othernode->right) || othernode->right->isBlack == true)
				{
					othernode->left->isBlack=true;
					othernode->isBlack = false;
					right_rotate(root, othernode);
					othernode = parent->right;
				}
				othernode->isBlack = parent->isBlack;
				parent->isBlack = true;
				othernode->right->isBlack = true;
				left_rotate(root, parent);
				node = root;
				break;
			}
		}
		else{
			othernode = parent->left;
			if (othernode->isBlack == false)
			{
				othernode->isBlack = true;
				parent->isBlack = false;
				right_rotate(root, parent);
				othernode = parent->left;
			}
			if ((!othernode->left || othernode->left->isBlack == true) && (!othernode->right || othernode->right->isBlack == true))
			{
				othernode->isBlack = false;
				node = parent;
				parent = node->parent;
			}
			else
			{
				if (!(othernode->left) || othernode->left->isBlack == true)
				{
					othernode->right->isBlack = true;
					othernode->isBlack = false;
					left_rotate(root, othernode);
					othernode = parent->left;
				}
				othernode->isBlack = parent->isBlack;
				parent->isBlack = true;
				othernode->left->isBlack = true;
				right_rotate(root, parent);
				node = root;
				break;
			}

		}
	}
	if(node)
		node->isBlack = true;
}
 int RedBlackTree:: closestGreater(int data){
	 bool truth = false;
	 NodeT* temp = my_search(root,data, truth);

	 if(temp->right != nullptr){
		 return minimum(temp->right)->data;
	 }
	 NodeT* y = temp->parent;
	 while (y != nullptr && temp == y->right)
	 {
		temp = y;
		y = y->parent;
	 }
	 
	 return y->data;
 }

int RedBlackTree:: closestLess(int data){
	bool truth = false;
	NodeT* temp = my_search(root, data, truth);

	if(temp->left != nullptr)
		return maximum(temp->left)->data;
	
	NodeT* y = temp->parent;
	while (y != nullptr && temp == y->left)
	{
		temp = y;
		y = y->parent;
	}
	 
	return y->data;
}

NodeT* RedBlackTree::minimum(NodeT* node){
	while(node->left != nullptr){
		node = node->left;
	}
	return node;
}

NodeT* RedBlackTree::maximum(NodeT* node){
	while(node->right != nullptr){
		node = node->right;
	}
	return node;
}

int RedBlackTree::size() const{
    return numOfValues;
}


void RedBlackTree::left_rotate(NodeT* &root, NodeT* x){
    NodeT* y = x->right;
    x->right = y->left;
    if(y->left != nullptr)
        y->left->parent = x;
    
    y->parent = x->parent;
	if (x->parent == nullptr)
		root = y;
	else {
		if (x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;
	}
	y->left = x;
	x->parent = y;
}

void RedBlackTree::right_rotate(NodeT* &root, NodeT* y){
    NodeT* x = y->left;
    y->left = x->right;
    if (x->right != nullptr)
		x->right->parent = y;

	x->parent = y->parent;
	if (y->parent == nullptr)
		root = x;
	else {
		if  (y == y->parent->right)
			y->parent->right = x;
		else
			y->parent->left = x;
	}
	x->right = y;
	y->parent = x;
}

bool RedBlackTree::insert(const int& val){
    NodeT* z = new NodeT(val);
    my_insert(root, z);
	numOfValues++;
    return true;
}

void RedBlackTree::my_insert(NodeT* &root, NodeT* node){
    NodeT* x = root;
    NodeT* y = nullptr;
    
    while (x != nullptr)
	{
		y = x;
		if (node->data > x->data)
			x = x->right;
		else
			x = x->left;
	}
	node->parent = y;
	if(y!=nullptr)
	{
		if (node->data > y->data)
			y->right = node;
		else
			y->left = node;
	}
	else 
		root = node;

	node->isBlack = false;
	insertFix(root, node);
}

void RedBlackTree::insertFix(NodeT* &root, NodeT* node){
    NodeT* parent;
    parent = node->parent;
    while(node != this->root && parent->isBlack == false){
        NodeT* gparent = parent->parent;
        if(gparent->left == parent){
            NodeT* uncle = gparent->right;
            if(uncle != nullptr && uncle->isBlack == false)
			{
				parent->isBlack = true;
				uncle->isBlack = true;
				gparent->isBlack = false;
				node = gparent;
				parent = node->parent;
			}
			else
			{
				if (parent->right == node)
				{
					left_rotate(root, parent);
					swap(node, parent);
				}
				right_rotate(root, gparent);
				gparent->isBlack = false;
				parent->isBlack = true;
				break;
			}
        }
        else{
            NodeT*uncle = gparent->left;
			if (uncle != nullptr && uncle->isBlack == false)
			{
				gparent->isBlack = false;
				parent->isBlack = true;
				uncle->isBlack = true;

				node = gparent;
				parent = node->parent;
			}
			else
			{
				if (parent->left == node)
				{
					right_rotate(root, parent);
					swap(parent, node);
				}
				left_rotate(root, gparent);
				parent->isBlack = true;
				gparent->isBlack = false;
				break;
			}
        }
    }
    root->isBlack = true;
}

void RedBlackTree::swap(NodeT* node1, NodeT* node2){
    NodeT* temp = node1;
    node1 = node2;
    node2 = temp;
}

void RedBlackTree::print() {
	if (root == nullptr)
		cout << "empty RBtree\n";
	else
		print(root);
}


void RedBlackTree::print(NodeT* node)const {
	if (node == nullptr)
		return;
	if (node->parent == nullptr)
		cout << node->data << endl;
	else if(node->parent->left==node)
	{
		cout << node->data << " is "<<node->parent->data<<"'s "<<"left child" << endl;
	}
	else
	{
		cout << node->data <<" is " << node->parent->data << "'s " << "right child" << endl;
	}
	print(node->left);
	print(node->right);
}