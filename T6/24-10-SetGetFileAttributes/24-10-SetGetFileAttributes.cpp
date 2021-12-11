#include <Windows.h>
#include <iostream>

using namespace std;

int main()
{
	// читаем атрибуты файла
	const DWORD file_attr = GetFileAttributes(L"demo_file.txt");
    if (file_attr == INVALID_FILE_ATTRIBUTES)
    {
        cerr << "Get file attributes failed." << endl
            << "The last error code: " << GetLastError() << endl;
        cout << "Press any key to finish.";
        cin.get();
        return 0;
    }
    // проверяем, является ли файл нормальным
    if (file_attr == FILE_ATTRIBUTE_NORMAL)
        cout << "This is a normal file." << endl;
    else
    {
        cout << "This is a not normal file." << endl;
        return 0;
    }
    // устанавливаем атрибут скрытого файла
    if (!SetFileAttributes(L"demo_file.txt", FILE_ATTRIBUTE_HIDDEN))
    {
        cerr << "Set file attributes failed." << endl
            << "The last error code: " << GetLastError() << endl;
        cout << "Press any key to finish.";
        cin.get();

        return 0;
    }
    // Теперь можно проверить, что файл скрылся
    cout << "Now the file is hidden." << endl
        << "Press any key to continue.";
    cin.get();
    // Обратно делаем файл обычным
    if (!SetFileAttributes(L"demo_file.txt", FILE_ATTRIBUTE_NORMAL))
    {
        cerr << "Set file attributes failed." << endl
            << "The last error code: " << GetLastError() << endl;
        cout << "Press any key to finish.";
        cin.get();

        return 0;
    }
    cout << "Now the file is again normal." << endl;

    return 0;
}