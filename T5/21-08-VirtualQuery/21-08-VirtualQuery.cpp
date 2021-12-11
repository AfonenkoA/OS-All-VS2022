#include <Windows.h>
#include <iostream>

using namespace std;

int main()
{
	constexpr int size = 10000;  // размер области
    constexpr int shift = 5000;  // смещения для подобласти

    MEMORY_BASIC_INFORMATION  mbi;   // структура для информации 
                                     // о виртуальной памяти
	constexpr DWORD  mbi_size = sizeof(MEMORY_BASIC_INFORMATION);

    // распределяем виртуальную память
    BYTE* a = static_cast<BYTE*>(VirtualAlloc(nullptr, size, MEM_COMMIT, PAGE_READWRITE));
    if (!a)
    {
	    std::cout << "Virtual allocation failed." << endl;
        return GetLastError();
    }

    // устанавливает адрес подобласти
	const BYTE* b = a + shift;

    // определяем информацию о виртуальной памяти
    if (mbi_size != VirtualQuery(b, &mbi, mbi_size))
    {
        cout << "Virual query failed." << endl;
        return GetLastError();
    }
    // распечатываем эту информацию
    cout << "Base address: " << mbi.BaseAddress << endl;
    cout << "Allocation base: " << mbi.AllocationBase << endl;
    cout << "Allocation protect: " << mbi.AllocationProtect << endl;
    cout << "Region size: " << mbi.RegionSize << endl;
    cout << "State: " << mbi.State << endl;
    cout << "Protect: " << mbi.Protect << endl;
    cout << "Type: " << mbi.Type << endl;

    // освобождаем виртуальную память
    if (!VirtualFree(a, 0, MEM_RELEASE))
    {
        cout << "Memory release failed." << endl;
        return GetLastError();
    }

    return 0;
}