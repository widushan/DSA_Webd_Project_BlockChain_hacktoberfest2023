#include <iostream>
#include <string>
#include <fstream>
#include <vector>

class BankAccount {
protected:
    std::string accountNumber;
    std::string accountHolder;
    double balance;

public:
    BankAccount(const std::string& accNum, const std::string& accHolder, double initialBalance)
        : accountNumber(accNum), accountHolder(accHolder), balance(initialBalance) {}

    virtual void deposit(double amount) {
        balance += amount;
    }

    virtual void withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
        } else {
            std::cout << "Insufficient funds for withdrawal." << std::endl;
        }
    }

    virtual void displayInfo() const {
        std::cout << "Account Number: " << accountNumber << std::endl;
        std::cout << "Account Holder: " << accountHolder << std::endl;
        std::cout << "Balance: $" << balance << std::endl;
    }

    virtual ~BankAccount() {}
};

class SavingsAccount : public BankAccount {
    double interestRate;

public:
    SavingsAccount(const std::string& accNum, const std::string& accHolder, double initialBalance, double interest)
        : BankAccount(accNum, accHolder, initialBalance), interestRate(interest) {}

    void addInterest() {
        balance += (balance * interestRate / 100);
    }

    void displayInfo() const override {
        BankAccount::displayInfo();
        std::cout << "Interest Rate: " << interestRate << "%" << std::endl;
    }
};

int main() {
    std::vector<BankAccount*> accounts;

    accounts.push_back(new SavingsAccount("SAV123", "Alice", 5000.0, 3.5));
    accounts.push_back(new SavingsAccount("SAV456", "Bob", 3000.0, 2.5));

    for (const auto& account : accounts) {
        account->displayInfo();
        account->deposit(1000.0);
        account->withdraw(800.0);
        account->addInterest();
        account->displayInfo();
        std::cout << "---------------------------------------" << std::endl;
    }

    // Save account information to a file
    std::ofstream outputFile("bank_accounts.txt");
    if (outputFile.is_open()) {
        for (const auto& account : accounts) {
            outputFile << "Account Type: " << typeid(*account).name() << std::endl;
            outputFile << "Account Details:" << std::endl;
            account->displayInfo();
            outputFile << "---------------------------------------" << std::endl;
        }
        outputFile.close();
    } else {
        std::cerr << "Unable to open the file for writing." << std::endl;
    }

    // Clean up dynamic memory
    for (const auto& account : accounts) {
        delete account;
    }

    return 0;
}
