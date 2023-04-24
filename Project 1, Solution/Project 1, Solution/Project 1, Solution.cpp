#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>

using namespace std;

const string ClientsFileName = "Clients.txt";

const string UsersFileName = "Users.txt";

bool BackToMain = true;

struct sClient
{
    string AcountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelet = false;
};

struct sUser {
    string username;
    string password;
    short Permisson;
    bool MarkForDelet = false;
};

sUser CurrentUser;

void ShowMainMenue(vector <sClient>& Clients);

void ShowTransactionsMenueScreen(vector <sClient>& vClients);

enum enMainMenueOption
{
    enAllClients = 1, enAddNewClients = 2, enDeleteClients = 3, enUpdateClients = 4, enFindClient = 5, enTransactions = 6, enMangeUsers = 7, enLogout = 8
};

enum enManageUsersOption {
    enListeUsers = 1, enAddNewUser = 2, enDeleteUser = 3, enUpdateUser = 4, enFindUser = 5, enUsersToMain = 6
};

enum enUserPermisson {
    enPerAll = -1, enPerAllClients = 1, enPerAddNewClients = 2, enPerDeleteClients = 4, enPerUpdateClients = 8, enPerFindClient = 16, enPerTransactions = 32, enPerMangeUsers = 64
};

enum enTransactionsMenueOption
{
    enDeposit = 1, enWithdraw = 2, enTotalBalances = 3, enMainMenue = 4
};

vector <string> SplitString(string Line, string Separator = "#||#")
{
    vector <string> vDataClient;
    string sWord;
    short pos;
    while ((pos = Line.find(Separator)) != string::npos)
    {
        sWord = Line.substr(0, pos);
        if (sWord != "")
            vDataClient.push_back(sWord);

        Line = Line.erase(0, pos + Separator.length());
    }
    if (Line != "")
        vDataClient.push_back(Line);

    return vDataClient;
}

sClient ConvertLineToRecord(string Line)
{
    sClient Client;
    vector <string> vDataClient = SplitString(Line);
    if (vDataClient.size() > 4)
    {
        Client.AcountNumber = vDataClient[0];
        Client.PinCode = vDataClient[1];
        Client.Name = vDataClient[2];
        Client.Phone = vDataClient[3];
        Client.AccountBalance = stod(vDataClient[4]);
    }

    return Client;
}

vector <sClient> LoadClientsDataFromFile(string FileName)
{
    vector <sClient> vClients;
    sClient Client;
    fstream MyFile;
    string Line;
    MyFile.open(FileName, ios::in);
    if (MyFile.is_open())
    {
        while (getline(MyFile, Line))
        {
            Client = ConvertLineToRecord(Line);
            vClients.push_back(Client);
        }
        MyFile.close();
    }
    return vClients;
}

void GoBackToMainMenue(vector <sClient>& vClients)
{
    cout << "\n\nPress a key to return to Main Menue...";
    system("pause>0");
    //ShowMainMenue(vClients);
}

void PrintClientsRecordLine(vector <sClient>& vClients)
{
    for (sClient C : vClients)
    {
        cout << "| " << left << setw(15) << C.AcountNumber;
        cout << "| " << left << setw(13) << C.PinCode;
        cout << "| " << left << setw(35) << C.Name;
        cout << "| " << left << setw(15) << C.Phone;
        cout << "| " << to_string(C.AccountBalance) << endl;
    }
}

bool CheckAccessPermission(enUserPermisson enPermisson)
{
    if ((CurrentUser.Permisson & enPermisson) == enPermisson)
        return true;
    else
        return false;
}

void PrintAccessDenied()
{
    cout << "--------------------------------\n";
    cout << "Access Denied,\n";
    cout << "you dont have permission to do this \nplease contact your admin.\n";
    cout << "--------------------------------\n\n";   
}

