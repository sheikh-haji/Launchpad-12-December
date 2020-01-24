#include <iostream>

using namespace std;

class node{
public:
	int data;
	node* left;
	node* right;

	node(int data){
		this->data = data;
		this->left = NULL;
		this->right = NULL;
	}
};

node* buildTree(node* root){
	int data;
	cin>>data;

	if(data==-1){
		return NULL;
	}

	if(root==NULL){
		root = new node(data);
	}

	root->left = buildTree(root->left);
	root->right = buildTree(root->right);

	return root;
}

node* buildBST(node* root,int data){
	if(root==NULL){
		node* n = new node(data);
		root = n;
		return root;
	}

	if(data > root->data){
		root->right = buildBST(root->right,data);
	}else{
		root->left = buildBST(root->left,data);
	}

	return root;
}

node* insert(){
	node* root = NULL;

	int data;
	cin>>data;

	while(data!=-1){

		root = buildBST(root,data);

		cin>>data;
	}

	return root;
}

void preOrder(node*root){
	if(root==NULL){
		return;
	}

	cout<<root->data<<" ";
	preOrder(root->left);
	preOrder(root->right);
}

void inOrder(node*root){
	if(root==NULL){
		return;
	}

	inOrder(root->left);
	cout<<root->data<<" ";
	inOrder(root->right);
}

bool search(node* root,int item){
	if(root==NULL){
		return false;
	}

	if(root->data==item){
		return true;
	}

	if(item > root->data){
		return search(root->right,item);
	}else{
		return search(root->left,item);
	}
}

bool isBST(node* root,int minRange = INT_MIN,int maxRange = INT_MAX){
	if(root==NULL){
		return true;
	}

	bool leftBST = isBST(root->left,minRange,root->data);
	bool rightBST = isBST(root->right,root->data,maxRange);

	if(leftBST and rightBST and root->data > minRange and root->data < maxRange){
		return true;
	}else{
		return false;
	}
}

class TreeDetail{
public:
	bool bst;
	int size;
	int maxValue;
	int minValue;
};

TreeDetail largestBstInABinaryTree(node* root){

	TreeDetail val;

	if(root==NULL){

		val.bst = true;
		val.size = 0;
		val.minValue = INT_MAX;
		val.maxValue = INT_MIN;
		return val;
	}

	TreeDetail leftStatus = largestBstInABinaryTree(root->left);
	TreeDetail rightStatus = largestBstInABinaryTree(root->right);

	if(!leftStatus.bst or !rightStatus.bst or root->data < leftStatus.maxValue or root->data > rightStatus.minValue){

		val.bst = false;
		val.size = max(leftStatus.size,rightStatus.size);
		return val;
	}

	val.bst = true;
	val.size = leftStatus.size + rightStatus.size + 1;

	val.minValue = root->left==NULL ? root->data : leftStatus.minValue;

	val.maxValue = root->right == NULL ? root->data : rightStatus.maxValue;

	return val;
}

int main(){

	// node* root = insert();

	node* root = NULL;
	root = buildTree(root);

	// preOrder(root);
	// cout<<endl;

	// inOrder(root);
	// cout<<endl;

	// cout<<search(root,5)<<endl;
	// cout<<search(root,15)<<endl;

	// cout<<isBST(root)<<endl;

	TreeDetail val = largestBstInABinaryTree(root);

	cout<<val.size<<endl;

	return 0;
}

// 4 2 6 1 3 5 7 -1

// Input for largest bst in a bt
// 8 4 2 1 -1 -1 3 -1 -1 6 5 -1 -1 7 -1 -1 9 7 -1 -1 10 -1 -1