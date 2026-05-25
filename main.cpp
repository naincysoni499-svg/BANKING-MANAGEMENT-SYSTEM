#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

class BankAccount
{
private:
    int accountNumber;
    char name[50];
    float balance;

public:
    void createAccount()
    {
        cout << "\nEnter Account Number: ";
        cin >> accountNumber;

        cin.ignore();

        cout << "Enter Account Holder Name: ";
        cin.getline(name, 50);

        cout << "Enter Initial Balance: ";
        cin >> balance;
    }

    void displayAccount() const
    {
        cout << left << setw(15) << accountNumber
             << setw(25) << name
             << setw(15) << balance << endl;
    }

    int getAccountNumber() const
    {
        return accountNumber;
    }

    void deposit()
    {
        float amount;

        cout << "\nEnter Amount to Deposit: ";
        cin >> amount;

        balance += amount;

        cout << "\nAmount Deposited Successfully!\n";
    }

    void withdraw()
    {
        float amount;

        cout << "\nEnter Amount to Withdraw: ";
        cin >> amount;

        if (amount > balance)
        {
            cout << "\nInsufficient Balance!\n";
        }
        else
        {
            balance -= amount;
            cout << "\nWithdrawal Successful!\n";
        }
    }

    void checkBalance() const
    {
        cout << "\nCurrent Balance: " << balance << endl;
    }
};

// Create New Account
void createNewAccount()
{
    BankAccount acc;

    ofstream file("bank.dat", ios::binary | ios::app);

    acc.createAccount();

    file.write((char*)&acc, sizeof(acc));

    file.close();

    cout << "\nAccount Created Successfully!\n";
}

// Display All Accounts
void displayAccounts()
{
    BankAccount acc;

    ifstream file("bank.dat", ios::binary);

    if (!file)
    {
        cout << "\nNo Records Found!\n";
        return;
    }

    cout << "\n-------------------------------------------------------\n";

    cout << left << setw(15) << "Account No"
         << setw(25) << "Name"
         << setw(15) << "Balance" << endl;

    cout << "-------------------------------------------------------\n";

    while (file.read((char*)&acc, sizeof(acc)))
    {
        acc.displayAccount();
    }

    file.close();
}

// Deposit Money
void depositMoney()
{
    BankAccount acc;

    int accNo;
    bool found = false;

    fstream file("bank.dat", ios::binary | ios::in | ios::out);

    cout << "\nEnter Account Number: ";
    cin >> accNo;

    while (file.read((char*)&acc, sizeof(acc)))
    {
        if (acc.getAccountNumber() == accNo)
        {
            acc.deposit();

            int pos = (-1) * sizeof(acc);

            file.seekp(pos, ios::cur);

            file.write((char*)&acc, sizeof(acc));

            found = true;

            break;
        }
    }

    if (!found)
    {
        cout << "\nAccount Not Found!\n";
    }

    file.close();
}

// Withdraw Money
void withdrawMoney()
{
    BankAccount acc;

    int accNo;
    bool found = false;

    fstream file("bank.dat", ios::binary | ios::in | ios::out);

    cout << "\nEnter Account Number: ";
    cin >> accNo;

    while (file.read((char*)&acc, sizeof(acc)))
    {
        if (acc.getAccountNumber() == accNo)
        {
            acc.withdraw();

            int pos = (-1) * sizeof(acc);

            file.seekp(pos, ios::cur);

            file.write((char*)&acc, sizeof(acc));

            found = true;

            break;
        }
    }

    if (!found)
    {
        cout << "\nAccount Not Found!\n";
    }

    file.close();
}

// Balance Inquiry
void balanceInquiry()
{
    BankAccount acc;

    int accNo;
    bool found = false;

    ifstream file("bank.dat", ios::binary);

    cout << "\nEnter Account Number: ";
    cin >> accNo;

    while (file.read((char*)&acc, sizeof(acc)))
    {
        if (acc.getAccountNumber() == accNo)
        {
            acc.checkBalance();

            found = true;

            break;
        }
    }

    if (!found)
    {
        cout << "\nAccount Not Found!\n";
    }

    file.close();
}

// Main Function
int main()
{
    int choice;

    do
    {
        cout << "\n========== BANK MANAGEMENT SYSTEM ==========\n";

        cout << "1. Create New Account\n";
        cout << "2. Display All Accounts\n";
        cout << "3. Deposit Money\n";
        cout << "4. Withdraw Money\n";
        cout << "5. Balance Inquiry\n";
        cout << "6. Exit\n";

        cout << "\nEnter Your Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            createNewAccount();
            break;

        case 2:
            displayAccounts();
            break;

        case 3:
            depositMoney();
            break;

        case 4:
            withdrawMoney();
            break;

        case 5:
            balanceInquiry();
            break;

        case 6:
            cout << "\nThank You!\n";
            break;

        default:
            cout << "\nInvalid Choice!\n";
        }

    } while (choice != 6);

    return 0;
}