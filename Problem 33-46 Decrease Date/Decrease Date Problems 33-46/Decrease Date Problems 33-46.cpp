#include <iostream>

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

bool IsLeapYear(int Year)
{
    return (Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0);
}

short DaysInMonth(sDate Date)
{
    short Arr[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    return Date.Month == 2 ? (IsLeapYear(Date.Year) ? 29 : 28) : Arr[Date.Month];
}

sDate DecreaseDateByOneDay(sDate Date)
{
    if (Date.Day == 1)
    {
        if (Date.Month == 1)
        {
            Date.Year--;
            Date.Month = 12;
            Date.Day = 31;
        }
        else
        {
            Date.Month--;
            Date.Day = DaysInMonth(Date);
        }
    }
    else
        Date.Day--;

    return Date;
}

sDate DecreaseDateByXdays(sDate Date, short HowManyDays)
{
    for (short i = 0; i < HowManyDays; i++)
        Date = DecreaseDateByOneDay(Date);

    return Date;
}

sDate DecreaseDateByOneWeek(sDate Date)
{
    Date = DecreaseDateByXdays(Date, 7);

    return Date;
}

sDate DecreaseDateByXWeeks(sDate Date, short HowManyWeeks)
{
    for (short i = 0; i < HowManyWeeks; i++)
        Date = DecreaseDateByOneWeek(Date);

    return Date;
}

sDate DecreaseDateByOneMonth(sDate Date, bool CheckDaysInMonth = true)
{
    if (Date.Month == 1)
    {
        Date.Month = 12;
        Date.Year--;
    }
    else
        Date.Month--;

    if (CheckDaysInMonth && DaysInMonth(Date) < Date.Day)
        Date.Day = DaysInMonth(Date);

    return Date;
}

sDate DecreaseDateByXMonths(sDate Date, short HowManyMonths)
{
    for (short i = 0; i < HowManyMonths - 1; i++)
        Date = DecreaseDateByOneMonth(Date, false);

    return DecreaseDateByOneMonth(Date);
}

sDate DecreaseDateByOneYear(sDate Date, bool CheckDaysInYear = true)
{
    Date.Year--;
    if (CheckDaysInYear && (Date.Day > DaysInMonth(Date)))
        Date.Day = DaysInMonth(Date);

    return Date;
}

sDate DecreaseDateByXYear(sDate Date, short HowManyMonths)
{
    HowManyMonths--;
    for (short i = 0; i < HowManyMonths; i++)
        Date = DecreaseDateByOneYear(Date, false);

    return DecreaseDateByOneYear(Date);
}

sDate DecreaseDateByXYearFaster(sDate Date, short HowManyMonths)
{
    Date.Year -= (HowManyMonths - 1);

    return DecreaseDateByOneYear(Date);
}

sDate DecreaseDateByOneDecade(sDate Date, bool CheckDaysInYear = true)
{
    Date.Year -= 10;
    if (CheckDaysInYear && (Date.Day > DaysInMonth(Date)))
        Date.Day = DaysInMonth(Date);

    return Date;
}

sDate DecreaseDateByXDecades(sDate Date, short HowManyDecades)
{
    HowManyDecades--;

    for (short i = 0; i < HowManyDecades; i++)
        Date = DecreaseDateByOneDecade(Date, false);

    return DecreaseDateByOneDecade(Date);
}

sDate DecreaseDateByXDecadesFaster(sDate Date, short HowManyDecades)
{
    HowManyDecades--;
    Date.Year -= (HowManyDecades * 10);

    return DecreaseDateByOneDecade(Date);
}

sDate DecreaseDateByOneCentury(sDate Date)
{
    Date.Year -= 100;

    return Date;
}

sDate DecreaseDateByOneMillennium(sDate Date)
{
    Date.Year -= 1000;

    return Date;
}

int main()
{
    sDate Date = ReadFullDate();

    cout << "\nDate After\n\n";

    Date = DecreaseDateByOneDay(Date);
    cout << "01-Subtracting Date By One Day is : " << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;

    Date = DecreaseDateByXdays(Date, 10);
    cout << "02-Subtracting Date By 10 Days is : " << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;

    Date = DecreaseDateByOneWeek(Date);
    cout << "03-Subtracting Date By One Week is : " << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;

    Date = DecreaseDateByXWeeks(Date, 10);
    cout << "04-Subtracting Date By 10 Weeks is : " << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;

    Date = DecreaseDateByOneMonth(Date);
    cout << "05-Subtracting Date By One Month is : " << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;

    Date = DecreaseDateByXMonths(Date, 5);
    cout << "06-Subtracting Date By 5 Months is : " << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;

    Date = DecreaseDateByOneYear(Date);
    cout << "07-Subtracting Date By one year is : " << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;

    Date = DecreaseDateByXYear(Date, 10);
    cout << "08-Subtracting Date By 10 years is : " << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;

    Date = DecreaseDateByXYearFaster(Date, 10);
    cout << "09-Subtracting Date By 10 years (faster) is : " << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;

    Date = DecreaseDateByOneDecade(Date);
    cout << "10-Subtracting Date By one decade is : " << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;

    Date = DecreaseDateByXDecades(Date, 10);
    cout << "11-Subtracting Date By 10 decades is : " << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;

    Date = DecreaseDateByXDecadesFaster(Date, 10);
    cout << "12-Subtracting Date By 10 decades (faster) is : " << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;

    Date = DecreaseDateByOneCentury(Date);
    cout << "13-Subtracting Date By One Century is : " << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;

    Date = DecreaseDateByOneMillennium(Date);
    cout << "14-Subtracting Date By One Millennium is : " << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;
}