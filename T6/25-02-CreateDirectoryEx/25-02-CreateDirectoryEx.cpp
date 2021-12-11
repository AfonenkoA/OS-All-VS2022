#include <Windows.h>
#include <iostream>

using namespace std;

int main()
{
    // создаем подкаталог
    CreateDirectory(L"demo_dir",nullptr);
    if (!CreateDirectoryEx(L"demo_dir", L"demo_dir\\demo_subdir", nullptr))
    {
        cerr << "Create directory failed." << endl
            << "The last error code: " << GetLastError() << endl;
        cout << "Press any key to finish.";
        cin.get();

        return 0;
    }

    cout << "The subdirectory is created." << endl;

    return 0;
}