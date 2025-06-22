#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<iomanip>
using namespace std;

const string ClientsFileName = "Clients.txt";

enum eChoose_1 {
    Show_Client_List = 1, Add_New_Client, Delete_Client, Update_Client_Info, Find_Client, Transaction, Exit
};
enum eChoose_2 {
    Deposit = 1, Withdraw, TotalBalance, MainMenu
};
struct sClient
{
    string AccountNumber = "";
    string PinCode = "";
    string ClientName = "";
    string PhoneNumber = "";
    double Balance = 0;
    bool MarkForDelete = false;
};

void Details(eChoose_1);
void GoBackToMainMenu();
void ShowMenu();
eChoose_2 Select2();
eChoose_1 Select1();
void GoBackToTransactionMenu();
void TransactionMainMenuScreen();

sClient ReadInputClients() {
    sClient client;

    cout << "\nPlease enter data: " << "\n\n";
    cout << "Enter Account number: ";
    getline(cin >> ws, client.AccountNumber);
    cout << "Enter PinCode: ";
    getline(cin, client.PinCode);
    cout << "Enter Name: ";
    getline(cin, client.ClientName);
    cout << "Enter Phone: ";
    getline(cin, client.PhoneNumber);
    cout << "Enter Account Balance: ";
    cin >> client.Balance;

    return client;
}
sClient ReadUpdateClients(string Account) {
    sClient client;
    client.AccountNumber = Account;

    cout << "\n\nEnter PinCode: ";
    getline(cin >> ws, client.PinCode);
    cout << "Enter Name: ";
    getline(cin, client.ClientName);
    cout << "Enter Phone: ";
    getline(cin, client.PhoneNumber);
    cout << "Enter Account Balance: ";
    cin >> client.Balance;
    cout << "\n\n";

    return client;
}
string ReadAccountNumber() {
    string account = "";
    cout << "Please enter account number: ";
    cin >> account;
    return account;
}

vector <string> SplitString(string sentence, string delim) {
    vector <string> vString;
    int pos = 0;
    string word = " ";
    while ((pos = sentence.find(delim)) != std::string::npos) {
        word = sentence.substr(0, pos);
        if (word != " ")
            vString.push_back(word);
        sentence.erase(0, pos + delim.length());
    }
    if (sentence != " ")
        vString.push_back(sentence);
    return vString;
}
string ConvertRecordToLine(sClient Client, string Seperator = "#//#") {
    string stClientRecord = "";

    stClientRecord += Client.AccountNumber + Seperator;
    stClientRecord += Client.PinCode + Seperator;
    stClientRecord += Client.ClientName + Seperator;
    stClientRecord += Client.PhoneNumber + Seperator;
    stClientRecord += to_string(Client.Balance);

    return stClientRecord;
}
sClient ConvertLinetoRecord(string Line, string Seperator = "#//#") {
    sClient Client;
    vector<string> vClientData;

    vClientData = SplitString(Line, Seperator);
    Client.AccountNumber = vClientData[0];
    Client.PinCode = vClientData[1];
    Client.ClientName = vClientData[2];
    Client.PhoneNumber = vClientData[3];
    Client.Balance = stod(vClientData[4]);

    return Client;
}

void PrintInfoAboutAccountNumber(sClient client) {
    cout << "\n\nThe following are the client details:\n\n";
    cout << "\nAccount Number       :" << client.AccountNumber;
    cout << "\nPin Code             :" << client.PinCode;
    cout << "\nName                 :" << client.ClientName;
    cout << "\nPhone                :" << client.PhoneNumber;
    cout << "\nBalance              :" << client.Balance << "\n\n";
}

vector <sClient> LoadClientsDataFromFile(string FileName) {
    vector <sClient> vClients;
    fstream MyFile;
    MyFile.open(FileName, ios::in);

    if (MyFile.is_open()) {
        string line;
        sClient client;
        while (getline(MyFile, line)) {
            client = ConvertLinetoRecord(line);
            vClients.push_back(client);
        }
        MyFile.close();
    }
    return vClients;
}

