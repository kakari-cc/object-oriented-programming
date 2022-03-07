//
// rec03.cpp
//
// Created by Mingxuan Zhang
// Bank Accounts
//

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#define DEPOSIT true
#define WITHDRAW false

using namespace std;

// Task 1
// Define an Account struct
struct Account {
    string name;
    long number;
};

// Task 2
// Define an Account class (use a different name than in Task 1)
class GoodAccount {
private:
    string name;
    long number;
public:
    GoodAccount(string name, long number)
        : name(name)
        , number(number)
    {}
    friend ostream& operator<<(ostream&, const GoodAccount&);
    const string& get_name() const {return name;}
    long get_number() const {return number;}
};

// Task 3
// Define an Account (use a different name than in Task 1&2) and
// Transaction classes
class Transcation {
private:
    bool type;
    double amount;
public:
    Transcation(bool type, double amount)
        : type(type)
        , amount(amount)
    {}
    friend ostream& operator<<(ostream&, const Transcation&);
};

class BetterAccount {
private:
    string name;
    long number;
    vector<Transcation> transcations;
    double balance;
public:
    BetterAccount(string name, long number)
        : name(name)
        , number(number)
    {balance = 0;}
    friend ostream& operator<<(ostream&, const BetterAccount&);
    const string& get_name() const {return name;}
    long get_number() const {return number;}
    void deposit(double amount) {
        balance += amount;
        transcations.push_back(Transcation(DEPOSIT, amount));
    }
    void withdrawal(double amount) {
        if(amount > balance) {
            cerr << "Balance too Low ($" << balance << ") to Withdraw $" << amount << "." << endl;
            return;
        }
        balance -= amount;
        transcations.push_back(Transcation(WITHDRAW, amount));
    }
};

// Task 4
// Define an Account with a nested public Transaction class
// (use different names than in the previous Tasks)
class BestAccount {
public:
    class NestedTranscation {
    private:
        bool type;
        double amount;
    public:
        NestedTranscation(bool type, double amount)
            : type(type)
            , amount(amount)
        {}
        friend ostream& operator<<(ostream&, const BestAccount::NestedTranscation&);
    };
private:
    string name;
    long number;
    vector<NestedTranscation> nested_transcations;
    double balance;
public:
    BestAccount(string name, long number)
        : name(name)
        , number(number)
    {balance = 0;}
    friend ostream& operator<<(ostream&, const BestAccount&);
    const string& get_name() const {return name;}
    long get_number() const {return number;}
    void deposit(double amount) {
        balance += amount;
        nested_transcations.push_back(NestedTranscation(DEPOSIT, amount));
    }
    void withdrawal(double amount) {
        if(amount > balance) {
            cerr << "Balance too Low ($" << balance << ") to Withdraw $" << amount << "." << endl;
            return;
        }
        balance -= amount;
        nested_transcations.push_back(NestedTranscation(WITHDRAW, amount));
    }
};

// Task 5
// Define an Account with a nested private Transaction class
// (use different names than in the previous Tasks)

void open_file(ifstream&, string);

void fill_vector_1a(ifstream&, vector<Account>&);

void fill_vector_1b(ifstream&, vector<Account>&);

void fill_vector_2a(ifstream&, vector<GoodAccount>&);

//ostream& operator<<(ostream&, const GoodAccount&);

void fill_vector_2d(ifstream&, vector<GoodAccount>&);

void fill_vector_2e(ifstream&, vector<GoodAccount>&);

void fill_vector_3(ifstream&, vector<BetterAccount>&);

size_t find_account(long, const vector<BetterAccount>&);

void fill_vector_4(ifstream&, vector<BestAccount>&);

size_t find_account(long, const vector<BestAccount>&);


