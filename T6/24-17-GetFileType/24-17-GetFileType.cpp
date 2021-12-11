#include <Windows.h>
#include <iostream>

using namespace std;

int main()
{
	// открываем файл для чтения
    HANDLE hFile = CreateFile(
	    L"demo_file.txt", // имя файла
	    0, // получение информации о файле
	    0, // монопольный доступ к файлу
	    nullptr, // защиты нет 
	    OPEN_EXISTING, // открываем существующий файл
	    FILE_ATTRIBUTE_NORMAL, // обычный файл
	    nullptr // шаблона нет
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
    // определяем тип файла
    DWORD dwFileType = GetFileType(hFile);
    // распечатываем тип файла
    switch (dwFileType)
    {
    case FILE_TYPE_UNKNOWN:
        cout << "Unknown type file." << endl;
        break;
    case FILE_TYPE_DISK:
        cout << "Disk type file." << endl;
        break;
    case FILE_TYPE_CHAR:
        cout << "Char type file." << endl;
        break;
    case FILE_TYPE_PIPE:
        cout << "Pipe type file." << endl;
        break;
    default:
        break;
    }

    return 0;
}