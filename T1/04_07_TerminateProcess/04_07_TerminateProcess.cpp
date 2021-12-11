#include <windows.h>
#include <conio.h>

int main()
{
  wchar_t lpszAppName[] = L"W:\\РФиКТ\\Операционные системы\\u+3к ОС\\c0a2 Практ C++ Проекты\\T1\\04_06_ConsoleProcess\\x64\\Debug\\04_06_ConsoleProcess.exe";

  STARTUPINFO si;
  PROCESS_INFORMATION pi;

  ZeroMemory(&si, sizeof(STARTUPINFO));
  si.cb=sizeof(STARTUPINFO);

  // ������� ����� ���������� �������
  if (!CreateProcess(lpszAppName, NULL, NULL, NULL, FALSE,
      CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
  {
    _cputs("The new process is not created.\n");
    _cputs("Check a name of the process.\n");
    _cputs("Press any key to finish.\n");
    _getch();
    return 0;
  }

  _cputs("The new process is created.\n");

  while (true)
  {
    char c;

    _cputs("Input 't' to terminate the new console process: ");
    c = _getch();
    if (c == 't')
    {
      _cputs("t\n");
      // ��������� ����� �������
      TerminateProcess(pi.hProcess,1);
      break;
    }
  }

  // ��������� ����������� ������ �������� � ������� ��������
  CloseHandle(pi.hThread);
  CloseHandle(pi.hProcess);

  return 0;
}