#include "BinaryTree.h"


void test()
{
	char arr[10] = { '1', '2', '3', '#', '#', '4', '#', '#', '5', '6' };

	//Node<int>* root = new Node<int>;

	BinaryTree<char> Tree(arr, 10, '#');
	Tree.PreOrderTraverse();
	cout << endl;
	Tree.InsOrderTraverse();
	cout << endl;
	Tree.PosOrderTraverse();
	cout << endl;

	BinaryTree<char> tree2(Tree);
	tree2.PreOrderTraverse();
	cout << endl;
	BinaryTree<char> t3;
	t3 = Tree;
	t3.PreOrderTraverse();
	cout << endl;

	Tree.LevelOrder();

	Tree.PreOrder1();

	Tree.PosOrder();
	Tree.PosOrder1();
	Tree.InOrder();

}

void test1()
{
	char arr1[11] = { '1', '2', '3', '#', '#', '#', '4', '5', '#', '#', '6' };
	char arr2[12] = { '1', '2', '3', '#', '7', '#', '#', '4', '#', '#', '5', '6' };

	BinaryTree<char> Tree(arr1, 11, '#');
	BinaryTree<char> t(arr2, 12, '#');

	t.GetBinaryMirror_Nor();
	t.PreOder2();

	Tree.GetBinaryMirror_Nor();
	Tree.PreOder2();

// 	t.PreOrder1();
// 	t.PreOder2();
// 	Tree.PreOrder1();
// 	Tree.PreOder2();
// 	t.PosOrder();
// 	t.PosOrder1();
// 
// 	Tree.PosOrder();
// 	Tree.PosOrder1();

	// 	Node<char>* pCur1 = Tree.Find('6');
	// 	Node<char>* pCur2 = Tree.Find('2');
	// 
	// 	Tree.GetLatestAnceetorNode(pCur2, pCur1);
	// 	Tree.GetLatestAnceetorNode(pCur1, pCur1);
	// 
	// 	pCur1 = Tree.Find('1');
	// 	Tree.GetLatestAnceetorNode(pCur2, pCur1);
	// 	pCur1 = Tree.Find('2');
	// 	Tree.GetLatestAnceetorNode(pCur2, pCur1);


	//pCur = Tree.GetParent(pCur);

	//cout << Tree.GetKLevelNode(5) << endl;;

	// 	cout << Tree.GetHigh() << endl;
	// 	cout << Tree.GetLeaf1() << endl;
}

int main()
{

	test1();
	int a = 10;
	char b = a;

	cout << sizeof(a = a + b) << endl << a << endl;

	return 0;
}