#pragma warning(disable : 4996)
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
using namespace std;

string ClientsFile = "AllClientsData.txt";

void PauseSystem()
{
    cout << "\nPress Any Key To Go Back" << endl;
    system("pause>0");
}

string GetSystemDate()
{
    time_t Time = time(0);
    tm* Now = localtime(&Time);

    string Year = to_string(Now->tm_year + 1900);
    string Month = to_string(Now->tm_mon + 1);
    string Day = to_string(Now->tm_mday);


    return Day + "/" + Month + "/" + Year;
}

string ReadString(string Message)
{
    string S;

    cout << Message;
    getline(cin >> ws, S);

    return S;
}

double ReadDoubleNumber(string Message)
{
    double D;

    cout << Message;
    cin >> D;

    return D;
}

struct stClientInfo
{
    string Name = "";
    string PINCode = "";
    string PhoneNum = "";
    string AccountNum = "";
    double AccountBalance = 0;
    bool DeletionFlag = false;
};

stClientInfo CurrentClient;

vector<string> vSplitFunction(string S, string Seperator = "#//#")
{
    string SWord = "";
    short Pos = 0;
    vector<string> V;

    while ((Pos = S.find(Seperator)) != std::string::npos)
    {
        if ((SWord = S.substr(0, Pos)) != "")
        {
            V.push_back(SWord);
        }
        S.erase(0, Pos + Seperator.length());
    }
    if (S != "")
        V.push_back(S);

    return V;
}

stClientInfo GetClientInfoFromLineToStruct(string S, string Seperator = "#//#")
{
    stClientInfo Client;
    vector<string> vSplit = vSplitFunction(S);

    Client.AccountNum = vSplit[0];
    Client.PINCode = vSplit[1];
    Client.Name = vSplit[2];
    Client.PhoneNum = vSplit[3];
    Client.AccountBalance = stod(vSplit[4]);

    return Client;
}

vector<stClientInfo> LoadClientsInfoFromFileToVector(string FileName, string Seperator = "#//#")
{
    fstream MyFile;
    vector<stClientInfo> vClients;
    stClientInfo Client;

    MyFile.open(FileName, ios::in);

    if (MyFile.is_open())
    {
        string Line = "";
        while (getline(MyFile, Line))
        {
            Client = GetClientInfoFromLineToStruct(Line);
            vClients.push_back(Client);
        }
    }
    return vClients;
}

enum enMainMenueOptions
{ eQuickWithdraw = 1, eNormalWithdraw = 2, eDeposit = 3, eCheckBalance = 4, eChangePIN, eLogout = 6, eEndProgram = 7};

enMainMenueOptions GetUserMenueOption(short From, short To)
{
    short S;

    do
    {
        cout << "Please Enter Your Choice ? [" << From << " To " << To << "] : ";
        cin >> S;

    } while (S < From || S > To);

    return enMainMenueOptions(S);
}

short GetUserChoiceInRange(short From, short To)
{
    short S;

    do
    {
        cout << "Please Enter Your Withdrawal Choice ? [" << From << " To " << To << "] : ";
        cin >> S;

    } while (S < From || S > To);

    return S;

}

string ConvertClientDataToOneLine(stClientInfo C, string Seperator = "#//#")
{
    string S = "";

    S = C.AccountNum + Seperator + C.PINCode + Seperator + C.Name
        + Seperator + C.PhoneNum + Seperator + to_string(C.AccountBalance);

    return S;
}

void SaveClientsDataToFile(string FileName, vector<stClientInfo>& Clients)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out);

    if (MyFile.is_open())
    {
        for (stClientInfo& C : Clients)
        {
            if (!C.DeletionFlag)
            {
                MyFile << ConvertClientDataToOneLine(C) << endl;
            }
        }

        MyFile.close();
    }
}

bool IsUserSure()
{
    char Sure = 'n';
    cout << "Are You Sure ?? [y][n] : ";
    cin >> Sure;

    return toupper(Sure) == 'Y';
}

short GetQuickWithdrawAmount(short Choice)
{
    short arr[] = { 20, 50, 100, 200, 400, 600, 800, 1000, 0 };

    return arr[Choice - 1];
}

