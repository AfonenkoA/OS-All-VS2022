#include <Windows.h>
#include <iostream>

using namespace std;

int main()
{
	WIN32_FIND_DATA  fd;

    // находим первый файл
    HANDLE hFindFile = FindFirstFile(L"demo_dir\\*", &fd);
    if (hFindFile == INVALID_HANDLE_VALUE)
    {
        wcerr << "Find first file failed." << endl
            << "The last error code: " << GetLastError() << endl;
        wcout << "Press any key to finish.";
        wcin.get();

        return 0;
    }
    // выводим на консоль имя первого файла
    wcout << "The first file name: " << fd.cFileName << endl;
    // удаляем из каталога файлы
    while (FindNextFile(hFindFile, &fd))
    {
        // если это не подкаталог, то удаляем его
        if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
        {
            wstring s = L"demo_dir\\" + wstring(fd.cFileName);
	        // формируем имя файла
            // удаляем файл
            if (!DeleteFile(s.c_str()))
            {
                wcerr << "Delete file failed." << endl
                    << "The last error code: " << GetLastError() << endl;
                wcout << "Press any key to finish.";
                wcin.get();
            }
	        wcout << "The next file: " << fd.cFileName << " is deleted." << endl;
        }
        else
            wcout << "The next directory: " << fd.cFileName << " is not deleted." << endl;
    }
    // закрываем дескриптор поиска
    if (!FindClose(hFindFile))
    {
        wcout << "Find close failed." << endl;
        return 0;
    }
    // удалаем каталог
    if (!RemoveDirectory(L"demo_dir"))
    {
        wcerr << "Remove directory failed." << endl
            << "The last error code: " << GetLastError() << endl;
        wcout << "Press any key to finish.";
        wcin.get();

        return 0;
    }

    wcout << "The directory is removed." << endl;

    return 0;
}