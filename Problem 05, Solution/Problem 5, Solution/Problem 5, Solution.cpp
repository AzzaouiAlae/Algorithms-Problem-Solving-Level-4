#include <iostream>

using namespace std;

int ReadYear()
{
    cout << "Please enter a year to check : ";
    int Year;
    cin >> Year;
    return Year;
}

int ReadMonth()
{
    int Month;

    do {
        cout << "Please enter a month to check : ";
        cin >> Month;
    } while (Month < 1 && Month > 13);

    return Month;
}

bool isLeapYear(int Year)
{
    return (Year % 4 == 0 && Year % 100 != 0) || Year % 400 == 0;
}

int DaysInMonth(int Year, int Month)
{
    if (Month == 2)
        return isLeapYear(Year) ? 29 : 28;

    short Arr31Days[] = { 1, 3, 5, 7, 8, 10, 12 };

    for (int i = 0; i < 7; i++)
    {
        if (Arr31Days[i] == Month)
        {
            return 31;
        }
    }
    return 30;
}

int HoursInMonth(int Year, int Month)
{
    return DaysInMonth(Year, Month) * 24;
}

int MinutesInMonth(int Year, int Month)
{
    return HoursInMonth(Year, Month) * 60;
}

int SecondsInMonth(int Year, int Month)
{
    return MinutesInMonth(Year, Month) * 60;
}

int main()
{
    int Year = ReadYear();

    int Month = ReadMonth();

    cout << "\nNumber of days    in Month [" << Month << "] is " << DaysInMonth(Year, Month);
    cout << "\nNumber of hours   in Month [" << Month << "] is " << HoursInMonth(Year, Month);
    cout << "\nNumber of Minutes in Month [" << Month << "] is " << MinutesInMonth(Year, Month);
    cout << "\nNumber of Seconds in Month [" << Month << "] is " << SecondsInMonth(Year, Month) << endl;
    system("pause>0");
}