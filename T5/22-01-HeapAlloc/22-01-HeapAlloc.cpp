#include <Windows.h>
#include <iostream>

using namespace std;

int main()
{
	int* a = nullptr;     // указатель на массив
	constexpr int size = 1000;   // размерность массива

    // получаем дескриптор кучи процесса, созданной по умолчанию
	const HANDLE h_heap = GetProcessHeap();
    if (!h_heap)
    {
        cout << "Heap create failed." << endl;
        return GetLastError();
    }
    // распределяем память под массив
    a = static_cast<int*>(HeapAlloc(h_heap, HEAP_ZERO_MEMORY, size * sizeof(int)));
    // распечатываем один элемент массива
    cout << "a[10] = " << a[10] << endl;
    // освобождаем память из кучи
    if (!HeapFree(h_heap, NULL, a))
    {
        cout << "Heap free failed." << endl;
        return GetLastError();
    }

    return 0;
}