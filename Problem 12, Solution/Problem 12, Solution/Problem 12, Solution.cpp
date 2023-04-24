#include <iostream>

using namespace std;

struct sDate
{
    short Day;
    short Month;
    short Year;
};

short ReadNumInRange(string msg, short From, short To)
{
    short Num;
    do {
        cout << msg;
        cin >> Num;
    } while (Num < From || Num > To);
    return Num;
}

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

short CountDaysFromDay1InYear(short Day, short Month, short Year)
{
    short NumOfDays = 0;
    for (int i = 1; i < Month; i++)
        NumOfDays += DaysInMonth(Year, i);

    NumOfDays += Day;

    return NumOfDays;
}

sDate AddDaysToDate(sDate Date, short DaysToAdd)
{
    short RemainingDays = DaysToAdd + CountDaysFromDay1InYear(Date.Day, Date.Month, Date.Year);
    short MonthDays = 0;
    Date.Month = 1;

    while (true)
    {
        MonthDays = DaysInMonth(Date.Year, Date.Month);

        if (MonthDays <= RemainingDays)
        {
            RemainingDays -= MonthDays;
            Date.Month++;

            if (Date.Month > 12)
            {
                Date.Month = 1;
                Date.Year++;
            }
        }
        else
        {
            Date.Day = RemainingDays;
            break;
        }
    }
    return Date;
}

int main()
{
    sDate Date = ReadFullDate();

    short DaysToAdd = ReadNumInRange("How many Days To Add : ", 1, 10000);

    Date = AddDaysToDate(Date, DaysToAdd);


    cout << "\nDate After Adding [" << DaysToAdd << "] is: " << Date.Day << "/" << Date.Month << "/" << Date.Year << "\n";

    system("pause>0");
}