void ShowAllClientsScreen(vector <sClient>& vClients)
{
    if (!CheckAccessPermission(enPerAllClients))
    {
        PrintAccessDenied();        
        return;
    }

    cout << "__________________________________________________________________________________________________________\n";
    cout << "\t\t\t\tClients List (" << vClients.size() << ") Clients.\n";
    cout << "__________________________________________________________________________________________________________\n";
    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(13) << "Pin Code";
    cout << "| " << left << setw(35) << "Name";
    cout << "| " << left << setw(15) << "Phone";
    cout << "| Account Balance" << endl;
    cout << "__________________________________________________________________________________________________________\n";
    PrintClientsRecordLine(vClients);
    cout << "__________________________________________________________________________________________________________\n";
}

sClient ReadNewClient()
{
    sClient Client;

    cout << "Enter Account Number : ";
    getline(cin >> ws, Client.AcountNumber);

    cout << "Enter Pin Code : ";
    getline(cin, Client.PinCode);

    cout << "Enter Name : ";
    getline(cin, Client.Name);

    cout << "Enter Phone : ";
    getline(cin, Client.Phone);

    cout << "Enter Account Balance : ";
    cin >> Client.AccountBalance;

    return Client;
}

void AddDataLineToFile(string Line, string fileName = ClientsFileName)
{
    fstream MyFile;
    MyFile.open(fileName, ios::out | ios::app);
    if (MyFile.is_open())
    {
        MyFile << Line << endl;
        MyFile.close();
    }
}

string ConvertRecordToLine(sClient Client, string Separator = "#||#")
{
    string StDataClient = Client.AcountNumber + Separator;
    StDataClient += Client.PinCode + Separator;
    StDataClient += Client.Name + Separator;
    StDataClient += Client.Phone + Separator;
    StDataClient += to_string(Client.AccountBalance);
    return StDataClient;
}

void AddNewClient(vector <sClient>& vClients)
{
    sClient Client = ReadNewClient();
    vClients.push_back(Client);
    AddDataLineToFile(ConvertRecordToLine(Client));
}

void AddNewClients(vector <sClient>& vClients)
{
    char Answer;
    do {
        AddNewClient(vClients);
        cout << "\nAre you want to add more client (Y/N) :";
        cin >> Answer;
    } while (tolower(Answer) == 'y');
}

void ShowAddNewClientsScreen(vector <sClient>& vClients)
{
    if (!CheckAccessPermission(enPerAddNewClients))
    {
        PrintAccessDenied();
        return;
    }

    cout << "____________________________________________";
    cout << "\n\t   Add new clients screen";
    cout << "\n____________________________________________\n";
    AddNewClients(vClients);
}

bool FindClientsByAccountNumber(vector <sClient>& vClients, short& AccNumInVec, string AccountNumber)
{
    for (int i = 0; i < vClients.size(); i++)
    {
        if (vClients[i].AcountNumber == AccountNumber)
        {
            AccNumInVec = i;
            return true;
        }
    }
    return false;
}

void PrintClientCard(sClient Client)
{
    cout << "\n_________________________________________";
    cout << "\nThe following are client details\n";
    cout << "\n_________________________________________";
    cout << "\nAcount Number   : " << Client.AcountNumber;
    cout << "\nPin Code        : " << Client.PinCode;
    cout << "\nName            : " << Client.Name;
    cout << "\nPhone           : " << Client.Phone;
    cout << "\nAccount Balance : " << Client.AccountBalance;
    cout << "\n_________________________________________";
}

void SaveClientDataToFile(vector <sClient>& vClients)
{
    fstream MyFile;
    string Line;
    MyFile.open(ClientsFileName, ios::out);

    if (MyFile.is_open())
    {
        for (sClient C : vClients)
        {
            if (!C.MarkForDelet)
            {
                Line = ConvertRecordToLine(C);
                MyFile << Line << endl;
            }
        }
    }
}

