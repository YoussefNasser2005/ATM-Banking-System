#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

struct sClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    long long AccountBalance = 0;
    bool MarkForDelete = false;
    bool DoTransaction = false;
};

const string ClientsFileName = "Clients.txt";

enum EnPermissions
{
    pcall = -1,
    pcClientList = 1,
    pcNew_Client = 2,
    pcDeleteAcc = 4,
    pcUpdate_Client = 8,
    pcFind_Client = 16,
    pcTrans_actions = 32,
    pcManage_Users = 64,
};

enum EnTransactionsMenuOptions
{
    Deposit = 1, Withdraw = 2, Total_Balance = 3, Main_Menu = 4
};

enum EnMainMenuOptions
{
    Quick_With = 1, Norm_With = 2, De_posit = 3, Check_Balance = 4, Log_out = 5, Exit = 6,
};

void SwitchOpenMainMenu();

vector<string> SplitString(string s1, string delim = " ")
{
    short pos = 0; string sword;
    vector<string> vString;
    while ((pos = s1.find(delim)) != std::string::npos)
    {
        sword = s1.substr(0, pos);
        if (!sword.empty())
            vString.push_back(sword);
        s1.erase(0, pos + delim.length());
    }
    if (!s1.empty())
        vString.push_back(s1);
    return vString;
}

sClient ConvertLineToRecord(string Line, string Separator = "//")
{
    sClient Client;
    vector<string> vString = SplitString(Line, Separator);
    if (vString.size() < 5) return sClient();
    Client.AccountNumber = vString[0];
    Client.Name = vString[1];
    Client.PinCode = vString[2];
    Client.Phone = vString[3];
    Client.AccountBalance = stoll(vString[4]);
    return Client;
}

vector<sClient> LoadClientsDataFromFile(string FileName)
{
    fstream MyFile;
    vector<sClient> vClients;
    MyFile.open(FileName, ios::in);
    if (MyFile.is_open())
    {
        string line;
        while (getline(MyFile, line))
            vClients.push_back(ConvertLineToRecord(line));
        MyFile.close();
    }
    return vClients;
}

string ConvertRecordToLine(sClient Client, string delim = "//")
{
    string s1 = "";
    s1 += Client.AccountNumber + delim;
    s1 += Client.Name + delim;
    s1 += Client.PinCode + delim;
    s1 += Client.Phone + delim;
    s1 += to_string(Client.AccountBalance);
    return s1;
}

vector<sClient> SaveClientsDataToFile(string FileName, vector<sClient> vClients)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out);
    if (MyFile.is_open())
    {
        for (sClient& C : vClients)
        {
            if (!C.MarkForDelete)
            {
                string DataLine = ConvertRecordToLine(C);
                MyFile << DataLine << endl;
            }
        }
        MyFile.close();
    }
    return vClients;
}

sClient CurrentClient;
vector<sClient> vClients = LoadClientsDataFromFile(ClientsFileName);

short MainMenu()
{
    short num = 0;
    system("cls");
    cout << "***************************************************************\n";
    cout << "\t\t\t|================|                    *\n";
    cout << "\t\t\t|      ATM       |                    *\n";
    cout << "\t\t\t|Main Menu Screen|                    *\n";
    cout << "\t\t\t|================|                    *\n";
    cout << "***************************************************************\n\n";
    cout << " [1] Quick Withdraw.                                          *\n\n";
    cout << " [2] Normal Withdraw.                                         *\n\n";
    cout << " [3] Deposit.                                                 *\n\n";
    cout << " [4] Check Balance.                                           *\n\n";
    cout << " [5] Logout                                                   *\n\n";
    cout << " [6] Exit.                                                    *\n\n";
    cout << "***************************************************************\n\n";
    cout << " -Choose What DO You Want To Do? [1 -> 6] ";
    cin >> num;
    return num;
}

short QuickWithDrawMainMenu()
{
    short num = 0;
    system("cls");
    cout << "********************************\n";
    cout << "\t|================|     *\n";
    cout << "\t|Quick With Draw |     *\n";
    cout << "\t|================|     *\n";
    cout << "********************************\n\n";
    cout << " [1]  20         [2]  50       *\n\n";
    cout << " [3]  100        [4]  200      *\n\n";
    cout << " [5]  400        [6]  600      *\n\n";
    cout << " [7]  800        [8]  1000     *\n\n";
    cout << " [9] Exit.                     *\n\n";
    cout << "********************************\n\n";
    cout << "Your Balance Is: " << CurrentClient.AccountBalance << endl;
    cout << " -Choose What DO You Want To Do? [1 -> 9] ";
    cin >> num;
    return num;
}

void PressKey_GoOut()
{
    cout << "\n\nPress Any Key To Close This Window....";
    system("pause>0");
}

void MessagesScreens(string Title)
{
    system("cls");
    cout << "_______________________________\n\n";
    cout << "      " << Title << "           \n";
    cout << "_______________________________\n\n";
}

