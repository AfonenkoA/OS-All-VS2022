﻿#include <Windows.h>
#include <iostream>

using namespace std;

int main()
{
	// открываем файл для записи
    HANDLE hFile = CreateFile(
	    L"demo_file.txt", // имя файла
	    GENERIC_WRITE, // запись в файл
	    0, // монопольный доступ к файлу
	    nullptr, // защиты нет 
	    OPEN_EXISTING, // открываем существующий файл
	    FILE_ATTRIBUTE_NORMAL, // обычный файл
	    nullptr	    // шаблона нет
    );
    // проверяем на успешное открытие
    if (hFile == INVALID_HANDLE_VALUE)
    {
        cerr << "Create file failed." << endl
            << "The last error code: " << GetLastError() << endl;
        cout << "Press any key to finish.";
        cin.get();

        return 0;
    }
    // определяем размер файла
    const auto dwFileSize = GetFileSize(hFile, nullptr);
    if (dwFileSize == INVALID_FILE_SIZE)
    {
        cerr << "Get file size failed." << endl
            << "The last error code: " << GetLastError() << endl;
        CloseHandle(hFile);
        cout << "Press any key to finish.";
        cin.get();

        return 0;
    }
    // блокируем файл
    if (!LockFile(hFile, 0, 0, dwFileSize, 0))
    {
        cerr << "Lock file failed." << endl
            << "The last error code: " << GetLastError() << endl;
        CloseHandle(hFile);
        cout << "Press any key to finish.";
        cin.get();

        return 0;
    }
    cout << "Now the file is locked." << endl
        << "Press any key to continue." << endl;
    cin.get();
    // разблокируем файл
    if (!UnlockFile(hFile, 0, 0, dwFileSize, 0))
    {
        cerr << "Unlock file failed." << endl
            << "The last error code: " << GetLastError() << endl;
        CloseHandle(hFile);
        cout << "Press any key to finish.";
        cin.get();

        return 0;
    }
    cout << "Now the file is unlocked." << endl
        << "Press any key to continue." << endl;
    cin.get();
    // закрываем дескриптор файла 
    CloseHandle(hFile);

    return 0;
}