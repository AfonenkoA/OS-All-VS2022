#include <Windows.h>
#include <iostream>

using namespace std;

int main()
{
	// находим первое изменение в каталоге
    HANDLE hChangeHandle = FindFirstChangeNotification(
	    L"demo_dir", // имя каталога
	    TRUE, // отслеживать также подкаталоги
	    FILE_NOTIFY_CHANGE_FILE_NAME // отслеживать изменение имени каталога
	    | FILE_NOTIFY_CHANGE_SIZE // и изменение его размера
    );

    if (hChangeHandle == INVALID_HANDLE_VALUE)
    {
        wcerr << "Find first change notification failed." << endl
            << "The last error code: " << GetLastError() << endl;
        wcout << "Press any key to finish.";
        cin.get();

        return 0;
    }
    // нужно изменить каталог
    wcout << "Wait for changes in the directory." << endl;
    // ждем первого изменения в каталоге
    if (WaitForSingleObject(hChangeHandle, INFINITE) == WAIT_OBJECT_0)
        wcout << "First notification: the directory was changed." << endl;
    else
    {
        wcerr << "Wait for single object failed." << endl
            << "The last error code: " << GetLastError() << endl;
        wcout << "Press any key to finish.";
        cin.get();

        return 0;
    }
    // находим второе изменение в каталоге
    if (!FindNextChangeNotification(hChangeHandle))
    {
        wcerr << "Find next change notification failed." << endl
            << "The last error code: " << GetLastError() << endl;
        wcout << "Press any key to finish.";
        cin.get();

        return 0;
    }
    // ждем второго изменения в каталоге
    if (WaitForSingleObject(hChangeHandle, INFINITE) == WAIT_OBJECT_0)
        wcout << "Next notification: the directory was changed." << endl;
    else
    {
        wcerr << "Wait for single object failed." << endl
            << "The last error code: " << GetLastError() << endl;
        wcout << "Press any key to finish.";
        cin.get();

        return 0;
    }
    // закрываем дескриптор поиска
    FindCloseChangeNotification(hChangeHandle);

    return 0;
}