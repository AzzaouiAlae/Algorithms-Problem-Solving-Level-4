#include <iostream>

using namespace std;

short ReadNumInRange(string msg, short From, short To)
{
    short Num;
    do {
        cout << msg;
        cin >> Num;
    } while (Num < From || Num > To);
    return Num;
}

struct sDate
{
    short Day;
    short Month;
    short Year;
};

sDate ReadFullDate()
{
    sDate Date;
    Date.Day = ReadNumInRange("Please enter a day : ", 1, 31);
    Date.Month = ReadNumInRange("Please enter a Month : ", 1, 12);
    Date.Year = ReadNumInRange("Please enter a Year : ", 1, 5000);
    return Date;
}

bool IsDate1EqualsDate2(sDate Date1, sDate Date2)
{
    return Date1.Year == Date2.Year ? (Date1.Month == Date2.Month ? (Date1.Day == Date2.Day ? true : false) : false) : false;
}

int main()
{
    sDate Date1 = ReadFullDate();
    cout << "\n";
    sDate Date2 = ReadFullDate();

    if (IsDate1EqualsDate2(Date1, Date2))
        cout << "\n\nYes, Date1 is Equals than Datr2.\n";
    else
        cout << "\n\nNo, Date1 is Not Equals than Date2.\n";

    system("pause>0");
}