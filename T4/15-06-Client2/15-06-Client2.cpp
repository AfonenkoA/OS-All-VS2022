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

    // читаем целые числа из анонимного канала
    for (int i = 0; i < 5; ++i)
    {
        int nData;
        cin >> nData;
        _cprintf("The number %d is read from the pipe.\n", nData);
    }

    // разрешаем читать плавающие числа из анонимного канала
    SetEvent(hReadFloat);
    // пишем плавающие числа в анонимный канал
    for (int j = 0; j < 5; ++j)
    {
        Sleep(500);
        cout << j * 0.1 << endl;
    }

    // ждем разрешения на чтение текста
    WaitForSingleObject(hReadText, INFINITE);
    _cputs("The process read the text: ");
    // теперь читаем текст
    char lpszInput[80];
    do
    {
        Sleep(500);
        cin >> lpszInput;
        _cputs(lpszInput);
        _cputs(" ");
    } while (*lpszInput != '\0');

    _cputs("\nThe process finished transmission of data.\n");
    _cputs("Press any key to exit.\n");
    _getch();

    CloseHandle(hReadFloat);
    CloseHandle(hReadText);

    return 0;
}