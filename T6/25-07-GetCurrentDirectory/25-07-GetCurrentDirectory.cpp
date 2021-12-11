#include <Windows.h>
#include <iostream>

using namespace std;

int main()
{
	wchar_t  szDirName[MAX_PATH];

    // определяем имя текущего каталога
    DWORD dwNumberOfChar = GetCurrentDirectory(MAX_PATH, szDirName);
    if (dwNumberOfChar == 0)
    {
        wcerr << L"Get current directory failed." << endl
            << L"The last error code: " << GetLastError() << endl;
        wcout << L"Press any key to finish.";
        wcin.get();

        return 0;
    }
    // выводим на консоль имя текущего каталога
    wcout << L"Current directory name: " << endl;
    wprintf(szDirName);
    // устанавливаем текущий каталог для удаления из него файлов
    if (!SetCurrentDirectory(L"demo_dir"))
    {
        wcerr << L"Set current directory failed." << endl
            << L"The last error code: " << GetLastError() << endl;
        wcout << L"Press any key to finish.";
        wcin.get();

        return 0;
    }
    // определяем имя нового текущего каталога
    dwNumberOfChar = GetCurrentDirectory(MAX_PATH, szDirName);
    if (dwNumberOfChar == 0)
    {
        wcerr << L"Get current directory failed." << endl
            << L"The last error code: " << GetLastError() << endl;
        wcout << L"Press any key to finish.";
        wcin.get();

        return 0;
    }
    // выводим на консоль имя нового текущего каталога
    wcout << L"Current directory name: " << endl;
    wcout << szDirName << endl;
    return 0;
}