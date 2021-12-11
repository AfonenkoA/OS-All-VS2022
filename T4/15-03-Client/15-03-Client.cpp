#include <Windows.h>
#include <conio.h>

using namespace std;

int main(int argc, char* argv[])
{
	wchar_t lpszEnableRead[] = L"EnableRead";

    // открываем событие, разрешающее чтение
    HANDLE hEnableRead = OpenEvent(EVENT_ALL_ACCESS, FALSE, lpszEnableRead);

    // преобразуем символьное представление дескрипторов в число
	HANDLE hWritePipe = reinterpret_cast<HANDLE>(atoi(argv[1]));
    HANDLE hReadPipe = reinterpret_cast<HANDLE>(atoi(argv[2]));
    // ждем команды о начале записи в анонимный канал
    _cputs("Press any key to start communication.\n");
    _getch();
    // пишем в анонимный канал
    for (int i = 0; i < 10; i++)
    {
        DWORD dwBytesWritten;
        if (!WriteFile(
            hWritePipe,
            &i,
            sizeof(i),
            &dwBytesWritten,
        nullptr))
        {
            _cputs("Write to file failed.\n");
            _cputs("Press any key to finish.\n");
            _getch();
            return GetLastError();
        }
        _cprintf("The number %d is written to the pipe.\n", i);
    }
    _cputs("The process finished writing to the pipe.\n");

    // ждем разрешения на чтение
    WaitForSingleObject(hEnableRead, INFINITE);
    // читаем ответ из анонимного канала
    for (int j = 0; j < 10; j++)
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
    _cputs("Press any key to exit.\n");
    _getch();

    // закрываем дескрипторы канала
    CloseHandle(hWritePipe);
    CloseHandle(hReadPipe);
    CloseHandle(hEnableRead);

    return 0;
}