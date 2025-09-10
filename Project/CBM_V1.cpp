#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>
using namespace std;

void MainMenue();
void LoadDataFromFileToVector(string data, vector <string>& vFileContent);
void ChoicCase(vector <string>& vFileContent);
void ShowClientList(string data, vector <string>& vFileContent);
void AddNewClient(string data, vector <string>& vFileContent);
bool SearchAccount(string& AccNum, vector <string>& vFileContent);
void FindClientAccount(string data, vector <string>& vFileContent);
void SaveVectorToFile(string data, vector <string> vFileContent);
void ShowClient(int count, vector <string>& vFileContent);
void DeleteClient(string data, vector <string>& vFileContent);
void UpdateClientsData(string data, vector <string>& vFileContent);
void Transaction(string data, vector <string>& vFileContent);
void Depoaite(string data, vector <string>& vFileContent);
void TotalBalance(string data, vector <string>& vFileContent);
void Withdraw(string data, vector <string>& vFileContent);

struct Client {
	string AccNum;
	int PinCode;
	string ClientName;
	long long phone;
	float balance;
};

int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	vector <string> vFileContent;


	LoadDataFromFileToVector("data.txt", vFileContent);
	ChoicCase(vFileContent);



}

void MainMenue() {
	
	cout << "---------------------------------------------------------------------\n";
	cout << "                             Main Menue                              \n";
	cout << "---------------------------------------------------------------------\n";
	cout << "[1] Show Client List\n";
	cout << "[2] Add New Client\n";
	cout << "[3] Delete Client\n";
	cout << "[4] Update Client Info\n";
	cout << "[5] Find Client\n";
	cout << "[6] Transaction\n";
	cout << "[7] Exit\n";
	cout << "---------------------------------------------------------------------\n";
	cout << "What you want to do [1 to 7] : ";
}

void ChoicCase(vector <string>& vFileContent) {


	MainMenue();

	int t; // for choic
Wrong:
	cin >> t;

	switch (t) {
	case 1: // Show Client 
		ShowClientList("data.txt", vFileContent);
		break;


	case 2: // Add New Client
		AddNewClient("data.txt", vFileContent);
		break;


	case 3: // Delete 
		DeleteClient("data.txt", vFileContent);
		break;


	case 4: // Update Client Info
		UpdateClientsData("data.txt", vFileContent);
		break;


	case 5: // Find Client
		FindClientAccount("data.txt", vFileContent);
		break;

	case 6: // Transaction

		Transaction("data.txt", vFileContent);

		break;
	case 7: // Exit
		cout << "Thanks...\n";
		break;
	default:
		cout << "Wrong,try again : ";
		goto Wrong;

	}
}

void LoadDataFromFileToVector(string data, vector <string>& vFileContent) {
	fstream MyFile(data, ios::in);

	if (MyFile.is_open()) {
		string Line;

		while (getline(MyFile, Line)) {
			vFileContent.push_back(Line);
		}
		MyFile.close();
	}

}

void ShowClientList(string data, vector <string>& vFileContent) {

	LoadDataFromFileToVector("data.txt", vFileContent);

	system("cls");
	cout << "\t\t\t\t\t\tClient List (" << vFileContent.size() / 6 << ") Client(s)" << endl;
	cout << "-----------------------------------------------------------------------------------------------------------------------------------\n";
	cout << "|  Account Number" << setw(23) << "|  Pin Code" << setw(23) << "|  Client Name" << setw(23) << "|  Phone" << setw(23) << "|  Balance" << endl;
	cout << "-----------------------------------------------------------------------------------------------------------------------------------\n";
	cout << endl;




	for (int i = 0; i < vFileContent.size(); i++) {
		if (vFileContent[i] == "new") {
			cout << endl;
			continue;
		}
		else {
			cout << "|  " << setw(23) << vFileContent[i];
		}




	}

	// press any key to continue . . . 
	system("pause");
	system("cls");

	ChoicCase(vFileContent);
}


bool SearchAccount(string& AccNum, vector <string>& vFileContent) {
	for (int i = 0; i < vFileContent.size(); i += 6) {
		if (vFileContent[i] == AccNum) {
			return true;
		}

	}
	return false;
}

