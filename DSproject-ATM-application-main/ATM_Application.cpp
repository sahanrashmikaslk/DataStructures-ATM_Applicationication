#include "Bank.h"
#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

void welcome_display() {

    system("CLS");
    cout << R"(
    _     ___    ___     ___     _     _  _   _  __
   /_\   | _ )  / __|   | _ )   /_\   | \| | | |/ /
  / _ \  | _ \ | (__    | _ \  / _ \  | .` | | ' < 
 /_/ \_\ |___/  \___|   |___/ /_/ \_\ |_|\_| |_|\_\ ATM )" << endl;
    cout << endl;

}


void menu() {


    Bank bank = Bank();
    bank.createCustomer("123", "5000", "John", "4321", "22", "12, Church road, Nuwara Eliya");
    bank.createCustomer("231", "324443", "Susan", "3242", "32", "16, Ocean Street, Galle");
    bank.createCustomer("435", "34222", "Robert", "7686", "23", "43, Main Street, Kandy");
    bank.createCustomer("987", "9000", "Jason", "9987", "20", "13, Main Road, Kegalle");
    bank.createCustomer("657", "2000", "Ann", "1253", "34", "1, Lake Road, Matara");
    int account_no;
    int pin;
    int current_pin;
    int new_pin;
    int count = 0;
    int entry;
    int deposit;
    int withdraw;
    bool isTrue = true;
    bool isInnerTrue = true;
    bool firstTime = true;
    system("Color 4E");

    //display bank name
    welcome_display();
    cout << "Enter your card or ACC. No: ";
    cin >> account_no;
    cout << "Enter your pin:";
    cin >> pin;

    do {
        int condition;
        if (!firstTime) {
            welcome_display();
            cout << "1. Log in again\n" << "2. Exit\n";
            cin >> entry;
            switch (entry) {
            case 1:
                welcome_display();
                cout << "Enter your card or ACC. No: ";
                cin >> account_no;
                cout << "Enter your pin:";
                cin >> pin;
                condition = bank.atmAccess(to_string(account_no), to_string(pin));
                break;
            case 2:
                isTrue = false;
                condition = INT_MIN;
                break;
            }
        }
        else
            condition = bank.atmAccess(to_string(account_no), to_string(pin));

        switch (condition) {
        case 2:
            do {
                isInnerTrue = true;
                welcome_display();
                // display menu
                cout << "Welcome " << bank.printName(to_string(account_no)) << "!" << endl;
                cout << "1. Deposit\n"
                    << "2. Withdraw\n"
                    << "3. Balance\n"
                    << "4. To change your pin\n"
                    << "5. Bank Transfer\n"
                    << "6. Print Account History\n"
                    << "7. Exit\n\n";
                cout << "Choose an option: ";
                cin >> entry;

                switch (entry) {
                case 1:
                    cout << "\nDeposit amount: ";
                    cin >> deposit;
                    bank.depositMoney(to_string(account_no), to_string(deposit));
                    system("pause");
                    break;

                case 2:
                    cout << "\nWithdraw amount: ";
                    cin >> withdraw;
                    if (withdraw <= stoi(bank.printBalance(to_string(account_no)))) {
                        bank.withdrawMoney(to_string(account_no), to_string(withdraw));
                        cout << "You have succesfully added money to account!" << endl;
                        system("pause");
                    }
                    else {
                        cout << "Insufficient balance!" << endl;
                        system("pause");
                    }
                    break;

                case 3:
                    cout << "\nCurrent balance is: Rs. " << bank.printBalance(to_string(account_no)) << endl;
                    system("pause");
                    break;

                case 4:
                    cout << "\nEnter your current pin: ";
                    cin >> current_pin;
                    if (bank.checkPin(to_string(account_no), to_string(current_pin))) {
                        cout << "Enter your new pin: ";
                        cin >> new_pin;
                        bank.setPin(to_string(account_no), to_string(new_pin));
                        system("pause");
                    }
                    else {
                        cout << "Wrong pin!" << endl;
                        system("pause");
                    }

                    break;

                case 5:
                    cout << "Enter the account Number you wish to transfer: " << endl;
                    int transferAcc;
                    cin >> transferAcc;
                    cout << "Enter the amount you wish to transfer: " << endl;
                    int transferAmount;
                    cin >> transferAmount;
                    if (bank.isAccExist(to_string(transferAcc)) && (transferAmount <= stoi(bank.printBalance(to_string(account_no))))) {
                        bank.bankTransfer(to_string(transferAmount), to_string(account_no), to_string(transferAcc));
                        cout << "Transfer successful" << endl;
                    }
                    else {
                        cout << "Transfer unsuccessful. Make sure you have enough funds and entered the transfer account correct" << endl;
                    }
                    system("pause");
                    break;

                case 6:
                    bank.printTransactionHistory(to_string(account_no));
                    system("pause");
                    break;

                case 7:
                    cout << "Have a nice day!" << endl;
                    system("pause");
                    isInnerTrue = false;
                    break;
                case INT_MIN:
                    isInnerTrue = false;
                    break;
                }
            } while (isInnerTrue);
            break;

        case 1:
            welcome_display();
            cout << "Account Number is incorrect" << endl;
            system("pause");
            break;

        case 3:
            welcome_display();
            cout << "Wrong pin!" << endl;
            system("pause");

            break;
        }
        firstTime = false;
    } while (isTrue);
}

int main()
{

    menu();
    return 0;
}