void DeleteClientByAccountNumber(vector <sClient>& vClients, string AccountNumber)
{
    short AccNumInVec = 0; // Account Number in vector
    char Answer;
    if (FindClientsByAccountNumber(vClients, AccNumInVec, AccountNumber))
    {
        PrintClientCard(vClients[AccNumInVec]);
        cout << "\n\nAre you sure you want to delete this client (y/n) : ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            vClients[AccNumInVec].MarkForDelet = true;

            SaveClientDataToFile(vClients);

            vClients = LoadClientsDataFromFile(ClientsFileName);
        }
        else
            cout << "Account Number (" << AccountNumber << ") not found";
    }
}

string ReadAccountNumber()
{
    cout << "\nEnter acount number : ";
    string AccountNumber;
    cin >> AccountNumber;
    return AccountNumber;
}

void ChangeClientRecord(sClient& Client)
{
    cout << "\nEnter Account Number : ";
    getline(cin >> ws, Client.AcountNumber);

    cout << "Enter Pin Code : ";
    getline(cin, Client.PinCode);

    cout << "Enter Name : ";
    getline(cin, Client.Name);

    cout << "Enter Phone : ";
    getline(cin, Client.Phone);

    cout << "Enter Account Balance : ";
    cin >> Client.AccountBalance;
}

void UpdateClientsByAccountNumber(vector <sClient>& vClients, string AccountNumber)
{
    short AccNumInVec;
    char Answer = 'y';

    if (FindClientsByAccountNumber(vClients, AccNumInVec, AccountNumber))
    {
        PrintClientCard(vClients[AccNumInVec]);

        cout << "\n\nAre you sure you want to change this client (y/n) : ";
        cin >> Answer;

        if (tolower(Answer) == 'y')
        {
            ChangeClientRecord(vClients[AccNumInVec]);
            SaveClientDataToFile(vClients);
        }
    }
}

void ShowDeleteClientsScreen(vector <sClient>& vClients)
{
    if (!CheckAccessPermission(enPerDeleteClients))
    {
        PrintAccessDenied();
        return;
    }

    cout << "____________________________________________";
    cout << "\n\t     Delete clients screen";
    cout << "\n____________________________________________";

    string AccountNumber = ReadAccountNumber();
    DeleteClientByAccountNumber(vClients, AccountNumber);
}

void ShowUpdateClientsScreen(vector <sClient>& vClients)
{
    if (!CheckAccessPermission(enPerUpdateClients))
    {
        PrintAccessDenied();
        return;
    }

    cout << "____________________________________________";
    cout << "\n\t     Update clients screen";
    cout << "\n____________________________________________";

    string AccountNumber = ReadAccountNumber();
    UpdateClientsByAccountNumber(vClients, AccountNumber);
}

void ShowFindClientsScreen(vector <sClient>& vClients)
{
    if (!CheckAccessPermission(enPerFindClient))
    {
        PrintAccessDenied();
        return;
    }

    cout << "____________________________________________";
    cout << "\n\t     Update clients screen";
    cout << "\n____________________________________________";

    short AccNumInVec;
    string AccountNumber = ReadAccountNumber();
    if (FindClientsByAccountNumber(vClients, AccNumInVec, AccountNumber))
        PrintClientCard(vClients[AccNumInVec]);

    else
        cout << "Account Number (" << AccountNumber << ") not found";
}

void ShowEndScreen()
{
    cout << "____________________________________________";
    cout << "\n\t            End screen";
    cout << "\n____________________________________________\n";
}

void Deposit(vector <sClient>& vClients)
{
    char Answer = 'n';
    string AccountNumber = ReadAccountNumber();
    short AccNumInVec;
    if (FindClientsByAccountNumber(vClients, AccNumInVec, AccountNumber))
    {
        PrintClientCard(vClients[AccNumInVec]);
        double Amoust;
        cout << "\nPlease enter deposit amoust : ";
        cin >> Amoust;
        cout << "\nAre you sure you want perform this transactions (y/n) : ";
        cin >> Answer;
        if (tolower(Answer) == 'y')
        {
            vClients[AccNumInVec].AccountBalance += Amoust;
            SaveClientDataToFile(vClients);
            cout << "\n\nDone Successfully. New Balance is : " << vClients[AccNumInVec].AccountBalance;
        }
    }
    else
        cout << "\nClient [" << AccountNumber << "] does not existe";
}

