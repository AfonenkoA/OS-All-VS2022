#include <Windows.h>
#include <iostream>

using namespace std;

int main()
{
	// открываем файл для чтения
    HANDLE hFile = CreateFile(
	    L"demo_file.txt", // имя файла
	    GENERIC_READ, // чтение из файла
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
    DWORD dwFileSize = GetFileSize(hFile, nullptr);
    if (dwFileSize == INVALID_FILE_SIZE)
    {
        cerr << "Get file size failed." << endl
            << "The last error code: " << GetLastError() << endl;
        CloseHandle(hFile);
        cout << "Press any key to finish.";
        cin.get();

        return 0;
    }
    // выводим размер файла
    cout << "File size: " << dwFileSize << endl;
    // закрываем дескриптор файла 
    CloseHandle(hFile);

    return 0;
}