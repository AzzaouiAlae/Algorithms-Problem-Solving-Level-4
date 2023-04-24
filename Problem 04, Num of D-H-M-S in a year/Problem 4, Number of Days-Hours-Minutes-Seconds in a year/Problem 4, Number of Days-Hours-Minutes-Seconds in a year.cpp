#include <iostream>

using namespace std;

int ReadYear()
{
    cout << "Please enter a year to check : ";
    int Year;
    cin >> Year;
    return Year;
}

bool isLeapYear(int Year)
{
    return (Year % 4 == 0 && Year % 100 != 0) || Year % 400 == 0;
}

int DaysInYear(int Year)
{
    return isLeapYear(Year) ? 366 : 365;
}

int HoursInYear(int Year)
{
    return DaysInYear(Year) * 24;
}

int MinutesInYear(int Year)
{
    return HoursInYear(Year) * 60;
}

int SecondsInYear(int Year)
{
    return MinutesInYear(Year) * 60;
}

int main()
{
    int Year = ReadYear();

    cout << "\nNumber of days    in year [" << Year << "] is " << DaysInYear(Year);
    cout << "\nNumber of hours   in year [" << Year << "] is " << HoursInYear(Year);
    cout << "\nNumber of Minutes in year [" << Year << "] is " << MinutesInYear(Year);
    cout << "\nNumber of Seconds in year [" << Year << "] is " << SecondsInYear(Year) << endl;
    system("pause>0");
}