void Withdraw(vector <sClient>& vClients)
{
    char Answer = 'n';
    string AccountNumber = ReadAccountNumber();
    short AccNumInVec = 0;
    if (FindClientsByAccountNumber(vClients, AccNumInVec, AccountNumber))
    {
        PrintClientCard(vClients[AccNumInVec]);
        double Amoust = 0;
        cout << "\nPlease enter Withdraw amoust : ";
        cin >> Amoust;

        bool AmountExeeds = true;
        while (AmountExeeds)
        {
            cout << "\nAre you sure you want perform this transactions (y/n) : ";
            cin >> Answer;
            if (tolower(Answer) == 'y')
            {
                if (Amoust > vClients[AccNumInVec].AccountBalance)
                {
                    cout << "\nAmount exeeds the balance, you can withdraw up to : " << to_string(vClients[AccNumInVec].AccountBalance);
                    cout << "\nPlease enter another amount : ";
                    cin >> Amoust;
                }
                else
                {
                    vClients[AccNumInVec].AccountBalance -= Amoust;
                    SaveClientDataToFile(vClients);
                    AmountExeeds = false;
                }
            }
        }
    }
    else
        cout << "\nClient [" << AccountNumber << "] does not existe";
}

void ShowDepositScreen(vector <sClient>& vClients)
{
    char Answer = 'n';
    do {
        system("cls");
        cout << "____________________________________________";
        cout << "\n             Deposit screen";
        cout << "\n____________________________________________";

        Deposit(vClients);
        cout << "\n\nDo you want to deposit more (y/n) : ";
        cin >> Answer;
    } while (Answer == 'y');
}

void ShowWithdrawScreen(vector <sClient>& vClients)
{
    char Answer = 'n';
    do {
        system("cls");
        cout << "____________________________________________";
        cout << "\n            Withdraw screen";
        cout << "\n____________________________________________";

        Withdraw(vClients);
        cout << "\n\nDo you want to withdraw more (y/n) : ";
        cin >> Answer;
    } while (Answer == 'y');
}

void TotalBalances(vector <sClient>& vClients, short& TotalBalance)
{
    for (sClient C : vClients)
    {
        cout << "| " << left << setw(15) << C.AcountNumber;
        cout << "| " << left << setw(35) << C.Name;
        cout << "| " << to_string(C.AccountBalance) << endl;
        TotalBalance += C.AccountBalance;
    }
}

void ShowTotalBalances(vector <sClient>& vClients)
{
    short TotalBalance = 0;
    cout << "____________________________________________________________________________________________\n";
    cout << "\t\t\t\tClients List (" << vClients.size() << ") Clients.\n";
    cout << "____________________________________________________________________________________________\n";
    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(35) << "Name";
    cout << "| Account Balance" << endl;
    cout << "____________________________________________________________________________________________\n";
    TotalBalances(vClients, TotalBalance);
    cout << "____________________________________________________________________________________________";
    cout << "\n\t\t\t\tTotal Balances = " << TotalBalance;

    system("pause>0");
}

void PerformTransactionsMenueOption(vector <sClient>& vClients, enTransactionsMenueOption Option)
{
    switch (Option)
    {
    case enDeposit:
        system("cls");
        ShowDepositScreen(vClients);
        return;
        break;
    case enWithdraw:
        system("cls");
        ShowWithdrawScreen(vClients);
        return;
        break;
    case enTotalBalances:
        system("cls");
        ShowTotalBalances(vClients);
        return;
        break;
    case enMainMenue:
        system("cls");
        return;
        break;
    default: break;
    }
}

