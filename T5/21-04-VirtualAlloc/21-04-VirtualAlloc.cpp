#include <Windows.h>
#include <iostream>

int main()
{
	constexpr int size = 1024;   // размерность массива

    // распределяем виртуальную память
    int* a = static_cast<int*>(VirtualAlloc(
	    nullptr,
	    size * sizeof(int),
	    MEM_COMMIT,
	    PAGE_READWRITE | PAGE_GUARD));
    if (!a)
    {
	    std::cout << "Virtual allocation failed." << std::endl;
        return GetLastError();
    }

    __try
    {
        a[10] = 10;
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
	    const DWORD ecode = GetExceptionCode();

        if (ecode == EXCEPTION_GUARD_PAGE)
	        std::cout << "Access to a guard virtual page." << std::endl;
        else
	        std::cout << "Some exception." << std::endl;
    }

    std::cout << "a[10] = " << a[10] << std::endl;
    a[10] = 10;
    std::cout << "a[10] = " << a[10] << std::endl;

    // освобождаем виртуальную память
    if (!VirtualFree(a, 0, MEM_RELEASE))
    {
	    std::cout << "Memory release failed." << std::endl;
        return GetLastError();
    }

    return 0;
}