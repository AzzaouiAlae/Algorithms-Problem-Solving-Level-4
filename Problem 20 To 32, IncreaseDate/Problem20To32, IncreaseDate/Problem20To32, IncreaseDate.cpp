#include <iostream>

using namespace std;

struct sDate {
    short Day;
    short Month;
    short Year;
};

bool IsLeapYear(int Year)
{
    return (Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0);
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

sDate IncroseDateByXdays(sDate Date, short HowManyDays)
{
    for (short i = 0; i < HowManyDays; i++)    
        Date = IncreseDateByOneDay(Date);
    
    return Date;
}

sDate IncroseDateByOneWeek(sDate Date)
{
    Date = IncroseDateByXdays(Date, 7);

    return Date;
}

sDate IncroseDateByXWeek(sDate Date, short HowManyWeeks)
{
    for(short i = 0; i < HowManyWeeks; i++)
        Date = IncroseDateByOneWeek(Date);

    return Date;
}

sDate IncroseDateByOneMonth(sDate Date)
{
    if (IsLastMonth(Date))
    {
        Date.Year++;
        Date.Month = 1;
    }
    else
        Date.Month++;

    if (Date.Day > DaysInMonth(Date.Year, Date.Month))
        Date.Day = DaysInMonth(Date.Year, Date.Month);

    return Date;
}

sDate IncroseDateByXmonth(sDate Date, short HowManyMonth)
{
    for (short i = 0; i < HowManyMonth; i++)    
        Date = IncroseDateByOneMonth(Date);

    return Date;    
}

sDate IncroseDateByOneYear(sDate Date)
{
    Date.Year++;

    return Date;
}

sDate IncroseDateByXyear(sDate Date, short HowManyYear)
{
    for (int i = 0; i < HowManyYear; i++)
        Date = IncroseDateByOneYear(Date);

    return Date;
}

sDate IncroseDateByXyearFaster(sDate Date, short HowManyYear)
{
    Date.Year += HowManyYear;

    return Date;        
}

sDate IncroseDateByOneDecade(sDate Date)
{
    Date = IncroseDateByXyearFaster(Date, 10);

    return Date;
}

sDate IncroseDateByXdecade(sDate Date, short HowManyDecade)
{
    for(int i = 0; i < HowManyDecade; i++)
        Date = IncroseDateByXyearFaster(Date, 10);

    return Date;
}

sDate IncroseDateByXdecadeFaster(sDate Date, short HowManyDecade)
{    
    Date = IncroseDateByXyearFaster(Date, (10 * HowManyDecade));
    return Date;
}

sDate IncroseDateByOneCentury(sDate Date)
{
    Date.Year += 100;
    return Date;
}

sDate IncroseDateByOneMillennium(sDate Date)
{
    Date.Year += 1000;
    return Date;
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

int main()
{
    sDate Date = ReadFullDate();

    cout << "\nDate After\n\n";

    Date = IncreseDateByOneDay(Date);
    cout << "01-Adding one day is : " << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;

    Date = IncroseDateByXdays(Date, 10);
    cout << "02-Adding 10 days is : " << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;

    Date = IncroseDateByOneWeek(Date);
    cout << "03-Adding One Week is : " << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;

    Date = IncroseDateByXWeek(Date, 10);
    cout << "04-Adding 10 Week is : " << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;

    Date = IncroseDateByOneMonth(Date);
    cout << "05-Adding One Month is : " << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;

    Date = IncroseDateByXmonth(Date, 5);
    cout << "06-Adding 5 Month is : " << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;

    Date = IncroseDateByOneYear(Date);
    cout << "07-Adding One Year is : " << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;

    Date = IncroseDateByXyear(Date, 10);
    cout << "08-Adding 10 Years is : " << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;

    Date = IncroseDateByXyearFaster(Date, 10);
    cout << "09-Adding 10 Years (faster) is : " << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;

    Date = IncroseDateByOneDecade(Date);
    cout << "10-Adding One Decade is : " << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;

    Date = IncroseDateByXdecade(Date, 10);
    cout << "11-Adding 10 Decade is : " << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;

    Date = IncroseDateByXdecadeFaster(Date, 10);
    cout << "12-Adding 10 Decade (faster) is : " << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;

    Date = IncroseDateByOneCentury(Date);
    cout << "13-Adding One Century is : " << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;

    Date = IncroseDateByOneMillennium(Date);
    cout << "14-Adding One Millennium is : " << Date.Day << "/" << Date.Month << "/" << Date.Year << endl;


}