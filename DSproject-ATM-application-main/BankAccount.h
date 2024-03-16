#pragma once
#include <string>
#include <iostream>


using namespace std;


// ***********************ACCOUNT HISTORY*******************************

// Node for History_List singly Linked List
class Node {
public:
	string elem;
	Node* next;

	Node() {
		elem = "";
		next = NULL;
	}

	Node(string val) {
		elem = val;
		next = NULL;
	}
};


// Singly Linked List for Account History stack
class History_List {
private:
	int size;
	Node* head;
	Node* tail;

public:
	History_List()
	{
		size = 0;
		head = NULL;
		tail = NULL;
	}



	// This is actually a insertFirst function
	void insertEntry(string val) {
		Node* temp = new Node(val);
		if (head == NULL) {
			head = temp;
			tail = temp;
		}
		else {
			temp->next = head;
			head = temp;
		}
		size++;
	}

	// This is actually a deleteFirst function
	void deleteEntry() {
		if (head == NULL)
			cout << "List is empty" << endl;
		else {
			Node* temp = head;

			if (size == 1) {
				delete temp;
				head = NULL;
				tail = NULL;
			}
			else {
				head = head->next;
				delete temp;
			}
			size--;
		}
	}

	string printHead() {
		return head->elem;
	}

	void print() {
		Node* current = head;
		while (current != NULL) {
			cout << current->elem << "\t";
			current = current->next;
		}
		cout << endl;
	}


};

class Account_History {
public:
	int top;
	History_List* data;

	Account_History()
	{
		data = new History_List();
		top = 0;
	}

	void push(string val) {
		data->insertEntry(val);
		top++;
	}

	string pop()
	{
		if (top == 0)
			return "Stack is empty";
		else {
			top--;
			return data->printHead();
		}
	}

	string peek() {
		return data->printHead();
	}

	void traverse() {
		data->print();
	}
};

class Customer {

public:
	Account_History* deposits;
	Account_History* withdrawals;
	Account_History* totalBalance;


	Customer() {
		deposits = new Account_History();
		withdrawals = new Account_History();
		totalBalance = new Account_History();
	}


	int deposit(string val, string total) {
		deposits->push(val);
		withdrawals->push("");
		int balance = stoi(total);
		balance += stoi(val);
		totalBalance->push(to_string(balance));
		return balance;
	}

	int withdraw(string val, string total) {
		withdrawals->push(val);
		deposits->push("");
		int balance = stoi(total);
		balance -= stoi(val);
		totalBalance->push(to_string(balance));
		return balance;
	}
};


// **************************ACCOUNT DATA************************
// Hash Table

class Data_item {
public:
	string accNum;
	string accBalance;
	string name;
	string atmPin;
	string age;
	string address;
	Customer* customer;

	Data_item()
	{
		accNum = "";
		accBalance = "";
		name = "";
		atmPin = "";
		age = "";
		address = "";
		customer = nullptr;
	}


	Data_item(string accNum1, string accBalance1, string name1,
		string atmPin1, string age1, string address1) {
		accNum = accNum1;
		accBalance = accBalance1;
		name = name1;
		atmPin = atmPin1;
		age = age1;
		address = address1;
		customer = new Customer;
	}

};

class NodeD {
public:
	Data_item item;
	NodeD* prev;
	NodeD* next;

	NodeD() {
		prev = NULL;
		next = NULL;
	}

	NodeD(Data_item itm) {
		item = itm;
		prev = NULL;
		next = NULL;
	}
};



class ListD {
private:
	NodeD* head;
	NodeD* tail;
	int capacity;
	int size;

public:
	ListD()
	{
		size = 0;
		capacity = 10;
		head = NULL;
		tail = NULL;

		NodeD* temp1 = new NodeD();
		head = temp1;
		tail = temp1;

		for (int i = 1; i < capacity; i++) {
			NodeD* temp = new NodeD();
			tail->next = temp;
			temp->prev = tail;
			tail = temp;
			size++;
		}
	}



	void assign(int pos, Data_item itm) {
		if (pos < 0 || pos > size)
			cout << "Invalid Position" << endl;
		else {
			if (pos < size / 2) {
				NodeD* current = head;
				for (int i = 0; i < pos; i++) {
					current = current->next;
				}
				current->item = itm;
			}
			else {
				NodeD* current = tail;
				for (int i = size; i > pos; i--) {
					current = current->prev;
				}
				current->item = itm;
			}
		}
	}

	string accNumber(int index) {
		NodeD* current = head;
		for (int i = 0; i < index; i++) {
			current = current->next;
		}
		return current->item.accNum;
	}

	Customer* accHistory(int index) {
		NodeD* current = head;
		for (int i = 0; i < index; i++) {
			current = current->next;
		}
		return current->item.customer;
	}

	NodeD* accDetails(int index) {
		NodeD* current = head;
		for (int i = 0; i < index; i++) {
			current = current->next;
		}
		return current;
	}

	void deleteEntry(int index) {
		NodeD* current = head;
		for (int i = 0; i < index; i++) {
			current = current->next;
		}
		Data_item dataitem;
		current->item = dataitem;		// emptying the entry
	}

};

