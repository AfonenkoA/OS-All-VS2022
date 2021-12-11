#include <Windows.h>
#include <iostream>

using namespace std;

int main()
{
	LARGE_INTEGER  li_file_size;  // размер файла

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
    if (!GetFileSizeEx(hFile, &li_file_size))
    {
        cerr << "Get file size failed." << endl
            << "The last error code: " << GetLastError() << endl;
        CloseHandle(hFile);
        cout << "Press any key to finish.";
        cin.get();
        return 0;
    }

// выводим размер файла
cout << "File size: " << li_file_size.LowPart << endl;
// закрываем дескриптор файла 
CloseHandle(hFile);

return 0;
}