enTransactionsMenueOption ReadTransactionsMenueOption()
{
    short Choose;
    cout << "\n____________________________________________";
    cout << "\nChoose what do you want to do [1 to 4] : ";
    cin >> Choose;
    return (enTransactionsMenueOption)Choose;
}

enManageUsersOption ReadManageUsersOption()
{
    short Choose;
    cout << "\nChoose what do you want to do [1 to 6] : ";
    cin >> Choose;
    return (enManageUsersOption)Choose;
}

void ShowTransactionsMenueScreen(vector <sClient>& vClients)
{
    if (!CheckAccessPermission(enPerTransactions))
    {
        PrintAccessDenied();
        return;
    }

    enTransactionsMenueOption Option;
    do {
        system("cls");
        cout << "____________________________________________";
        cout << "\n        Transactions Menue screen";
        cout << "\n____________________________________________";
        cout << "\n\t[1] Deposit";
        cout << "\n\t[2] Withdraw";
        cout << "\n\t[3] Total Balances";
        cout << "\n\t[4] Main Menue";

        Option = ReadTransactionsMenueOption();

        PerformTransactionsMenueOption(vClients, Option);
    } while (Option != enMainMenue);

}

vector <sUser> LoadUsersDataFromFile();

void PrintUsersScreen(vector <sUser>& vUsers)
{
    for (short i = 0; i < vUsers.size(); i++)
    {
        cout << "| " << left << setw(30) << vUsers[i].username;
        cout << "| " << left << setw(30) << vUsers[i].password;
        cout << "| " << vUsers[i].Permisson << endl;
    }
    cout << "_____________________________________________________________________________\n";
}

void ShowListeUsersScreen(vector <sUser> vUsers)
{
    cout << "_____________________________________________________________________________\n";
    cout << "\t\t\tUsers List (" << vUsers.size() << ") User(s).\n";
    cout << "_____________________________________________________________________________\n";
    cout << "| " << left << setw(30) << "Username";
    cout << "| " << left << setw(30) << "Password";
    cout << "| " << "Permissions" << endl;
    cout << "_____________________________________________________________________________\n";
    PrintUsersScreen(vUsers);

    cout << "\n\nPress a key to return to Mange Users Menue...";
    system("pause>0");
}

bool UserAlredyExists(vector <sUser>& vUsers, string username)
{
    for (short i = 0; i < vUsers.size(); i++)
    {
        if (vUsers[i].username == username)
            return true;
    }
    return false;
}

bool UserAlredyExists(vector <sUser>& vUsers, string username, short& UserNumber)
{
    for (short i = 0; i < vUsers.size(); i++)
    {
        if (vUsers[i].username == username)
        {
            UserNumber = i;
            return true;
        }

    }
    return false;
}

sUser AddNewUser(vector <sUser>& vUsers)
{
    sUser user;
    char AccessAnswer;
    cout << "Adding new user\n";

    cout << "Enter username : ";
    cin >> user.username;

    while (UserAlredyExists(vUsers, user.username))
    {
        cout << "Username with [" << user.username << "] alredy exists,\nenter another username : ";
        cin >> user.username;
    }

    cout << "Enter password : ";
    cin >> user.password;

    user.Permisson = 0;

    cout << "\nDo you want to give full access y/n : ";
    cin >> AccessAnswer;

    if (AccessAnswer == 'y')
        user.Permisson = -1;
    else
    {
        cout << "\nClient List y/n : ";
        cin >> AccessAnswer;
        if (AccessAnswer == 'y')
            user.Permisson += enPerAllClients;

        cout << "\nAdd new client y/n : ";
        cin >> AccessAnswer;
        if (AccessAnswer == 'y')
            user.Permisson += enPerAddNewClients;

        cout << "\nDelete Client y/n : ";
        cin >> AccessAnswer;
        if (AccessAnswer == 'y')
            user.Permisson += enPerDeleteClients;

        cout << "\nUpdate Clients y/n : ";
        cin >> AccessAnswer;
        if (AccessAnswer == 'y')
            user.Permisson += enPerUpdateClients;

        cout << "\nFind Clent y/n : ";
        cin >> AccessAnswer;
        if (AccessAnswer == 'y')
            user.Permisson += enPerFindClient;

        cout << "\nTransactions y/n : ";
        cin >> AccessAnswer;
        if (AccessAnswer == 'y')
            user.Permisson += enPerTransactions;

        cout << "\nManage Users y/n : ";
        cin >> AccessAnswer;
        if (AccessAnswer == 'y')
            user.Permisson += enMangeUsers;
    }

    return user;
}

