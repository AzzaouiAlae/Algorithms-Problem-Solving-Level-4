#include <iostream>
#include <string>


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

bool IsLeapYear(int Year)
{
    return (Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0);
}

short DaysInMonth(short Year, short Month)
{
    short Arr[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    return Month == 2 ? (IsLeapYear(Year) ? 29 : 28) : Arr[Month];
}

short DaysInMonth(sDate Date)
{
    return DaysInMonth(Date.Year, Date.Month);
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

bool IsWeekend(short Day)
{
    return Day == 5 || Day == 6;
}

short NumberOfDayInWeek(short Year, short Month, short Day)
{
    short a = (14 - Month) / 12;
    short y = Year - a;
    short m = Month + 12 * a - 2;

    short R = (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12));

    return R % 7;
}

short NumberOfDayInWeek(sDate Date)
{
    return NumberOfDayInWeek(Date.Year, Date.Month, Date.Day);
}

short DaysOfVacation(sDate Date1, sDate Date2)
{
    short NumberOfDays = 0;

    while (IsDate1BeforeDate2(Date1, Date2))
    {
        if (!IsWeekend(NumberOfDayInWeek(Date1)))
            NumberOfDays++;

        Date1 = IncreseDateByOneDay(Date1);
    }
    return NumberOfDays;
}

bool IsBusinessDay(short Day)
{
    return !IsWeekend(Day);
}

sDate DateOfEndVacation(sDate DateVacStart, short VacationDays)
{
    /*short Weekend = 0;
    for (short i = 1; i <= VacationDays; i++)
    {
        if (IsWeekend(NumberOfDayInWeek(DateVacStart)))
            Weekend++;

        DateVacStart = IncreseDateByOneDay(DateVacStart);
    }

    for (short i = 1; i <= Weekend; i++)
        DateVacStart = IncreseDateByOneDay(DateVacStart);

    return DateVacStart;*/

    short WeekEndCounter = 0;
    for (short i = 1; i <= VacationDays; i++)
    {
        if (IsWeekend(NumberOfDayInWeek(DateVacStart)))
            WeekEndCounter++;

        DateVacStart = IncreseDateByOneDay(DateVacStart);
    }
    //to add weekends 
    for (short i = 1; i <= WeekEndCounter; i++)
        DateVacStart = IncreseDateByOneDay(DateVacStart);
    //in case the return date is week end keep adding one day util you reach business day
     
    return DateVacStart;
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

string DayName(short Day)
{
    string Days[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };

    return Days[Day];
}

string DateToText(sDate Date)
{
    return DayName(NumberOfDayInWeek(Date)) + " , " + to_string(Date.Day) + "/" + to_string(Date.Month) + "/" + to_string(Date.Year) + "\n";
}

int main()
{
    cout << "Vacation Starts:\n";
    sDate DateVacStart = ReadFullDate();

    short VacationDays = ReadNumInRange("Vacation Days : ", 1, 30);


    cout << "\nDate End of Vacation : " << DateToText(DateOfEndVacation(DateVacStart, VacationDays));



}