bool DepositOrWithdrawBalanceToClientByAccountNumber(long long Amount)
{
    char Answer = 'n';
    cout << "Are you sure you want perform this transaction? y/n ? ";
    cin >> Answer;

    if (Answer == 'y' || Answer == 'Y')
    {
        CurrentClient.AccountBalance += Amount;

        for (sClient& C : vClients)
        {
            if (C.AccountNumber == CurrentClient.AccountNumber)
            {
                C.AccountBalance = CurrentClient.AccountBalance;
                break;
            }
        }

        SaveClientsDataToFile(ClientsFileName, vClients);
        cout << "\n\nDone Successfully. New balance is: " << CurrentClient.AccountBalance;
    }

    PressKey_GoOut();
    return true;
}

void HandleTransaction(string ScreenTitle, bool IsDeposit)
{
    long long amount;
    MessagesScreens(ScreenTitle);
    cout << "Your Balance Is: " << CurrentClient.AccountBalance << endl;

    if (!IsDeposit)
    {
        cout << "Enter an amount of 5's\n";
        cin >> amount;
        while (amount % 5 != 0)
        {
            cout << "Invalid input! Enter an amount of 5's: ";
            cin >> amount;
        }
        if (amount > CurrentClient.AccountBalance)
        {
            cout << "\nAmount Exceeds Balance, You Can Withdraw Up To: " << CurrentClient.AccountBalance << endl;
            PressKey_GoOut();
            return;
        }
    }
    else
    {
        cout << "Enter the amount of your transaction: "; cin >> amount;
    }

    long long FinalAmount = IsDeposit ? amount : -amount;
    DepositOrWithdrawBalanceToClientByAccountNumber(FinalAmount);
}

sClient GetClientInfo(vector <sClient>& vClients, string& AccNum, string& Picode)
{
    for (sClient& C : vClients)
    {
        if (C.AccountNumber == AccNum && C.PinCode == Picode)
        {
            return C;
        }
    }
    return sClient{ "", "" };
}

void CheckBalance()
{
    MessagesScreens("Check Balance Screen.");
    cout << "Your Balance Is: " << CurrentClient.AccountBalance;
    PressKey_GoOut();
}

void Ends_Program()
{
    MessagesScreens("Program Closed :-)");
    PressKey_GoOut();
}

void MakeQuickWDraw()
{
    long long WithdrawOptions[] = { 0, 20, 50, 100, 200, 400, 600, 800, 1000 };

    while (true)
    {
        short choose = QuickWithDrawMainMenu();

        if (choose == 9)
        {
            cout << "Transaction canceled.\n";
            break;
        }

        if (choose < 1 || choose > 8)
        {
            cout << "Invalid option. Try again.\n";
            system("pause>0");
            continue;
        }

        char Ans;
        cout << "Are You Sure to perform this transaction Y/N\n";
        cin >> Ans;

        if (tolower(Ans) != 'y')
        {
            cout << "Transaction canceled.\n";
            break;
        }

        long long WithDrawAmount = WithdrawOptions[choose];

        if (CurrentClient.AccountBalance >= WithDrawAmount)
        {
            CurrentClient.AccountBalance -= WithDrawAmount;
            cout << "Done Successfully. New Balance: " << CurrentClient.AccountBalance << endl;

            for (sClient& C : vClients)
            {
                if (C.AccountNumber == CurrentClient.AccountNumber)
                {
                    C.AccountBalance = CurrentClient.AccountBalance;
                    break;
                }
            }

            SaveClientsDataToFile(ClientsFileName, vClients);
            break;
        }
        else
        {
            cout << "\nAmount Exceeds Balance. You Can Withdraw Up To: "
                << CurrentClient.AccountBalance << endl;
            cout << "Press any key to try again...\n";
            system("pause > 0");
        }
    }

    PressKey_GoOut();
}

void Login()
{
    string AccNum, Pincode;
    MessagesScreens("Login Screen");

    do
    {
        cout << "Enter Account Number: "; cin >> AccNum;
        cout << "Enter Pin Code: "; cin >> Pincode;
        CurrentClient = GetClientInfo(vClients, AccNum, Pincode);

        if (CurrentClient.AccountNumber == "")
        {
            system("cls");
            MessagesScreens("Login Screen");
            cout << "Invalid Account Number / PinCode\n";
        }
    } while (CurrentClient.AccountNumber == "");

    system("cls");
    SwitchOpenMainMenu();
}

bool Program_Ends_Screen()
{
    system("cls");
    cout << "___________________________\n\n";
    cout << "      Program Ends :-)     \n";
    cout << "___________________________\n\n";
    return true;
}

void SwitchOpenMainMenu()
{
    EnMainMenuOptions MainMenuOptions;
    bool ExitProgram = false;
    do
    {
        MainMenuOptions = (EnMainMenuOptions)MainMenu();

        switch (MainMenuOptions)
        {
        case Quick_With:        MakeQuickWDraw();                            break;
        case Norm_With:         HandleTransaction("Withdraw Screen", false); break;
        case De_posit:          HandleTransaction("Deposit Screen", true);   break;
        case Check_Balance:     CheckBalance();                              break;
        case Log_out:           Login();                                     break;
        case Exit:              Ends_Program();                              break;
        }

    } while (MainMenuOptions != Exit);
}

int main()
{
    Login();
    return 0;
}
