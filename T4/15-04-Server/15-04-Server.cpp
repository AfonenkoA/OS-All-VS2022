#include <Windows.h>
#include <conio.h>

using namespace std;

int main()
{
    wchar_t lpszComLine[250];  // для командной строки

    constexpr wchar_t lpszEnableRead[] = L"EnableRead";

    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    HANDLE hWritePipe, hReadPipe;
    SECURITY_ATTRIBUTES sa;

    // создаем событие для синхронизации обмена данными
    HANDLE hEnableRead = CreateEvent(nullptr, FALSE, FALSE, lpszEnableRead);

    // устанавливает атрибуты защиты канала
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.lpSecurityDescriptor = nullptr;    // защита по умолчанию
    sa.bInheritHandle = TRUE;          // дескрипторы наследуемые

    // создаем анонимный канал
    if (!CreatePipe(
        &hReadPipe,  // дескриптор для чтения
        &hWritePipe, // дескриптор для записи
        &sa,   // атрибуты защиты по умолчанию, дескрипторы наследуемые
        0))    // размер буфера по умолчанию

    {
        _cputs("Create pipe failed.\n");
        _cputs("Press any key to finish.\n");
        _getch();
        return GetLastError();
    }
    // устанавливаем атрибуты нового процесса
    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);
    // формируем командеую строку
    wsprintf(lpszComLine, LR"(W:\РФиКТ\Операционные системы\u+3к ОС\c0a2 Практ C++ Проекты\T4\15-03-Client\Debug\15-03-Client.exe %d %d)",
        reinterpret_cast<int>(hWritePipe),
        reinterpret_cast<int>(hReadPipe));
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
    // читаем из анонимного канала
    for (int i = 0; i < 10; i++)
    {
        int nData;
        DWORD dwBytesRead;
        if (!ReadFile(
            hReadPipe,
            &nData,
            sizeof nData,
            &dwBytesRead,
        nullptr))
        {
            _cputs("Read from the pipe failed.\n");
            _cputs("Press any key to finish.\n");
            _getch();
            return GetLastError();
        }
        _cprintf("The number %d is read from the pipe.\n", nData);
    }
    _cputs("The process finished reading from the pipe.\n");

    // даем сигнал на разрешение чтения клиентом
    SetEvent(hEnableRead);

    // пишем ответ в анонимный канал
    for (int j = 10; j < 20; j++)
    {
        DWORD dwBytesWritten;
        if (!WriteFile(
            hWritePipe,
            &j,
            sizeof j,
            &dwBytesWritten,
        nullptr))
        {
            _cputs("Write to file failed.\n");
            _cputs("Press any key to finish.\n");
            _getch();
            return GetLastError();
        }
        _cprintf("The number %d is written to the pipe.\n", j);
    }
    // закрываем дескрипторы канала
    CloseHandle(hReadPipe);
    CloseHandle(hWritePipe);
    CloseHandle(hEnableRead);

    _cputs("The process finished writing to the pipe.\n");
    _cputs("Press any key to exit.\n");
    _getch();

    return 0;
}