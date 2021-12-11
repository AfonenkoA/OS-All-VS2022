#include <Windows.h>
#include <iostream>

using namespace std;

int main()
{
    // перемещаем файл
    if (!MoveFile(L"demo_file.txt", L"new_file.txt"))
    {
        cerr << "Move file failed." << endl
            << "The last error code: " << GetLastError() << endl;
        cout << "Press any key to finish.";
        cin.get();
        return 0;
    }

    cout << "The file is moved." << endl;

    return 0;
}