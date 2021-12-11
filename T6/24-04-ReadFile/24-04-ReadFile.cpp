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

    // читаем данные из файла
    for (;;)
    {
        DWORD  dwBytesRead;
        char    n;

        // читаем одну запись
        if (!ReadFile(
            hFile,               // дескриптор файла
            &n,                  // адрес буфера, куда читаем данные
            sizeof n,           // количество читаемых байтов
            &dwBytesRead,        // количество прочитанных байтов
            nullptr             // чтение синхронное
        ))
        {
            cerr << "Read file failed." << endl
                << "The last error code: " << GetLastError() << endl;
            CloseHandle(hFile);
            cout << "Press any key to finish.";
            cin.get();
            return 0;
        }
        // проверяем на конец файла
        if (dwBytesRead == 0)
            // если да, то выходим из цикла
            break;
	        // иначе выводим запись на консоль
        cout << n << ' ';
    }

    cout << endl;

    // закрываем дескриптор файла 
    CloseHandle(hFile);

    cout << "The file is opened and read." << endl;

    return 0;
}