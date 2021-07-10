#include <fstream>
#include <iostream>
#include "account.h"
#include "accounterror.h"
#include "bank.h"

using namespace std;

// Constructors
Bank::Bank() {
	
	ifstream ifs;
	ifs.open("bankdatabase.txt");
	Account acc;	
	
	if (ifs.is_open()) {
		if (ifs.peek() != EOF) {			
			while (!ifs.eof()) {			
				ifs >> acc; 
				accounts[acc.getAccountNumber()] = acc; // or use insert(pair<long, Account>)
			}	
			ifs.close();
			
			map<long, Account>::reverse_iterator rit = accounts.rbegin();			
			long lastAccNum = rit->first;			
			Account::setLastAccountNumber(lastAccNum);				
		}		
	}

	cout << "*** Welcome to Joseph Banking Corp ***" << endl;	
}


// Getter functions
int Bank::getNumberOfAccounts() {
	return accounts.size();
}


// Display functions
void Bank::displayMainOptions() {
	cout << "\t1) Log in" << endl;
	cout << "\t2) Open account" << endl;
	cout << "\t3) Close account" << endl;
	cout << "\t4) Investments or Other Enquiries" << endl;
	cout << "\t5) Display account details" << endl;
	cout << "\t6) Quit" << endl;
}

void Bank::displayAccountOptions() {
	cout << "\t1) Deposit" << endl;
	cout << "\t2) Withdrawal" << endl;
	cout << "\t3) Balance enquiry" << endl;
	cout << "\t4) Check profile" << endl;
	cout << "\t5) Log out" << endl;	
}

void Bank::displayAccount(long accountNumber) {
	map<long, Account>::iterator it = accounts.find(accountNumber);
	if (it == accounts.end()) {
		throw AccountError(3);
	}
	cout << it->second;
}


// Bank functions
void Bank::processMainChoice(int choice) {
	switch (choice) {
		case 1: 											
			long accNum, pinNum;				
			cout << "Enter your account number: ";
			cin >> accNum;
			cout << "Enter your pin number: ";
			cin >> pinNum;
			try {
				bool isLoggedIn = login(accNum, pinNum);
				if (isLoggedIn) {				
					Account& acc = accounts[accNum];
					int choice;
					do {
						cout << "\nWhat would you like to do today?" << endl;		
						displayAccountOptions();
						cin >> choice;
						acc.processAccountChoice(choice);
					} while (choice != 5);												
				} 
				else {					
					cout << "Account number does not exist!" << endl;
				}								
			}
			catch(AccountError err) {
				cout << "Please try again." << endl;
			}						
			break;		
		
		case 2:	
			try {
				Account newAcc = openAccount();
				accounts[newAcc.getAccountNumber()] = newAcc;
			}
			catch(AccountError err) {
				cout << "Please try again." << endl;
			}
			break;		
			
		case 3: {						
			cout << "Enter your account number: ";
			cin >> accNum;
			cout << "Enter your pin number: ";
			cin >> pinNum;
			
			try {
				if (validateAccount(accNum, pinNum)) {
					cout << "Are you sure you want to close this account? This action will be irrevocable!" << endl;
					cout << "Yes or No?" << endl;
					string answer;
					cin >> answer;
					
					if (answer[0] == 'y' || answer[0] == 'Y') {
						closeAccount(accNum);
					}
				}				
				else {
					cout << "You may have entered the wrong account number or pin number. Please try again." << endl;	
				}	
			}
			
			catch (AccountError err) {
				cout << "Please try again." << endl;
			}
			
			break;	
		}
				
		case 4:			
			cout << "For investment related help or other enquiries, please contact Joseph Banking Corp hotline @ 12344321." << endl;
			break;
		
		case 5:
			cout << "Enter the account number of the account to be displayed: ";
			long accountNumber;
			cin >> accountNumber;
			try {
				displayAccount(accountNumber);	
			}
			catch (AccountError err) {
				cout << "Please try again." << endl;
			}
			
			break;	
			
		case 6:			
			cout << "Goodbye! Have a nice day to all " << getNumberOfAccounts() << " members!." << endl;
 			break;		
					
		default:
			cout << "You have entered an invalid choice." << endl;
	}
}

bool Bank::login(long accountNumber, long pinNumber) {	
	
	if (validateAccount(accountNumber, pinNumber)) {
		Account& acc = accounts[accountNumber];
		acc.setLogin();
		cout << "Login Success!" << endl;
		cout << "Welcome " << acc.getFirstName() << "!" << endl;
		return true;
	}
	return false;
}

Account Bank::openAccount() {
	long pinNumber;
	string firstName, lastName;
	cout << "First name: ";
	cin >> firstName;
	cout << "Last name: ";
	cin >> lastName;
	cout << "Pin number: ";
	cin >> pinNumber;
	Account acc(firstName, lastName, pinNumber);
	cout << "Your account is successfully created." << endl;
	cout << acc;
	return acc;
}

void Bank::closeAccount(long accountNumber) {
	accounts.erase(accountNumber);
	cout << "Your account has succesfully been closed. We hope to serve you again!" << endl; 	
}


// Validation functions
bool Bank::validateAccount(long accountNumber, long pinNumber) {
	map<long, Account>::iterator it = accounts.find(accountNumber);
	if (it == accounts.end()) {
		throw AccountError(3);
	}
	else if (it->second.getPinNumber() != pinNumber) {
		throw AccountError(4);
	}
	else {
		return true;
	}
}


// Destructor
Bank::~Bank() {
	ofstream ofs("bankdatabase.txt", ios::trunc);
	map<long, Account>::iterator it;
	// map::iterator is bidirectional iterator, cannot use accounts.end() - 1.
	// https://stackoverflow.com/questions/52544364/map-iterator-no-match-for-operator/52544489
	// use std::prev instead
	auto last = prev(accounts.end());
	for (it = accounts.begin(); it != accounts.end(); it++) {
		ofs << it->second;
		if (it != last) {
			ofs << "\n";
		}
	}
	ofs.close();	
}
