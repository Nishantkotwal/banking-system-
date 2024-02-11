#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

using namespace std;

class BankAccount {
private:
    char accountNumber[20];
    char accountHolderName[50];
    double balance;

public:
    BankAccount() {
        balance = 0.0;
    }

    void createAccount() {
        cout << "Enter Account Number: ";
        cin >> accountNumber;
        cout << "Enter Account Holder Name: ";
        cin.ignore();
        cin.getline(accountHolderName, 50);
        cout << "Account created successfully!\n";
    }

    void displayAccount() {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Account Holder Name: " << accountHolderName << endl;
        cout << "Balance: $" << balance << endl;
    }

    void deposit() {
        double amount;
        cout << "Enter the amount to deposit: $";
        cin >> amount;
        balance += amount;
        cout << "Deposit successful. Current Balance: $" << balance << endl;
    }

    void withdraw() {
        double amount;
        cout << "Enter the amount to withdraw: $";
        cin >> amount;
        if (amount <= balance) {
            balance -= amount;
            cout << "Withdrawal successful. Current Balance: $" << balance << endl;
        } else {
            cout << "Insufficient funds!\n";
        }
    }

    void writeToFile() {
        ofstream outFile("bank_data.txt", ios::app);
        if (!outFile) {
            cerr << "Error opening file!" << endl;
            exit(1);
        }
        outFile.write(reinterpret_cast<char*>(this), sizeof(*this));
        outFile.close();
    }

    void readFromFile() {
        ifstream inFile("bank_data.txt");
        if (!inFile) {
            cerr << "Error opening file!" << endl;
            exit(1);
        }
        while (inFile.read(reinterpret_cast<char*>(this), sizeof(*this))) {
            displayAccount();
            cout << "-------------------\n";
        }
        inFile.close();
    }
};

int main() {
    BankAccount account;
    int choice;

    do {
        cout << "1. Create Account\n";
        cout << "2. Display Account Details\n";
        cout << "3. Deposit\n";
        cout << "4. Withdraw\n";
        cout << "5. Display All Accounts\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                account.createAccount();
                account.writeToFile();
                break;
            case 2:
                account.displayAccount();
                break;
            case 3:
                account.deposit();
                account.writeToFile();
                break;
            case 4:
                account.withdraw();
                account.writeToFile();
                break;
            case 5:
                account.readFromFile();
                break;
            case 6:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}
