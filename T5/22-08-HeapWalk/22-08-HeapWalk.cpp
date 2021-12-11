#include <Windows.h>
#include <iostream>

using namespace std;

int main()
{
	constexpr int  size = 4096;            // размер кучи
	const int * a = nullptr;
	const int* b = nullptr;   // указатели на массивы
    PROCESS_HEAP_ENTRY  phe;     // состояние элемента кучи

    // создаем кучу динамически
	const HANDLE hHeap = HeapCreate(HEAP_NO_SERIALIZE, size, 0);
    // распределям память под массивы
    a = static_cast<int*>(HeapAlloc(hHeap, NULL, 4 * sizeof(int)));
    b = static_cast<int*>(HeapAlloc(hHeap, NULL, 16 * sizeof(int)));
    // инициализируем цикл проверки состояния кучи
    phe.lpData = nullptr;
    // проверяем состояние элементов кучи
    while (HeapWalk(hHeap, &phe))
    {
        if (phe.wFlags & PROCESS_HEAP_REGION)
	        std::cout << "PROCESS_HEAP_REGION flag is set." << endl;
        if (phe.wFlags & PROCESS_HEAP_UNCOMMITTED_RANGE)
            cout << "PROCESS_HEAP_UNCOMMITTED_RANGE flag is set" << endl;
        cout << "lpData = " << phe.lpData << endl;
        cout << "cbData = " << phe.cbData << endl;
        cout << endl;
    }
    // разрушаем кучу
    HeapDestroy(hHeap);

    return 0;
}