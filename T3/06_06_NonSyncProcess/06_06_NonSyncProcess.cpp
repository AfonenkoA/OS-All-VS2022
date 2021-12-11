#include <Windows.h>
#include <iostream>

using namespace std;

int main()
{
    wchar_t  lpszAppName[] = L"W:\\РФиКТ\\Операционные системы\\u+3к ОС\\c0a2 Практ C++ Проекты\\T3\\06_07_ConsoleProcess\\x64\\Release\\06_07_ConsoleProcess.exe";
    STARTUPINFO  si;
    PROCESS_INFORMATION  pi;

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
        for (int i = 0; i < 10; ++i)
        {
            cout << j << ' ' << flush;
            Sleep(10);
        }
        cout << endl;
    }

    // ����, ���� �������� ������� �������� ������
    WaitForSingleObject(pi.hProcess, INFINITE);

    // ��������� ����������� ��������� �������� � ������� ��������
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);

    return 0;
}