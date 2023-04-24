#include <iostream>

using namespace std;

enum enDateCompare{
    Before = -1,
    Equal = 0,
    After = 1
};

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

bool IsDate1BeforeDate2(sDate Date1, sDate Date2)
{
    return Date1.Year < Date2.Year ? true : (Date1.Year > Date2.Year ? false :
        (Date1.Month < Date2.Month ? true : (Date1.Month > Date2.Month ? false :
            (Date1.Day < Date2.Day ? true : false))));
}

bool IsDate1EqualsDate2(sDate Date1, sDate Date2)
{
    return Date1.Year == Date2.Year ? (Date1.Month == Date2.Month ? (Date1.Day == Date2.Day ? true : false) : false) : false;
}

enDateCompare CompareDate(sDate Date1, sDate Date2)
{
    if (IsDate1BeforeDate2(Date1, Date2))
        return Before;
    else if (IsDate1EqualsDate2(Date1, Date2))
        return Equal;
    else
        return After;
}

int main()
{
    cout << "Enter Date1:\n";
    sDate Date1 = ReadFullDate();

    cout << "\nEnter Date2:\n";
    sDate Date2 = ReadFullDate();

    cout << "\n\nCompare Result : " << CompareDate(Date1, Date2) << "\n\n";

    system("pause>0");
}