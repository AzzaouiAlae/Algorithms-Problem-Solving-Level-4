#include <iostream>
#include <vector>
#include <string>

using namespace std;

int ReadNumber()
{
    cout << "Enter Number : ";
    int Number;
    cin >> Number;
    return Number;
}

void Convert(string &TextNumber, int &Number, short j = 0)
{
    vector <string> vTextNumber = { "", "One", "two", "three", "four", "five", "six", "seven", "eight", "nine" };

    vector <string> vTextNumber2 = { "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen",
                                    "eighteen", "nineteen", };

    vector <string> vTextNumber3 = { "twenty", "thirty", "forty", "fifty", "sixty", "seventy",
                                    "eighty", "ninety" };

    vector <string> vTextNumber4 = { "hundred", "thousand", "million", "billion" };

    
        if (Number - ((Number / 100) * 100) <= 9)
        {
            if (!(Number - ((Number / 10) * 10) == 0))
                TextNumber = vTextNumber[Number - ((Number / 100) * 100)] + TextNumber;
            Number /= 100;
        }
        else if (Number - ((Number / 100) * 100) <= 19)
        {
            TextNumber = vTextNumber2[Number - ((Number / 100) * 100) - 10] + TextNumber;
            Number /= 100;
        }
        else if (Number - ((Number / 100) * 100) <= 99)
        {
            if (!(Number - ((Number / 10) * 10) == 0))
                TextNumber = vTextNumber[Number - ((Number / 10) * 10)] + TextNumber;
            Number /= 10;

            TextNumber = vTextNumber3[Number - ((Number / 10) * 10) - 2] + " " + TextNumber;
            Number /= 10;
        }      

        if (Number - ((Number / 10) * 10) <= 9)
        {
            if (!(Number - ((Number / 10) * 10) == 0))
                TextNumber = vTextNumber[Number - ((Number / 10) * 10)] + " " + vTextNumber4[0] + " " + TextNumber;
            Number /= 10;
        }
    

    if (Number > 0)
    {
        j++;
        TextNumber = " " + vTextNumber4[j] + " " + TextNumber;
        Convert(TextNumber, Number, j);
    }

}

string ConvertNumberToText(int Number)
{    
    string TextNumber = "";

    Convert(TextNumber, Number);
    
    return TextNumber;
}

int main()
{
    int Number = ReadNumber();
    cout << endl << ConvertNumberToText(Number) << endl;
    system("pause>0");
}