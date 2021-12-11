#include <Windows.h>
#include <iostream>

using namespace std;

int main()
{
	// создаем файл для записи данных
	HANDLE hFile = CreateFile(
	    L"temp.txt", // имя файла
	    GENERIC_WRITE, // запись в файл
	    0, // монопольный доступ к файлу
	    nullptr, // защиты нет 
	    CREATE_NEW, // создаем новый файл
	    FILE_ATTRIBUTE_NORMAL, // обычный файл
	    nullptr	    // шаблона нет
    );
    // проверяем на успешное создание
    if (hFile == INVALID_HANDLE_VALUE)
    {
        cerr << "Create file failed." << endl
            << "The last error code: " << GetLastError() << endl;
        cout << "Press any key to finish.";
        cin.get();
        return 0;
    }

    // пишем данные в файл
    for (int i = 65; i < 65+26; ++i)
    {
        DWORD dwBytesWrite;

        if (!WriteFile(
            hFile,               // дескриптор файла
            &i,                  // адрес буфера, откуда идет запись
            sizeof i,           // количество записываемых байтов
            &dwBytesWrite,       // количество записанных байтов
            nullptr // запись синхронная
        ))
        {
            cerr << "Write file failed." << endl
                << "The last error code: " << GetLastError() << endl;
            CloseHandle(hFile);
            cout << "Press any key to finish.";
            cin.get();
            return 0;
        }
    }
    // закрываем дескриптор файла 
    CloseHandle(hFile);

    cout << "The file is created and written." << endl;

    return 0;
}