void Deposit(double Amount, vector<stClientInfo>& Clients)
{
    char Sure = 'n';

    if ((Amount < 0) && ((Amount * -1) > CurrentClient.AccountBalance))
    {
        cout << "No Enough Cash In Your Account" << endl;
        return;
    }

    for (stClientInfo& C : Clients)
    {
        if (C.AccountNum == CurrentClient.AccountNum)
        {
            CurrentClient.AccountBalance += Amount;
            C.AccountBalance += Amount;
            return;
        }
    }
}

void Withdraw(double Amount, vector<stClientInfo>& Clients, bool IsQuickWithdraw = false)
{

    while (Amount > CurrentClient.AccountBalance)
    {
        if (IsQuickWithdraw)
        {
            cout << "No Enough Cash ): ";
            short Choice = GetUserChoiceInRange(1, 9);
            if (Choice == 9)
                return;

            Amount = GetQuickWithdrawAmount(Choice);
            continue;
        }

        Amount = ReadDoubleNumber("No Enough Cash, Try Again : ");
    }

    Deposit(-Amount, Clients);
    SaveClientsDataToFile(ClientsFile, Clients);
    cout << "\nWithdrawed Successfully..." << endl;
    cout << "Your Updated Account Balance Is : " << CurrentClient.AccountBalance << endl;

}

void PrintQuickWithdawMenue()
{
    system("cls");
    cout << "===========================================" << endl;
    cout << "               Quick Withdraw" << endl;
    cout << "===========================================" << endl;
    cout << "\t[1] 20 \t\t[2] 50" << endl;
    cout << "\t[3] 100\t\t[4] 200" << endl;
    cout << "\t[5] 400\t\t[6] 600" << endl;
    cout << "\t[7] 800\t\t[8] 1000" << endl;
    cout << "\t       [9] Exit" << endl;
    cout << "===========================================" << endl;

    cout << "Your Balance Is " << CurrentClient.AccountBalance << endl;
}

void PerformQuickWithdraw(vector<stClientInfo>& Clients)
{
    PrintQuickWithdawMenue();
    short Choice = GetUserChoiceInRange(1, 9);

    if (Choice == 9)
    {
        return;
    }

    short Amount = GetQuickWithdrawAmount(Choice);

    if (IsUserSure())
    {
        Withdraw(Amount, Clients, true);
        PauseSystem();
    }
    else
    {
        PauseSystem();
        return;
    }
}

void PrintCheckBalanceScreen()
{
    system("cls");
    cout << "=========================================" << endl;
    cout << "           Check Balance Screen" << endl;
    cout << "=========================================" << endl;
    cout << "Your Balance Is : " << CurrentClient.AccountBalance << endl;

    PauseSystem();
}

bool IsTrueLoginInfo(vector<stClientInfo>& Clients, stClientInfo& CurrentClient, string AccountNumber, string PIN)
{
    for (stClientInfo& C : Clients)
    {
        if (C.AccountNum == AccountNumber && C.PINCode == PIN)
        {
            CurrentClient = C;
            return true;
        }
    }
    return false;
}

void Login(vector<stClientInfo>& Clients)
{
    system("cls");
    cout << "========================================================" << endl;
    cout << "                      Login Screen" << endl;
    cout << "========================================================" << endl;

    string AccountNumber = ReadString("Please Enter Account Number : ");
    string PIN = ReadString("Please Enter PIN Code : ");

    while (!IsTrueLoginInfo(Clients, CurrentClient, AccountNumber, PIN))
    {
        system("cls");
        cout << "========================================" << endl;
        cout << "              Login Screen" << endl;
        cout << "========================================" << endl;
        cout << "Wrong Account Number Or PIN Code, Try Again" << endl;

        AccountNumber = ReadString("Please Enter Account Number : ");
        PIN = ReadString("Please Enter PIN Code : ");
    }

}

void PrintMainMenueScreen()
{
    system("cls");
    cout << "====================================================" << endl;
    cout << " Logged In As " << CurrentClient.Name << endl;
    cout << " Today's Date : " << GetSystemDate() << endl;
    cout << "====================================================" << endl;
    cout << "                      ATM System" << endl;
    cout << "====================================================" << endl;
    cout << " 1-Quick Withdraw" << endl;
    cout << " 2-Normal Withdraw" << endl;
    cout << " 3-Deposit" << endl;
    cout << " 4-Check Balance" << endl;
    cout << " 5-Change PIN Code" << endl;
    cout << " 6-Logout" << endl;
    cout << " 7-End Program" << endl;
    cout << "====================================================" << endl;

}