class AccDataTable {
private:
	static const int size = 10;
	ListD table;

public:

	int getHash(string key) {
		int sum = 0;
		for (int i = 0; i < key.length(); i++) {
			sum = sum + key[i];
		}
		return sum % size;
	}

	// Linear Probing used
	void insert(string accNum1, string accBalance1, string name1,
		string atmPin1, string age1, string address1) {
		// cant have same 2 acc numbersssss
		int index = getHash(accNum1);
		Data_item di(accNum1, accBalance1, name1, atmPin1, age1, address1);

		while (table.accNumber(index) != "") {
			index++;
			index %= size;
		}
		table.assign(index, di);
	}

	void remove(string key) {
		if (!isAccExist(key))
			cout << "Key does not exist" << endl;
		else {
			int index = getHash(key);

			while (table.accNumber(index) != "") {
				if (table.accNumber(index) == key)
					table.deleteEntry(index);
				else {
					index++;
					index %= size;
				}
			}
		}
	}

	bool isAccExist(string key) {
		int index = getHash(key);
		for (int i = 0; i < size; i++) {
			if (table.accNumber(index) == key)
				return true;
			else
				index = (index + 1) % size;
		}
		return false;
	}

	bool isPinCorrect(string key, string pin) {
		int index = getHash(key);
		for (int i = 0; i < size; i++) {
			if (table.accNumber(index) == key) {
				if (table.accDetails(index)->item.atmPin == pin)
					return true;
			}
			else
				index = (index + 1) % size;
		}
		return false;
	}

	int getIndex(string key) {
		int index = getHash(key);
		for (int i = 0; i < size; i++) {
			if (table.accNumber(index) == key) {
				return index;
			}
			else
				index = (index + 1) % size;
		}
	}

	void setPin(string key, string pin) {
		int index = getHash(key);
		for (int i = 0; i < size; i++) {
			if (table.accNumber(index) == key) {
				table.accDetails(index)->item.atmPin = pin;
				return;
			}
			else
				index = (index + 1) % size;
		}
	}

	string getName(string key) {
		int index = getHash(key);
		for (int i = 0; i < size; i++) {
			if (table.accNumber(index) == key) {
				return table.accDetails(index)->item.name;
			}
			else
				index = (index + 1) % size;
		}
	}

	void updateBalance(string key, string money, bool withdrawal) {
		int index = getHash(key);
		for (int i = 0; i < size; i++) {
			if (table.accNumber(index) == key) {
				if (withdrawal) {
					string balance = table.accDetails(index)->item.accBalance;
					int amount = table.accDetails(index)->item.customer->withdraw(money, balance);
					table.accDetails(index)->item.accBalance = to_string(amount);
					return;
				}
				else {
					string balance = table.accDetails(index)->item.accBalance;
					int amount = table.accDetails(index)->item.customer->deposit(money, balance);
					table.accDetails(index)->item.accBalance = to_string(amount);
					return;
				}
			}
			else
				index = (index + 1) % size;
		}
	}

	string printBalance(string key) {
		int index = getHash(key);
		for (int i = 0; i < size; i++) {
			if (table.accNumber(index) == key) {
				string balance = table.accDetails(index)->item.accBalance;
				return balance;
			}
			else
				index = (index + 1) % size;
		}
	}

	string printCustomer(string key) {
		int index = getHash(key);
		for (int i = 0; i < size; i++) {
			if (table.accNumber(index) == key) {
				NodeD* itemDetail = table.accDetails(index);
				string details;
				details = "=================\nAcc No. : " + itemDetail->item.accNum
					+ "Name: " + itemDetail->item.name + "\n" +
					"Acc Balance: " + itemDetail->item.accBalance + "\n" + "Age: " + itemDetail->item.age + "\n" +
					"Address: " + itemDetail->item.address + "\n" + "ATM Pin: " + itemDetail->item.atmPin
					+ "\n=================\n";
				return details;
			}
			else
				index = (index + 1) % size;
		}
		return "Customer not found";
	}

	void printCustomerHistory(string key) {
		int index = getHash(key);
		for (int i = 0; i < size; i++) {
			if (table.accNumber(index) == key) {
				Customer* history = table.accHistory(index);
				// *************************************************************************
				cout << "Deposits	:";
				history->deposits->traverse();
				cout << "Withdrawals	:";
				history->withdrawals->traverse();
				cout << "Total Balance	:";
				history->totalBalance->traverse();
				return;
			}
			else
				index = (index + 1) % size;
		}
	}

	void printTable() {
		cout << "===================" << endl;
		for (int i = 0; i < size; i++) {
			cout << "Index: " << i << endl;
			NodeD* itemDetail = table.accDetails(i);
			string details;
			details = "---------------------\nAcc No. : " + itemDetail->item.accNum
				+ "Name: " + itemDetail->item.name + "\n" +
				"Acc Balance: " + itemDetail->item.accBalance + "\n" + "Age: " + itemDetail->item.age + "\n" +
				"Address: " + itemDetail->item.address + "\n" + "ATM Pin: " + itemDetail->item.atmPin
				+ "\n-----------------\n";
			cout << details;
		}
		cout << "===================" << endl;
	}

};

