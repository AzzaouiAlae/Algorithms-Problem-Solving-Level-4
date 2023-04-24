#include <iostream>

using namespace std;

int ReadYaer()
{
    cout << "Enter the year : ";
    int Year; cin >> Year;
    return Year;
}

bool IsLeapYear(int Year)
{ 
    return  (Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0) ;
}

int main()
{
    while (true)
    {
        system("cls");

        int Year = ReadYaer();

        if (IsLeapYear(Year))
            cout << "\n" << Year << " is leap year\n";
        else
            cout << "\n" << Year << " is not leap year\n";
        system("pause>0");
    }
}