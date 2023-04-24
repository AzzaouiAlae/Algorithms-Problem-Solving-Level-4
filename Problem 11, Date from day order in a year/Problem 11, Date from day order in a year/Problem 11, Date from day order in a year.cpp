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

bool isLeapYear(short Year)
{
    return (Year % 4 == 0 && Year % 100 != 0) || Year % 400 == 0;
}

short DaysInMonth(short Year, short Month)
{
    short Arr[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    return isLeapYear(Year) ? (Month == 2 ? 29 : 28) : Arr[Month];
}

short CountDaysFromDay1InYear(short Day, short Month, short Year)
{
    short NumOfDays = 0;
    for (int i = 1; i < Month; i++)
        NumOfDays += DaysInMonth(Year, i);

    NumOfDays += Day;

    return NumOfDays;
}

string ConvertDaysToDate(short Days, short Year)
{   
    short Month = 0;

    for (Month = 1; Month <= 12; Month++)
    {
        short day = DaysInMonth(Year, Month);

        if (Days - day > 0)
            Days -= day;        

        else                 
            break;        
    }

    return to_string(Days) + "/" + to_string(Month) + "/" + to_string(Year);
}

int main()
{
    short Day = ReadNumInRange(1, 31, "Plase enter a day : ");

    short Month = ReadNumInRange(1, 12, "\nPlase enter a Month : ");

    short Year = ReadNumInRange(1, 5000, "\nPlase enter a Year : ");

    short daysFromTheBeginning = CountDaysFromDay1InYear(Day, Month, Year);

    cout << "\nNumber of days from the beginning of the year are : " << daysFromTheBeginning << endl;

    cout << "\nDate for [" << daysFromTheBeginning << "] is: " << ConvertDaysToDate(daysFromTheBeginning, Year) << "\n";
}