// WRITE A PROGRAM TO IMPLEMENT ENCAPSULATION AND ABSTRACTION
#include <iostream>
#include <string>
using namespace std;

// class with encapsulation and Data Abstraction

class BankAccount
{
private:
    string accountHolder;
    double balance;

public:
    // constructor to intialize the account
    BankAccount(string holder, double intialBalance)
    {
        accountHolder = holder;
        /*
        The statement accountHolder = holder;
        ensures that the data member accountHolder is initialized with the name of the person or entity
        holding the account.It allows you to store a value that is passed from outside the class (via the constructor) into the private data member.
        This makes the accountHolder data available for use within the class, and the value is tied to the specific object (account) being created.
        This is an example of encapsulation, one of the key principles of object-oriented programming. By using the constructor to set the value of
        accountHolder,you encapsulate the details of how the account is initialized.The private member accountHolder is hidden from outside access,
        and its value can only be set through the constructor or setter methods.
        */
        if (intialBalance >= 0)
            balance = intialBalance;
        else
            balance = 0.0;
    }
    // getter method for balance - Encapsulation
    double getBalance() const
    {
        return balance;
    }
    // setter method for deposit - Encapsulation
    void deposit(double amount)
    {
        if (amount  >0)
            balance += amount;
        else
            cout << "Invalid deposit amount " << endl;
    }
    // setter method for withdrawl - Encapsulation
    void withdraw(double amount)
    {
        if (amount > 0 && amount <= balance)
            balance -= amount;
        else
            cout << "Invalid or insufficient funds for withdrawl " << endl;
    }
    // Abstracting behavior of the account: View Account Details - Data Abstraction
    void showDataInfo() const
    {
        cout << "Account Holder : " << accountHolder << endl;
        cout << "Balance        : " << balance << " Rs " << endl;
    }
};
int main()
{
    // creating a bank account object "account" (Encapsulation in use)
    BankAccount account("Sahastrajeet Hardaha", 50000.00);

    // displaying account details (Data Abstraction)
    account.showDataInfo();

    // depositing and withdrawing money
    account.deposit(20000);  // Encapsulation: using setter to modify data
    account.withdraw(10000); // Encapsulation: using setter to modify data

    // displaying updated account details (Data Abstraction)
    account.showDataInfo();
    return 0;
}