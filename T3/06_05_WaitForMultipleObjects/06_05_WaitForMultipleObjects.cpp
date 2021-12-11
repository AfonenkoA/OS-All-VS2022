#include <Windows.h>
#include <iostream>

using namespace std;

DWORD WINAPI thread_0(LPVOID)
{
    int i;

    for (i = 0; i < 5; ++i)
    {
        cout << i << ' ' << flush;
        Sleep(7);
    }
    cout << endl;
    return 0;
}

DWORD WINAPI thread_1(LPVOID)
{
    int i;

    for (i = 5; i < 10; ++i)
    {
        cout << i << ' ' << flush;
        Sleep(7);
    }
    cout << endl;
    return 0;
}

int main()
{
    HANDLE   hThread[2];
    DWORD  dwThread[2];

    // ��������� ������ �����
    hThread[0] = CreateThread(NULL, 0, thread_0,
        NULL, 0, &dwThread[0]);
    if (hThread[0] == NULL)
        return GetLastError();
    // ��������� ������ �����
    hThread[1] = CreateThread(NULL, 0, thread_1,
        NULL, 0, &dwThread[1]);
    if (hThread[1] == NULL)
        return GetLastError();

    // ���� ���������� ������� thread_1 � thread_2
    if (WaitForMultipleObjects(2, hThread, TRUE, INFINITE) == WAIT_FAILED)
    {
        cout << "Wait for multiple objects failed." << endl;
        cout << "Input any char to exit." << endl;
        cin.get();
    }

    // ��������� ����������� ������� thread_0 � thread_1
    CloseHandle(hThread[0]);
    CloseHandle(hThread[1]);

    return 0;
}
