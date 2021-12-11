#include <Windows.h>
#include <iostream>

using namespace std;

DWORD WINAPI thread(LPVOID)
{
    int i;

    for (i = 0; i < 10; ++i)
    {
        cout << i << ' ' << flush;
        Sleep(100);
    }
    cout << endl;
}

int main()
{
    HANDLE   hThread;
    DWORD  dwThread;

    hThread = CreateThread(NULL, 0, thread, NULL,
        0, &dwThread);
    if (hThread == NULL)
        return GetLastError();

    // ���� ���������� ������ thread
    if (WaitForSingleObject(hThread, INFINITE) != WAIT_OBJECT_0)
    {
        cout << "Wait for single object failed." << endl;
        cout << "Press any key to exit." << endl;
        cin.get();
    }
    // ��������� ���������� ������ thread
    CloseHandle(hThread);

    return 0;
}