#include <Windows.h>
#include <iostream>

using namespace std;

int main()
{
    // удалаем каталог
    CreateDirectory(L"demo_dir", nullptr);
    if (!RemoveDirectory(L"demo_dir"))
    {
        cerr << "Remove directory failed." << endl
            << "The last error code: " << GetLastError() << endl;
        cout << "Press any key to finish.";
        cin.get();

        return 0;
    }

    cout << "The directory is removed." << endl;

    return 0;
}