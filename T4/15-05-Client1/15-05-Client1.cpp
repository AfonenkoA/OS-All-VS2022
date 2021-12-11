﻿#include <Windows.h>
#include <conio.h>
#include <iostream>

using namespace std;

int main()
{
	constexpr wchar_t lpszReadFloat[] = L"ReadFloat";
    constexpr wchar_t lpszReadText[] = L"ReadText";

    // открываем события
    HANDLE hReadFloat = CreateEvent(nullptr, FALSE, FALSE, lpszReadFloat);
    HANDLE hReadText = CreateEvent(nullptr, FALSE, FALSE, lpszReadText);

    // ждем команды о начале записи в анонимный канал
    _cputs("Press any key to start communication.\n");
    _getch();
    // пишем целые числа в анонимный канал
    for (int i = 0; i < 5; ++i)
    {
        Sleep(500);
        cout << i << endl;
    }

    // ждем разрешение на чтение плавающих чисел из канала
    WaitForSingleObject(hReadFloat, INFINITE);
    // читаем плавающие числа из анонимного канала
    for (int j = 0; j < 5; ++j)
    {
        float nData;
        cin >> nData;
        _cprintf("The number %2.1f is read from the pipe.\n", nData);
    }

    // отмечаем, что можно читать текст из анонимного канала
    SetEvent(hReadText);
    // теперь передаем текст
    cout << "This is a demo sentence." << endl;
    // отмечаем конец передачи
    cout << '\0' << endl;

    _cputs("The process finished transmission of data.\n");
    _cputs("Press any key to exit.\n");
    _getch();

    CloseHandle(hReadFloat);
    CloseHandle(hReadText);

    return 0;
}