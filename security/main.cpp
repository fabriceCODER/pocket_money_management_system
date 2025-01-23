#include <iostream>
#include <string>
#include <ctime>
using namespace std;

// Structure for Customer
struct Customer {
    int code;
    string name;
    string dob;
    int balance;
    string pin; // Added for security
    Customer* next;
};

// Structure for Transaction
struct Transaction {
    int id;
    int customerCode;
    string type; // "deposit" or "withdraw"
    int amount;
    string date;
    Transaction* next;
};

class PocketMoneyManagement {
private:
    Customer* customerHead;
    Transaction* transactionHead;
    int transactionCounter;

    // Get current date as a string
    string getCurrentDate() {
        time_t now = time(0);
        tm* localtm = localtime(&now);
        char buffer[11];
        strftime(buffer, sizeof(buffer), "%d/%m/%Y", localtm);
        return string(buffer);
    }

    void updateCustomerBalance(int customerCode, int newBalance) {
        Customer* customer = findCustomer(customerCode);
        if (customer) {
            customer->balance = newBalance;
        }
    }

    // Validate PIN for a customer
    bool validatePin(Customer* customer, const string& pin) {
        return customer && customer->pin == pin;
    }

public:
    PocketMoneyManagement() : customerHead(nullptr), transactionHead(nullptr), transactionCounter(0) {}

    // Add a new customer
    void addCustomer(int code, const string& name, const string& dob, int balance, const string& pin) {
        Customer* newCustomer = new Customer{code, name, dob, balance, pin, nullptr};
        if (!customerHead) {
            customerHead = newCustomer;
        } else {
            Customer* temp = customerHead;
            while (temp->next) temp = temp->next;
            temp->next = newCustomer;
        }
        cout << "Customer added successfully.\n";
    }

    // Find a customer by code
    Customer* findCustomer(int code) {
        Customer* temp = customerHead;
        while (temp) {
            if (temp->code == code) return temp;
            temp = temp->next;
        }
        return nullptr;
    }

    // Record a transaction
    void recordTransaction(int customerCode, const string& type, int amount) {
        string date = getCurrentDate();
        Transaction* newTransaction = new Transaction{++transactionCounter, customerCode, type, amount, date, nullptr};
        if (!transactionHead) {
            transactionHead = newTransaction;
        } else {
            Transaction* temp = transactionHead;
            while (temp->next) temp = temp->next;
            temp->next = newTransaction;
        }
    }

    // Deposit money
    void deposit(int customerCode, int amount, const string& pin) {
        Customer* customer = findCustomer(customerCode);
        if (!customer) {
            cout << "Customer not found.\n";
            return;
        }
        if (!validatePin(customer, pin)) {
            cout << "Invalid PIN.\n";
            return;
        }
        int newBalance = customer->balance + amount;
        updateCustomerBalance(customerCode, newBalance);
        recordTransaction(customerCode, "deposit", amount);
        cout << "Deposit successful. New balance: " << newBalance << "\n";
    }

    // Withdraw money
    void withdraw(int customerCode, int amount, const string& pin) {
        Customer* customer = findCustomer(customerCode);
        if (!customer) {
            cout << "Customer not found.\n";
            return;
        }
        if (!validatePin(customer, pin)) {
            cout << "Invalid PIN.\n";
            return;
        }
        if (customer->balance < amount) {
            cout << "Insufficient balance.\n";
            return;
        }
        int newBalance = customer->balance - amount;
        updateCustomerBalance(customerCode, newBalance);
        recordTransaction(customerCode, "withdraw", amount);
        cout << "Withdrawal successful. New balance: " << newBalance << "\n";
    }

    // Check balance
    void checkBalance(int customerCode, const string& pin) {
        Customer* customer = findCustomer(customerCode);
        if (!customer) {
            cout << "Customer not found.\n";
            return;
        }
        if (!validatePin(customer, pin)) {
            cout << "Invalid PIN.\n";
            return;
        }
        cout << "Customer balance: " << customer->balance << "\n";
    }

    // Display all customers
    void displayCustomers() {
        Customer* temp = customerHead;
        if (!temp) {
            cout << "No customers found.\n";
            return;
        }
        cout << "Customers:\n";
        while (temp) {
            cout << "Code: " << temp->code << ", Name: " << temp->name << ", DOB: " << temp->dob << ", Balance: " << temp->balance << "\n";
            temp = temp->next;
        }
    }

    // Display all transactions
    void displayTransactions() {
        Transaction* temp = transactionHead;
        if (!temp) {
            cout << "No transactions found.\n";
            return;
        }
        cout << "Transactions:\n";
        while (temp) {
            cout << "ID: " << temp->id << ", Customer Code: " << temp->customerCode
                 << ", Type: " << temp->type << ", Amount: " << temp->amount
                 << ", Date: " << temp->date << "\n";
            temp = temp->next;
        }
    }
};

int main() {
    PocketMoneyManagement system;

    int choice, code, amount;
    string name, dob, pin;

    do {
        cout << "\nPocket Money Management System:\n";
        cout << "1. Add Customer\n2. Deposit\n3. Withdraw\n4. Check Balance\n5. Display Customers\n6. Display Transactions\n7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Customer Code: ";
                cin >> code;
                cout << "Enter Name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter DOB (dd/mm/yyyy): ";
                cin >> dob;
                cout << "Enter Initial Balance: ";
                cin >> amount;
                cout << "Set PIN: ";
                cin >> pin;
                system.addCustomer(code, name, dob, amount, pin);
                break;
            case 2:
                cout << "Enter Customer Code: ";
                cin >> code;
                cout << "Enter Deposit Amount: ";
                cin >> amount;
                cout << "Enter PIN: ";
                cin >> pin;
                system.deposit(code, amount, pin);
                break;
            case 3:
                cout << "Enter Customer Code: ";
                cin >> code;
                cout << "Enter Withdrawal Amount: ";
                cin >> amount;
                cout << "Enter PIN: ";
                cin >> pin;
                system.withdraw(code, amount, pin);
                break;
            case 4:
                cout << "Enter Customer Code: ";
                cin >> code;
                cout << "Enter PIN: ";
                cin >> pin;
                system.checkBalance(code, pin);
                break;
            case 5:
                system.displayCustomers();
                break;
            case 6:
                system.displayTransactions();
                break;
            case 7:
                cout << "Exiting the system.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 7);

    return 0;
}
