#include <iostream>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <string>
#include <sstream> 

using namespace std;

// ================== Transaction Class ==================
class Transaction {
public:
    string accountNumber;
    string type;  
    double amount;

    Transaction(string accNo, string tType, double amt) {
        accountNumber = accNo;
        type = tType;
        amount = amt;
    }

    void displayTransaction() const {
        cout << "Account: " << accountNumber
             << " | Type: " << type
             << " | Amount: $" << fixed << setprecision(2) << amount << "\n";
    }
};

// ================== Account Class ==================
class Account {
public:
    string fullName;
    string dob;
    string aadhaar;
    string accountType;
    string accountNumber;
    string password;
    double balance;

    void createAccount() {
        cin.ignore(); 
        cout << "Enter Full Name: ";
        getline(cin, fullName);

        cout << "Enter Date of Birth (DD/MM/YYYY): ";
        getline(cin, dob);

        while (true) {
            cout << "Enter 12-digit Aadhaar Number: ";
            cin >> aadhaar;
            if (aadhaar.length() == 12 && isDigitsOnly(aadhaar)) {
                break;
            }
            cout << "Invalid Aadhaar! Must be 12 digits.\n";
        }

        cout << "Enter Account Type (Saving/Current): ";
        cin >> accountType;

        
        accountNumber = generateRandomNumber(12);

        
        password = generateRandomPassword(8);

        balance = 0.0; 

        cout << "\nAccount Created Successfully!\n";
        cout << "Your Account Number: " << accountNumber << endl;
        cout << "Your Password: " << password << "\nKeep it safe!\n";
    }

    void displayAccount() const {
        cout << "\n===== Account Details =====\n";
        cout << "Full Name: " << fullName << endl;
        cout << "Date of Birth: " << dob << endl;
        cout << "Aadhaar Number: " << aadhaar << endl;
        cout << "Account Type: " << accountType << endl;
        cout << "Account Number: " << accountNumber << endl;
        cout << "Balance: $" << fixed << setprecision(2) << balance << endl;
    }

    void deposit(double amount) {
        balance += amount;
        cout << "Deposited $" << fixed << setprecision(2) << amount << " successfully!\n";
    }

    bool withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient Balance!\n";
            return false;
        }
        balance -= amount;
        cout << "Withdrawn $" << fixed << setprecision(2) << amount << " successfully!\n";
        return true;
    }

    void checkBalance() const {
        cout << "Your current balance is: $" << fixed << setprecision(2) << balance << endl;
    }

private:
    static bool isDigitsOnly(const string &str) {
        for (size_t i = 0; i < str.length(); i++) {
            if (!isdigit(str[i])) return false;
        }
        return true;
    }

    static string generateRandomNumber(int length) {
        string result = "";
        stringstream ss; 
        for (int i = 0; i < length; i++) {
            ss << (rand() % 10); 
        }
        return ss.str(); 
    }

    static string generateRandomPassword(int length) {
        string result = "";
        string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
        for (int i = 0; i < length; i++) {
            result += chars[rand() % chars.length()];
        }
        return result;
    }
};

// ================== Banking System Class ==================
class BankingSystem {
private:
    vector<Account> accounts;
    vector<Transaction> transactions;

public:
    void createAccount() {
        Account a;
        a.createAccount();
        accounts.push_back(a);
    }

    void depositMoney() {
        string accNo;
        double amount;
        cout << "Enter Account Number: ";
        cin >> accNo;
        cout << "Enter Deposit Amount: $";
        cin >> amount;

        for (size_t i = 0; i < accounts.size(); i++) {
            if (accounts[i].accountNumber == accNo) {
                accounts[i].deposit(amount);
                transactions.push_back(Transaction(accNo, "Deposit", amount));
                return;
            }
        }
        cout << "Account not found!\n";
    }

    void withdrawMoney() {
        string accNo;
        double amount;
        cout << "Enter Account Number: ";
        cin >> accNo;
        cout << "Enter Withdraw Amount: $";
        cin >> amount;

        for (size_t i = 0; i < accounts.size(); i++) {
            if (accounts[i].accountNumber == accNo) {
                if (accounts[i].withdraw(amount)) {
                    transactions.push_back(Transaction(accNo, "Withdraw", amount));
                    return;
                }
            }
        }
        cout << "Account not found!\n";
    }

    void transferMoney() {
        string fromAcc, toAcc;
        double amount;
        cout << "Enter Sender Account Number: ";
        cin >> fromAcc;
        cout << "Enter Receiver Account Number: ";
        cin >> toAcc;
        cout << "Enter Transfer Amount: $";
        cin >> amount;

        int senderIndex = -1, receiverIndex = -1;
        for (size_t i = 0; i < accounts.size(); i++) {
            if (accounts[i].accountNumber == fromAcc) senderIndex = i;
            if (accounts[i].accountNumber == toAcc) receiverIndex = i;
        }

        if (senderIndex != -1 && receiverIndex != -1) {
            if (accounts[senderIndex].withdraw(amount)) {
                accounts[receiverIndex].deposit(amount);
                transactions.push_back(Transaction(fromAcc, "Transfer", amount));
                cout << "Transfer Successful!\n";
            }
        } else {
            cout << "One or both accounts not found!\n";
        }
    }

    void viewCustomerDetails() {
        string accNo, pass;
        cout << "Enter Account Number: ";
        cin >> accNo;
        cout << "Enter Password: ";
        cin >> pass;

        for (size_t i = 0; i < accounts.size(); i++) {
            if (accounts[i].accountNumber == accNo && accounts[i].password == pass) {
                accounts[i].displayAccount();
                return;
            }
        }
        cout << "Invalid Account Number or Password!\n";
    }

    void checkBalance() {
        string accNo, pass;
        cout << "Enter Account Number: ";
        cin >> accNo;
        cout << "Enter Password: ";
        cin >> pass;

        for (size_t i = 0; i < accounts.size(); i++) {
            if (accounts[i].accountNumber == accNo && accounts[i].password == pass) {
                accounts[i].checkBalance();
                return;
            }
        }
        cout << "Invalid Account Number or Password!\n";
    }

    void showTransactions() {
        if (transactions.empty()) {
            cout << "No transactions found.\n";
            return;
        }
        cout << "\n===== Transaction History =====\n";
        for (size_t i = 0; i < transactions.size(); i++) {
            transactions[i].displayTransaction();
        }
    }
};

// ================== Main Function ==================
int main() {
    srand(time(0)); 
    BankingSystem bank;
    int choice;

    while (true) {
        cout << "\n===== Banking System Menu =====\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Transfer Money\n";
        cout << "5. View Customer Details\n";
        cout << "6. Check Balance\n";
        cout << "7. Show Transactions\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: bank.createAccount(); break;
            case 2: bank.depositMoney(); break;
            case 3: bank.withdrawMoney(); break;
            case 4: bank.transferMoney(); break;
            case 5: bank.viewCustomerDetails(); break;
            case 6: bank.checkBalance(); break;
            case 7: bank.showTransactions(); break;
            case 8: cout << "Exiting...\n"; return 0;
            default: cout << "Invalid choice, try again!\n";
        }
    }
}

