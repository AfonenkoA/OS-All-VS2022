#include <Windows.h>
#include <iostream>

using namespace std;

int main()
{
    DWORD  dw_old_protect;     // для старых атрибутов защиты  
    constexpr int size = 1000;   // размерность массива

    // распределяем виртуальную память
    int* a = static_cast<int*>(VirtualAlloc(
	    nullptr,
	    size * sizeof(int),
	    MEM_COMMIT,
	    PAGE_READONLY));
    if (!a)
    {
        cout << "Virtual allocation failed." << endl;
        return GetLastError();
    }

    // попробуем записать в виртуальную память
    __try
    {
        a[10] = 10;
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        DWORD ecode = GetExceptionCode();

        if (ecode == EXCEPTION_ACCESS_VIOLATION)
            cout << "Access to write protected page." << endl;
        else
            cout << "Some exception." << endl;
    }

    // изменим атрибуты доступа
    if (!VirtualProtect(a, size, PAGE_READWRITE, &dw_old_protect))
    {
        cout << "Virtual protect failed." << endl;
        return GetLastError();
    }

    // теперь можно писать в виртуальную память 
    a[10] = 10;
    cout << "a[10] = " << a[10] << endl;

    // освобождаем виртуальную память
    if (!VirtualFree(a, 0, MEM_RELEASE))
    {
        cout << "Memory release failed." << endl;
        return GetLastError();
    }

    return 0;
}