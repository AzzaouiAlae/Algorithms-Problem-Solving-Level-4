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

bool IsDate1BeforeDate2(sDate Date1, sDate Date2)
{   
    return Date1.Year < Date2.Year ? true : (Date1.Year > Date2.Year ? false :
           (Date1.Month < Date2.Month ? true : (Date1.Month > Date2.Month ? false :
           (Date1.Day < Date2.Day ? true : false))));
}

int main()
{
    sDate Date1 = ReadFullDate();
    cout << "\n";
    sDate Date2 = ReadFullDate();

    if (IsDate1BeforeDate2(Date1, Date2))
        cout << "\n\nYes, Date1 is Less than Datr2.\n";
    else
        cout << "\n\nNo, Date1 is Not Less than Date2.\n";

    system("pause>0");
}