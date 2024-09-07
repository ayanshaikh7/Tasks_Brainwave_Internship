#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Account {
private:
    int accountNumber;
    string ownerName;
    double balance;

public:
    Account(int accNumber, string name, double initialDeposit)
        : accountNumber(accNumber), ownerName(name), balance(initialDeposit) {}

    int getAccountNumber() const {
        return accountNumber;
    }

    string getOwnerName() const {
        return ownerName;
    }

    double getBalance() const {
        return balance;
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposit successful! New balance: $" << balance << endl;
        } else {
            cout << "Deposit amount must be positive!" << endl;
        }
    }

    bool withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient funds!" << endl;
            return false;
        } else if (amount <= 0) {
            cout << "Withdrawal amount must be positive!" << endl;
            return false;
        } else {
            balance -= amount;
            cout << "Withdrawal successful! New balance: $" << balance << endl;
            return true;
        }
    }

    void display() const {
        cout << "Account Number: " << accountNumber << ", Owner: " << ownerName
             << ", Balance: $" << balance << endl;
    }
};

class Bank {
private:
    vector<Account> accounts;
    int nextAccountNumber = 1001; // Account numbers start from 1001

    Account* findAccount(int accountNumber) {
        for (auto& account : accounts) {
            if (account.getAccountNumber() == accountNumber) {
                return &account;
            }
        }
        return nullptr;
    }

public:
    void createAccount(string ownerName, double initialDeposit) {
        Account newAccount(nextAccountNumber, ownerName, initialDeposit);
        accounts.push_back(newAccount);
        cout << "Account created successfully! Account Number: " << nextAccountNumber << endl;
        nextAccountNumber++;
    }

    void deposit(int accountNumber, double amount) {
        Account* account = findAccount(accountNumber);
        if (account != nullptr) {
            account->deposit(amount);
        } else {
            cout << "Account not found!" << endl;
        }
    }

    void withdraw(int accountNumber, double amount) {
        Account* account = findAccount(accountNumber);
        if (account != nullptr) {
            account->withdraw(amount);
        } else {
            cout << "Account not found!" << endl;
        }
    }

    void transfer(int fromAccountNumber, int toAccountNumber, double amount) {
        Account* fromAccount = findAccount(fromAccountNumber);
        Account* toAccount = findAccount(toAccountNumber);

        if (fromAccount == nullptr || toAccount == nullptr) {
            cout << "One or both accounts not found!" << endl;
            return;
        }

        if (fromAccount->withdraw(amount)) {
            toAccount->deposit(amount);
            cout << "Transfer successful!" << endl;
        } else {
            cout << "Transfer failed!" << endl;
        }
    }

    void displayAccount(int accountNumber) {
        Account* account = findAccount(accountNumber);
        if (account != nullptr) {
            account->display();
        } else {
            cout << "Account not found!" << endl;
        }
    }
};

void displayMenu() {
    cout << "1. Create an Account" << endl;
    cout << "2. Deposit Money" << endl;
    cout << "3. Withdraw Money" << endl;
    cout << "4. Transfer Money" << endl;
    cout << "5. Display Account Information" << endl;
    cout << "6. Exit" << endl;
    cout << "Choose an option: ";
}

int main() {
    Bank bank;
    int choice;

    while (true) {
        displayMenu();
        cin >> choice;

        switch (choice) {
        case 1: {
            string name;
            double initialDeposit;
            cout << "Enter your name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter initial deposit: ";
            cin >> initialDeposit;
            bank.createAccount(name, initialDeposit);
            break;
        }
        case 2: {
            int accNumber;
            double amount;
            cout << "Enter account number: ";
            cin >> accNumber;
            cout << "Enter amount to deposit: ";
            cin >> amount;
            bank.deposit(accNumber, amount);
            break;
        }
        case 3: {
            int accNumber;
            double amount;
            cout << "Enter account number: ";
            cin >> accNumber;
            cout << "Enter amount to withdraw: ";
            cin >> amount;
            bank.withdraw(accNumber, amount);
            break;
        }
        case 4: {
            int fromAccNumber, toAccNumber;
            double amount;
            cout << "Enter the source account number: ";
            cin >> fromAccNumber;
            cout << "Enter the target account number: ";
            cin >> toAccNumber;
            cout << "Enter amount to transfer: ";
            cin >> amount;
            bank.transfer(fromAccNumber, toAccNumber, amount);
            break;
        }
        case 5: {
            int accNumber;
            cout << "Enter account number: ";
            cin >> accNumber;
            bank.displayAccount(accNumber);
            break;
        }
        case 6:
            cout << "Thank you for using the banking system!" << endl;
            return 0;
        default:
            cout << "Invalid option! Please try again." << endl;
        }
    }
    return 0;
}