#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

enum enMainMenueOption {
    enQuickWithdraw = 1, enNormalWithdraw = 2, enDeposit = 3, enCheckBalance = 4, enChangePassword = 5, enLogout = 6
};

struct stAccount {
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkOfDelete = false;
};

string AccountsFileName = "Clients.txt";

vector <stAccount> Accounts;

stAccount CurrentAcc;

double ReadNumInRange(string msg, double From, double To)
{
    double Num = 0;
    do {
        cout << msg;
        cin >> Num;
    } while (Num < From || To < Num);

    return Num;
}

bool MainMenueLoop = true;

string ConvertRecordToLine(stAccount Acc, string Sep = "#||#")
{
    string Line = Acc.AccountNumber + Sep;
    Line += Acc.PinCode + Sep;
    Line += Acc.Name + Sep;
    Line += Acc.Phone + Sep;
    Line += to_string(Acc.AccountBalance);
    return Line;
}

void SaveVecAccToFile()
{
    fstream MyFile;
    MyFile.open(AccountsFileName, ios::out);
    if (MyFile.is_open())
    {
        for (stAccount &Acc : Accounts)
        {
            if (Acc.AccountNumber == CurrentAcc.AccountNumber)
                Acc = CurrentAcc;

            if (!Acc.MarkOfDelete)
                MyFile << ConvertRecordToLine(Acc) << endl;      
        }
        MyFile.close();
    }
}

void NormalWithdraw(double Amount)
{
    while ((int)Amount % 10 != 0)
        Amount = ReadNumInRange("\n\nEnter en amount multiple of 10 : ", 1, 3200);

    char Answer;
    cout << "\nAre you sure you want to perfom this transaction y/n : ";
    cin >> Answer;
    if (tolower(Answer) == 'y')
    {
        if (CurrentAcc.AccountBalance - Amount > 0)
        {
            CurrentAcc.AccountBalance -= Amount;
            cout << "\n\nDone successfuly, New Balance is : " << CurrentAcc.AccountBalance << endl;
            SaveVecAccToFile();
            system("pause>0");
        }
        else
        {
            cout << "\n\nThe amount exceeds your balance, Make another Choise.\n";
            system("pause>0");
        }
    }     
}

void QuickWithdraw(double Withdraw)
{      
    switch (short(Withdraw))
    {
    case 1: NormalWithdraw(20); break;
    case 2: NormalWithdraw(50); break;
    case 3: NormalWithdraw(100); break;
    case 4: NormalWithdraw(200); break;
    case 5: NormalWithdraw(400); break;
    case 6: NormalWithdraw(600); break;
    case 7: NormalWithdraw(800); break;
    case 8: NormalWithdraw(1000); break;
    case 9: return;
    }
}

void ShowQuickWithdraw()
{
    system("cls");
    cout << "=================================\n";
    cout << "\tQuick Withdraw\n";
    cout << "=================================\n";
    cout << "\t[1] 20\t[2] 50\n";
    cout << "\t[3] 100\t[4] 200\n";
    cout << "\t[5] 400\t[6] 600\n";
    cout << "\t[7] 800\t[8] 1000\n";
    cout << "\t[9] Exit\n";
    cout << "=================================\n";
    cout << "\nYour Balance is : " << to_string(CurrentAcc.AccountBalance);
    
    QuickWithdraw(ReadNumInRange("\n\nChoose what do you want to do [1 to 9] : ", 1, 9));
}

void ShowNormalWithdraw()
{
    system("cls");
    cout << "=================================\n";
    cout << "\tQuick Withdraw\n";
    cout << "=================================\n";
    cout << "Your Balance is : " << to_string(CurrentAcc.AccountBalance); 

    NormalWithdraw(ReadNumInRange("\n\nEnter en amount multiple of 10 : ", 1, DBL_MAX));
}

void Deposit(double DepositAmount)
{
    cout << "\n\n\nAre you sure you want to perform this transaction y/n : ";
    char Answer;
    cin >> Answer;
    if (tolower(Answer) == 'y')
    {
        CurrentAcc.AccountBalance += DepositAmount;
        cout << "\n\nDone successfuly, New Balance is : " << CurrentAcc.AccountBalance << endl;
        SaveVecAccToFile();
        system("pause>0");
    }
}

void ShowDepositScreen()
{
    system("cls");
    cout << "=================================\n";
    cout << "\tDeposit Screen\n";
    cout << "=================================\n";

    Deposit(ReadNumInRange("Enter a positive Deposit Amount : ", 1, DBL_MAX));
}

void ShowCheckBalaceScreen()
{
    system("cls");
    cout << "=================================\n";
    cout << "\tCheck Balace\n";
    cout << "=================================\n";
    cout << "Your Balance is : " << to_string(CurrentAcc.AccountBalance);
    cout << "\n\n\nPress any key to go back to main...";
    system("pause>0");
}

