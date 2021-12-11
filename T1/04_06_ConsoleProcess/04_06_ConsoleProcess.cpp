#include <Windows.h>
#include <iostream>



using namespace std;
int c;
void main()
{
    for (; ; )
    {
        c++;
        Sleep(1000);
        cout << "c = " << c << endl;
    }
}