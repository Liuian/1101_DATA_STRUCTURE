#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
using namespace std;

//string output;
//ofstream OutputFile(output);
//fstream OutputFile;

/* A binary tree node has data, pointer to left child and a pointer to right child */
class node{
    public:
    int data;
    node* left;
    node* right;
};

/* Helper function that allocates a new node with the given data and NULL left and right pointers. */
node* newNode(int data){
    node* Node = new node();
    Node->data = data;
    Node->left = NULL;
    Node->right = NULL;
    return (Node);
}

/* UTILITY FUNCTIONS */
/* Function to find index of value in arr[start...end] The function assumes that value is present in in[] */
int search(int arr[], int strt, int end, int value){
    int i;
    for (i = strt; i <= end; i++){
        if (arr[i] == value)
            return i;
    }
}

/* Recursive function to construct binary of size len from Inorder traversal in[] and Preorder traversal pre[]. Initial values of inStrt and inEnd should be 0 and len -1. The function doesn't do any error checking for cases where inorder and preorder do not form a tree */
int preIndex;
node* buildTreePre(int in[], int pre[], int inStrt, int inEnd){
	if (inStrt > inEnd)
		return NULL;
	/* Pick current node from Preorder traversal using preIndex and increment preIndex */
	node* tNode = newNode(pre[preIndex++]);
	/* If this node has no children then return */
	if (inStrt == inEnd)
		return tNode;
	/* Else find the index of this node in Inorder traversal */
	int inIndex = search(in, inStrt, inEnd, tNode->data);
	/* Using index in Inorder traversal, construct left and right subtress */
	tNode->left = buildTreePre(in, pre, inStrt, inIndex - 1);
	tNode->right = buildTreePre(in, pre, inIndex + 1, inEnd);
	return tNode;
}
/*----------------------------to change--------------------*/
/* Recursive function to construct binary of size len from Inorder traversal in[] and Preorder traversal pre[]. Initial values of inStrt and inEnd should be 0 and len -1. The function doesn't do any error checking for cases where inorder and preorder do not form a tree */
int postIndex;
node* buildTreePost(int in[], int post[], int inStrt, int inEnd){
	if (inStrt > inEnd)
        return NULL;
	/* Pick current node from Preorder traversal using preIndex and increment preIndex */
    node* tNode = newNode(post[postIndex--]);
	/* If this node has no children then return */
    if (inStrt == inEnd)
        return tNode;
	/* Else find the index of this node in Inorder traversal */
    int inIndex = search(in, inStrt, inEnd, tNode->data);
	/* Using index in Inorder traversal, construct left and right subtress */
    tNode->right = buildTreePost(in, post, inIndex + 1, inEnd);
    tNode->left = buildTreePost(in, post, inStrt, inIndex - 1);
	return tNode;
}

fstream OutputFile;
/* This function is here just to test buildTree() */
//print the tree in post order
void printPostorder(node* node, string output){
    if (node == NULL)
        return;
    /* first recur on left child */
    printPostorder(node->left, output);
    /* now recur on right child */
    printPostorder(node->right, output);
    /* then print the data of node */
	OutputFile.open(output, ios::app);
	OutputFile << node->data <<" ";
	OutputFile.close();
}

/* This function is here just to test buildTree() */
//print the tree in pre order
void printPreorder(node* node, string output){
    if (node == NULL)
        return;
	OutputFile.open(output, ios::app);
	OutputFile << node->data <<" ";
	OutputFile.close();
    /* first recur on left child */
    printPreorder(node->left, output);
    /* now recur on right child */
    printPreorder(node->right, output);
}

int main(){
	//open the indicated file from the command line
	cout << "please type input file's name : ";
	string input;
	cin >> input;
	ifstream InputFile(input);
	if(!InputFile.is_open()) 
		cout << "fild open fail";
	//create output file
	string output = "out";
	int length = input.length();
	output.append(input, 2, length - 2);
	OutputFile.open(output, ios::out);
	OutputFile.close();
	//begin to read the data from the input file
	int round;
	InputFile >> round;
	for(int i = 0; i < round; i++){
		string str;
		InputFile >> str;
		int NodeCount;
		InputFile >> NodeCount;
		int first[NodeCount];
		int second[NodeCount];
		for(int j = 0; j < NodeCount; j++){
			InputFile >> first[j];
		}
		for(int k = 0; k < NodeCount; k++){
			InputFile >> second[k];
		}
		node* root = NULL;
		//judge the input file is what kind of file
		if(str == "preorder-inorder"){
			preIndex = 0;
			//build the binary tree
			root = buildTreePre(second, first, 0, NodeCount - 1);
			//print the tree in post - order
			printPostorder(root, output);
			OutputFile.open(output, ios::app);
			OutputFile << '\n';
			OutputFile.close();
			//cout << '\n';
			//OutputFile << '\n';
		}
		if(str == "postorder-inorder"){
			postIndex = NodeCount - 1;
			//build the binary tree
			root = buildTreePost(second, first, 0, NodeCount - 1);
			//print the tree in pre - order
			printPreorder(root, output);
			OutputFile.open(output, ios::app);
			OutputFile << '\n';
			OutputFile.close();
			//OutputFile << '\n';
			//cout << '\n';
		}
	}
	return 0;
}
