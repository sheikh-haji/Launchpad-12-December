#include <iostream>
#include <queue>

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

int countNodes(node* root){
	if(root==NULL){
		return 0;
	}

	int leftCount = countNodes(root->left);
	int rightCount = countNodes(root->right);

	int totalCount = leftCount + 1 + rightCount;
	return totalCount;
}

// L R N
void postOrder(node* root){
	if(root==NULL){
		return;
	}

	postOrder(root->left);
	postOrder(root->right);
	cout<<root->data<<" ";
}

int sumOfNodes(node* root){
	if(root==NULL){
		return 0;
	}

	int leftSum = sumOfNodes(root->left);
	int rightSum = sumOfNodes(root->right);

	int totalSum = leftSum + root->data + rightSum;
	return totalSum;
}

int height(node* root){
	if(root==NULL){
		return -1;
	}

	int leftHeight = height(root->left);
	int rightHeight = height(root->right);

	int totalHeight = max(leftHeight,rightHeight) + 1;
	return totalHeight;
}

bool search(node* root,int item){
	if(root==NULL){
		return false;
	}

	if(root->data==item){
		return true;
	}

	bool leftSearch = search(root->left,item);
	bool rightSearch = search(root->right,item);

	// if(leftSearch or rightSearch){
	// 	return true;
	// }

	// return false;
	return leftSearch or rightSearch;
}

void levelOrder(node* root){

	queue<node*> q;

	q.push(root);

	while(!q.empty()){

		node* temp = q.front();
		q.pop();

		cout<<temp->data<<" ";

		if(temp->left){
			q.push(temp->left);
		}

		if(temp->right){
			q.push(temp->right);
		}
	}

	cout<<endl;
}

int diameter(node* root){
	if(root==NULL){
		return 0;
	}

	int leftDiameter = diameter(root->left);
	int rightDiameter = diameter(root->right);

	int leftHeight = height(root->left);
	int rightHeight = height(root->right);

	int meraDia = leftHeight + rightHeight + 2;

	int totalDiameter = max(meraDia,max(leftDiameter,rightDiameter));
	return totalDiameter;
}		

class DiaHeight{
public:
	int diameter;
	int height;
};

DiaHeight diameterOptimized(node* root){
	DiaHeight val;

	if(root==NULL){
		val.diameter = 0;
		val.height = -1;
		return val;
	}

	DiaHeight leftPair = diameterOptimized(root->left);
	DiaHeight rightPair = diameterOptimized(root->right);

	val.diameter = max(leftPair.diameter,max(rightPair.diameter,leftPair.height + rightPair.height + 2));
	val.height = max(leftPair.height,rightPair.height) + 1;

	return val;
}

bool isHeightBalanced(node* root){
	if(root==NULL){
		return true;
	}

	bool leftBalanced = isHeightBalanced(root->left);
	bool rightBalanced = isHeightBalanced(root->right);

	if(!leftBalanced or !rightBalanced){
		return false;
	}

	int leftHeight = height(root->left);
	int rightHeight = height(root->right);

	int diff = abs(leftHeight - rightHeight);

	if(diff>1){
		return false;
	}else{
		return true;
	}
}

void printRootToLeaf(node* root,string path){
	if(root==NULL){
		return;
	}

	string val = to_string(root->data);

	if(root->left==NULL and root->right==NULL){
		path = path + val;
		cout<<path<<endl;
		return;
	}

	printRootToLeaf(root->left,path + val);
	printRootToLeaf(root->right,path + val);
}

node* lca(node* root,int data1,int data2){
	if(root==NULL){
		return NULL;
	}

	if(root->data == data1 or root->data == data2){
		return root;
	}

	node* leftLCA = lca(root->left,data1,data2);
	node* rightLCA = lca(root->right,data1,data2);

	if(leftLCA!=NULL and rightLCA!=NULL){
		return root;
	}

	if(leftLCA==NULL and rightLCA==NULL){
		return NULL;
	}

	return leftLCA!=NULL ? leftLCA : rightLCA;
}

int main(){

	node* root = NULL;
	root = buildTree(root);

	// preOrder(root);
	// cout<<endl;
	// inOrder(root);
	// cout<<endl;
	// postOrder(root);
	// cout<<endl;

	// cout<<countNodes(root)<<endl;
	// cout<<sumOfNodes(root)<<endl;

	// cout<<search(root,3)<<endl;
	// cout<<height(root)<<endl;

	// levelOrder(root);

	// cout<<diameter(root)<<endl;
	// DiaHeight val = diameterOptimized(root);
	// cout<<val.diameter<<endl;
	// cout<<val.height<<endl;

	// cout<<isHeightBalanced(root)<<endl;

	// printRootToLeaf(root,"");

	node* val = lca(root,6,5);
	cout<<val->data<<endl;
	return 0;
}

// Input Tree
// 4 2 1 -1 -1 3 -1 -1 6 5 -1 -1 7 -1 -1

// 1 -1 2 3 -1 5 6 -1 -1 7 -1 -1 4 -1 -1

// Balanced Input
// 1 2 -1 -1 3 -1 4 -1 6 -1 -1