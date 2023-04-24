#include <iostream>

using namespace std;

int ReadYear()
{
    cout << "Please enter year : ";
    int Year;
    cin >> Year;
    return Year;
}

int ReadMonth()
{
    cout << "\nPlease enter month : ";
    int Month;
    cin >> Month;
    return Month;
}

int ReadDay()
{
    cout << "\nPlease enter day : ";
    int day;
    cin >> day;
    return day;
}

int NumberOfDayInWeek(int Year, int Month, int Day)
{
    float a = (14 - Month) / 12;
    float y = Year - a;
    float m = Month + 12 * a - 2;

    int R = (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12));

    return R % 7;
}

string DayName(int Day)
{
    string Days[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };

    return Days[Day];
}

int main()
{
    int year = ReadYear();

    int Month = ReadMonth();

    int Day = ReadDay();

    cout << "\nDate       : " << Day << "/" << Month << "/" << year << endl;
    cout << "Date Order : " << NumberOfDayInWeek(year, Month, Day);
    cout << "\nDay Name   : " << DayName(NumberOfDayInWeek(year, Month, Day)) << endl;
}