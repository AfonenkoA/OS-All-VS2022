#include <Windows.h>
#include <iostream>

using namespace std;

int main()
{
	int* a = nullptr;    // указатель на массив
    int* b = nullptr;    // указатель на массив
	const int* c = nullptr;    // указатель на массив
	constexpr int  size = 4096;  // размер кучи

	// создаем кучу динамически
	const HANDLE hHeap = HeapCreate(HEAP_NO_SERIALIZE, size, size);
    if (!hHeap)
    {
        cout << "Heap create failed." << endl;
        return GetLastError();
    }
    // распределям память под массивы
    a = static_cast<int*>(HeapAlloc(hHeap, NULL, 1024));
    cout << "a = " << a << endl;
    b = static_cast<int*>(HeapAlloc(hHeap, NULL, 1024));
    cout << "b = " << b << endl;
    c = static_cast<int*>(HeapAlloc(hHeap, NULL, 1024));
    cout << "c = " << c << endl << endl;

    // проверяем, сколько осталось свободного места в куче
    SIZE_T free = HeapCompact(hHeap, HEAP_NO_SERIALIZE);
    if (!free)
    {
        cout << "Heap compact failed." << endl;
        return GetLastError();
    }
	cout << "Free: " << free << endl;

	// освобождаем первых два массива
    HeapFree(hHeap, NULL, b);
    HeapFree(hHeap, NULL, a);

    // уплотняем кучу
    free = HeapCompact(hHeap, HEAP_NO_SERIALIZE);
    if (!free)
    {
        cout << "Heap compact failed." << endl;
        return GetLastError();
    }
	cout << "Free: " << free << endl;

	// разрушаем кучу
    HeapDestroy(hHeap);

    return 0;
}