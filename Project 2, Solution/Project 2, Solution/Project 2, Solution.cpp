#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

struct stAccount {
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete = false;
};

enum enMainMeuneOption{enQuickWithdraw = 1, enNormalWithdraw = 2, enDeposit = 3, enCheckBalance = 4, enLogout = 5
};

vector <stAccount> Accounts;

short CurrentAccIndex = 0;

bool MainMenuLoop = true;

string ClientsFileName = "Clients.txt";

void ShowQuickWithdraw();

void ShowNormalWithdraw();

vector <string> SplitString(string Line, string Sep)
{
    vector <string> vData;
    string sWord;
    short Pos;
    while ((Pos = Line.find(Sep)) != string::npos)
    {
        sWord = Line.substr(0, Pos);

        if (sWord != "")
            vData.push_back(sWord);

        Line = Line.erase(0, Pos + Sep.length());
    }

    if (Line != "")
        vData.push_back(Line);

    return vData;
}

stAccount ConvertLineToRecord(string Line, string Sep = "#||#")
{
    stAccount Account;
    vector <string> vData = SplitString(Line, Sep);

    Account.AccountNumber = vData[0];
    Account.PinCode = vData[1];
    Account.Name = vData[2];
    Account.Phone = vData[3];
    Account.AccountBalance = stod(vData[4]);

    return Account;
}

void LoadAccountsDataFromFile()
{
    fstream MyFile;
    MyFile.open(ClientsFileName, ios::in);
    string Line;

    if (MyFile.is_open())
    {
        while (getline(MyFile, Line))        
            Accounts.push_back(ConvertLineToRecord(Line));     

        MyFile.close();
    }
}

bool FindClientByAccountNumberAndPinCode(string AccountNumber, string PinCode)
{
    LoadAccountsDataFromFile();

    for (short i = 0; i < Accounts.size(); i++)
    {
        if (Accounts[i].AccountNumber == AccountNumber && Accounts[i].PinCode == PinCode)
            return true;
    }
    return false;
}

bool LoadClientInfo(string AccountNumber, string PinCode)
{
    if (FindClientByAccountNumberAndPinCode(AccountNumber, PinCode))
        return true;
    else
        return false;
}

short ReadShortNumInRange(string msg, short From, short To)
{
    cout << msg;
    short Num;
    cin >> Num;
    while (Num < From || Num > To)
    {
        cout << msg;
        cin >> Num;
    }
    return Num;
}

int ReadNumMultipleBy(string msg, int Num)
{
    cout << msg;
    int Number = 0;
    cin >> Number;
    while (Number % Num != 0 || Number < 0)
    {
        cout << msg;
        cin >> Number;
    }
    return Number;
}

short GetQuickWithdrawAmount(short Option)
{
    switch (Option)
    {
    case 1: return 20;
    case 2: return 50;
    case 3: return 100;
    case 4: return 200;
    case 5: return 400;
    case 6: return 600;
    case 7: return 800;
    case 8: return 1000;
    default:return 0;
    }
    return 0;
}

string ConvertRecordToLine(stAccount Acc, string Sep = "#||#")
{
    string Line = Acc.AccountNumber + Sep;
    Line += Acc.PinCode + Sep;
    Line += Acc.Name + Sep;
    Line += Acc.Phone + Sep;
    Line += to_string(Acc.AccountBalance);
    return Line;
}

void SaveClientsDataToFile()
{
    fstream MyFile;
    MyFile.open(ClientsFileName, ios::out);

    for (stAccount& Acc : Accounts)
    {
        if (!Acc.MarkForDelete)
            MyFile << ConvertRecordToLine(Acc) << endl;
    }
}

void PerfromQuickWithdrawOption(short Option)
{
    char Answer;
    cout << "\nAre you sure you want to perfrom this trasaction y/n : ";
    cin >> Answer;
    if (tolower(Answer) == 'y')
    {
        if (Option == 9) // Exit
            return;
        short WithdrawAmount = GetQuickWithdrawAmount(Option);

        if (WithdrawAmount > Accounts[CurrentAccIndex].AccountBalance)
        {
            cout << "The Amount exceeds your balance, make another chooise";
            ShowQuickWithdraw();
            return;
        }
        Accounts[CurrentAccIndex].AccountBalance -= WithdrawAmount;
        SaveClientsDataToFile();
        cout << "Done Successdully. New Balance is : " << to_string(Accounts[CurrentAccIndex].AccountBalance) << endl;
        cout << "Press Any Key to go back to main...";
        system("pause>0");
    }
}

