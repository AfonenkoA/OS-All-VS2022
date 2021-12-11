#include <Windows.h>
#include <iostream>



int main()
{
	constexpr int size = 1000;   // размерность массива

    // распределяем виртуальную память
    int* a = static_cast<int*>(VirtualAlloc(
	    nullptr,
	    size * sizeof(int),
	    MEM_COMMIT,
	    PAGE_READWRITE));
    if (!a)
    {
	    std::cout << "Virtual allocation failed." << std::endl;
        return GetLastError();
    }

    std::cout << "Virtual memory address: " << a << std::endl;

    // освобождаем виртуальную память
    if (!VirtualFree(a, 0, MEM_RELEASE))
    {
	    std::cout << "Memory release failed." << std::endl;
        return GetLastError();
    }

    return 0;
}