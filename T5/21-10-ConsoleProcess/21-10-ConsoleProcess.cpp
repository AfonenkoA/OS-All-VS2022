#include <Windows.h>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	char c;
	constexpr char answer[] = "This is an answer.";
	constexpr wchar_t  write_event[] = L"WriteEvent";
	constexpr wchar_t  read_event[] = L"ReadEvent";

	// открываем события
	const HANDLE hWrite = OpenEvent(EVENT_MODIFY_STATE, FALSE, write_event);
	const HANDLE hRead = OpenEvent(EVENT_MODIFY_STATE, FALSE, read_event);

	// преобразуем параметр в адрес
	char* v = reinterpret_cast<char*>(atoi(argv[1]));
	// выводим сообщение
	cout << v << endl;

	// ждем разрешения на запись
	WaitForSingleObject(hWrite, INFINITE);
	// записываем ответ
	strcpy_s(v,sizeof answer,answer);
	// разрешаем чтение
	SetEvent(hRead);

	// закрываем дескрипторы
	CloseHandle(hWrite);
	CloseHandle(hRead);

	// ждем команды на завершение
	cout << "Input any char to exit: ";
	cin >> c;

	return 0;
}