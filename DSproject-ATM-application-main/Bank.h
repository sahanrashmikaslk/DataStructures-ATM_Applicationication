#pragma once
#include "BankAccount.h"

using namespace std;

class Bank {
private:
	AccDataTable* bankTable;

public:
	Bank()
	{
		bankTable = new AccDataTable();
	}

	~Bank() {
		delete bankTable;
	}

	void createCustomer(string accNum1, string accBalance1, string name1,
		string atmPin1, string age1, string address1) {
		bankTable->insert(accNum1, accBalance1, name1,
			atmPin1, age1, address1);
	}

	void deleteCustomer(string accNum) {
		bankTable->remove(accNum);
	}

	int atmAccess(string accNum, string pin) {
		if (!bankTable->isAccExist(accNum)) {
			cout << "Account Number does not exist" << endl;
			return 1;
		}
		else if (bankTable->isPinCorrect(accNum, pin)) {
			cout << "Access granted" << endl;
			return 2;
		}
		else
			return 3;
	}

	void withdrawMoney(string accNum, string money) {
		bankTable->updateBalance(accNum, money, true);
	}

	void depositMoney(string accNum, string money) {
		bankTable->updateBalance(accNum, money, false);
	}

	bool isAccExist(string accNum) {
		return bankTable->isAccExist(accNum);
	}

	string printBalance(string accNum) {
		return bankTable->printBalance(accNum);
	}

	string printName(string accNum) {
		return bankTable->getName(accNum);
	}

	void printTransactionHistory(string accNum) {
		bankTable->printCustomerHistory(accNum);
	}

	bool checkPin(string accNum, string pin) {
		return bankTable->isPinCorrect(accNum, pin);
	}

	void setPin(string accNum, string newPin) {
		bankTable->setPin(accNum, newPin);
	}

	void bankTransfer(string amount, string senderAcc, string receiverAcc) {
		bankTable->updateBalance(senderAcc, amount, true);
		bankTable->updateBalance(receiverAcc, amount, false);
	}

};


