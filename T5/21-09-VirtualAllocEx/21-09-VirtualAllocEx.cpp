#include <Windows.h>
#include <iostream>

using namespace std;

int main()
{
    char c;    // служебный символ
    wchar_t lpszCommandLine[250];            // командная строка
    constexpr char send[] = "This is a message.";  // строка для пересылки
    char buffer[80];                     // буфер для ответа
    auto v = reinterpret_cast<LPVOID>(0x00880000);      // указатель на область памяти

    // записи-чтения в виртуальную память
    constexpr wchar_t  write_event[] = L"WriteEvent";
    constexpr wchar_t  read_event[] = L"ReadEvent";

    // создаем события
    const HANDLE h_write = CreateEvent(nullptr, FALSE, FALSE, write_event);
    const HANDLE h_read = CreateEvent(nullptr, FALSE, FALSE, read_event);


    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);
    // формируем командную строку
    wsprintf(lpszCommandLine, L"W:\\РФиКТ\\Операционные системы\\u+3к ОС\\c0a2 Практ C++ Проекты\\T5\\21-10-ConsoleProcess\\Debug\\21-10-ConsoleProcess.exe %d", (int)v);
    // создаем новый консольный процесс
    if (!CreateProcess(nullptr,
        lpszCommandLine,
        nullptr,
        nullptr,
        FALSE,
        CREATE_NEW_CONSOLE,
        nullptr,
        nullptr, &si, &pi))
    {
	    std::cout << "Create process failed." << endl;
        return GetLastError();
    }

    // распределяем виртуальную память в этом процессе
    v = VirtualAllocEx(
        pi.hProcess,
        v,
        sizeof send,
        MEM_RESERVE | MEM_COMMIT,
        PAGE_READWRITE);
    if (!v)
    {
        cout << "Virtual allocation failed." << endl;
        return GetLastError();
    }

    // записываем в виртуальную память сообщение
    WriteProcessMemory(pi.hProcess, v, send, sizeof send, nullptr);
    // оповещаем о записи
    SetEvent(h_write);
    // ждем сигнала на чтение
    WaitForSingleObject(h_read, INFINITE);
    // читаем ответ
    ReadProcessMemory(pi.hProcess, v, buffer, sizeof buffer, nullptr);
    // выводим ответ
    cout << buffer << endl;

    // освобождаем виртуальную память
    if (!VirtualFreeEx(pi.hProcess, v, 0, MEM_RELEASE))
    {
        cout << "Memory release failed." << endl;
        return GetLastError();
    }

    cout << "Input any char to exit: ";
    cin >> c;

    return 0;
}