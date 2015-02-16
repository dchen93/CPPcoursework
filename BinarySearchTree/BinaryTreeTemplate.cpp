////////////////////////////////////
/*   HEADER FILE - DECLARATIONS   */
////////////////////////////////////

#include <iostream>
using namespace std;

template <class DataType>
class Tree; // forward declaration to use Tree in Node

template <class DataType>
class Node{
private:
	DataType data;
	Node *leftChild;
	Node *rightChild;
	int count; // allows duplicates in the node, just increases count

public:
	Node(const DataType passedData, Node *left, Node *right);
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
	Node<DataType> *max(Node<DataType> *currentNode) const;	
	const DataType &data(Node<DataType> *currentNode) const; // returns data in the node
	Node<DataType> *find(const DataType &passedData, Node<DataType> *currentNode) const;
	void printInc(Node<DataType> *currentNode) const; //prints in increasing order
	void printDec(Node<DataType> *currentNode) const; //prints in decreasing order



public:
	Tree();
	~Tree();
	void insert(const DataType &passedData);
	void remove(const DataType &passedData);
	bool find(const DataType &passedData); // returns true if found
	const DataType &extreme(bool minMax = false) const; //false for min, true for max. default is min
	void print(bool incDec = false) const; //if false, increasing order, if true, decreasing order. default is increasing
};


///////////////////////////////////////////
/*   IMPLEMENTATION FILE - DEFINITIONS   */
///////////////////////////////////////////

//Node Constructor
template <class DataType>
Node<DataType>::
Node(const DataType passedData, Node *left, Node *right){
	data = passedData;
	leftChild = left;
	rightChild = right;
	count = 1;
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

template <class DataType>
void Tree<DataType>::
insert(const DataType &passedData){
	insert(passedData, root);
}

template <class DataType>
void Tree<DataType>::
insert(const DataType &passedData, Node<DataType> *&currentNode) const{
	if(currentNode == NULL){
		currentNode = new Node<DataType>(passedData, NULL, NULL);
	}else if(passedData < currentNode->data){
		insert(passedData, currentNode->leftChild);
	}else if(passedData > currentNode->data){
		insert(passedData, currentNode->rightChild);
	}else{
		currentNode->count++;
	}
}

template <class DataType>
void Tree<DataType>::
remove(const DataType &passedData){
	remove(passedData, root);
}

template <class DataType>
void Tree<DataType>::
remove(const DataType &passedData, Node<DataType> *&currentNode) const {
	if(currentNode == NULL){
		return;
	}else if(passedData < currentNode->data){
		remove(passedData, currentNode->leftChild);
	}else if(passedData > currentNode->data){
		remove(passedData, currentNode->rightChild);
	}else if(currentNode->data == passedData && currentNode->count > 1){
		currentNode->count--;
	}else if(currentNode->data == passedData && currentNode->leftChild != NULL && currentNode->rightChild != NULL){
		currentNode->data = min(currentNode->rightChild)->data;
		currentNode->count = min(currentNode->rightChild)->count;
		remove(currentNode->data, currentNode->rightChild);
	}else{
		Node<DataType> *temp = currentNode;

		if(currentNode->leftChild != NULL){
			currentNode = currentNode->leftChild;
		}else{
			currentNode = currentNode->rightChild;
		}

		delete temp;
	}
}

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

template <class DataType>
Node<DataType> *Tree<DataType>::
max(Node<DataType> *currentNode) const {
	if(currentNode == NULL){
		return NULL;
	}else if(currentNode->rightChild == NULL){
		return currentNode;
	}else{
		return max(currentNode->rightChild);
	}
}

template <class DataType>
const DataType &Tree<DataType>::
extreme(bool minMax) const {
	if(minMax == false){
		return data(min(root));
	}else{
		return data(max(root));
	}
}

template <class DataType>
bool Tree<DataType>::
find(const DataType &passedData){
	if(find(passedData, root)){
		return true;
	}else{
		return false;
	}
}

template <class DataType>
const DataType &Tree<DataType>::
data(Node<DataType> *currentNode) const {
	return currentNode->data;
}

template <class DataType>
Node<DataType> *Tree<DataType>::
find(const DataType &passedData, Node<DataType> *currentNode) const {
	if(currentNode == NULL){
		return NULL;
	}else if(passedData < currentNode->data){
		return find(passedData, currentNode->leftChild);
	}else if(passedData > currentNode->data){
		return find(passedData, currentNode->rightChild);
	}else{
		return currentNode;
	}
}

template <class DataType>
void Tree<DataType>::
print(bool maxMin) const {
	if(root == NULL){
		cout << "Nothing in Tree" << endl;
	}else{
		if(maxMin == false){
			printInc(root);
		}else{
			printDec(root);
		}
	}
}

template <class DataType>
void Tree<DataType>::
printInc(Node<DataType> *currentNode) const {
	if(currentNode != NULL){
		printInc(currentNode->leftChild);
		for(int i = 0; i < currentNode->count; i++){
			cout << currentNode->data << endl;
		}
		printInc(currentNode->rightChild);
	}
}

template <class DataType>
void Tree<DataType>::
printDec(Node<DataType> *currentNode) const {
	if(currentNode != NULL){
		printDec(currentNode->rightChild);
		for(int i = 0; i < currentNode->count; i++){
			cout << currentNode->data << endl;
		}
		printDec(currentNode->leftChild);
	}
}



///////////////////////////////////
/*   MAIN FUNCTION - EXECUTION   */
///////////////////////////////////

int main(){
	Tree<int> tree;

	tree.insert(4);
	tree.insert(5);
	tree.insert(4);
	tree.insert(8);
	tree.insert(1234);

	cout << "find 8 " << endl;
	if(tree.find(8) == true){
		cout << "success!" << endl;
	}else{
		cout << "find doesn't work properly" << endl;
	}
	cout << endl;

	cout << "8 is deleted." << endl;
	tree.remove(8);

	cout << endl << "min and max" << endl;
	cout << tree.extreme() << " and " << tree.extreme(true) << endl << endl;

	cout << "print inc" << endl;
	tree.print();

	cout << endl;
	cout << "one 4 is deleted." << endl;
	tree.remove(4);

	cout << endl << "print dec" << endl;
	tree.print(true);

	return 0;
}