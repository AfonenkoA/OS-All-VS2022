#include <Windows.h>
#include <iostream>

int main()
{
	constexpr int size = 1000;

    // распределяем виртуальную память
	const LPVOID lp = VirtualAlloc(
	    reinterpret_cast<LPVOID>(0x00890002),
	    size,
	    MEM_RESERVE | MEM_COMMIT,
	    PAGE_READWRITE);
    if (!lp)
    {
	    std::cout << "Virtual allocation failed." << std::endl;
        return GetLastError();
    }

    std::cout << "Virtual memory address: " << lp << std::endl;

    // освобождаем виртуальную память
    if (!VirtualFree(lp, 0, MEM_RELEASE))
    {
	    std::cout << "Memory release failed." << std::endl;
        return GetLastError();
    }
    return 0;
}