void PrintInfoClient(sClient infoclient) {
    cout << "|" << setw(16) << infoclient.AccountNumber;
    cout << "|" << setw(16) << infoclient.PinCode;
    cout << "|" << setw(20) << infoclient.ClientName;
    cout << "|" << setw(18) << infoclient.PhoneNumber;
    cout << "|" << setw(15) << infoclient.Balance;
    cout << "\n\n";
}
void PrintAllClients() {
    vector <sClient> vInfo = LoadClientsDataFromFile(ClientsFileName);
    cout << "\n\t\t\t\tClient list(" << vInfo.size() << ") Client(s)\n";
    cout << "----------------------------------------------------------------------------------------------------------\n\n";
    cout << "|" << setw(16) << "Account Number";
    cout << "|" << setw(16) << "Pin Code";
    cout << "|" << setw(20) << "Client Name";
    cout << "|" << setw(18) << "Phone";
    cout << "|" << setw(15) << "Balance";
    cout << "\n----------------------------------------------------------------------------------------------------------\n";
    if (vInfo.size() == 0)
        cout << "\nNo Client Available In the system!\n";
    else {
        for (sClient c : vInfo) {
            PrintInfoClient(c);
        }
        cout << "\n----------------------------------------------------------------------------------------------------------\n";
    }
}

void AddDataToFile(string FileName, string DataLine) {
    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app);
    if (MyFile.is_open()) {
        MyFile << DataLine << endl;
        MyFile.close();
    }
}
void AddNewClient() {
    sClient client;
    client = ReadInputClients();
    string Data = ConvertRecordToLine(client);
    AddDataToFile(ClientsFileName, Data);
}
void AddClient() {
    char add = ' ';
    do {
        system("cls");
        cout << "Add new client: \n";

        try {
            AddNewClient();
            cout << "Client added successfully!\n";
        }
        catch (const exception& e) {
            cout << "An error occurred: " << e.what() << endl;
        }
        catch (...) {
            cout << "An unknown error occurred while adding the client.\n";
        }
        cout << "Do you want to add a new client? ";
        cin >> add;

    } while (add == 'y' || add == 'Y');
}

bool CheckAccountNumberIsFound(string account, vector <sClient> vClient, sClient& accountCheck) {
    for (sClient& c : vClient) {
        if (c.AccountNumber == account) {
            accountCheck = c;
            return true;
        }
    }
    return false;
}
void PrintClientRecord() {
    sClient Client;
    cout << "\n-----------------------------------\n";
    cout << "\nFind Client Screen";
    cout << "\n-----------------------------------\n";
    vector <sClient> vClient = LoadClientsDataFromFile(ClientsFileName);
    string account = ReadAccountNumber();

    if (CheckAccountNumberIsFound(account, vClient, Client)) {
        cout << "\n\nThe following is the extracted client record:\n";
        cout << "\nAccount Number  : " << Client.AccountNumber;
        cout << "\nPin Code       : " << Client.PinCode;
        cout << "\nName           : " << Client.ClientName;
        cout << "\nPhone          : " << Client.PhoneNumber;
        cout << "\nAccount Balance: " << Client.Balance << endl;
    }
    else
        cout << "The account is not found\n";
}

vector <sClient> SaveDataAfterChanges(string FileName, vector <sClient>& vClients) {
    fstream MyFile;
    string DataLine;

    MyFile.open(FileName, ios::out);
    if (MyFile.is_open()) {
        for (sClient& c : vClients) {
            if (c.MarkForDelete == false) {
                DataLine = ConvertRecordToLine(c);
                MyFile << DataLine << endl;
            }
        }
        MyFile.close();
    }
    return vClients;
}

bool AccountNumberMarkForDelete(string account, vector <sClient>& vClient) {
    for (sClient& c : vClient) {
        if (c.AccountNumber == account) {
            c.MarkForDelete = true;
            return true;
        }
    }
    return false;
}
bool DeleteClientByAccountNumber(string AccountNumber, vector <sClient>& vClients) {
    sClient client;
    char sure = ' ';
    if (CheckAccountNumberIsFound(AccountNumber, vClients, client)) {
        PrintInfoAboutAccountNumber(client);
        cout << "\n\nAre you sure you want delete this client? y/n ? ";
        cin >> sure;
        if (sure == 'y' || sure == 'Y') {
            AccountNumberMarkForDelete(AccountNumber, vClients);
            SaveDataAfterChanges(ClientsFileName, vClients);
            vClients = LoadClientsDataFromFile(ClientsFileName);
            cout << "\n\nClient Deleted Successfully.\n\n";
            return true;
        }
        else {
            cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!\n\n";
            return false;
        }
    }
    return false;
}
void DeleteAccountNumber() {
    cout << "\n-----------------------------------\n";
    cout << "\tDelete Client Screen";
    cout << "\n-----------------------------------\n";
    vector <sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
    string AccountNumber = ReadAccountNumber();
    DeleteClientByAccountNumber(AccountNumber, vClients);
}

