#ifndef ACCOUNT_H
#define ACCOUNT_H

using namespace std;

////////////////////////////// ACCOUNT ///////////////////////////////
class Account {	
private:
	long accountNumber;
	long pinNumber;
	string firstName;
	string lastName;
	float balance;
	bool isLoggedIn;
	static long lastAccountNumber;
	
public:
	// Constructors
	Account();
	Account(string fn, string ln, long pinNumber);
	
	// Getter functions
	long getAccountNumber();
	long getPinNumber();
	string getFirstName();
	string getLastName();
	float getBalance();
	bool getLoginStatus();
	
	// Setter functions
	void setPinNumber(long pin);
	void setLogin();
	void setLogout();
	static void setLastAccountNumber(long lastAccNum);
	
	// Validation functions
	void checkIsValidDeposit(float amount);
	void checkIsValidWithdrawal(float amount);	
	
	// Client functions
	void checkAccountBalance();
	void deposit(float amount);
	void withdraw(float amount);	
	void checkProfile(Account* acc);
	
	// Backend
	void processAccountChoice(int choice);
		
	// Friend functions
	friend ofstream& operator<<(ofstream& ofs, Account& acc);
	friend ifstream& operator>>(ifstream& ifs, Account& acc);
	friend ostream& operator<<(ostream& os, Account& acc);
};

#endif
