#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum enFormatDate {
    enDay, enMonth, enYear
};

struct sDate {
    short Year;
    short Month;
    short Day;
};

vector <string> SplitString(string Text, string delim)
{
    vector <string> vecWords;
    short pos = 0;
    string sWord;
    while ((pos = Text.find(delim)) != string::npos)
    {
        sWord = Text.substr(0, pos);
        if (sWord != "")
        {
            vecWords.push_back(sWord);
            sWord = "";
        }

        Text = Text.erase(0, pos + delim.length());
    }

    if (Text != "")
        vecWords.push_back(Text);

    return vecWords;
}

string ReadDateString()
{
    string StrDate;
    cout << "Please enter Date dd/mm/yyyy : ";
    cin >> StrDate;
    return StrDate;
}

sDate CovertStringToDate(string strDate)
{
    vector <string> vDate = SplitString(strDate, "/");
    sDate Date;
    if (vDate.size() == 3)
    {
        Date.Day = stoi(vDate[0]);
        Date.Month = stoi(vDate[1]);
        Date.Year = stoi(vDate[2]);
    }
    return Date;
}

string Covert_sDateToString(sDate Date)
{
    return to_string(Date.Day) + "/" + to_string(Date.Month) + "/" + to_string(Date.Year) + "\n";
}

void PrintFormatDate(sDate Date, enFormatDate Format1, enFormatDate Format2, enFormatDate Format3, string Sep)
{
    string Date_String = "";

    if (Sep == "T")
    {
        switch (Format1)
        {
        case enDay: Date_String += "Day: " + to_string(Date.Day) + ", "; break;
        case enMonth: Date_String += "Month: " + to_string(Date.Month) + ", "; break;
        case enYear: Date_String += "Year: " + to_string(Date.Year) + ", "; break;
        }

        switch (Format2)
        {
        case enDay: Date_String += "Day: " + to_string(Date.Day) + ", "; break;
        case enMonth: Date_String += "Month: " + to_string(Date.Month) + ", "; break;
        case enYear: Date_String += "Year: " + to_string(Date.Year) + ", "; break;
        }

        switch (Format3)
        {
        case enDay: Date_String += "Day: " + to_string(Date.Day); break;
        case enMonth: Date_String += "Month: " + to_string(Date.Month); break;
        case enYear: Date_String += "Year: " + to_string(Date.Year); break;
        }
    }
    else
    {
        switch (Format1)
        {
        case enDay: Date_String += to_string(Date.Day) + Sep; break;
        case enMonth: Date_String += to_string(Date.Month) + Sep; break;
        case enYear: Date_String += to_string(Date.Year) + Sep; break;
        }

        switch (Format2)
        {
        case enDay: Date_String += to_string(Date.Day) + Sep; break;
        case enMonth: Date_String += to_string(Date.Month) + Sep; break;
        case enYear: Date_String += to_string(Date.Year) + Sep; break;
        }

        switch (Format3)
        {
        case enDay: Date_String += to_string(Date.Day); break;
        case enMonth: Date_String += to_string(Date.Month); break;
        case enYear: Date_String += to_string(Date.Year); break;
        }
    }
    cout << Date_String << "\n\n";
}

void PrintDate(sDate Date)
{
    cout << "Day : " << Date.Day << endl;
    cout << "Month : " << Date.Month << endl;
    cout << "Year : " << Date.Year << endl;
    cout << endl;
}

int main()
{
    sDate Date = CovertStringToDate(ReadDateString());

    cout << endl << Covert_sDateToString(Date) << endl;    
    
    PrintFormatDate(Date, enYear, enDay, enMonth, "/");

    PrintFormatDate(Date, enMonth, enDay, enYear, "/");

    PrintFormatDate(Date, enMonth, enDay, enYear, "-");

    PrintFormatDate(Date,enDay, enMonth, enYear, "-");

    PrintFormatDate(Date, enDay, enMonth, enYear, "T");
}