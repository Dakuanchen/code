#include "HuffmanTree.hpp"

void Test()
{
// 	int arr[] = { 18, 56, 96, 7, 5, 21, 58, 69, 32, 14, 25, 86, 41, 55, 33, 85 };
// 	Heap<int, Greater<int>> BigHeap(arr, sizeof(arr) / sizeof(arr[0]));
// 	Heap<int, Less<int>> SmallHeap(arr, sizeof(arr) / sizeof(arr[0]));
	Heap<int> h;

	//h.FindKBigNumber(arr, sizeof(arr) / sizeof(arr[0]), 20);

	h.Push(1);
	h.Push(2);
	h.Push(3);
	h.Push(4);
	h.Push(5);
	h.Pop();
	h.Pop();
	h.Pop();
	h.Pop();
	h.Pop();
	h.Pop();
// 	BigHeap.Pop();
// 	SmallHeap.Pop();
// 
// 	BigHeap.Push(100);
// 	SmallHeap.Push(3);

}


int main()
{
	char a = -1;
	char b = -128;
	//test1();
	//Test();
	//Test2();
	return 0;
}