bool UpdateClientByAccountNumber(string AccountNumber, vector <sClient>& vClients) {
    sClient client;
    char sure = ' ';
    if (CheckAccountNumberIsFound(AccountNumber, vClients, client)) {
        PrintInfoAboutAccountNumber(client);
        cout << "\n\nAre you sure you want update this client? y/n ? ";
        cin >> sure;
        if (sure == 'y' || sure == 'Y') {
            for (sClient& C : vClients) {
                if (C.AccountNumber == AccountNumber) {
                    C = ReadUpdateClients(AccountNumber);
                    break;
                }
            }
            SaveDataAfterChanges(ClientsFileName, vClients);
            vClients = LoadClientsDataFromFile(ClientsFileName);
            cout << "\n\nClient Updated Successfully.\n\n";
            return true;
        }
        else {
            cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!\n\n";
            return false;
        }
    }
    return false;
}
void UpdateClientAccount() {
    cout << "\n-----------------------------------\n";
    cout << "\tUpdate Client Screen";
    cout << "\n-----------------------------------\n";
    vector <sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
    string AccountNumber = ReadAccountNumber();
    UpdateClientByAccountNumber(AccountNumber, vClients);
}

eChoose_1 Select1() {
    short choose;
    do {
        cout << "Choose what do you want to do? ";
        cin >> choose;
    } while (choose < 1 || choose > 7);
    return (eChoose_1)choose;
}
void ShowEndScreen() {
    cout << "\n-----------------------------------\n";
    cout << "\tProgram Ends :-)";
    cout << "\n-----------------------------------\n";
}
void GoBackToMainMenu() {
    cout << "\n\nPress any key to go back to Main Menu...";
    system("pause>0");
    system("cls");
    ShowMenu();
}

eChoose_2 Select2() {
    short choose;
    do {
        cout << "Choose what do you want to do? ";
        cin >> choose;
    } while (choose < 1 || choose > 4);
    return (eChoose_2)choose;
}
void GoBackToTransactionMenu() {
    cout << "\n\nPress any key to go back to Transaction Menu...";
    system("pause>0");
    system("cls");
    TransactionMainMenuScreen();
}

double ReadDeposit() {
    double deposit = 0;
    do {
        cout << "\nPlease enter deposit amount: ";
        cin >> deposit;
    } while (deposit < 0);
    return deposit;
}
void DepositToBalanceByClient(sClient& client, vector<sClient>& vClients) {
    char sure = ' ';
    double deposit = ReadDeposit();

    cout << "\nAre you sure you want perform this transaction? ";
    cin >> sure;

    if (sure == 'y' || sure == 'Y') {
        client.Balance += deposit;
       
        for (sClient& c : vClients) {
            if (c.AccountNumber == client.AccountNumber) {
                c.Balance = client.Balance;
                break;
            }
        }
        
        SaveDataAfterChanges(ClientsFileName, vClients);
        cout << "Deposit successful!\nYour new balance is: " << client.Balance << endl;
    }
    else {
        cout << "\nTransaction canceled. Thank you!\n";
    }
}
void DepositBalance() {
    vector <sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
    sClient Client;
    cout << "\n-----------------------------------\n";
    cout << "\tDeposit Screen:";
    cout << "\n-----------------------------------\n";
    string account = ReadAccountNumber();

    if (CheckAccountNumberIsFound(account, vClients, Client)) {
        cout << "\n\nThe following is the extracted client record:\n";
        cout << "\nAccount Number  : " << Client.AccountNumber;
        cout << "\nPin Code       : " << Client.PinCode;
        cout << "\nName           : " << Client.ClientName;
        cout << "\nPhone          : " << Client.PhoneNumber;
        cout << "\nAccount Balance: " << Client.Balance << endl;

        DepositToBalanceByClient(Client, vClients);
    }
    else {
        cout << "The account is not found\n";
    }
}

double ReadWithdraw(sClient& client) {
    double withdraw = 0;
    do {
        cout << "Please enter withdraw amount: ";
        cin >> withdraw;
    } while (withdraw < 0 || withdraw > client.Balance);
    return withdraw;
}
void WithdrawFromBalanceByClient(sClient& client, vector<sClient>& vClients) {
    char sure = ' ';
    double withdraw = ReadWithdraw(client);

    cout << "\nAre you sure you want perform this transaction? ";
    cin >> sure;

    if (sure == 'y' || sure == 'Y') {
        client.Balance -= withdraw;
        for (sClient& c : vClients) {
            if (c.AccountNumber == client.AccountNumber) {
                c.Balance = client.Balance;
                break;
            }
        }
        SaveDataAfterChanges(ClientsFileName, vClients);
        cout << "Withdraw successful!\nYour new balance is: " << client.Balance << endl;
    }
    else {
        cout << "\nTransaction canceled. Thank you!\n";
    }
}
void WithdrawBalance() {
    vector <sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
    sClient Client;
    cout << "\n-----------------------------------\n";
    cout << "\tWithdraw Screen:";
    cout << "\n-----------------------------------\n";
    string account = ReadAccountNumber();

    if (CheckAccountNumberIsFound(account, vClients, Client)) {
        cout << "\n\nThe following is the extracted client record:\n";
        cout << "\nAccount Number  : " << Client.AccountNumber;
        cout << "\nPin Code       : " << Client.PinCode;
        cout << "\nName           : " << Client.ClientName;
        cout << "\nPhone          : " << Client.PhoneNumber;
        cout << "\nAccount Balance: " << Client.Balance << endl;

        WithdrawFromBalanceByClient(Client, vClients);
    }
    else {
        cout << "The account is not found\n";
    }
}

