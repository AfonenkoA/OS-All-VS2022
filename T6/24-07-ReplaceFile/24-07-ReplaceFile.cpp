#include <Windows.h>
#include <iostream>
using namespace std;

int main()
{
    // перемещаем файл
    if (!ReplaceFile(
        L"demo_file.txt",       // имя замесщаемого файла
        L"new_file.txt",        // имя файла заместителя
        L"back_file.txt",       // имя резервного файла
        REPLACEFILE_WRITE_THROUGH, // освободить буферы
        nullptr, nullptr // не используются
    ))
    {
        cerr << "Replace file failed." << endl
            << "The last error code: " << GetLastError() << endl;
        cout << "Press any key to finish.";
        cin.get();
        return 0;
    }

    cout << "The file is replaced." << endl;

    return 0;
}