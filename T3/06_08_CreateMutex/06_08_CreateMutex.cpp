#include <Windows.h>
#include <iostream>

using namespace  std;

int main()
{
    HANDLE  hMutex;
    wchar_t  lpszAppName[] = L"W:\\РФиКТ\\Операционные системы\\u+3к ОС\\c0a2 Практ C++ Проекты\\T3\\06_09_ConsoleProcess\\x64\\Release\\06_09_ConsoleProcess.exe";
    STARTUPINFO  si;
    PROCESS_INFORMATION  pi;

    // ������� �������
    hMutex = CreateMutex(NULL, FALSE, L"DemoMutex");
    if (hMutex == NULL)
    {
        cout << "Create mutex failed." << endl;
        cout << "Press any key to exit." << endl;
        cin.get();

        return GetLastError();
    }

    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);

    // ������� ����� ���������� �������
    if (!CreateProcess(lpszAppName, NULL, NULL, NULL, FALSE,
        NULL, NULL, NULL, &si, &pi))
    {
        cout << "The new process is not created." << endl;
        cout << "Press any key to exit." << endl;
        cin.get();

        return GetLastError();
    }

    // ������� �� ����� ������
    for (int j = 0; j < 10; ++j)
    {
        // ����������� �������
        WaitForSingleObject(hMutex, INFINITE);
        for (int i = 0; i < 10; i++)
        {
            cout << j << ' ' << flush;
            Sleep(10);
        }
        cout << endl;
        // ����������� �������
        ReleaseMutex(hMutex);
    }
    // ��������� ���������� ��������
    CloseHandle(hMutex);

    // ���� ���� �������� ������� �������� ������
    WaitForSingleObject(pi.hProcess, INFINITE);

    // ��������� ����������� ��������� �������� � ������� ��������
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);

    return 0;
}