string ConvertUserToLine(sUser User, string Separator = "#||#")
{
    string StDataUser = User.username + Separator;
    StDataUser += User.password + Separator;
    StDataUser += to_string(User.Permisson);
    return StDataUser;
}

void ShowAddNewUsersScreen(vector <sUser>& vUsers)
{
    cout << "----------------------------------\n";
    cout << "\tAdd new user screen.\n";
    cout << "----------------------------------\n";
    vUsers.push_back(AddNewUser(vUsers));
    AddDataLineToFile(ConvertUserToLine(vUsers[vUsers.size() - 1]), UsersFileName);
}

void PrintUserCard(sUser user)
{
    cout << "------------------------\n";
    cout << "username  : " << user.username << endl;
    cout << "password  : " << user.password << endl;
    cout << "Permisson : " << user.Permisson << endl;
    cout << "------------------------\n";
}

void DeleteUserFromFile(vector <sUser>& vUsers, string username)
{
    fstream MyFile;
    string Line;
    MyFile.open(UsersFileName, ios::out);

    if (MyFile.is_open())
    {
        for (sUser U : vUsers)
        {
            if (U.username != username)
            {
                Line = ConvertUserToLine(U);
                MyFile << Line << endl;
            }
        }
    }
}

void ShowDeleteUsersScreen(vector <sUser>& vUsers)
{
    cout << "--------------------------------\n";
    cout << "\tDelete users Screen.\n";
    cout << "--------------------------------\n";
    string username;
    cout << "Please enter username : ";
    cin >> username;
    short UserNumber = 0;
    if (username == "Admin")
        cout << "\nYou cannot delete this user.\n";

    else if (UserAlredyExists(vUsers, username, UserNumber))
    {
        PrintUserCard(vUsers[UserNumber]);
        char AccessAnswer;

        cout << "Are you sure you want to delet this user y/n : ";
        cin >> AccessAnswer;

        if (tolower(AccessAnswer) == 'y')
        {
            DeleteUserFromFile(vUsers, username);
            vUsers = LoadUsersDataFromFile();
        }
    }

    else
        cout << "User with username (" << username << ") is not found!";

    cout << "\n\nPress any key to go back to Menue...";
    system("pause>0");
}

void UpdateUser(sUser& user)
{
    char AccessAnswer;

    cout << "Enter password : ";
    cin >> user.password;

    user.Permisson = 0;

    cout << "\nDo you want to give full access y/n : ";
    cin >> AccessAnswer;

    if (AccessAnswer == 'y')
        user.Permisson = -1;
    else
    {
        cout << "\nClient List y/n : ";
        cin >> AccessAnswer;
        if (AccessAnswer == 'y')
            user.Permisson += enPerAllClients;

        cout << "\nAdd new client y/n : ";
        cin >> AccessAnswer;
        if (AccessAnswer == 'y')
            user.Permisson += enPerAddNewClients;

        cout << "\nDelete Client y/n : ";
        cin >> AccessAnswer;
        if (AccessAnswer == 'y')
            user.Permisson += enPerDeleteClients;

        cout << "\nUpdate Clients y/n : ";
        cin >> AccessAnswer;
        if (AccessAnswer == 'y')
            user.Permisson += enPerUpdateClients;

        cout << "\nFind Clent y/n : ";
        cin >> AccessAnswer;
        if (AccessAnswer == 'y')
            user.Permisson += enPerFindClient;

        cout << "\nTransactions y/n : ";
        cin >> AccessAnswer;
        if (AccessAnswer == 'y')
            user.Permisson += enPerTransactions;

        cout << "\nManage Users y/n : ";
        cin >> AccessAnswer;
        if (AccessAnswer == 'y')
            user.Permisson += enMangeUsers;
    }
}

