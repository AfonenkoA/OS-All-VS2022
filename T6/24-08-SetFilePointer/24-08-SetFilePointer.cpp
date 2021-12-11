#include <Windows.h>
#include <iostream>

using namespace std;

int main()
{
	long    n;         // для номера записи
	DWORD dw_bytes_read; // количество прочитанных байт
    char     m;         // прочитанное число

    // открываем файл для чтения
    HANDLE hFile = CreateFile(
	    L"demo_file.txt", // имя файла
	    GENERIC_READ, // чтение из файла
	    0, // монопольный доступ к файлу
	    nullptr, // защиты нет 
	    OPEN_EXISTING, // открываем существующий файл
	    FILE_ATTRIBUTE_NORMAL, // обычный файл
	    nullptr	    // шаблона нет
    );
    // проверяем на успешное открытие
    if (hFile == INVALID_HANDLE_VALUE)
    {
        cerr << "Create file failed." << endl
            << "The last error code: " << GetLastError() << endl;
        cout << "Press any key to finish.";
        cin.get();
        return 0;
    }

    // вводим номер нужной записи
    cout << "Input a number from 0 to 9: ";
    cin >> n;
    // сдвигаем указатель позиции файла
	const auto p = SetFilePointer(hFile, n * sizeof(int), nullptr, FILE_BEGIN);
    if (p == INVALID_SET_FILE_POINTER)
    {
        cerr << "Set file pointer failed." << endl
            << "The last error code: " << GetLastError() << endl;
        CloseHandle(hFile);
        cout << "Press any key to finish.";
        cin.get();
        return 0;
    }
    // выводим на консоль значение указателя позиции файла
    cout << "File pointer: " << p << endl;
    // читаем данные из файла
    if (!ReadFile(
        hFile,             // дескриптор файла
        &m,                // адрес буфера, куда читаем данные
        sizeof m,         // количество читаемых байтов
        &dw_bytes_read,      // количество прочитанных байтов
        nullptr
        // чтение синхронное
    ))
    {
        cerr << "Read file failed." << endl
            << "The last error code: " << GetLastError() << endl;
        CloseHandle(hFile);
        cout << "Press any key to finish.";
        cin.get();
        return 0;
    }
    // выводим прочитанное число на консоль
    cout << "The read number: " << m << endl;
    // закрываем дескриптор файла 
    CloseHandle(hFile);

    return 0;
}