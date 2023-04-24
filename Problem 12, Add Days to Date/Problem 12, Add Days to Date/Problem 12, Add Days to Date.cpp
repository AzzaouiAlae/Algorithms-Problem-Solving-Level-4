#include <iostream>
#include <string>

using namespace std;

short ReadNumInRange(short from, short To, string msg)
{
    short Num;
    do {
        cout << msg;
        cin >> Num;
    } while (from > Num || To < Num);
    return Num;
}

struct sDate
{
    short Day;
    short Month;
    short Year;
};

bool isLeapYear(short Year)
{
    return (Year % 4 == 0 && Year % 100 != 0) || Year % 400 == 0;
}

short DaysInMonth(short Year, short Month)
{
    short Arr[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    return Month == 2 ? (isLeapYear(Year) ? 29 : 28) : Arr[Month];
}

sDate AddDaysToDate(sDate Date, short DaysToAdd)
{        
    while (true)
    {        
        if (DaysToAdd - 366 > 0 && isLeapYear(Date.Year))
        {
            DaysToAdd -= 366;
            Date.Year++;
        }
        else if (DaysToAdd - 365 > 0 && !isLeapYear(Date.Year))
        {            
            DaysToAdd -= 365;
            Date.Year++;            
        }        
        else if (DaysToAdd - DaysInMonth(Date.Year, Date.Month) > 0)
        {
            if (Date.Month + 1 > 12)
            {                
                DaysToAdd -= DaysInMonth(Date.Year, Date.Month);
                Date.Month = 1;
                Date.Year++;                
            }
            else
            {
                DaysToAdd -= DaysInMonth(Date.Year, Date.Month);
                Date.Month++;                
            }
        }
        else if (Date.Day + DaysToAdd <= DaysInMonth(Date.Year, Date.Month))
        {
            Date.Day += DaysToAdd;
            break;
        }
        else
        {
            DaysToAdd = DaysToAdd - (DaysInMonth(Date.Year, Date.Month) - Date.Day);
            Date.Month++;            
            Date.Day = DaysToAdd;
            break;
        }
    }
    return Date;
}

int main()
{
    sDate Date;
    Date.Day = ReadNumInRange(1, 31, "Plase enter a day : ");
    Date.Month = ReadNumInRange(1, 12, "\nPlase enter a Month : ");
    Date.Year = ReadNumInRange(1, 5000, "\nPlase enter a Year : ");
    short DaysToAdd = ReadNumInRange(1, 5000, "\nHow many days to add? : ");

    Date = AddDaysToDate(Date, DaysToAdd);

    cout << "\nDate After Adding [" << DaysToAdd << "] is: " << Date.Day << "/" << Date.Month << "/" << Date.Year << "\n";

    system("pause>0");
}