# include <bits/stdc++.h>

using namespace std;

int itr = 0;
int arr[] = {7,5,10,3,6,9,12};
int size = sizeof(arr)/sizeof(arr[0]);


typedef struct Node
{
	int data;
	struct Node* left;
	struct Node* right;

}node;

node* getNode()
{
	node* newnode = (node*)malloc(sizeof(node));
	return newnode;
}

void readNode(node* newnode)
{
	newnode->data = arr[itr];
	newnode->left = NULL;
	newnode->right = NULL;
	itr = itr + 1;
}

node* insertNode(node* btree,node* newnode)
{
	if(btree == NULL)
	{
		return newnode;
	}
	else if(newnode->data > btree->data)
	{
		btree->right =  insertNode(btree->right,newnode);
	}
	else if(newnode->data < btree->data)
	{
		btree->left =  insertNode(btree->left,newnode);
	}
	else if(newnode->data == btree->data)
	{
		cout << "data already exist" << endl;
		return btree;
	}
	return btree;
}

node* createBtree()
{
	node* btree = NULL;
	for(int i=0;i<size;i++)
	{
		node* newnode = getNode();
		readNode(newnode);
		btree = insertNode(btree,newnode);
	}
	return btree;
}

void inorder(node* newnode)
{
	if(newnode != NULL)
	{
		inorder(newnode->left);
		cout << newnode->data << " ";
		inorder(newnode->right);
	}
}

void preorder(node* newnode)
{
	if(newnode != NULL)
	{
		cout << newnode->data << " ";
		preorder(newnode->left);
		preorder(newnode->right);
	}
}

void postorder(node* newnode)
{
	if(newnode != NULL)
	{
		postorder(newnode->left);
		postorder(newnode->right);
		cout << newnode->data << " ";
	}
}

int heightOfTree(node* root)
{
	if(root == NULL)
	{
		return 0;
	}

	int lh = heightOfTree(root->left);
	int rh = heightOfTree(root->right);

	return 1 + max(lh,rh);
}

int diameterOfTree(node* root)
{
	if(root == NULL)
	{
		return 0;
	}

	int lh = heightOfTree(root->left);
	int rh = heightOfTree(root->right);

	int ldia = diameterOfTree(root->left);
	int rdia = diameterOfTree(root->right);

	return max(1+lh+rh,max(ldia,rdia));
}

int distanceFromRoot(node* root,int x)
{
	if(x > root->data)
	{
		return 1 + distanceFromRoot(root->right,x);
	}
	else if(x < root->data)
	{
		return 1 + distanceFromRoot(root->left,x);
	}

	return 0;
}

int distBetween2Nodes(node* root,int a,int b)
{
	if(root == NULL)
	{
		return 0;
	}

	if(a > b)
	{
		swap(a,b);
	}

	if(a < root->data && b < root->data)
	{
		return distBetween2Nodes(root->left,a,b);
	}

	if(a > root->data && b > root->data)
	{
		return distBetween2Nodes(root->right,a,b);
	}

	if(a <= root->data && b >= root->data)
	{
		return distanceFromRoot(root,a) + distanceFromRoot(root,b);
	}

	return 0;
}

void printAtLevelK(node* root,int k)
{
	if(root == NULL)
	{
		return;
	}

	if(k == 0)
	{
		cout << root->data << " ";
	}

	k = k - 1;
	printAtLevelK(root->left,k);
	printAtLevelK(root->right,k);
}

bool isBalanced(node* root)
{
	if(root == NULL)
	{
		return true;
	}

	int lh = heightOfTree(root->left);
	int rh = heightOfTree(root->right);

	if(abs(lh-rh) <= 1 && isBalanced(root->left) == true && isBalanced(root->right) == true)
	{
		return true;
	}

	return false;
}

bool findPath(node* root,vector<int> &path,int k)
{
	if(root == NULL)
	{
		return false;
	}
	path.push_back(root->data);

	if(root->data == k)
	{
		return true;
	}

	if(root->left != NULL)
	{
		bool res = findPath(root->left,path,k);

		if(res == true )
		{
			return true;
		}
	}

	if(root->right != NULL)
	{
		bool res = findPath(root->right,path,k);
		if(res == true)
		{
			return true;
		}
	}

	path.pop_back();

	return false;
}

int findLCA(node* root,int n1,int n2)
{
	vector<int> path1;
	vector<int> path2;

	if(findPath(root,path1,n1) == false || findPath(root,path2,n2) == false)
	{
		return -1;
	}

	int i;

	for(i=0;i<path1.size() && i<path2.size();i++)
	{
		if(path1[i] != path2[i])
		{
			break;
		}
	}

	return path1[i-1];
}

bool isCproperty(node* root)
{
	if(root == NULL)
	{
		return true;
	}

	int sum = 0;
	if(root->left != NULL)
	{
		sum = sum + root->left->data;
	}

	if(root->right != NULL)
	{
		sum = sum + root->right->data;
	}

	if(sum == root->data && isCproperty(root->left) && isCproperty(root->right))
	{
		return true;
	}

	return false;
}

int main()
{
	node* btree = createBtree();
	cout << "----" << endl;
	cout << "inorder => ";
	inorder(btree);
	cout << endl;
	cout << "preorder => ";
	preorder(btree);
	cout << endl;
	cout << "postorder => ";
	postorder(btree);
	cout << endl;
	cout << "----" << endl;
	cout << "heightOfTree => " << heightOfTree(btree) << endl;
	cout << "diameterOfTree => " << diameterOfTree(btree) << endl;
	cout << "----" << endl;
	cout << "distanceFromRoot => " << distanceFromRoot(btree,3) << endl;
	cout << "distBetween2Nodes => " << distBetween2Nodes(btree,3,10) << endl;
	cout << "----" << endl;
	cout << "printAtLevelK => ";
	printAtLevelK(btree,1);
	cout << endl; 
	cout << "----" << endl;
	cout << "isBalanced => " << isBalanced(btree) << endl;
	cout << "----" << endl;
	cout << "findLCA => " << findLCA(btree,9,12) << endl;
	cout << "----" << endl;

	return 0;
}