#include <Windows.h>
#include <iostream>

using namespace std;

int main()
{
    constexpr int size = 4096;   // размер страницы

    SIZE_T  min, max;  // мин. и макс. размеры рабочего множества страниц
    SIZE_T* p_min = &min;    // указатель на минимальный размер
    SIZE_T* p_max = &max;    // указатель на максимальный размер

    // получить дескриптор текущего процесса
    const HANDLE h_process = GetCurrentProcess();
    // прочитать границы рабочего множества
    if (!GetProcessWorkingSetSize(h_process, p_min, p_max))
    {
	    std::cout << "Get process working set size failed." << endl;
        return GetLastError();
    }
    cout << "Min = " << (min / size) << endl;
    cout << "Max = " << (max / size) << endl;

    // установить новые границы рабочего множества
    if (!SetProcessWorkingSetSize(h_process, min - 10, max - 10))
    {
        cout << "Set process working set size failed." << endl;
        return GetLastError();
    }

    // прочитать новые границы рабочего множества
    if (!GetProcessWorkingSetSize(h_process, p_min, p_max))
    {
        cout << "Get process working set size failed." << endl;
        return GetLastError();
    }
    cout << "Min = " << (min / size) << endl;
    cout << "Max = " << (max / size) << endl;
    return 0;
}