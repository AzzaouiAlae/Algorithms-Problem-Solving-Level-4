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
    switch (Month)
    {
    case 1: return 31;
    case 2: return isLeapYear(Year) ? 29 : 28;
    case 3: return 31;
    case 4: return 30;
    case 5: return 31;
    case 6: return 30;
    case 7: return 31;
    case 8: return 31;
    case 9: return 30;
    case 10: return 31;
    case 11: return 30;
    case 12: return 31;
    default: break;
    }
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