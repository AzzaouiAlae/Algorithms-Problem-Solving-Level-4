#include <iostream>

using namespace std;

short ReadNumInRange(string msg, short From, short To)
{
    short Num;
    do {
        cout << msg;
        cin >> Num;
    } while (Num < From || Num > To);
    return Num;
}

struct sDate
{
    short Day;
    short Month;
    short Year;
};

sDate ReadFullDate()
{
    sDate Date;
    Date.Day = ReadNumInRange("Please enter a day : ", 1, 31);
    Date.Month = ReadNumInRange("Please enter a Month : ", 1, 12);
    Date.Year = ReadNumInRange("Please enter a Year : ", 1, 5000);
    return Date;
}

bool isLeapYear(short Year)
{
    return (Year % 4 == 0 && Year % 100 != 0) || Year % 400 == 0;
}

short DaysInMonth(short Year, short Month)
{
    short Arr[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    return Month == 2 ? (isLeapYear(Year) ? 29 : 28) : Arr[Month];
}

sDate IncreseDateByOneDay(sDate Date)
{
    Date.Day++;
    if (Date.Day > DaysInMonth(Date.Year, Date.Month))
    {
        Date.Month++;
        Date.Day = 1;
    }      

    if (Date.Month > 12)
    {
        Date.Year++;
        Date.Month = 1;
    }
    return Date;
}

int main()
{
    sDate Date = ReadFullDate();

    Date = IncreseDateByOneDay(Date);

    cout << "Date after increse by one day is : " << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;

    system("pause>0");
}