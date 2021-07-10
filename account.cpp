#include <iostream>
#include <fstream>
#include <string>
#include "account.h"
#include "accounterror.h"

using namespace std;

long Account::lastAccountNumber = 0;

// Constructors
Account::Account() {}

Account::Account(string fn, string ln, long pinNumber) {
	accountNumber = ++lastAccountNumber;
	setPinNumber(pinNumber);
	firstName = fn;
	lastName = ln;	
	balance = 0.0f;
	isLoggedIn = false;
}


// Getter functions
long Account::getAccountNumber() {
	return accountNumber;
}

long Account::getPinNumber() {
	return pinNumber;
}

string Account::getFirstName() {
	return firstName;
}

string Account::getLastName() {
	return lastName;
}

float Account::getBalance() {
	return balance;
}
	
bool Account::getLoginStatus() {
	return isLoggedIn;
}


// Setter functions
void Account::setPinNumber(long pin) {
	// minimum 8 digits
	if (to_string(pin).length() < 8) throw AccountError(5);
	pinNumber = pin;
}

void Account::setLogin() {
	isLoggedIn = true;
} 

void Account::setLogout() {
	isLoggedIn = false;
}

void Account::setLastAccountNumber(long lastAccNum) {
	lastAccountNumber = lastAccNum;
};


// Validation functions
void Account::checkIsValidDeposit(float amount) {
	if (amount < 0) throw AccountError(1);	
}

void Account::checkIsValidWithdrawal(float amount) {
	if (amount < 0) throw AccountError(1);
	else if (amount > balance) throw AccountError(2);
}


// Client functions
void Account::checkAccountBalance() {
	cout << "Your account balance is $" << getBalance() << "." << endl;
}

void Account::deposit(float amount) {
	try {
		checkIsValidDeposit(amount);		
		balance += amount;
		cout << "You have successfully deposited $" << amount << ". Your new balance is $" << balance << "." << endl; 			
	}
	catch (AccountError err) {
		cout << "Please try again." << endl;
	}
}

void Account::withdraw(float amount) {
	try {
		checkIsValidWithdrawal(amount);		
		balance -= amount;
		cout << "You have successfully withdrawn $" << amount << ". Your new balance is $" << balance << "." << endl;			
	}
	catch (AccountError err) {
		cout << "Please try again." << endl;
	}	
}

void Account::checkProfile(Account* acc) {
	cout << *acc;
}


// Backend
void Account::processAccountChoice(int choice) {
	switch (choice) {
		float amount;
		case 1:
			cout << "Enter amount to deposit: ";
			cin >> amount;
			deposit(amount);
			break;
			
		case 2:
			cout << "Enter amount to withdraw: ";
			cin >> amount;
			withdraw(amount);
			break;
			
		case 3:
			checkAccountBalance();
			break;
			
		case 4:
			checkProfile(this);
			break;
			
		case 5:			
			setLogout();
			cout << "Log out success!" << endl;
 			break;		
					
		default:
			cout << "You have entered an invalid choice." << endl;
	}
}


// Friend functions
ofstream& operator<<(ofstream &ofs, Account &acc) {
	ofs << acc.accountNumber << endl;
	ofs << acc.pinNumber << endl;
	ofs << acc.firstName << endl;
	ofs << acc.lastName << endl;
	ofs << acc.balance << endl;
	return ofs;	
}

ifstream& operator>>(ifstream &ifs, Account &acc) {
	ifs >> acc.accountNumber;
	ifs >> acc.pinNumber;
	ifs >> acc.firstName;
	ifs >> acc.lastName;
	ifs >> acc.balance;
	return ifs;
}

ostream& operator<<(ostream &os, Account &acc) {
	os << "Full name: " << acc.firstName << " " << acc.lastName << endl;
	os << "Account number: " << acc.accountNumber << endl;
	os << "Pin number: " << acc.pinNumber << endl;
	os << "Balance: " << acc.balance << endl;
	return os;
}

