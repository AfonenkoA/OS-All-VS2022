#include <Windows.h>
#include <iostream>

HANDLE h_event;

using namespace std;

DWORD WINAPI thread(LPVOID)
{
    for (int i = 0; i < 10; ++i)
    {
        cout << i << endl;
        if (i == 4)
        {
            cout << "A half of the work is done." << endl;
            cout << "Press any key to continue." << endl;
        	WaitForSingleObject(h_event, INFINITE);
        }
    }
    return 0;
}

int main()
{
	DWORD  id_thread;
    h_event = CreateEvent(nullptr, FALSE, FALSE, nullptr);

    if (h_event == nullptr)
        return GetLastError();


	HANDLE h_thread = CreateThread(nullptr, 0, thread, nullptr, 0, &id_thread);
    if (h_thread == nullptr)
        return GetLastError();

    cin.get();
	SetEvent(h_event);

    WaitForSingleObject(h_thread, INFINITE);
    CloseHandle(h_thread);
    CloseHandle(h_event);

    cout << "The work is done." << endl;

    return 0;
}