void PrintInfoClientInTransaction(sClient& infoclient) {
    cout << "|" << setw(16) << infoclient.AccountNumber;
    cout << "|" << setw(20) << infoclient.ClientName;
    cout << "|" << setw(15) << infoclient.Balance;
    cout << "\n\n";
}
void PrintAllClientsInTransaction() {
    vector <sClient> vInfo = LoadClientsDataFromFile(ClientsFileName);
    double NewTotalBalance = 0;
    cout << "\n\t\t\t\tClient list(" << vInfo.size() << ") Client(s)\n";
    cout << "----------------------------------------------------------------------------------------------------------\n\n";
    cout << "|" << setw(16) << "Account Number";
    cout << "|" << setw(20) << "Client Name";
    cout << "|" << setw(15) << "Balance";
    cout << "\n----------------------------------------------------------------------------------------------------------\n";
    if (vInfo.size() == 0)
        cout << "\nNo Client Available In the system!\n";
    else {
        for (sClient& c : vInfo) {
            PrintInfoClientInTransaction(c);
            NewTotalBalance += c.Balance;
        }
        cout << "\n----------------------------------------------------------------------------------------------------------\n";
        cout << "\t\t\t\tTotal Balance:" << NewTotalBalance << endl;
    }
}

void Transaction_Details(eChoose_2 choose) {
    switch (choose) {
    case Deposit:
        system("cls");
        DepositBalance();
        GoBackToTransactionMenu();
        break;
    case Withdraw:
        system("cls");
        WithdrawBalance();
        GoBackToTransactionMenu();
        break;
    case TotalBalance:
        system("cls");
        PrintAllClientsInTransaction();
        GoBackToTransactionMenu();
        break;
    case MainMenu:
        system("cls");
        ShowMenu();
        break;
    }
}
void TransactionMainMenuScreen() {
    cout << "---------------------------------------------\n";
    cout << "---------------------------------------------\n";
    cout << "\t\tTransaction Menu screen\n";
    cout << "---------------------------------------------\n";
    cout << "---------------------------------------------\n";
    cout << "[1] Deposit\n";
    cout << "[2] Withdraw\n";
    cout << "[3] Total Balance\n";
    cout << "[4] Main Menu\n";
    cout << "---------------------------------------------\n";
    cout << "---------------------------------------------\n";
    Transaction_Details(Select2());
}

void Details(eChoose_1 choose) {
    switch (choose) {
    case Show_Client_List:
        system("cls");
        PrintAllClients();
        GoBackToMainMenu();
        break;
    case Add_New_Client:
        system("cls");
        AddClient();
        GoBackToMainMenu();
        break;
    case Delete_Client:
        system("cls");
        DeleteAccountNumber();
        GoBackToMainMenu();
        break;
    case Update_Client_Info:
        system("cls");
        UpdateClientAccount();
        GoBackToMainMenu();
        break;
    case Find_Client:
        system("cls");
        PrintClientRecord();
        GoBackToMainMenu();
        break;
    case Transaction:
        system("cls");
        TransactionMainMenuScreen();
        break;
    case Exit:
        ShowEndScreen();
        break;
    default:
        cout << "Thank you for using";
    }
}

void ShowMenu() {
    cout << "---------------------------------------------\n";
    cout << "---------------------------------------------\n";
    cout << "\t\tMain Menu screen\n";
    cout << "---------------------------------------------\n";
    cout << "---------------------------------------------\n";
    cout << "[1] Show Client List\n";
    cout << "[2] Add New Client\n";
    cout << "[3] Delete Client\n";
    cout << "[4] Update Client Info\n";
    cout << "[5] Find Client\n";
    cout << "[6] Transaction\n";
    cout << "[7] Exit\n";
    cout << "---------------------------------------------\n";
    cout << "---------------------------------------------\n";
    Details(Select1());
}

int main() {
    ShowMenu();
    system("pause");
    return 0;
}