#include <iostream>

using namespace std;

int ReadNumber()
{
    cout << "Enter Number : ";
    int Number;
    cin >> Number;
    return Number;
}

string NumberToText(int Number)
{
    if (Number == 0)
        return "";

    else if (Number >= 1 && Number <= 19)
    {
        string Arr[] = { "", "One", "Two","Three","Four","Five","Six","Seven",
                             "Eight","Nine","Ten","Eleven","Twelve","Thirteen","Fourteen",
                             "Fifteen","Sixteen","Seventeen","Eighteen","Nineteen" };
        return Arr[Number] + " ";
    }

    else if (Number >= 20 && Number <= 99)
    {
        string Arr[] = { "", "", "Twenty","Thirty","Forty","Fifty","Sixty","Seventy","Eighty","Ninety" };

        return Arr[Number / 10] + " " + NumberToText(Number % 10);
    }

    else if (Number >= 100 && Number <= 199)
    {
        return "One Hundred " + NumberToText(Number % 100);
    }

    else if (Number >= 200 && Number <= 999)
    {
        return NumberToText(Number / 100) + "Hundreds " + NumberToText(Number % 100);
    }

    else if (Number >= 1000 && Number <= 1999)
    {
        return "One Thousand " + NumberToText(Number % 1000);
    }

    else if (Number >= 2000 && Number <= 999999)
    {
        return NumberToText(Number / 1000) + "Thousands " + NumberToText(Number % 1000);
    }

    else if (Number >= 1000000 && Number <= 1999999)
    {
        return "One Million " + NumberToText(Number % 1000000);
    }

    else if (Number >= 2000000 && Number <= 999999999)
    {
        return NumberToText(Number / 1000000) + "Millions " + NumberToText(Number % 1000000);
    }

    else if (Number >= 100000000 && Number <= 199999999)
    {
        return "One Billion " + NumberToText(Number % 100000000);
    }

    else if (Number >= 200000000 && Number <= 99999999999)
    {
        return NumberToText(Number / 100000000) + "Billions " + NumberToText(Number % 100000000);
    }
}

int main()
{
    int Number = ReadNumber();

    cout << endl << NumberToText(Number) << endl;
}