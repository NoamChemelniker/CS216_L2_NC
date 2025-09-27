/*
Noam Chemelniker
Lab #2
*/
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>
using namespace std;

// Global constants
const string INPUT_FILE = "accounts.txt";
const string OUTPUT_FILE = "created_accounts.txt";
const string ERROR_FILE = "invalid_accounts.txt";
const string LOG_FILE = "log.txt";
const int MAX_ACCOUNTS = 1000;

// Function prototypes
bool isValidSSN(const string&);
bool isValidName(const string&);
bool isValidEmail(const string&);
void processAccounts(class BankAccount[], int&, int&, int&);
void printCreatedAccounts(const class BankAccount[], int);
void printInvalidAccounts(int);
void printLog();
void writeAccountsToFile(const class BankAccount[], int);
string generateAccountID(int);

// BankAccount class
class BankAccount {
private:
    string accountID;
    string ssn;
    string firstName;
    string lastName;
    string email;
    double availableBalance;
    double presentBalance;

public:
    BankAccount() {
        accountID = "00000000";
        ssn = "0000000000";
        firstName = "NA";
        lastName = "NA";
        email = "na@na.com";
        availableBalance = 0.0;
        presentBalance = 0.0;
    }

    BankAccount(const string& ssn, const string& fName, const string& lName, const string& mail, int seqNum) {
        setAccount(ssn, fName, lName, mail, seqNum);
    }

    BankAccount(const BankAccount& other) {
        accountID = other.accountID;
        ssn = other.ssn;
        firstName = other.firstName;
        lastName = other.lastName;
        email = other.email;
        availableBalance = other.availableBalance;
        presentBalance = other.presentBalance;
    }

    ~BankAccount() {
        accountID = "00000000";
        ssn = "";
        firstName = "";
        lastName = "";
        email = "";
        availableBalance = 0.0;
        presentBalance = 0.0;
    }

    bool setAccount(const string& ssnIn, const string& fName, const string& lName, const string& mail, int seqNum) {
        if (!isValidSSN(ssnIn) || !isValidName(fName) || !isValidName(lName) || !isValidEmail(mail)) {
            ofstream(LOG_FILE, ios::app) << "Invalid record: " << ssnIn << " " << fName << " " << lName << " " << mail << endl;
            return false;
        }

        ssn = ssnIn;
        firstName = fName;
        lastName = lName;
        email = mail;
        accountID = generateAccountID(seqNum);

        double startingPresent = (email.find(".edu") != string::npos) ? 150.0 : 100.0;
        setPresentBalance(startingPresent);
        setAvailableBalance(0.0);

        return true;
    }

    void setPresentBalance(double amount) {
        if (amount < -50.0) presentBalance = -50.0;
        else presentBalance = amount;
        if (availableBalance > presentBalance) availableBalance = presentBalance;
    }

    void setAvailableBalance(double amount) {
        if (amount > presentBalance) availableBalance = presentBalance;
        else if (amount < -50.0) availableBalance = -50.0;
        else availableBalance = amount;
    }

    string getAccountID() const { return accountID; }
    string getFirstName() const { return firstName; }
    string getLastName() const { return lastName; }
    string getEmail() const { return email; }
    double getAvailableBalance() const { return availableBalance; }
    double getPresentBalance() const { return presentBalance; }
};

// Main program
int main() {
    BankAccount accounts[MAX_ACCOUNTS];
    int numAccounts = 0;
    int numProcessed = 0;
    int numInvalid = 0;

    srand(time(0));

    int choice;
    do {
        cout << "====== Bank Menu ======" << endl;
        cout << "1. Process new checking account requests" << endl;
        cout << "2. Print all successfully created accounts" << endl;
        cout << "3. Print all invalid records" << endl;
        cout << "4. Print log file" << endl;
        cout << "5. Quit and write accounts to output file" << endl;
        cout << "Enter choice: " << endl;
        cin >> choice;

        switch (choice) {
            case 1:
                processAccounts(accounts, numAccounts, numProcessed, numInvalid);
                break;
            case 2:
                if (numAccounts == 0) {
                    cout << endl << "Error: No accounts have been created yet. Please process accounts first." << endl << endl;
                } else {
                    printCreatedAccounts(accounts, numAccounts);
                }
                break;
            case 3:
                printInvalidAccounts(numInvalid);
                break;
            case 4:
                printLog();
                break;
            case 5:
                writeAccountsToFile(accounts, numAccounts);
                cout << "Accounts written to file. Exiting..." << endl;
                break;
            default:
                cout << "Invalid option." << endl;
        }
    } while (choice != 5);

    return 0;
}