int main() {
    //==================================
    // Task 1: account as struct
    //      1a
    cout << "Task1a:\n";
    vector<Account> accounts;
    ifstream fin;
    open_file(fin, "accounts.txt");
    fill_vector_1a(fin, accounts);
    fin.close();
    for(const Account& i : accounts) {
        cout << "\"" << i.name << "\" has account number " << i.number << endl;
    }

    //      1b
    cout << "Task1b:\n";
    cout << "Filling vector of struct objects, using {} initialization:\n";
    accounts.clear();
    open_file(fin, "accounts.txt");
    fill_vector_1b(fin, accounts);
    fin.close();
    for(const Account& i : accounts) {
        cout << "\"" << i.name << "\" has account number " << i.number << endl;
    }

    //==================================
    // Task 2: account as class
    //      2a
    cout << "==============\n";
    cout << "\nTask2a:";
    cout << "\nFilling vector of class objects, using local class object:\n";
    vector<GoodAccount> good_accounts;
    open_file(fin, "accounts.txt");
    fill_vector_2a(fin, good_accounts);
    fin.close();
    for(const GoodAccount& i : good_accounts) {
        cout << "\"" << i.get_name() << "\" has account number " << i.get_number() << endl;
    }

    cout << "\nTask2b:\n";
    cout << "output using output operator with getters\n";
    for(const GoodAccount& i : good_accounts) {
        cout << i;
    }

    cout << "\nTask2c:\n";
    cout << "output using output operator as friend without getters\n";
    for(const GoodAccount& i : good_accounts) {
        cout << i;
    }

    cout << "\nTask2d:\n";
    cout << "Filling vector of class objects, using temporary class object:\n";
    good_accounts.clear();
    open_file(fin, "accounts.txt");
    fill_vector_2d(fin, good_accounts);
    fin.close();
    for(const GoodAccount& i : good_accounts) {
        cout << i;
    }
    
    cout << "\nTask2e:\n";
    cout << "Filling vector of class objects, using emplace_back:\n";
    good_accounts.clear();
    open_file(fin, "accounts.txt");
    fill_vector_2e(fin, good_accounts);
    fin.close();
    for(const GoodAccount& i : good_accounts) {
        cout << i;
    }
    
    //==================================
    cout << "==============\n";
    cout << "\nTask 3:\nAccounts and Transaction:\n";
    vector<BetterAccount> better_accounts;
    open_file(fin, "transactions.txt");
    fill_vector_3(fin, better_accounts);
    fin.close();
    for(const BetterAccount& i : better_accounts) {
        cout << i;
    }

    //==================================
    cout << "==============\n";
    cout << "\nTask 4:\nTransaction nested in public section of Account:\n";
    vector<BestAccount> best_accounts;
    open_file(fin, "transactions.txt");
    fill_vector_4(fin, best_accounts);
    fin.close();
    for(const BestAccount& i : best_accounts) {
        cout << i;
    }

    //==================================
    cout << "==============\n";
    cout << "\nTask 5:\nTransaction nested in private section of Account:\n";
    
}

void open_file(ifstream& fin, string fname) {
    fin.open(fname);
    while(!fin) {
        fin.clear();
        cout << "Failed to Open, Enter Another File Name... ";
        cin >> fname;
        fin.open(fname);
    }
}

void fill_vector_1a(ifstream& fin, vector<Account>& accounts) {
    string name;
    long number;
    while(fin >> name >> number) {
        Account new_account;
        new_account.name = name;
        new_account.number = number;
        accounts.push_back(new_account);
    }
}

void fill_vector_1b(ifstream& fin, vector<Account>& accounts) {
    string name;
    long number;
    while(fin >> name >> number) {
        Account new_account{name, number};
        accounts.push_back(new_account);
    }
}

void fill_vector_2a(ifstream& fin, vector<GoodAccount>& good_accounts) {
    string name;
    long number;
    while(fin >> name >> number) {
        GoodAccount new_good_account(name, number);
        good_accounts.push_back(new_good_account);
    }
}

//ostream& operator<<(ostream& os, cosnt GoodAccount& rhs) {
//    os << "\"" << rhs.get_name() << "\" has account number " << rhs.get_number() << endl;
//    return os;
//}