void ShowQuickWithdraw()
{
    system("cls");
    cout << "================================\n";
    cout << "\tQuick Withdraw\n";
    cout << "================================\n";
    cout << "\t[1] 20\t\t[2] 50\n";
    cout << "\t[3] 100\t\t[4] 200\n";
    cout << "\t[5] 400\t\t[6] 600\n";
    cout << "\t[7] 800\t\t[8] 1000\n";
    cout << "\t[9] Exit\n";
    cout << "================================\n";
    cout << "Your balance is : " << to_string(Accounts[CurrentAccIndex].AccountBalance) << endl;
    PerfromQuickWithdrawOption(ReadShortNumInRange
    ("Choose What do you want to do [1 to 9] : ", 1, 9));
}

void NormalWithdraw(int Withdraw)
{
    char Answer;
    cout << "Are you sure you want to perfrom this transaction y/n : ";
    cin >> Answer;
    if (tolower(Answer) != 'y')
        return;

    while (Withdraw > Accounts[CurrentAccIndex].AccountBalance)
    {
        cout << "The amount exceeds your balance, make another choice.\n";
        ShowNormalWithdraw();
        return;
    }
    Accounts[CurrentAccIndex].AccountBalance -= Withdraw;
    SaveClientsDataToFile();
    cout << "Done successfully. New balances is : " << to_string(Accounts[CurrentAccIndex].AccountBalance);
    cout << "\n\nPress any key to continue...";
    system("pause>0");
}

void ShowNormalWithdraw()
{
    system("cls");
    cout << "================================\n";
    cout << "\tNormal Withdraw\n";
    cout << "================================\n";
    cout << "Your balance is : " << to_string(Accounts[CurrentAccIndex].AccountBalance) << endl;
    NormalWithdraw(ReadNumMultipleBy
    ("\nEnter an amount multiple of 10 : ", 10));
}

void Deposit(int Deposit)
{
    cout << "Are you sure you want to perfrom this transaction y/n : ";
    char Answer;
    cin >> Answer;
    if (tolower(Answer) != 'y')
        return;

    Accounts[CurrentAccIndex].AccountBalance += Deposit;
    SaveClientsDataToFile();
    cout << "Done successfully. New balances is : " << to_string(Accounts[CurrentAccIndex].AccountBalance);
    cout << "\n\nPress any key to continue...";
    system("pause>0");
}

void ShowDepositScreen()
{
    system("cls");
    cout << "================================\n";
    cout << "\tDeposit Screen\n";
    cout << "================================\n";
    Deposit(ReadNumMultipleBy("Enter a positive Deposit Amount : ", 10));    
}

void CheckBalance()
{
    system("cls");
    cout << "================================\n";
    cout << "\tCheck Balance\n";
    cout << "================================\n";
    cout << "Your balance is  : " << to_string(Accounts[CurrentAccIndex].AccountBalance) << endl;
    system("pause>0");
}

void PerfromMainMenue(enMainMeuneOption Option)
{
    switch (Option)
    {
    case enQuickWithdraw:
        ShowQuickWithdraw();
        break;
    case enNormalWithdraw:
        ShowNormalWithdraw();
        break;
    case enDeposit:
        ShowDepositScreen();
        break;
    case enCheckBalance:
        CheckBalance();
        break;
    case enLogout:
        MainMenuLoop = false;
        break;
    default:
        break;
    }
}

void ShowMainMenue()
{
    while (MainMenuLoop)
    {
        system("cls");
        cout << "================================\n";
        cout << "\tATM Main Menue Screen\n";
        cout << "================================\n";
        cout << "\t[1] Quick Withdraw.\n";
        cout << "\t[2] Normal Withdrew.\n";
        cout << "\t[3] Deposit.\n";
        cout << "\t[4] Check Balance.\n";
        cout << "\t[5] Logout.\n";
        cout << "================================\n";
        PerfromMainMenue((enMainMeuneOption)ReadShortNumInRange
        ("Choose What do you want to do [1 to 5] : ", 1, 5));
    }    
}

void Login()
{
    string AccountNumber, PinCode;
    bool InvalidAccCode = false;
    do {
        system("cls");
        cout << "------------------------\n";
        cout << "\tLogin screen\n";
        cout << "------------------------\n";
        if (InvalidAccCode)
            cout << "Invalid Account Numbber code!\n";

        cout << "Enter Account Number : ";
        cin >> AccountNumber;

        cout << "Enter Pin Code : ";
        cin >> PinCode;

        InvalidAccCode = !LoadClientInfo(AccountNumber, PinCode);

    } while (InvalidAccCode);
    MainMenuLoop = true;
    ShowMainMenue();
}

int main()
{
    while(true)
        Login();
}