// Validate SSN
bool isValidSSN(const string& ssn) {
    if (ssn.length() != 10) return false;
    for (char c : ssn) if (!isdigit(c)) return false;
    return true;
}

// Validate names
bool isValidName(const string& name) {
    if (name.length() < 2) return false;
    for (char c : name) if (!isalpha(c)) return false;
    return true;
}

// Validate email
bool isValidEmail(const string& email) {
    size_t at = email.find('@');
    size_t dot = email.find_last_of('.');
    if (at == string::npos || dot == string::npos || at > dot) return false;

    string user = email.substr(0, at);
    string mailserver = email.substr(at + 1, dot - at - 1);
    string domain = email.substr(dot + 1);

    if (user.length() < 4 || mailserver.length() < 4) return false;
    if (domain != "com" && domain != "edu") return false;
    return true;
}

// Generate account ID
string generateAccountID(int seqNum) {
    stringstream ss;
    int randNum = rand() % 900000 + 100000;
    ss << randNum << setw(2) << setfill('0') << seqNum;
    return ss.str();
}

// Process input accounts
void processAccounts(BankAccount accounts[], int& numAccounts, int& numProcessed, int& numInvalid) {
    ifstream fin(INPUT_FILE);

    if (!fin) {
        cout << endl << "Error opening input file." << endl << endl;
        return;
    } else {
        cout << endl << "Accounts Processed." <<endl << endl;
    }

    string ssn, fName, lName, email;
    int seqNum = 1;

    while (fin >> ssn >> fName >> lName >> email) {
        numProcessed++;
        BankAccount temp;
        if (temp.setAccount(ssn, fName, lName, email, seqNum)) {
            accounts[numAccounts++] = temp;
            seqNum++;
        } else {
            numInvalid++;
            ofstream(ERROR_FILE, ios::app) << ssn << " " << fName << " " << lName << " " << email << endl;
        }
    }
}

// Print all created accounts
void printCreatedAccounts(const BankAccount accounts[], int numAccounts) {
    cout << endl << left << setw(12) << "AccountID"
         << setw(12) << "First"
         << setw(12) << "Last"
         << setw(25) << "Email"
         << right << setw(12) << "AvailBal"
         << setw(12) << "PresBal" << endl << endl;

    for (int i = 0; i < numAccounts; i++) {
        cout << left << setw(12) << accounts[i].getAccountID()
             << setw(12) << accounts[i].getFirstName()
             << setw(12) << accounts[i].getLastName()
             << setw(25) << accounts[i].getEmail()
             << right << setw(12) << fixed << setprecision(2) << accounts[i].getAvailableBalance()
             << setw(12) << accounts[i].getPresentBalance() << endl;
    }
    cout << endl;
}

// Print invalid records
void printInvalidAccounts(int numInvalid) {
    cout << endl << "Invalid records: " << numInvalid << endl << endl;
    ifstream fin(ERROR_FILE);
    string line;
    while (getline(fin, line)) {
        cout << line << endl;
        cout << "----------------" << endl;
    }
    cout << endl;
}

// Print log
void printLog() {
    ifstream fin(LOG_FILE);
    if (!fin) {
        cout << endl << "Log file not found." << endl << endl;
        return;
    }

    cout << "====== Log File ======" << endl << endl;

    string line;
    while (getline(fin, line)) {
        cout << line << endl;
    }

    cout << endl;
}

// Write accounts to file
void writeAccountsToFile(const BankAccount accounts[], int numAccounts) {
    ofstream fout(OUTPUT_FILE);
    fout << left << setw(12) << "AccountID"
         << setw(12) << "First"
         << setw(12) << "Last"
         << setw(25) << "Email"
         << right << setw(12) << "AvailBal"
         << setw(12) << "PresBal" << endl;

    for (int i = 0; i < numAccounts; i++) {
        fout << left << setw(12) << accounts[i].getAccountID()
             << setw(12) << accounts[i].getFirstName()
             << setw(12) << accounts[i].getLastName()
             << setw(25) << accounts[i].getEmail()
             << right << setw(12) << fixed << setprecision(2) << accounts[i].getAvailableBalance()
             << setw(12) << accounts[i].getPresentBalance() << endl;
    }
}

