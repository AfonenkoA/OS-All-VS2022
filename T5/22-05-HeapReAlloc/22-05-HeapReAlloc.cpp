#include <Windows.h>
#include <iostream>

using namespace std;

int main()
{
	int* a = nullptr;        // указатель на массив
	constexpr int  h_size = 4096;    // размер кучи
	constexpr int  a_size = 5;       // размер массива

    // создаем кучу динамически
    HANDLE h_heap = HeapCreate(HEAP_NO_SERIALIZE | HEAP_GENERATE_EXCEPTIONS,
                              h_size, 0);
    if (!h_heap)
    {
        cout << "Heap create failed." << endl;
        return GetLastError();
    }
    // распределяем память из кучи
    a = static_cast<int*>(HeapAlloc(h_heap, NULL, a_size * sizeof(int)));
    // инициализируем и распечатываем массив
    for (int i = 0; i < a_size; i++)
    {
        a[i] = i;
        cout << "a[" << i << "] = " << a[i] << endl;
    }
    // распределяем дополнительный блок
    a = (int*)HeapReAlloc(h_heap, HEAP_ZERO_MEMORY, a,
                          2 * a_size * sizeof(int));
    // распечатываем элементы массива
    for (auto i = 0; i < 2 * a_size; i++)
        cout << "\ta[" << i << "] = " << a[i] << endl;
    // разрушаем кучу
    if (!HeapDestroy(h_heap))
    {
        cout << "Heap destroy failed." << endl;
        return GetLastError();
    }

    return 0;
}