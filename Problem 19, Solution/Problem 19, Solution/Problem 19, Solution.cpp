#include <iostream>

using namespace std;

struct sDate {
    short Year;
    short Month;
    short Day;
};

bool IsDate1BeforeDate2(sDate Date1, sDate Date2)
{
    return Date1.Year < Date2.Year ? true : (Date1.Year > Date2.Year ? false :
        (Date1.Month < Date2.Month ? true : (Date1.Month > Date2.Month ? false :
            (Date1.Day < Date2.Day ? true : false))));
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

bool IsLeapYear(int Year)
{
    return(Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0);
}

int DaysInMonth(int Year, int Month)
{
    return Month == 2 ? (IsLeapYear(Year) ? 29 : 28) : (Month == 1 || Month == 3 || Month == 5 || Month == 7 || Month == 8 || Month == 10 || Month == 12) ? 31 : 30;
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

void SwapDates(sDate& Date1, sDate& Date2)
{
    sDate DateTemp;
    DateTemp.Day = Date1.Day;
    DateTemp.Month = Date1.Month;
    DateTemp.Year = Date1.Year;

    Date1.Day = Date2.Day;
    Date1.Month = Date2.Month;
    Date1.Year = Date2.Year;

    Date2.Day = DateTemp.Day;
    Date2.Month = DateTemp.Month;
    Date2.Year = DateTemp.Year;
}

short DaysBetweenDate1Date2(sDate Date1, sDate Date2, bool IncludEndDay = false)
{
    short NumberOfDays = 0;
    short SwapFlagValue = 1;

    if (!IsDate1BeforeDate2(Date1, Date2))
    {
        SwapDates(Date1, Date2);
        SwapFlagValue = -1;
    }     

    while (IsDate1BeforeDate2(Date1, Date2))
    {
        NumberOfDays++;
        Date1 = IncreseDateByOneDay(Date1);
    }
        
    
    return IncludEndDay ? (++NumberOfDays) * SwapFlagValue : NumberOfDays * SwapFlagValue;
}


int main()
{
    sDate Date1 = ReadFullDate();
    cout << endl;
    sDate Date2 = ReadFullDate();

    cout << "\nDiffrence is : " << DaysBetweenDate1Date2(Date1, Date2) << " Day(s)";
    cout << "\nDiffrence is (Including End Day) is : " << DaysBetweenDate1Date2(Date1, Date2, true) << " Day(s)\n";
    system("pause>0");
}