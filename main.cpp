#include <iostream>
#include <string>
#include <ctime>
#include <sstream>
#include <vector> // For storing transactions

using namespace std;

// Define structures for Customer and Transaction
struct Customer {
    int code;
    string name;
    string dob;
    int balance;
    Customer* next;
};

struct Transaction {
    static int counter; // Static counter for unique IDs
    int id;
    int customerCode;
    string transactionType;
    int amount;
    string date;
    Transaction* next;

    Transaction(int custCode, string type, int amt, string txnDate) {
        id = ++counter;
        customerCode = custCode;
        transactionType = type;
        amount = amt;
        date = txnDate;
        next = nullptr;
    }
};

int Transaction::counter = 0;

// Function prototypes
Customer* addCustomer(Customer* head, int code, string name, string dob);
Customer* findCustomer(Customer* head, int code);
void deposit(Customer*& head, Transaction*& txnHead, int customerCode, int amount);
void withdraw(Customer*& head, Transaction*& txnHead, int customerCode, int amount);
void checkBalance(Customer* head, int code);
void viewCustomer(Customer* head, int code);
void displayCustomers(Customer* head);
void displayTransactions(Transaction* txnHead, int customerCode);
string getCurrentDate();

int main() {
    Customer* customerHead = nullptr; // Head of the customer linked list
    Transaction* transactionHead = nullptr; // Head of the transaction linked list
    int choice;

    do {
        cout << "\nPocket Money Management System\n";
        cout << "1. Add Customer\n";
        cout << "2. View Customer\n";
        cout << "3. Deposit\n";
        cout << "4. Withdraw\n";
        cout << "5. Check Balance\n";
        cout << "6. Display All Customers\n";
        cout << "7. Display Transactions\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int code;
                string name, dob;
                cout << "Enter Customer Code: ";
                cin >> code;
                cout << "Enter Customer Name: ";
                cin >> name;
                cout << "Enter Date of Birth (DD/MM/YYYY): ";
                cin >> dob;
                customerHead = addCustomer(customerHead, code, name, dob);
                break;
            }
            case 2: {
                int code;
                cout << "Enter Customer Code: ";
                cin >> code;
                viewCustomer(customerHead, code);
                break;
            }
            case 3: {
                int code, amount;
                cout << "Enter Customer Code: ";
                cin >> code;
                cout << "Enter Deposit Amount: ";
                cin >> amount;
                deposit(customerHead, transactionHead, code, amount);
                break;
            }
            case 4: {
                int code, amount;
                cout << "Enter Customer Code: ";
                cin >> code;
                cout << "Enter Withdraw Amount: ";
                cin >> amount;
                withdraw(customerHead, transactionHead, code, amount);
                break;
            }
            case 5: {
                int code;
                cout << "Enter Customer Code: ";
                cin >> code;
                checkBalance(customerHead, code);
                break;
            }
            case 6:
                displayCustomers(customerHead);
                break;
            case 7: {
                int code;
                cout << "Enter Customer Code: ";
                cin >> code;
                displayTransactions(transactionHead, code);
                break;
            }
            case 8:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 8);

    return 0;
}

// Function to add a new customer to the linked list
Customer* addCustomer(Customer* head, int code, string name, string dob) {
    Customer* newCustomer = new Customer;
    newCustomer->code = code;
    newCustomer->name = name;
    newCustomer->dob = dob;
    newCustomer->balance = 0;
    newCustomer->next = nullptr;

    if (head == nullptr) {
        return newCustomer;
    } else {
        Customer* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newCustomer;
        return head;
    }
}

// Function to find a customer by code
Customer* findCustomer(Customer* head, int code) {
    Customer* temp = head;
    while (temp != nullptr) {
        if (temp->code == code) {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}

// Function to deposit money for a customer
void deposit(Customer*& head, Transaction*& txnHead, int customerCode, int amount) {
    Customer* customer = findCustomer(head, customerCode);
    if (customer) {
        customer->balance += amount;
        string date = getCurrentDate();
        Transaction* newTransaction = new Transaction(customerCode, "Deposit", amount, date);
        newTransaction->next = txnHead;
        txnHead = newTransaction;
        cout << "Deposit successful.\n";
    } else {
        cout << "Customer not found.\n";
    }
}

// Function to withdraw money for a customer
void withdraw(Customer*& head, Transaction*& txnHead, int customerCode, int amount) {
    Customer* customer = findCustomer(head, customerCode);
    if (customer && customer->balance >= amount) {
        customer->balance -= amount;
        string date = getCurrentDate();
        Transaction* newTransaction = new Transaction(customerCode, "Withdraw", amount, date);
        newTransaction->next = txnHead;
        txnHead = newTransaction;
        cout << "Withdrawal successful.\n";
    } else {
        cout << "Insufficient balance or customer not found.\n";
    }
}

// Function to check and display customer balance
void checkBalance(Customer* head, int code) {
    Customer* customer = findCustomer(head, code);
    if (customer) {
        cout << "Customer Balance: " << customer->balance << endl;
    } else {
        cout << "Customer not found.\n";
    }
}

// Function to view customer details
void viewCustomer(Customer* head, int code) {
    Customer* customer = findCustomer(head, code);
    if (customer) {
        cout << "Customer Code: " << customer->code << endl;
        cout << "Customer Name: " << customer->name << endl;
        cout << "Date of Birth: " << customer->dob << endl;
        cout << "Balance: " << customer->balance << endl;
    } else {
        cout << "Customer not found.\n";
    }
}

// Function to display all customers
void displayCustomers(Customer* head) {
    Customer* temp = head;
    if (temp == nullptr) {
        cout << "No customers found.\n";
    } else {
        cout << "Customer List:\n";
        while (temp != nullptr) {
            cout << "Code: " << temp->code << ", Name: " << temp->name << ", DOB: " << temp->dob << ", Balance: " << temp->balance << endl;
            temp = temp->next;
        }
    }
}

// Function to display transactions for a specific customer
void displayTransactions(Transaction* txnHead, int customerCode) {
    Transaction* temp = txnHead;
    bool found = false;
    while (temp != nullptr) {
        if (temp->customerCode == customerCode) {
            found = true;
            cout << "ID: " << temp->id << ", Type: " << temp->transactionType << ", Amount: " << temp->amount << ", Date: " << temp->date << endl;
        }
        temp = temp->next;
    }
    if (!found) {
        cout << "No transactions found for customer " << customerCode << ".\n";
    }
}

// Function to get the current date in DD/MM/YYYY format
string getCurrentDate() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    stringstream date;
    date << (ltm->tm_mday < 10 ? "0" : "") << ltm->tm_mday << "/"
         << ((ltm->tm_mon + 1) < 10 ? "0" : "") << (ltm->tm_mon + 1) << "/"
         << (1900 + ltm->tm_year);
    return date.str();
}
