#include <iostream>

using namespace std;

enum enDateCompare {
    Before = -1,
    Equal = 0,
    After = 1
};

struct sDate {
    short Year;
    short Month;
    short Day;
};

struct stPeriod {
    sDate Start;
    sDate End;
};

bool IsDate1BeforeDate2(sDate Date1, sDate Date2)
{
    return Date1.Year < Date2.Year ? true : (Date1.Year > Date2.Year ? false :
        (Date1.Month < Date2.Month ? true : (Date1.Month > Date2.Month ? false :
            (Date1.Day < Date2.Day ? true : false))));
}

bool IsDate1EqualsDate2(sDate Date1, sDate Date2)
{
    return Date1.Year == Date2.Year ? (Date1.Month == Date2.Month ? (Date1.Day == Date2.Day ? true : false) : false) : false;
}

enDateCompare CompareDate(sDate Date1, sDate Date2)
{
    if (IsDate1BeforeDate2(Date1, Date2))
        return Before;
    else if (IsDate1EqualsDate2(Date1, Date2))
        return Equal;
    else
        return After;
}

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

stPeriod ReadPeriod()
{
    stPeriod Period;
    cout << "\nEnter Start Date:\n";
    Period.Start = ReadFullDate();

    cout << "\nEnter End Date:\n";
    Period.End = ReadFullDate();

    return Period;
}

bool IsLeapYear(int Year)
{
    return (Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0);
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

bool IsDateWithInPeriod(stPeriod Period, sDate Date)
{
    return !(CompareDate(Date, Period.Start) == Before || CompareDate(Date, Period.End) == After);
}

bool IsOverlapPeriod(sDate Period1StartDate, sDate Period1EndDate, sDate Period2StartDate, sDate Period2EndDate)
{
    return CompareDate(Period1StartDate, Period2EndDate) != After && CompareDate(Period1EndDate, Period2StartDate) != Before;
}

bool IsOverlapPeriod(stPeriod Period1, stPeriod Period2)
{
    return IsOverlapPeriod(Period1.Start, Period1.End, Period2.Start, Period2.End);
}

short CountOverlapDays(stPeriod Period1, stPeriod Period2)
{
    if (IsOverlapPeriod(Period1, Period2))
    {
        if (CompareDate(Period1.Start, Period2.End) == Before && CompareDate(Period1.Start, Period2.Start) == After && CompareDate(Period1.End, Period2.End) == After)
            return DaysBetweenDate1Date2(Period1.Start, Period2.End);

        else if(CompareDate(Period2.Start, Period1.Start) == After && CompareDate(Period2.Start, Period1.End) == Before && CompareDate(Period2.End, Period1.End) == After)
            return DaysBetweenDate1Date2(Period2.Start, Period1.End);

        else if(CompareDate(Period1.Start, Period2.Start) == After && CompareDate(Period1.End, Period2.End) == Before)
            return DaysBetweenDate1Date2(Period1.Start, Period1.End);

        else if (CompareDate(Period1.Start, Period2.Start) == Before && CompareDate(Period1.End, Period2.End) == After)
            return DaysBetweenDate1Date2(Period2.Start, Period2.End);

        else 
            return 1;
    }
    else
        return 0;
}

int main()
{
    cout << "Enter Period 1:\n";
    stPeriod Period1 = ReadPeriod();

    cout << "Enter Period 2:\n";
    stPeriod Period2 = ReadPeriod();

    cout << "\nOverlap days count is : " << CountOverlapDays(Period1, Period2) << "\n";

    system("pause>0");
}