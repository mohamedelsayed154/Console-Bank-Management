#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip> 
using namespace std;


struct Client {
    string AccNum;
    string PinCode;
    string ClientName;
    string phone;
    double balance; 
};


void LoadClientsFromFile(const string& fileName, vector<Client>& vClients);
void SaveClientsToFile(const string& fileName, const vector<Client>& vClients);
vector<string> SplitString(const string& s, const string& delimiter);
void ShowMainMenu();

void ShowClientsList(const vector<Client>& vClients);
void AddNewClient(vector<Client>& vClients);
void DeleteClient(vector<Client>& vClients);
void UpdateClientData(vector<Client>& vClients);
void FindClient(const vector<Client>& vClients);
void TransactionsMenu(vector<Client>& vClients, const string& fileName);
void Deposit(vector<Client>& vClients, const string& fileName);
void Withdraw(vector<Client>& vClients, const string& fileName);
void ShowTotalBalances(const vector<Client>& vClients);

int main() {
    vector<Client> vClients;
    const string fileName = "BankData.txt";

    LoadClientsFromFile(fileName, vClients);

    int choice = 0;
    do {
        system("cls");
        ShowMainMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            ShowClientsList(vClients);
            break;
        case 2:
            AddNewClient(vClients);
            SaveClientsToFile(fileName, vClients); 
            break;
        case 3:
            DeleteClient(vClients);
            SaveClientsToFile(fileName, vClients); 
            break;
        case 4:
            UpdateClientData(vClients);
            SaveClientsToFile(fileName, vClients); 
            break;
        case 5:
            FindClient(vClients);
            break;
        case 6:
            TransactionsMenu(vClients, fileName);
            break;
        case 7:
            cout << "\nThank you for using our system." << endl;
            break;
        default:
            cout << "\nInvalid Choice, please try again." << endl;
            cin.clear();
            cin.ignore();
        }

        if (choice != 7) {
            cout << "\nPress any key to return to the main menu...";
            system("pause>nul"); 
        }

    } while (choice != 7);

    return 0;
}

vector<string> SplitString(const string& s, const string& delimiter = "#//#") {
    vector<string> result;
    string temp = s;
    size_t pos = 0;
    while ((pos = temp.find(delimiter)) != string::npos) {
        result.push_back(temp.substr(0, pos));
        temp.erase(0, pos + delimiter.length());
    }
    result.push_back(temp);
    return result;
}

Client LineToClient(const string& line) {
    Client c;
    vector<string> clientData = SplitString(line);
    if (clientData.size() == 5) {
        c.AccNum = clientData[0];
        c.PinCode = clientData[1];
        c.ClientName = clientData[2];
        c.phone = clientData[3];
        c.balance = stod(clientData[4]); 
    }
    return c;
}

string ClientToLine(const Client& c, const string& delimiter = "#//#") {
    return c.AccNum + delimiter + c.PinCode + delimiter + c.ClientName + delimiter + c.phone + delimiter + to_string(c.balance);
}

void LoadClientsFromFile(const string& fileName, vector<Client>& vClients) {
    vClients.clear();
    fstream MyFile;
    MyFile.open(fileName, ios::in);
    if (MyFile.is_open()) {
        string line;
        while (getline(MyFile, line)) {
            if (!line.empty()) {
                vClients.push_back(LineToClient(line));
            }
        }
        MyFile.close();
    }
}

void SaveClientsToFile(const string& fileName, const vector<Client>& vClients) {
    fstream MyFile;
    MyFile.open(fileName, ios::out);
    if (MyFile.is_open()) {
        for (const Client& c : vClients) {
            MyFile << ClientToLine(c) << endl;
        }
        MyFile.close();
    }
}

void ShowMainMenu() {
    cout << "========================================\n";
    cout << "           Main Menu Screen\n";
    cout << "========================================\n";
    cout << "[1] Show Client List  \n";
    cout << "[2] Add New Client  \n";
    cout << "[3] Delete Client \n";
    cout << "[4] Update Client Info \n";
    cout << "[5] Find Client \n";
    cout << "[6] Transactions \n";
    cout << "[7] Exit \n";
    cout << "========================================\n";
    cout << "Choose what you want to do [1 to 7] : ";
}

bool DoesAccountExist(const string& AccNum, const vector<Client>& vClients) {
    for (const Client& c : vClients) {
        if (c.AccNum == AccNum) {
            return true;
        }
    }
    return false;
}

int FindClientIndex(const string& AccNum, const vector<Client>& vClients) {
    for (int i = 0; i < vClients.size(); ++i) {
        if (vClients[i].AccNum == AccNum) {
            return i;
        }
    }
    return -1; // -1 means not found
}

