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

bool IsOverlapPeriod(stPeriod Period1, stPeriod Period2)
{
    if (CompareDate(Period2.End, Period1.Start) == Before 
        || 
        CompareDate(Period2.Start, Period1.End) == After)
        return false;
    
    return true;
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

int main()
{
    cout << "Enter Period 1:\n";
    stPeriod Period1 = ReadPeriod();

    cout << "\nEnter Period 2:\n";
    stPeriod Period2 = ReadPeriod();

    if (IsOverlapPeriod(Period1, Period2))
        cout << "\n\nYes, Overlap Periods\n\n";
    else
        cout << "\n\nNo, is not Overlap Periods\n\n";

    system("pause>0");
}