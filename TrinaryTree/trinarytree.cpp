/* 

trinarytree.cpp

Functionality: 
* I used templates so that the trinary tree can be used with various datatypes
* inserts and deletes without problems
* the delete function is called by remove(DataType data)
* if a node with both a left and right subtree is deleted, the min of the right subtree takes its place
* if a node with only one child (i.e. one subtree) is deleted, the child takes its place
* to verify correct subtree order, print() prints the tree in level-order through a breadth first search
* the node I used to represent the end of a level is impossible to insert manually, so there will be no accidental newlines in printing

Known Limitations:
* No known limitation

*/

////////////////////////////////////
/*   HEADER FILE - DECLARATIONS   */
////////////////////////////////////

#include <iostream>
#include <queue> // for breath first search in level order printing
#include <limits> // for max datatype number in newline
using namespace std;

template <class DataType>
class Tree; // forward declaration to use Tree in Node

template <class DataType>
class Node{
private:
	DataType data;
	Node *leftChild;
	Node *rightChild;
	Node *middleChild;

public:
	Node(const DataType passedData, Node *left, Node *right, Node *middle);
	friend class Tree<DataType>;
};

template <class DataType>
class Tree{
private:
	Node<DataType> *root;

	//for nodes (internal) - recursive
	void deleteSubtree(Node<DataType> *&currentNode) const; // delete current node and children. used in destructor
	void insert(const DataType &passedData, Node<DataType> *&currentNode) const;
	void remove(const DataType &passedData, Node<DataType> *&currentNode) const;
	Node<DataType> *min(Node<DataType> *currentNode) const;
	// void print(Node<DataType> *currentNode) const; //prints level order

public:
	Tree();
	~Tree();
	void insert(const DataType &passedData);
	void remove(const DataType &passedData);
	void print() const; // prints level order
};


///////////////////////////////////////////
/*   IMPLEMENTATION FILE - DEFINITIONS   */
///////////////////////////////////////////

//Node Constructor
template <class DataType>
Node<DataType>::
Node(const DataType passedData, Node *left, Node *right, Node *middle){
	data = passedData;
	leftChild = left;
	rightChild = right;
	middleChild = middle;
}

//Tree Constructor
template <class DataType>
Tree<DataType>::
Tree(){
	root = NULL;
}

//Tree Destructor
template <class DataType>
Tree<DataType>::
~Tree(){
	deleteSubtree(root);
}

//delete subtree, starting with current node
template <class DataType>
void Tree<DataType>::
deleteSubtree(Node<DataType> *&currentNode) const{
	if(currentNode != NULL){
		deleteSubtree(currentNode->leftChild);
		deleteSubtree(currentNode->rightChild);
		delete currentNode;
	}

	currentNode = NULL;
}

//public call, which then calls recursive call starting from root
template <class DataType>
void Tree<DataType>::
insert(const DataType &passedData){
	insert(passedData, root);
}

//recursive insert, traverses tree until NULL node
template <class DataType>
void Tree<DataType>::
insert(const DataType &passedData, Node<DataType> *&currentNode) const{
	if(currentNode == NULL){
		currentNode = new Node<DataType>(passedData, NULL, NULL, NULL);
	}else if(passedData < currentNode->data){
		insert(passedData, currentNode->leftChild);
	}else if(passedData > currentNode->data){
		insert(passedData, currentNode->rightChild);
	}else{
		insert(passedData, currentNode->middleChild);
	}
}

//public delete, which then calls recursive call starting from root
template <class DataType>
void Tree<DataType>::
remove(const DataType &passedData){
	remove(passedData, root);
}

//recursive delete, traverses tree until it finds a match, then delets the deepest middleChild of the match.
template <class DataType>
void Tree<DataType>::
remove(const DataType &passedData, Node<DataType> *&currentNode) const {
	if(currentNode == NULL){
		return;
	}else if(passedData < currentNode->data){
		remove(passedData, currentNode->leftChild);
	}else if(passedData > currentNode->data){
		remove(passedData, currentNode->rightChild);
	}else if(currentNode->data == passedData && currentNode->middleChild){
		remove(passedData, currentNode->middleChild); // continue to middle leaf
	}else if(currentNode->data == passedData && currentNode->leftChild != NULL && currentNode->rightChild != NULL){ // delete this node, with no middle childe.
		currentNode->data = min(currentNode->rightChild)->data; // replace deleted node with min of right subtree
		remove(currentNode->data, currentNode->rightChild); // delete the the replacing node from its origin
		while(min(currentNode->rightChild)->data == currentNode->data){ // if it has any middleChildren, move them over as well
			remove(currentNode->data, currentNode->rightChild);
			insert(currentNode->data, currentNode->middleChild);
		}
	}else{ // delete leaf node
		Node<DataType> *temp = currentNode;

		if(currentNode->leftChild != NULL){
			currentNode = currentNode->leftChild;
		}else{
			currentNode = currentNode->rightChild;
		}

		delete temp;
	}
}

//used to find min of right subtree
template <class DataType>
Node<DataType> *Tree<DataType>::
min(Node<DataType> *currentNode) const {
	if(currentNode == NULL){
		return NULL;
	}else if(currentNode->leftChild == NULL){
		return currentNode;
	}else{
		return min(currentNode->leftChild);
	}
}

//print level order traversal of tree
//insert impossible node of max possible value of datatype with root as sibling for newline signal (after each level)
template <class DataType>
void Tree<DataType>::
print() const {
	if(root == NULL){
		cout << "Nothing in Tree" << endl;
	}else{
		queue<Node<DataType>*> printQueue;
		Node<DataType> *newline = new Node<DataType>(numeric_limits<DataType>::max(), root, root, root); // least likely to be used

		printQueue.push(root);
		printQueue.push(newline);
		while(!printQueue.empty()){
			Node<DataType> *currentNode = printQueue.front();
			printQueue.pop();

			if(currentNode == newline){
				cout << endl;
				if(!printQueue.empty())
					printQueue.push(newline);
			}else{
				cout << currentNode->data << ' ';

				if(currentNode->leftChild != NULL)
					printQueue.push(currentNode->leftChild);
				if(currentNode->middleChild != NULL)
					printQueue.push(currentNode->middleChild);
				if(currentNode->rightChild != NULL)
					printQueue.push(currentNode->rightChild);
			}
		}
		delete newline;
	}
}


///////////////////////////////////
/*   MAIN FUNCTION - EXECUTION   */
///////////////////////////////////

int main(){
	Tree<int> tree;

	tree.insert(5);
	tree.insert(4);
	tree.insert(9);
	tree.insert(5);
	tree.insert(7);
	tree.insert(2);
	tree.insert(2);
	tree.insert(6);
	tree.insert(6);
	tree.insert(6);
	tree.insert(6);

	cout << endl << "print" << endl;
	tree.print();
	cout << endl;

	cout << "delete 5" << endl;
	tree.remove(5);
	cout << endl;
	cout << endl;

	cout << endl << "print" << endl;
	tree.print();
	cout << endl;

	cout << "delete other 5" << endl;
	tree.remove(5);

	cout << endl << "print" << endl;
	tree.print();

	cout << endl << "Correct!" << endl;

	return 0;
}