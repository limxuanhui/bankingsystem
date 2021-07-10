#include <iostream>
#include "accounterror.h"

using std::cout;
using std::endl;

AccountError::AccountError(int errCode) {
	cout << "Error code " << errCode << ": "; 
	if (errCode == 1) {
		cout << "Invalid amount." << endl;
	}
	else if (errCode == 2) {
		cout << "Insufficient balance." << endl;
	}
	else if (errCode == 3) {
		cout << "Account number does not exist." << endl;
	}
	else if (errCode == 4) {
		cout << "Wrong pin number." << endl;
	}
	else if (errCode == 5) {
		cout << "Pin number needs to be at least 8 digits long." << endl;
	}
	else {
		cout << "An unknown error occurred." << endl;
	}
}