void UpdateFileUser(vector <sUser>& vUsers)
{
    fstream MyFile;
    string Line;
    MyFile.open(UsersFileName, ios::out);

    if (MyFile.is_open())
    {
        for (sUser U : vUsers)
        {
            Line = ConvertUserToLine(U);
            MyFile << Line << endl;
        }
    }
}

void ShowUpdateUser(vector <sUser>& vUsers)
{
    cout << "------------------------------\n";
    cout << "\tUpdate user screen\n";
    cout << "------------------------------\n";
    string username;

    cout << "Please enter username : ";
    cin >> username;
    short UserNumber = 0;
    if (UserAlredyExists(vUsers, username, UserNumber))
    {
        PrintUserCard(vUsers[UserNumber]);
        char AccessAnswer;

        cout << "Are you sure you want to update this user y/n : ";
        cin >> AccessAnswer;

        if (tolower(AccessAnswer) == 'y')
        {
            UpdateUser(vUsers[UserNumber]);
            UpdateFileUser(vUsers);
            cout << "User updated successfully.\n";
        }
    }
    else
        cout << "User with username (" << username << ") is not found!";

    cout << "\n\nPress any key to go back to menue...\n";
    system("pause>0");
}

void ShowFindUser(vector <sUser>& vUsers)
{
    cout << "------------------------------\n";
    cout << "\tFind user screen\n";
    cout << "------------------------------\n";
    string username;

    cout << "Please enter username : ";
    cin >> username;
    short UserNumber = 0;
    if (UserAlredyExists(vUsers, username, UserNumber))
        PrintUserCard(vUsers[UserNumber]);

    else
        cout << "User with username (" << username << ") is not found!";

    cout << "\n\nPress any key to go back to menue...\n";
    system("pause>0");
}

void PerformMangeUsersOption(enManageUsersOption Option, bool& MangeUsersLoup, vector <sUser>& vUsers)
{
    switch (Option)
    {
    case enListeUsers:
        system("cls");
        ShowListeUsersScreen(vUsers);
        break;
    case enAddNewUser:
        system("cls");
        ShowAddNewUsersScreen(vUsers);
        break;
    case enDeleteUser:
        system("cls");
        ShowDeleteUsersScreen(vUsers);
        break;
    case enUpdateUser:
        system("cls");
        ShowUpdateUser(vUsers);
        break;
    case enFindUser:
        system("cls");
        ShowFindUser(vUsers);
        break;
    case enUsersToMain:
        MangeUsersLoup = false;
        break;
    }
}

void showMangeUsersMenueScreen()
{
    if (!CheckAccessPermission(enPerMangeUsers))
    {
        PrintAccessDenied();
        return;
    }

    vector <sUser> vUsers = LoadUsersDataFromFile();
    bool MangeUsersLoup = true;
    while (MangeUsersLoup)
    {
        system("cls");
        cout << "===========================================\n";
        cout << "\tManage Users Menue Screen\n";
        cout << "===========================================\n";
        cout << "\t[1] List Users.\n";
        cout << "\t[2] Add new users.\n";
        cout << "\t[3] Delete users.\n";
        cout << "\t[4] Update users.\n";
        cout << "\t[5] Find users.\n";
        cout << "\t[6] Main Menue\n";
        cout << "===========================================\n";
        PerformMangeUsersOption(ReadManageUsersOption(), MangeUsersLoup, vUsers);
    }
}

