﻿#include <Windows.h>
#include <conio.h>

using namespace std;

int main()
{
    wchar_t lpszComLine[250];  // для командной строки

    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    HANDLE hWritePipe, hReadPipe, hInheritWritePipe;

    // создаем анонимный канал
    if (!CreatePipe(
        &hReadPipe,    // дескриптор для чтения
        &hWritePipe,   // дескриптор для записи
        NULL,          // атрибуты защиты по умолчанию, в этом случае 
                       // дескрипторы hReadPipe и hWritePipe ненаследуемые
        0))            // размер буфера по умолчанию

    {
        _cputs("Create pipe failed.\n");
        _cputs("Press any key to finish.\n");
        _getch();
        return GetLastError();
    }
    // делаем наследуемый дубликат дескриптора hWritePipe
    if (!DuplicateHandle(
        GetCurrentProcess(),   // дескриптор текущего процесса
        hWritePipe,            // исходный дескриптор канала
        GetCurrentProcess(),   // дескриптор текущего процесса
        &hInheritWritePipe,    // новый дескриптор канала
        0,                     // этот параметр игнорируется
        TRUE,                  // новый дескриптор наследуемый
        DUPLICATE_SAME_ACCESS))  // доступ не изменяем
    {
        _cputs("Duplicate handle failed.\n");
        _cputs("Press any key to finish.\n");
        _getch();
        return GetLastError();
    }
    // закрываем ненужный дескриптор
    CloseHandle(hWritePipe);
    // устанавливаем атрибуты нового процесса
    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);
    // формируем командную строку
    wsprintf(lpszComLine, LR"(W:\РФиКТ\Операционные системы\u+3к ОС\c0a2 Практ C++ Проекты\T4\15-01-Client\Debug\15-01-Client.exe %d)",
        reinterpret_cast<int>(hInheritWritePipe));
    // запускаем новый консольный процесс
    if (!CreateProcess(
	    nullptr,    // имя процесса
        lpszComLine,   // командная строка
	    nullptr,    // атрибуты защиты процесса по умолчанию
	    nullptr,    // атрибуты защиты первичного потока по умолчанию
        TRUE,    // наследуемые дескрипторы текущего процесса
                 // наследуются новым процессом
        CREATE_NEW_CONSOLE,  // новая консоль  
	    nullptr,    // используем среду окружения процесса предка
	    nullptr,    // текущий диск и каталог, как и в процессе предке
        &si,     // вид главного окна - по умолчанию
        &pi      // здесь будут дескрипторы и идентификаторы
                 // нового процесса и его первичного потока
    ))
    {
        _cputs("Create process failed.\n");
        _cputs("Press any key to finish.\n");
        _getch();
        return GetLastError();
    }
    // закрываем дескрипторы нового процесса
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    // закрываем ненужный дескриптор канала
    CloseHandle(hInheritWritePipe);
    // читаем из анонимного канала
    for (int i = 0; i < 10; i++)
    {
        int nData;
        DWORD dwBytesRead;
        if (!ReadFile(
            hReadPipe,
            &nData,
            sizeof(nData),
            &dwBytesRead,
            NULL))
        {
            _cputs("Read from the pipe failed.\n");
            _cputs("Press any key to finish.\n");
            _getch();
            return GetLastError();
        }
        _cprintf("The number %d is read from the pipe.\n", nData);
    }
    // закрываем дескриптор канала
    CloseHandle(hReadPipe);

    _cputs("The process finished reading from the pipe.\n");
    _cputs("Press any key to exit.\n");
    _getch();

    return 0;
}