void AddNewClient(string data, vector <string>& vFileContent) {
	system("cls");

	Client NewClient;

	cout << "-----------------------------------------------------------------------------------------------------------------------------------\n";
	cout << "                                          Add New Client Screen                                                                    \n";
	cout << "-----------------------------------------------------------------------------------------------------------------------------------\n";



	while (true) {
		cout << "Adding New Client : \n";

		cout << "Entre Account Number : ";



		cin >> NewClient.AccNum;
		if (SearchAccount(NewClient.AccNum, vFileContent)) {
			cout << "Client With [" << NewClient.AccNum << "] Already Exists. Please enter another one." << endl;
		}
		else {
			break;
		}




	}

	fstream MyFile(data, ios::app);

	MyFile << NewClient.AccNum << endl;

	cout << "Entre Pin Code : ";
	cin >> NewClient.PinCode;
	MyFile << NewClient.PinCode << endl;

	cout << "Entre Name : ";
	cin.ignore();
	getline(cin, NewClient.ClientName);
	MyFile << NewClient.ClientName << endl;

	cout << "Entre Phone Number : ";
	cin >> NewClient.phone;
	MyFile << NewClient.phone << endl;

	cout << "Entre Account Balance : ";
	cin >> NewClient.balance;
	MyFile << NewClient.balance << endl;

	MyFile << "new\n";
	MyFile.close();

	char More;
	cout << "Client Added Successfully , do you want to add more Clients ? Y/N : ";
	cin >> More;

	if (More == 'Y' || More == 'y') {
		AddNewClient("data.txt", vFileContent);
	}
	else {

		system("cls");

		main();
	}


}

void FindClientAccount(string data, vector <string>& vFileContent) {
	system("cls");
	Client FindClient;
	cout << "-----------------------------------------------------------------------------------------------------------------------------------\n";
	cout << "                                             Find Client Screen                                                                    \n";
	cout << "-----------------------------------------------------------------------------------------------------------------------------------\n";


	cout << "Entre Account Number : ";
	cin >> FindClient.AccNum;

	if (SearchAccount(FindClient.AccNum, vFileContent)) {

		int count = 0;
		while (vFileContent[count] != FindClient.AccNum) {
			count += 6;

		}

		cout << "-----------------------------------\n";
		cout << "Account Number : " << vFileContent[count] << endl;
		cout << "Pin Code       : " << vFileContent[count + 1] << endl;
		cout << "Name           : " << vFileContent[count + 2] << endl;
		cout << "Phone          : " << vFileContent[count + 3] << endl;
		cout << "Account Balance: " << vFileContent[count + 4] << endl;
		cout << "-----------------------------------\n";

		system("pause");
		system("cls");
		main();
	}
	else {

		cout << "Client With Account Number [" << FindClient.AccNum << "] is not Fount\n";
		cout << "Do you want Find any Clients ? Y/N : ";
		char more;
		cin >> more;

		if (more == 'Y' || more == 'y') {
			FindClientAccount("data.txt", vFileContent);
		}
		else {
			system("cls");
			main();
		}

	}



}

void SaveVectorToFile(string data, vector <string> vFileContent) {
	fstream MyFile(data, ios::out);

	if (MyFile.is_open()) {

		for (string& Line : vFileContent) {
			if (Line != "") {
				MyFile << Line << endl;
			}
		}
		MyFile.close();
	}
}

void DeleteClient(string data, vector <string>& vFileContent) {
	system("cls");
	Client MyClient;


	cout << "-----------------------------------------------------------------------------------------------------------------------------------\n";
	cout << "                                           Delete Client Screen                                                                    \n";
	cout << "-----------------------------------------------------------------------------------------------------------------------------------\n";




	cout << "Entre Account Number : ";
	cin >> MyClient.AccNum;

	if (SearchAccount(MyClient.AccNum, vFileContent)) {

		int count = 0;
		while (vFileContent[count] != MyClient.AccNum) {
			count += 6;

		}

		ShowClient(count, vFileContent);
		char Continue;
		cout << "Are you sure do you want delete this client ? Y/N : ";
		cin >> Continue;
		if (Continue == 'Y' || Continue == 'y') {
			vFileContent.erase(vFileContent.begin() + count, vFileContent.begin() + count + 6);
			cout << "Client deleted successfully\n";
			SaveVectorToFile("data.txt", vFileContent);

			system("pause");
			system("cls");
			main();
		}
		else {
			system("cls");
			main();
		}




	}
	else {
		cout << "Client With Account Number [" << MyClient.AccNum << "] is not Fount\n";
		cout << "Do you want Find any Clients ? Y/N : ";
		char more;
		cin >> more;

		if (more == 'Y' || more == 'y') {
			DeleteClient("data.txt", vFileContent);
		}
		else {
			system("cls");
			main();
		}
	}







}

