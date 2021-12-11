#include <Windows.h>
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	const auto path = LR"(W:\1.txt)";
    auto file = ofstream(path);
    file << L"1";
    file.close();
    // удаляем файл
    if (!DeleteFileW(path))
    {
        cerr << "Delete file failed." << endl
            << "The last error code: " << GetLastError() << endl;
        cout << "Press any key to finish.";
        cin.get();
        return 0;
    }
    cout << "The file is deleted." << endl;

    return 0;
}