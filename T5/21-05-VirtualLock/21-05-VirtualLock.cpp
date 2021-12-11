﻿#include <Windows.h>
#include <iostream>

using namespace std;

int main()
{
	constexpr SIZE_T  size = 4096;   // размер памяти

    // распределяем виртуальную память
	const LPVOID vm = VirtualAlloc(
	    nullptr,
	    size,
	    MEM_COMMIT,
	    PAGE_READWRITE);
    if (!vm)
    {
        cout << "Virtual allocation failed." << endl;
        return GetLastError();
    }

    // блокируем виртуальную память
    if (!VirtualLock(vm, size))
    {
        cout << "Virtual lock failed." << endl;
        return GetLastError();
    }
    // разблокируем виртуальную память
    if (!VirtualUnlock(vm, size))
    {
        cout << "Virtual unlock failed." << endl;
        return GetLastError();
    }

    // освобождаем виртуальную память
    if (!VirtualFree(vm, 0, MEM_RELEASE))
    {
        cout << "Memory release failed." << endl;
        return GetLastError();
    }

    return 0;
}