#include <iostream>
#include <string>
#include <vector>

using namespace std;

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
    return  to_string(Date.Day) + "/" + to_string(Date.Month) + "/" + to_string(Date.Year) + "\n";
}

void PrintDate(sDate Date)
{
    cout << "Day : " << Date.Day << endl;
    cout << "Month : " << Date.Month << endl;
    cout << "Year : " << Date.Year << endl;
    cout << endl;
}

void PrintDate(string Date)
{
    cout << "You Entered : " << Date;
}

int main()
{
    sDate Date = CovertStringToDate(ReadDateString());

    PrintDate(Date);

    PrintDate(Covert_sDateToString(Date));

    system("pause>0");
}