void ShowClientsList(const vector<Client>& vClients) {
    system("cls");
    cout << "\n\t\t\t\tClient List (" << vClients.size() << ") Client(s).\n";
    cout << "------------------------------------------------------------------------------------------------------------------------\n";
    cout << "| " << left << setw(15) << "Account Number : "
        << "| " << left << setw(15) << "Pin Code : "
        << "| " << left << setw(40) << "Client Name : "
        << "| " << left << setw(20) << "Phone : "
        << "| " << left << setw(15) << "Balance : ";
    cout << "\n------------------------------------------------------------------------------------------------------------------------\n";

    if (vClients.empty()) {
        cout << "\nNo clients to show \n";
    }
    else {
        for (const Client& c : vClients) {
            cout << "| " << left << setw(15) << c.AccNum
                << "| " << left << setw(15) << c.PinCode
                << "| " << left << setw(40) << c.ClientName
                << "| " << left << setw(20) << c.phone
                << "| " << left << setw(15) << fixed << setprecision(2) << c.balance << endl;
        }
    }
    cout << "------------------------------------------------------------------------------------------------------------------------\n";
}

void AddNewClient(vector<Client>& vClients) {
    system("cls");
    Client NewClient;
    cout << "--- Add New Client Screen ---\n\n";

    cout << "Enter Account Number : ";
    cin >> NewClient.AccNum;
    while (DoesAccountExist(NewClient.AccNum, vClients)) {
        cout << "Client with [" << NewClient.AccNum << "] already exists, enter another one : ";
        cin >> NewClient.AccNum;
    }

    cout << "Enter Pin Code : ";
    cin >> NewClient.PinCode;
    cout << "Enter Client Name : ";
    cin.ignore();
    getline(cin, NewClient.ClientName);
    cout << "Enter Phone Number : ";
    cin >> NewClient.phone;
    cout << "Enter Account Balance : ";
    cin >> NewClient.balance;

    vClients.push_back(NewClient);
    cout << "\nClient Added Successfully ";
}

void DeleteClient(vector<Client>& vClients) {
    system("cls");
    string AccNum;
    cout << "--- Delete Client Screen ---\n\n";
    cout << "Enter Account Number to delete: ";
    cin >> AccNum;

    int index = FindClientIndex(AccNum, vClients);
    if (index == -1) {
        cout << "\nClient with Account Number [" << AccNum << "] not found.";
        return;
    }

    cout << "Client Found \nName : " << vClients[index].ClientName << ", Balance : " << vClients[index].balance << endl;
    char confirm;
    cout << "Are you sure you want to delete this client? (Y/N) : ";
    cin >> confirm;
    if (confirm == 'Y' || confirm == 'y') {
        vClients.erase(vClients.begin() + index);
        cout << "\nClient Deleted Successfully ";
    }
    else {
        cout << "\nDeletion cancelled ";
    }
}

void UpdateClientData(vector<Client>& vClients) {
    system("cls");
    string AccNum;
    cout << "--- Update Client Screen ---\n\n";
    cout << "Enter Account Number to update : ";
    cin >> AccNum;

    int index = FindClientIndex(AccNum, vClients);
    if (index == -1) {
        cout << "\nClient with Account Number [" << AccNum << "] not found.";
        return;
    }

    cout << "\nUpdating data for client : " << vClients[index].ClientName << endl;

    cout << "Enter New Pin Code : ";
    cin >> vClients[index].PinCode;
    cout << "Enter New Client Name : ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, vClients[index].ClientName);
    cout << "Enter New Phone Number : ";
    cin >> vClients[index].phone;
    cout << "Enter New Account Balance : ";
    cin >> vClients[index].balance;

    cout << "\nClient Data Updated Successfully ";
}

void FindClient(const vector<Client>& vClients) {
    system("cls");
    string AccNum;
    cout << "--- Find Client Screen ---\n\n";
    cout << "Enter Account Number to find : ";
    cin >> AccNum;

    int index = FindClientIndex(AccNum, vClients);
    if (index != -1) {
        cout << "\nClient Found :\n";
        cout << "---------------------\n";
        cout << "Account Number : " << vClients[index].AccNum << endl;
        cout << "Pin Code : " << vClients[index].PinCode << endl;
        cout << "Name : " << vClients[index].ClientName << endl;
        cout << "Phone : " << vClients[index].phone << endl;
        cout << "Balance : " << vClients[index].balance << endl;
        cout << "---------------------\n";
    }
    else {
        cout << "\nClient with Account Number [" << AccNum << "] not found.";
    }
}


