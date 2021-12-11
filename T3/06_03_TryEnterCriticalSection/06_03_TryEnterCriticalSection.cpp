#define _WIN32_WINNT 0x0500

#include <Windows.h>
#include <iostream>

using namespace std;

CRITICAL_SECTION cs;

DWORD WINAPI thread(LPVOID)
{
    int i, j;

    for (j = 0; j < 10; ++j)
        // ������� ����� � ����������� ������
        if (TryEnterCriticalSection(&cs))
        {
            for (i = 0; i < 10; i++)
                cout << j << flush;
            cout << endl;
            // ����� �� ����������� ������
            LeaveCriticalSection(&cs);
        }

    return 0;
}

int main()
{
    int i, j;
    HANDLE  hThread;
    DWORD  IDThread;
    // �������������� ����������� ������
    InitializeCriticalSection(&cs);

    hThread = CreateThread(NULL, 0, thread, NULL, 0, &IDThread);
    if (hThread == NULL)
        return GetLastError();

    for (j = 10; j < 20; j++)
        // ������� ����� � ����������� ������
        if (TryEnterCriticalSection(&cs))
        {
            for (i = 0; i < 10; i++)
                cout << j << ' ' << flush;
            cout << endl;
            // ����� �� ����������� ������
            LeaveCriticalSection(&cs);
        }
    // ���� ���������� ������ ������ thread
    WaitForSingleObject(hThread, INFINITE);
    // ������� ����������� ������
    DeleteCriticalSection(&cs);

    return 0;
}