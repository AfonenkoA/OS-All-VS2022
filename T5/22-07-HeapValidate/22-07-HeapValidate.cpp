#include <Windows.h>
#include <iostream>

using namespace std;

int main()
{
	const int* a = nullptr;    // указатель на массив
	constexpr int  size = 4096;  // размер кучи

    // создаем кучу динамически
	const HANDLE hHeap = HeapCreate(HEAP_NO_SERIALIZE, size, 0);
    if (!hHeap)
    {
        cout << "Heap create failed." << endl;
        return GetLastError();
    }
    // распределяем память под массивы
    a = static_cast<int*>(HeapAlloc(hHeap, NULL, 4 * sizeof(int)));
    // проверяем состояние распределенного блока памяти
    if (!HeapValidate(hHeap, HEAP_NO_SERIALIZE, a))
        cout << "The block is bad." << endl;
    else
        cout << "The block is good." << endl;

    // разрушаем кучу
    HeapDestroy(hHeap);

    return 0;
}