void PerformMainMenuOption(vector <sClient>& vClients, enMainMenueOption Option)
{
    switch (Option)
    {
    case enAllClients:
        system("cls");        
        ShowAllClientsScreen(vClients);
        GoBackToMainMenue(vClients);
        break;
    case enAddNewClients:
        system("cls");        
        ShowAddNewClientsScreen(vClients);               
        GoBackToMainMenue(vClients);
        break;
    case enDeleteClients:
        system("cls");        
        ShowDeleteClientsScreen(vClients);                
        GoBackToMainMenue(vClients);
        break;
    case enUpdateClients:
        system("cls");       
        ShowUpdateClientsScreen(vClients);        
        GoBackToMainMenue(vClients);
        break;
    case enFindClient:
        system("cls");        
        ShowFindClientsScreen(vClients);        
        GoBackToMainMenue(vClients);
        break;
    case enTransactions:
        system("cls");        
        ShowTransactionsMenueScreen(vClients);              
        GoBackToMainMenue(vClients);
        break;
    case enMangeUsers:
        system("cls");        
        showMangeUsersMenueScreen();        
        GoBackToMainMenue(vClients);
        break;
    case enLogout:
        system("cls");
        BackToMain = false;
        break;
    default: GoBackToMainMenue(vClients); break;
    }
}

enMainMenueOption ReadMainMenueOption()
{
    short Choose;
    cout << "\n____________________________________________";
    cout << "\nChoose what do you want to do [1 to 8] : ";
    cin >> Choose;
    return (enMainMenueOption)Choose;
}

void ShowMainMenue(vector <sClient>& vClients)
{
    while (BackToMain)
    {
        system("cls");
        cout << "____________________________________________";
        cout << "\n\t   Main Menue Screen";
        cout << "\n____________________________________________";
        cout << "\n\t[1] Show Clients List";
        cout << "\n\t[2] Add New Clients";
        cout << "\n\t[3] Delete Clients";
        cout << "\n\t[4] Update Clients";
        cout << "\n\t[5] Find Clients";
        cout << "\n\t[6] Transactions";
        cout << "\n\t[7] Manage Users";
        cout << "\n\t[8] Logout";
        PerformMainMenuOption(vClients, ReadMainMenueOption());
    }
}

sUser ConvertLineToUser(string Line)
{
    sUser Users;
    vector <string> vUsers = SplitString(Line);
    if (vUsers.size() > 2)
    {
        Users.username = vUsers[0];
        Users.password = vUsers[1];
        Users.Permisson = stoi(vUsers[2]);
    }

    return Users;
}

vector <sUser> LoadUsersDataFromFile()
{
    vector <sUser> vUsers;

    fstream MyFile;
    MyFile.open(UsersFileName, ios::in);
    string Line;

    if (MyFile.is_open())
    {
        while (getline(MyFile, Line)) {
            vUsers.push_back(ConvertLineToUser(Line));
        }
    }
    return vUsers;
}

bool FindUserByUsernameAndPassword(string Username, string Password)
{
    vector <sUser> Users = LoadUsersDataFromFile();

    for (sUser U : Users)
    {
        if (U.username == Username && U.password == Password)
        {
            CurrentUser = U;
            return true;
        }
    }
    return false;
}

bool LoadUserInfo(string Username, string Password)
{
    if (FindUserByUsernameAndPassword(Username, Password))
        return true;

    else
        return false;
}

void LoginScreen()
{
    string Username, Password;
    bool LoginFail = false;
    do {
        system("cls");
        cout << "----------------------------\n";
        cout << "\tLogin Screen\n";
        cout << "----------------------------\n";

        if(LoginFail)
            cout << "Invalide username/password\n";

        cout << "Enter username : ";
        cin >> Username;
        cout << "Enter password : ";
        cin >> Password;

        LoginFail = !(LoadUserInfo(Username, Password));

    } while (LoginFail);
    BackToMain = true;
    vector <sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
    ShowMainMenue(vClients);
}

int main()
{    
    while(true)
        LoginScreen();

    system("pause>0");
}