void ShowClient(int count, vector <string>& vFileContent) {
	cout << "-----------------------------------\n";
	cout << "Account Number : " << vFileContent[count] << endl;
	cout << "Pin Code       : " << vFileContent[count + 1] << endl;
	cout << "Name           : " << vFileContent[count + 2] << endl;
	cout << "Phone          : " << vFileContent[count + 3] << endl;
	cout << "Account Balance: " << vFileContent[count + 4] << endl;
	cout << "-----------------------------------\n";

}

void UpdateClientsData(string data, vector <string>& vFileContent) {
	system("cls");
	Client MyClient;

	cout << "-----------------------------------------------------------------------------------------------------------------------------------\n";
	cout << "                                      Update Client data Screen                                                                    \n";
	cout << "-----------------------------------------------------------------------------------------------------------------------------------\n";

	cout << "Entre Account Number : ";
	cin >> MyClient.AccNum;


	if (SearchAccount(MyClient.AccNum, vFileContent)) {
		int count = 0;
		while (vFileContent[count] != MyClient.AccNum) {
			count += 6;

		}

		ShowClient(count, vFileContent);
		char Continue;
		cout << "Are you sure do you want update this client ? Y/N : ";
		cin >> Continue;

		if (Continue == 'Y' || Continue == 'y') {

			cout << "Account Number : ";
			cin >> vFileContent[count];
			cout << "Pin Code       : ";
			cin >> vFileContent[count + 1];
			cout << "Name           : ";
			cin.ignore();
			getline(cin, vFileContent[count + 2]);
			cout << "Phone          : ";
			cin >> vFileContent[count + 3];
			cout << "Account Balance: ";
			cin >> vFileContent[count + 4];


			cout << "Client updated Successfully\n";
			SaveVectorToFile("data.txt", vFileContent);

			cout << "Do you want update more clients data ? Y/N : ";
			char more;
			cin >> more;

			if (more == 'Y' || more == 'y') {
				UpdateClientsData("data.txt", vFileContent);
			}
			else {
				system("cls");
				main();
			}

		}
		else {
			system("cls");
			main();
		}
	}
	else {
		cout << "Client With Account Number [" << MyClient.AccNum << "] is not Fount\n";
		cout << "Do you want update another Client data ? Y/N : ";
		char more;
		cin >> more;

		if (more == 'Y' || more == 'y') {
			UpdateClientsData("data.txt", vFileContent);
		}
		else {
			system("cls");
			main();
		}
	}

}

void Transaction(string data, vector <string>& vFileContent) {
start:
	system("cls");
	cout << "-----------------------------------------------------------------------------------------------------------------------------------\n";
	cout << "                                                 Transaction Menue Screen \n";
	cout << "-----------------------------------------------------------------------------------------------------------------------------------\n";

	cout << "[1] Deposite\n";
	cout << "[2] Withdrw\n";
	cout << "[3] Total Balances\n";
	cout << "[4] Main Menue\n";
	cout << endl;

	int choic;
	cout << "Choose what do you want to do [1 to 4] : ";
	cin >> choic;

	switch (choic) {
	case 1: // Deposite
		Depoaite("data.txt", vFileContent);
		break;
	case 2: // Withdraw
		Withdraw("data.txt", vFileContent);
		break;
	case 3: // Total Balance
		TotalBalance("data.txt", vFileContent);
		break;
	case 4: // Main Menue
		system("cls");
		main();
		break;

	default:
		cout << "Wrong,try again\n";
		system("pause");
		system("cls");

		goto start;

	}

}

