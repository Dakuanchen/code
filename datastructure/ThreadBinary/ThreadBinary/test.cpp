#include "ThreadBinary.h"

void test()
{
	char arr1[] = { '1', '2', '3', '#', '#', '#', '4', '5', '#', '#', '6' };
	char arr2[] = { '1', '2', '3', '#', '7', '#', '#', '4', '#', '#', '5', '6' };

	ThreadBinary<char> t1(arr1, sizeof(arr1) / sizeof(arr1[0]), '#');
	ThreadBinary<char> t2(arr2, sizeof(arr2) / sizeof(arr2[0]), '#');

// 	t1.PreThread();
// 	t2.PreThread();
// 	t1.Preorder();
// 	t2.Preorder();
 
 	t1.InThread();
 	t2.InThread();
	t1.InOrder();
	t2.InOrder();

// 	t1.PosThread();
// 	t2.PosThread();
}

int main()
{
	test();
	
	return 0;
}