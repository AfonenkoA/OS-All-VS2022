#include <Windows.h>
#include <iostream>

using namespace std;

int main()
{
	// создаем файл для записи данных
    HANDLE hFile = CreateFile(
	    L"demo_file.txt", // имя файла
	    GENERIC_WRITE, // запись в файл
	    FILE_SHARE_READ, // разделяемое чтение файла
	    NULL, // защиты нет
	    CREATE_ALWAYS, // создаем новый файл
	    FILE_ATTRIBUTE_NORMAL, // обычный файл
	    NULL // шаблона нет
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
    for (int i = 'A'; i < 'Z'; ++i)
    {
        DWORD dwBytesWrite;

        if (!WriteFile(
            hFile,               // дескриптор файла
            &i,                  // адрес буфера, откуда идет запись
            sizeof i,           // количество записываемых байтов
            &dwBytesWrite,       // количество записанных байтов
            nullptr
            // запись синхронная
        ))
        {
            cerr << "Write file failed." << endl
                << "The last error code: " << GetLastError() << endl;
            CloseHandle(hFile);
            cout << "Press any key to finish.";
            cin.get();
            return 0;
        }
        // если достигли середины файла, то освобождаем буфер
        if (i == 'T')
        {
            if (!FlushFileBuffers(hFile))
            {
                cerr << "Flush file buffers failed." << endl
                    << "The last error code: " << GetLastError() << endl;
                CloseHandle(hFile);
                cout << "Press any key to finish.";
                cin.get();
                return 0;
            }
            // теперь можно просмотреть содержимое файла
            cout << "A half of the file is written." << endl
                << "Press any key to continue.";
            cin.get();
        }
    }
    // закрываем дескриптор файла 
    CloseHandle(hFile);

    cout << "The file is created and written." << endl;

    return 0;
}