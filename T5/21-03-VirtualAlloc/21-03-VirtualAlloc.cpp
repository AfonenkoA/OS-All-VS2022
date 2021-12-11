#include <Windows.h>
#include <iostream>

int main()
{
	constexpr int kb = 1024;
    constexpr int size = 100;

    // резервируем виртуальную память
	const LPVOID lpr = VirtualAlloc(
	    reinterpret_cast<LPVOID>(0x00880000),
	    size * kb,
	    MEM_RESERVE,
	    PAGE_READWRITE);
    if (!lpr)
    {
	    std::cout << "Virtual memory reservation failed." << std::endl;
        return GetLastError();
    }

    std::cout << "Virtual memory address: " << lpr << std::endl;

    // распределяем виртуальную память
	const LPVOID lpc = VirtualAlloc(
	    reinterpret_cast<LPVOID>(0x00888000),
	    kb,
	    MEM_COMMIT,
	    PAGE_READWRITE);
    if (!lpc)
    {
	    std::cout << "Virtual memory allocation failed." << std::endl;
        return GetLastError();
    }

    std::cout << "Virtual memory address: " << lpc << std::endl;

    // отменяем распределение
    if (!VirtualFree(lpc, kb, MEM_DECOMMIT))
    {
	    std::cout << "Memory decommit failed." << std::endl;
        return GetLastError();
    }

    // освобождаем виртуальную память
    if (!VirtualFree(lpr, 0, MEM_RELEASE))
    {
	    std::cout << "Memory release failed." << std::endl;
        return GetLastError();
    }

    return 0;
}
