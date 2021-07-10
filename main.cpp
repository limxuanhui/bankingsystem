#include <iostream>
#include "bank.h"

using std::cin;
using std::cout;

int main() {

	Bank bank;
	int choice;
	do {
		cout << "\nWhat would you like to do today?" << endl;		
		bank.displayMainOptions();
		cin >> choice;	
		bank.processMainChoice(choice);
	} while (choice != 6);
	
	return 0;
}