bool IsAmountValid(int Amount)
{
    return (Amount % 5) == 0;
}

void PrintNormalWithdrawMenue()
{
    system("cls");
    cout << "=========================================" << endl;
    cout << "             Normal Withdraw" << endl;
    cout << "=========================================" << endl;
    cout << "Your Balance Is " << CurrentClient.AccountBalance << endl;

}

void PerformNormalWithdraw(vector<stClientInfo>& Clients)
{
    PrintNormalWithdrawMenue();

    double Amount;

    do
    {
        Amount = ReadDoubleNumber("Please Enter Valid Amount To Withdraw [5s] : ");

    } while (!IsAmountValid(Amount));

    if (IsUserSure())
    {
        Withdraw(Amount, Clients);
        PauseSystem();
    }
    else
    {
        PauseSystem();
    }
}

void PrintDepositMenue()
{
    system("cls");
    cout << "=========================================" << endl;
    cout << "             Deposit Screen" << endl;
    cout << "=========================================" << endl;
    cout << "Your Balance Is " << CurrentClient.AccountBalance << endl;
}

void PerformDeposit(vector<stClientInfo>& Clients)
{
    PrintDepositMenue();

    double Amount;

    do
    {
        Amount = ReadDoubleNumber("Please Enter Valid Amount To Deposit [5s] : ");

    } while (!IsAmountValid(Amount));

    if (IsUserSure())
    {
        Deposit(Amount, Clients);
        SaveClientsDataToFile(ClientsFile, Clients);
        cout << "\nDeposited Successfully..." << endl;
        cout << "Your Updated Account Balance Is : " << CurrentClient.AccountBalance << endl;
        PauseSystem();
    }
    else
    {
        PauseSystem();
    }

}

void PrintChangePINCodeScreen()
{
    system("cls");
    cout << "=============================================" << endl;
    cout << "              Change PIN Screen" << endl;
    cout << "=============================================" << endl;

}

bool IsPINCodeTrue(string PIN)
{
    return CurrentClient.PINCode == PIN;
}

void UpdatePINCode(vector<stClientInfo>& Clients, string NewPIN)
{
    CurrentClient.PINCode = NewPIN;

    for (stClientInfo& C : Clients)
    {
        if (CurrentClient.AccountNum == C.AccountNum)
            C.PINCode = NewPIN;
    }
}

void ChangePINCode(vector<stClientInfo>& Clients)
{
    PrintChangePINCodeScreen();

    string OldPIN = ReadString("Please Enter Your Old PIN Code : ");

    while (!IsPINCodeTrue(OldPIN))
    {
        OldPIN = ReadString("Wrong PIN Code, Try Again : ");
    }

    string NewPINCode = ReadString("Please Enter Your New PIN Code : ");

    UpdatePINCode(Clients, NewPINCode);
    SaveClientsDataToFile(ClientsFile, Clients);

    cout << "Your PIN Code Has been Updated Successfully..." << endl;

    PauseSystem();
}

void RespondToMainMenue(enMainMenueOptions UserOption, vector<stClientInfo>& Clients)
{
    switch (UserOption)
    {
        case enMainMenueOptions::eQuickWithdraw:
        {
            PerformQuickWithdraw(Clients);
            break;
        }
        case enMainMenueOptions::eNormalWithdraw:
        {
            PerformNormalWithdraw(Clients);
            break;
        }
        case enMainMenueOptions::eDeposit:
        {
            PerformDeposit(Clients);
            break;
        }
        case enMainMenueOptions::eCheckBalance:
        {
            PrintCheckBalanceScreen();
            break;
        }
        case enMainMenueOptions::eChangePIN:
        {
            ChangePINCode(Clients);
            break;
        }
        case enMainMenueOptions::eLogout:
        {
            Login(Clients);
            break;
        }
    }
}

void StartSystem()
{
    vector<stClientInfo> Clients = LoadClientsInfoFromFileToVector(ClientsFile);
    enMainMenueOptions UserOption;

    Login(Clients);

    do
    {
        PrintMainMenueScreen();
        UserOption = GetUserMenueOption(1, 7);
        RespondToMainMenue(UserOption, Clients);

    } while (UserOption != enMainMenueOptions::eEndProgram);
}

int main()
{
    StartSystem();

    return 0;
}