/*
========Code Test========

    Test Data:
1234567890 Alice Johnson alice.johnson@school.edu
0987654321 Bob Smith bob.smith@gmail.com
12345 Carol Brown carol.brown@domain.com
123456789012 David Lee david.lee@domain.com
123456789A Eve Adams eve.adams@domain.com
1234567892 F@ith Miller faith.miller@domain.com
1234567893 George O'Neill george.oneill@school.edu
1234567894 Hannah White hannah@edu.org
1234567895 Jane Doe jane.doe@university.edu
1234567896 Kyle Green kyle.green@gmail.com
1234567897 Li Wei li.wei@college.edu
1234567898 Paul King paul.king@gmail.com



    Output:
====== Bank Menu ======
1. Process new checking account requests
2. Print all successfully created accounts
3. Print all invalid records
4. Print log file
5. Quit and write accounts to output file
Enter choice: 
2

Error: No accounts have been created yet. Please process accounts first.

====== Bank Menu ======
1. Process new checking account requests
2. Print all successfully created accounts
3. Print all invalid records
4. Print log file
5. Quit and write accounts to output file
Enter choice: 
3

Invalid records: 0


====== Bank Menu ======
1. Process new checking account requests
2. Print all successfully created accounts
3. Print all invalid records
4. Print log file
5. Quit and write accounts to output file
Enter choice: 
4

Log file not found.

====== Bank Menu ======
1. Process new checking account requests
2. Print all successfully created accounts
3. Print all invalid records
4. Print log file
5. Quit and write accounts to output file
Enter choice: 
1

Accounts Processed.

====== Bank Menu ======
1. Process new checking account requests
2. Print all successfully created accounts
3. Print all invalid records
4. Print log file
5. Quit and write accounts to output file
Enter choice: 
3

Invalid records: 6

12345 Carol Brown carol.brown@domain.com
----------------
123456789012 David Lee david.lee@domain.com
----------------
123456789A Eve Adams eve.adams@domain.com
----------------
1234567892 F@ith Miller faith.miller@domain.com
----------------
1234567893 George O'Neill george.oneill@school.edu
----------------
1234567894 Hannah White hannah@edu.org
----------------

====== Bank Menu ======
1. Process new checking account requests
2. Print all successfully created accounts
3. Print all invalid records
4. Print log file
5. Quit and write accounts to output file
Enter choice: 
2

AccountID   First       Last        Email                        AvailBal     PresBal

30854101    Alice       Johnson     alice.johnson@school.edu         0.00      150.00
17838602    Bob         Smith       bob.smith@gmail.com              0.00      100.00
80304003    Jane        Doe         jane.doe@university.edu          0.00      150.00
98976904    Kyle        Green       kyle.green@gmail.com             0.00      100.00
18267005    Li          Wei         li.wei@college.edu               0.00      150.00
20509606    Paul        King        paul.king@gmail.com              0.00      100.00

====== Bank Menu ======
1. Process new checking account requests
2. Print all successfully created accounts
3. Print all invalid records
4. Print log file
5. Quit and write accounts to output file
Enter choice: 
4
====== Log File ======

Invalid record: 12345 Carol Brown carol.brown@domain.com
Invalid record: 123456789012 David Lee david.lee@domain.com
Invalid record: 123456789A Eve Adams eve.adams@domain.com
Invalid record: 1234567892 F@ith Miller faith.miller@domain.com
Invalid record: 1234567893 George O'Neill george.oneill@school.edu
Invalid record: 1234567894 Hannah White hannah@edu.org

====== Bank Menu ======
1. Process new checking account requests
2. Print all successfully created accounts
3. Print all invalid records
4. Print log file
5. Quit and write accounts to output file
Enter choice: 
5
Accounts written to file. Exiting...



    In created_accounts.txt:
AccountID   First       Last        Email                        AvailBal     PresBal
30854101    Alice       Johnson     alice.johnson@school.edu         0.00      150.00
17838602    Bob         Smith       bob.smith@gmail.com              0.00      100.00
80304003    Jane        Doe         jane.doe@university.edu          0.00      150.00
98976904    Kyle        Green       kyle.green@gmail.com             0.00      100.00
18267005    Li          Wei         li.wei@college.edu               0.00      150.00
20509606    Paul        King        paul.king@gmail.com              0.00      100.00



    In invalid_accounts.txt:
12345 Carol Brown carol.brown@domain.com
123456789012 David Lee david.lee@domain.com
123456789A Eve Adams eve.adams@domain.com
1234567892 F@ith Miller faith.miller@domain.com
1234567893 George O'Neill george.oneill@school.edu
1234567894 Hannah White hannah@edu.org



    In log.txt:
Invalid record: 12345 Carol Brown carol.brown@domain.com
Invalid record: 123456789012 David Lee david.lee@domain.com
Invalid record: 123456789A Eve Adams eve.adams@domain.com
Invalid record: 1234567892 F@ith Miller faith.miller@domain.com
Invalid record: 1234567893 George O'Neill george.oneill@school.edu
Invalid record: 1234567894 Hannah White hannah@edu.org
*/