bool CheckPinCode(string PinCode)
{
    return PinCode == CurrentAcc.PinCode;
}

string ReadText(string msg)
{
    cout << msg;
    string Text;
    cin >> Text;
    return Text;
}

void ShowChangePinCodeScreen()
{
    system("cls");
    cout << "=================================\n";
    cout << "\tChange Pin Code\n";
    cout << "=================================\n";
    string PinCode = ReadText("\nPlease enter the old pin code : ");
    while (!CheckPinCode(PinCode))
    {
        cout << "\nWrong pin code!!\n";
        PinCode = ReadText("\nPlease enter the old pin code : ");
    }

    cout << "Please eneter the new pin code : ";
    cin >> CurrentAcc.PinCode;
    cout << "\nDone Successfully, Press any key to go back to main...\n\n";
    

    SaveVecAccToFile();
}

void PerformMainOption(enMainMenueOption Option)
{
    switch (Option)
    {
    case enQuickWithdraw :
        ShowQuickWithdraw();
        break;
    case enNormalWithdraw :
        ShowNormalWithdraw();
        break;
    case enDeposit :
        ShowDepositScreen();
        break;
    case enCheckBalance:
        ShowCheckBalaceScreen();
        break;
    case enChangePassword:
        ShowChangePinCodeScreen();
        break;
    case enLogout:
        MainMenueLoop = false;
        break;
    }
}

void ShowMainMenue()
{
    while (MainMenueLoop)
    {
        system("cls");
        cout << "=================================\n";
        cout << "\tATM Main Menue Screen\n";
        cout << "=================================\n";
        cout << "\t[1] Quick Withdraw\n";
        cout << "\t[2] Normal Withdraw\n";
        cout << "\t[3] Deposit\n";
        cout << "\t[4] Check Balance\n";
        cout << "\t[5] Change Password\n";
        cout << "\t[6] Logout\n";
        cout << "=================================\n";
        PerformMainOption((enMainMenueOption)ReadNumInRange("Choose what do you want to do [1 to 6] : ", 1, 6));
    }    
}

vector <string> SplitText(string Line, string Sep = "#||#")
{
    vector <string> vText;
    short pos = 0;
    string Word;
    while ((pos = Line.find(Sep)) != string::npos)
    {
        Word = Line.substr(0, pos);
        if (Word != "")
            vText.push_back(Word);
        Line = Line.erase(0, pos + Sep.size());
    }

    if(Line != "")
        vText.push_back(Line);

    return vText;
}

stAccount ConvertLineToAcc(string Line, string Sep = "#||#")
{
    vector <string> strAcc = SplitText(Line);
    stAccount Account;
    if (strAcc.size() > 4)
    {
        Account.AccountNumber = strAcc[0];
        Account.PinCode = strAcc[1];
        Account.Name = strAcc[2];
        Account.Phone = strAcc[3];
        Account.AccountBalance = stod(strAcc[4]);
    }    

    return Account;
}

vector <stAccount> LoadAccountFromFile()
{
    vector <stAccount> vAccounts;
    fstream MyFile;
    string Line = "";
    MyFile.open(AccountsFileName, ios::in);
    if (MyFile.is_open())
    {
        while (getline(MyFile, Line))
        {
            stAccount Account = ConvertLineToAcc(Line);
            vAccounts.push_back(Account);
        }
        MyFile.close();
    }
    return vAccounts;
}

bool FindClientByAccAndPass(string AccountNumber, string PinCode)
{
    Accounts = LoadAccountFromFile();

    for (stAccount Acc : Accounts)
    {
        if (Acc.AccountNumber == AccountNumber && Acc.PinCode == PinCode)
        {
            CurrentAcc = Acc;
            return true;
        }
        else
            return false;
    }
}

bool CheckAccAndPass(string AccountNumber, string PinCode)
{
    if (FindClientByAccAndPass(AccountNumber, PinCode))
        return true;
    else
        return false;
}

void Login()
{
    string AccountNumber, PinCode;
    bool InvalidAccPin = false;
    do
    {
        system("cls");
        cout << "--------------------------------------\n";
        cout << "\tATM Main Menue Screen\n";
        cout << "--------------------------------------\n";

        if (InvalidAccPin)
            cout << "invalid AccountNumber/Code!\n";

        cout << "Enter Account Number : ";
        cin >> AccountNumber;
        cout << "Enter Code : ";
        cin >> PinCode;

        InvalidAccPin = !CheckAccAndPass(AccountNumber, PinCode);

    } while (InvalidAccPin);
    MainMenueLoop = true;
    ShowMainMenue();
}

int main()
{
    while(true)
        Login();
}