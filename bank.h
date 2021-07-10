#ifndef BANK_H
#define BANK_H

#include <map>
#include "account.h"

////////////////////////////// BANK ///////////////////////////////

class Bank {
private:
	map<long, Account> accounts;
	
public:
	// Constructors
	Bank();
	
	// Getter functions
	int getNumberOfAccounts();
	
	// Display functions
	void displayMainOptions();
	void displayAccountOptions();	
	void displayAccount(long accountNumber);
	
	// Bank functions
	void processMainChoice(int choice);	
	bool login(long accountNumber, long pinNumber); 	
	Account openAccount();
	void closeAccount(long accountNumber);
	
	// Validation functions
	bool validateAccount(long accountNumber, long pinNumber);
	
	// Destructor
	~Bank();
};

#endif
