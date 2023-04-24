#include <iostream>

using namespace std;

struct sDate {
    short Year;
    short Month;
    short Day;
};

int ReadNum(string Message)
{
    int Number;
    cout << Message;
    cin >> Number;
    return Number;
}

sDate ReadFullDate()
{
    sDate Date;
    Date.Day = ReadNum("Please enter a day : ");
    Date.Month = ReadNum("Please enter a Month : ");
    Date.Year = ReadNum("Please enter a Year : ");
    return Date;
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

bool IsValidateDate(sDate Date)
{
    if (Date.Day > 31 || Date.Day < 1)
        return false;

    if (Date.Month < 1 || Date.Month > 12)
        return false;

    if (Date.Month == 2)
    {
        if (IsLeapYear(Date.Year))
        {
            if (Date.Day > 29)
                return false;           
        }
        else
        {
            if (Date.Day > 28)
                return false;
        }
    }

    short NumOfDaysInMonth = DaysInMonth(Date.Year, Date.Month);

    if (Date.Day > NumOfDaysInMonth)
        return false;

    return true;
}

int main()
{
    cout << "Enter a Date : \n";
    sDate Date = ReadFullDate();

    if (IsValidateDate(Date))
        cout << "\nYes, Date is a valide date.\n";
    else
        cout << "\nNo, Date is a Not valide date.\n";

    system("pause>0");
}