void TransactionsMenu(vector<Client>& vClients, const string& fileName) {
    int choice = 0;
        do {
        system("cls");
        cout << "----------------------------------------\n";
        cout << "         Transactions Menu Screen\n";
        cout << "----------------------------------------\n";
        cout << "[1] Deposit.\n";
        cout << "[2] Withdraw.\n";
        cout << "[3] Show Total Balances.\n";
        cout << "[4] Return to Main Menu.\n";
        cout << "----------------------------------------\n";
        cout << "Choose what you want to do [1 to 4] :  ";
        cin >> choice;

        switch (choice) {
        case 1:
            Deposit(vClients, fileName);
            break;
        case 2:
            Withdraw(vClients, fileName);
            break;
        case 3:
            ShowTotalBalances(vClients);
            break;
        case 4:
            system("cls");
            main();
           //  cout << "\nReturning to Main Menu..." << endl;
            break;
        default:
            cout << "\nInvalid Choice, please try again." << endl;
            cin.clear();
            cin.ignore();
        }

      /*  if (choice != 4) {
             system("pause");
            system("cls");
            
        }
        */

      } while (choice != 4);
}

void Deposit(vector<Client>& vClients, const string& fileName) {
    system("cls");
    string AccNum;
    cout << "--- Deposit Screen ---\n\n";
    cout << "Enter Account Number : ";
    cin >> AccNum;

    int index = FindClientIndex(AccNum, vClients);
    if (index == -1) {
        cout << "\nClient with Account Number [" << AccNum << "] not found ";
        return;
    }

    cout << "\nClient Found : " << vClients[index].ClientName << endl;
    cout << "Current Balance : " << vClients[index].balance << endl;

    double depositAmount = 0;
    cout << "Enter deposit amount : ";
    cin >> depositAmount;

    if (depositAmount <= 0) {
        cout << "\nInvalid deposit amount, Must be greater than zero.";
        return;
    }

    char confirm;
    cout << "Are you sure you want to deposit " << depositAmount << "? (Y/N) : ";
    cin >> confirm;

    if (confirm == 'Y' || confirm == 'y') {
        vClients[index].balance += depositAmount;
        SaveClientsToFile(fileName, vClients);
        cout << "\nDeposit Successful, New Balance : " << vClients[index].balance;
    }
    else {
        cout << "\nDeposit cancelled ";
    }
}

void Withdraw(vector<Client>& vClients, const string& fileName) {
    system("cls");
    string AccNum;
    cout << "--- Withdraw Screen ---\n\n";
    cout << "Enter Account Number : ";
    cin >> AccNum;

    int index = FindClientIndex(AccNum, vClients);
    if (index == -1) {
        cout << "\nClient with Account Number [" << AccNum << "] not found ";
        return;
    }

    cout << "\nClient Found : " << vClients[index].ClientName << endl;
    cout << "Current Balance : " << vClients[index].balance << endl;

    double withdrawAmount = 0;
    cout << "Enter withdraw amount : ";
    cin >> withdrawAmount;

    if (withdrawAmount <= 0) {
        cout << "\nInvalid withdraw amount. Must be greater than zero ";
        return;
    }

    if (withdrawAmount > vClients[index].balance) {
        cout << "\nAmount exceeds the current balance, Transaction failed ";
        return;
    }

    char confirm = 'n';
    cout << "Are you sure you want to withdraw " << withdrawAmount << "? (Y/N) : ";
    cin >> confirm;

    if (confirm == 'Y' || confirm == 'y') {
        vClients[index].balance -= withdrawAmount;
        SaveClientsToFile(fileName, vClients);
        cout << "\nWithdrawal Successful. New Balance : " << vClients[index].balance;
    }
    else {
        cout << "\nWithdrawal cancelled ";
    }
}

void ShowTotalBalances(const vector<Client>& vClients) {
    system("cls");
    cout << "\n\t\t\tBalances List (" << vClients.size() << ") Client(s).\n";
    cout << "--------------------------------------------------------------------------\n";
    cout << "| " << left << setw(15) << "Account Number"
        << "| " << left << setw(40) << "Client Name"
        << "| " << left << setw(15) << "Balance";
    cout << "\n--------------------------------------------------------------------------\n";

    double totalBalance = 0.0;
    for (const Client& c : vClients) {
        cout << "| " << left << setw(15) << c.AccNum
            << "| " << left << setw(40) << c.ClientName
            << "| " << left << setw(15) << fixed << setprecision(2) << c.balance << endl;
        totalBalance += c.balance;
    }
    cout << "--------------------------------------------------------------------------\n";
    cout << "\nTotal Balance of All Clients : " << fixed << setprecision(2) << totalBalance <<  endl;
}
