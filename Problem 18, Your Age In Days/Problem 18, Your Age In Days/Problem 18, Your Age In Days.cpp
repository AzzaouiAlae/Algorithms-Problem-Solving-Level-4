#pragma warning(disable : 4996)

#include <iostream>
#include <ctime>

using namespace std;

struct sDate {
    short Year;
    short Month;
    short Day;
};

int ReadNumInRange(string Message, int From, int To)
{
    int Number;
    do {
        cout << Message;
        cin >> Number;
    } while (Number < From || Number > To);
    return Number;
}

sDate ReadFullDate()
{
    sDate Date;
    Date.Day = ReadNumInRange("Please enter a day : ", 1, 31);
    Date.Month = ReadNumInRange("Please enter a Month : ", 1, 12);
    Date.Year = ReadNumInRange("Please enter a Year : ", 1, 5000);
    return Date;
}

sDate ReadDateNow()
{
    sDate Date;
    time_t t = time(0);
    tm* gmtm = gmtime(&t);
    Date.Year = gmtm->tm_year + 1900;
    Date.Month = gmtm->tm_mon + 1;
    Date.Day = gmtm->tm_mday;
    return Date;
}

bool IsLeapYear(int Year)
{
    return(Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0);
}

short DaysInMonth(short Year, short Month)
{
    short Arr[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    return Month == 2 ? (IsLeapYear(Year) ? 29 : 28) : Arr[Month];
}

bool IsLastDayInMonth(sDate Date)
{
    return Date.Day == DaysInMonth(Date.Year, Date.Month);
}

bool IsLastMonth(sDate Date)
{
    return Date.Month == 12;
}

sDate IncreseDateByOneDay(sDate Date)
{
    if (IsLastDayInMonth(Date))
    {
        if (IsLastMonth(Date))
        {
            Date.Year++;
            Date.Month = 1;
            Date.Day = 1;
        }
        else
        {
            Date.Month++;
            Date.Day = 1;
        }
    }
    else
        Date.Day++;

    return Date;
}

bool IsDate1BeforeDate2(sDate Date1, sDate Date2)
{
    return Date1.Year < Date2.Year ? true : (Date1.Year > Date2.Year ? false :
        (Date1.Month < Date2.Month ? true : (Date1.Month > Date2.Month ? false :
            (Date1.Day < Date2.Day ? true : false))));
}

short DaysBetweenDate1Date2(sDate Date1, sDate Date2, bool IncludEndDay = false)
{
    short NumberOfDays = 0;

    while (IsDate1BeforeDate2(Date1, Date2))
    {
        NumberOfDays++;
        Date1 = IncreseDateByOneDay(Date1);
    }
    return IncludEndDay ? ++NumberOfDays : NumberOfDays;
}



int main()
{    
    sDate DateNow = ReadDateNow();
    cout << "Enter date of your birth : \n";
    sDate BirthDate = ReadFullDate();

    cout << "\nYour Age is : " << DaysBetweenDate1Date2(BirthDate, DateNow) << " Days.\n";
}