void Depoaite(string data, vector <string>& vFileContent) {
	system("cls");
	Client MyClient;

	cout << "-----------------------------------------------------------------------------------------------------------------------------------\n";
	cout << "                                                     Deposite Screen \n";
	cout << "-----------------------------------------------------------------------------------------------------------------------------------\n";

	while (true) {
		cout << "Entre Account Number : ";
		cin >> MyClient.AccNum;

		if (SearchAccount(MyClient.AccNum, vFileContent)) {
			break;
		}

	}

	int count = 0;
	while (vFileContent[count] != MyClient.AccNum) {
		count += 6;

	}

	ShowClient(count, vFileContent);

	cout << "Entre deposite amount : ";
	int deposite;
	cin >> deposite;

	cout << "Are you sure you want perform this transaction ? Y/N : ";
	char ForSure;
	cin >> ForSure;

	if (ForSure == 'Y' || ForSure == 'y') {

		int x = stoi(vFileContent[count + 4]) + deposite;
		vFileContent[count + 4] = to_string(x);
		cout << "Your Transaction is successfully , your balanc : " << vFileContent[count + 4];
		SaveVectorToFile("data.txt", vFileContent);
	}
	else {
		Depoaite("data.txt", vFileContent);
	}

	system("pause");
	system("cls");
	Transaction("data.txt", vFileContent);
}

void TotalBalance(string data, vector <string>& vFileContent) {
	cout << "                                                  Balances List (" << vFileContent.size() / 6 << ") Client(s)" << endl;
	cout << "-----------------------------------------------------------------------------------------------------------------------------------\n";
	cout << "|  Account Number" << setw(23) << "|  Client Name" << "          |  Balance" << endl;
	cout << "-----------------------------------------------------------------------------------------------------------------------------------\n";
	cout << endl;



	for (int i = 0; i < vFileContent.size(); i += 6) {

		cout << "| " << left << setw(23) << vFileContent[i]  // Account Number
			<< "| " << left << setw(23) << vFileContent[i + 2] // Client Name
			<< "| " << left << setw(23) << vFileContent[i + 4] // Balance
			<< "|" << endl;
	}
	cout << endl;
	cout << "-----------------------------------------------------------------------------------------------------------------------------------\n";

	int totalbalance = 0;
	for (int x = 4; x < vFileContent.size(); x += 6) {
		totalbalance += stoi(vFileContent[x]);
	}
	cout << "                                           Total Balance : " << totalbalance << endl;
	system("pause");
	system("cls");
	Transaction("data.txt", vFileContent);
}

void Withdraw(string data, vector <string>& vFileContent) {
	system("cls");
	Client MyClient;

	cout << "-----------------------------------------------------------------------------------------------------------------------------------\n";
	cout << "                                                 Withdraw Screen \n";
	cout << "-----------------------------------------------------------------------------------------------------------------------------------\n";

	while (true) {
		cout << "Entre Account Number : ";
		cin >> MyClient.AccNum;

		if (SearchAccount(MyClient.AccNum, vFileContent)) {
			break;
		}

	}

	int count = 0;
	while (vFileContent[count] != MyClient.AccNum) {
		count += 6;

	}

	ShowClient(count, vFileContent);

	int withdraw;
	while (true) {
		cout << "Entre withdraw amount : ";
		cin >> withdraw;

		if (withdraw > stoi(vFileContent[count + 4])) {
			cout << "Amount Exceeds the balance , you can withdraw up to : " << vFileContent[count + 4] << endl;

		}
		else {
			break;
		}

	}
	cout << "Are you sure you want perform this transaction ? Y/N : ";
	char choose;
	cin >> choose;

	if (choose == 'y' || choose == 'Y') {
		int x = stoi(vFileContent[count + 4]) - withdraw;
		vFileContent[count + 4] = to_string(x);
		cout << "Withdraw is Successfully , your balance : " << vFileContent[count + 4] << endl;
		SaveVectorToFile("data.txt", vFileContent);

		system("pause");
		system("cls");
		Transaction("data.txt", vFileContent);
	}
	else {
		system("cls");
		Transaction("data.txt", vFileContent);
	}

}
