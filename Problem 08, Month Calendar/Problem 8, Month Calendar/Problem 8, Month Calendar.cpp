#include <iostream>
#include <iomanip>

using namespace std;

short ReadYear()
{
    cout << "Please enter a year to check : ";
    short Year;
    cin >> Year;
    return Year;
}

short ReadMonth()
{
    short Month;

    do {
        cout << "Please enter a month to check : ";
        cin >> Month;
    } while (Month < 1 && Month > 13);

    return Month;
}

bool isLeapYear(short Year)
{
    return (Year % 4 == 0 && Year % 100 != 0) || Year % 400 == 0;
}

short DaysInMonth(short Year, short Month)
{
    short Arr[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    return isLeapYear(Year) ? (Month == 2 ? 29 : 28) : Arr[Month];
}

short NumberOfDayInWeek(short Year, short Month, short Day)
{
    short a = (14 - Month) / 12;
    short y = Year - a;
    short m = Month + 12 * a - 2;    

    return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
}

string DayName(short Day)
{
    string DaysName[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };

    return DaysName[Day];
}

string MonthsName(short Month)
{
    string MonthsName[] = { "", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

    return MonthsName[Month];
}

void PrintCalendar(short Year, short Month)
{
    cout << "\n\n________________" << MonthsName(Month) << "________________\n\n";

    for (short i = 0; i < 7; i++)
        cout <<  setw(5) << DayName(i);

    cout << endl;

    short DaysMonth = DaysInMonth(Year, Month);

    short NumberOfDay = NumberOfDayInWeek(Year, Month, 1);

    short j;
    for (j = 0; j < NumberOfDay; j++)    
        cout << "     ";    
    
    for (short i = 0; i < DaysMonth;)
    {
        for (; j < 7 && i < DaysMonth; j++)
        {            
            cout << setw(5) << i + 1;
            i++;
        } 
        j = 0;
        cout << endl;
    }
    cout << "___________________________________\n";
}

int main()
{
    short Year = ReadYear();
    short Month = ReadMonth();

    PrintCalendar(Year, Month);

    system("pause>0");
}