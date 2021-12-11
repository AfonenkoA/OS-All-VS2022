#include <Windows.h>
#include <conio.h>

int main(int argc, char* argv[])
{
	// преобразуем символьное представление дескриптора в число
	const auto h_write_pipe = (HANDLE)atoi(argv[1]);
    // ждем команды о начале записи в анонимный канал
    _cputs("Press any key to start communication.\n");
    _getch();
    // пишем в анонимный канал
    for (int i = 0; i < 10; i++)
    {
        DWORD dw_bytes_written;
        if (!WriteFile(
            h_write_pipe,
            &i,
            sizeof(i),
            &dw_bytes_written,
            NULL))
        {
            _cputs("Write to file failed.\n");
            _cputs("Press any key to finish.\n");
            _getch();
            return GetLastError();
        }
        _cprintf("The number %d is written to the pipe.\n", i);
        Sleep(500);
    }
    // закрываем дескриптор канала
    CloseHandle(h_write_pipe);

    _cputs("The process finished writing to the pipe.\n");
    _cputs("Press any key to exit.\n");
    _getch();

    return 0;
}