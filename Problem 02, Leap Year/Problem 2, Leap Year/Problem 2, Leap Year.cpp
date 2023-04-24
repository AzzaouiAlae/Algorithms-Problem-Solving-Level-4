#include <iostream>

using namespace std;

int ReadYear()
{
    cout << "Enter the year : ";
    int Year;
    cin >> Year;
    return Year;
}

void LeapYearOrNot(int Year)
{
    if (Year % 400 == 0)
    {
        cout << endl << Year << " Leap Year\n";
        return;
    }
    else if (Year % 4 == 0 && Year % 100 != 0)
    {
        cout << endl << Year << " Leap Year\n";
        return;
    }
    cout << endl << Year << " Not Leap Year\n";
}

int main()
{
    while (true)
    {
        system("cls");

        int Year = ReadYear();

        LeapYearOrNot(Year);

        system("pause>0");
    }
    
}