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
   /* if (Year % 400 == 0)
        return true;

    else if (Year % 100 == 0)
        return false;

    else if (Year % 4 == 0)
        return true;

    else
        return false;*/

    //return Year % 400 == 0 ? true : Year % 100 == 0 ? false : Year % 4 == 0 ? true : false;

    /*if (Year % 400 == 0 && Year % 100 != 0 || Year % 4 == 0)
        return true;

    else
        return false;*/

    return Year % 400 == 0 && Year % 100 != 0 || Year % 4 == 0 ? true : false;
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