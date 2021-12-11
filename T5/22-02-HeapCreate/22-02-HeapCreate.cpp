#include <Windows.h>
#include <iostream>

using namespace std;

int main()
{
	int* a = nullptr;        // указатель на массив
	constexpr int  h_size = 4096;    // размер кучи
	constexpr int  a_size = 2048;    // размер массива 

    // создаем кучу динамически
	HANDLE h_heap = HeapCreate(HEAP_NO_SERIALIZE, h_size, h_size);
    if (!h_heap)
    {
        cout << "Heap create failed." << endl;
        return GetLastError();
    }
    // распределям память под массив
    a = static_cast<int*>(HeapAlloc(h_heap, NULL, a_size));
    // обрабатываем ошибку в случае неудачи
    if (!a)
    {
        cout << "Heap allocation failed." << endl;
        return GetLastError();
    }
    // распечатываем распределённую память
    cout << "a[10] = " << a[10] << endl;
    // освобождаем память из кучи
    if (!HeapFree(h_heap, NULL, a))
    {
        cout << "Heap free failed." << endl;
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