ostream& operator<<(ostream& os, const GoodAccount& rhs) {
    os << "\"" << rhs.name << "\" has account number " << rhs.number << endl;
    return os;
}

void fill_vector_2d(ifstream& fin, vector<GoodAccount>& good_accounts) {
    string name;
    long number;
    while(fin >> name >> number) {
        good_accounts.push_back(GoodAccount(name, number));
    }
}

void fill_vector_2e(ifstream& fin, vector<GoodAccount>& good_accounts) {
    string name;
    long number;
    while(fin >> name >> number) {
        good_accounts.emplace_back(name, number);
    }
}

ostream& operator<<(ostream& os, const Transcation& rhs) {
    if(rhs.type == DEPOSIT)
        os << "$" << rhs.amount << " deposited." << endl;
    else
        os << "$" << rhs.amount << " withdrawn." << endl;
    return os;
}

ostream& operator<<(ostream& os, const BetterAccount& rhs) {
    os << "\"" << rhs.name << "\" has account number " << rhs.number << endl;
    for(const Transcation& i : rhs.transcations)
        os << "\t" << i;
    return os;
}

void fill_vector_3(ifstream& fin, vector<BetterAccount>& better_accounts) {
    string cmd, name;
    long number;
    double amount;
    size_t index;
    while(fin >> cmd) {
        if(cmd == "Account") {
            fin >> name >> number;
            better_accounts.emplace_back(name, number);
        }
        else if(cmd == "Deposit") {
            fin >> number >> amount;
            index = find_account(number, better_accounts);
            if(index == better_accounts.size())
                cerr << "Account Number Queried Not Found" << endl;
            else
                better_accounts[index].deposit(amount);
        }
        else if(cmd == "Withdraw") {
            fin >> number >> amount;
            index = find_account(number, better_accounts);
            if(index == better_accounts.size())
                cerr << "Account Number Queried Not Found" << endl;
            else
                better_accounts[index].withdrawal(amount);
        }
        else cerr << "Bad Input!" << endl;
    }
}

size_t find_account(long number, const vector<BetterAccount>& better_accounts) {
    for(size_t i = 0; i < better_accounts.size(); i++)
        if(better_accounts[i].get_number() == number)
            return i;
    return better_accounts.size(); // Not Found
}

void fill_vector_4(ifstream& fin, vector<BestAccount>& best_accounts) {
    string cmd, name;
    long number;
    double amount;
    size_t index;
    while(fin >> cmd) {
        if(cmd == "Account") {
            fin >> name >> number;
            best_accounts.emplace_back(name, number);
        }
        else if(cmd == "Deposit") {
            fin >> number >> amount;
            index = find_account(number, best_accounts);
            if(index == best_accounts.size())
                cerr << "Account Number Queried Not Found" << endl;
            else
                best_accounts[index].deposit(amount);
        }
        else if(cmd == "Withdraw") {
            fin >> number >> amount;
            index = find_account(number, best_accounts);
            if(index == best_accounts.size())
                cerr << "Account Number Queried Not Found" << endl;
            else
                best_accounts[index].withdrawal(amount);
        }
        else cerr << "Bad Input!" << endl;
    }
}

size_t find_account(long number, const vector<BestAccount>& best_accounts) {
    for(size_t i = 0; i < best_accounts.size(); i++)
        if(best_accounts[i].get_number() == number)
            return i;
    return best_accounts.size(); // Not Found
}

ostream& operator<<(ostream& os, const BestAccount& rhs) {
    os << "\"" << rhs.name << "\" has account number " << rhs.number << endl;
    for(const BestAccount::NestedTranscation& i : rhs.nested_transcations)
        os << "\t" << i;
    return os;
}

ostream& operator<<(ostream& os, const BestAccount::NestedTranscation& rhs) {
    if(rhs.type == DEPOSIT)
        os << "$" << rhs.amount << " deposited." << endl;
    else
        os << "$" << rhs.amount << " withdrawn." << endl;
    return os;
}
