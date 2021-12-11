#include <Windows.h>
#include <iostream>

using namespace std;

int main()
{
	int* a = nullptr;      // указатель на массив
	const int  size = 4096;    // размер массива, а также кучи

    // создаем кучу динамически
    HANDLE h_heap = HeapCreate(HEAP_NO_SERIALIZE, size, size);
    if (!h_heap)
    {
        cout << "Heap create failed." << endl;
        return GetLastError();
    }
    // пытаемся распределить память под массив
    a = static_cast<int*>(HeapAlloc(h_heap, NULL, size * sizeof(int)));
    // обрабатываем ошибку в случае неудачи
    if (!a)
    {
        cout << "Heap allocation failed." << endl;
        return GetLastError();
    }
    // разрушаем кучу
    if (!HeapDestroy(h_heap))
    {
        cout << "Heap destroy failed." << endl;
        return GetLastError();
    }

    return 0;
}