//
//  hw05.cpp
//  Nobles and Warriors
//
//  Created by Mingxuan Zhang.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// ----- ----- ----- //

class Warrior {
    
private:
    const string name;
    bool hired;
    double strength;
    
public:
    Warrior(const string& name, double strength)
        : name(name)
        , strength(strength)
        , hired(false)
    {}
    
    friend ostream& operator<<(ostream& os, const Warrior& rhs) {
        os << rhs.name << ": " << rhs.strength;
        return os;
    }
    
    const string& get_name() const {
        return name;
    }
    
    double get_strength() const {
        return strength;
    }
    
    bool is_hired() const {
        return hired;
    }
    
    void hire() {  // Being Hired
        hired = true;
    }
    
    void fire() {  // Being Fired
        hired = false;
    }
    
    void reduce_strength(double ratio) {  // After Winning a Battle
        strength *= (1 - ratio);
    }
    
};

// ----- ----- ----- //

class Noble {
    
private:
    const string name;
    bool alive;
    vector<Warrior*> army;
    
public:
    Noble(const string& name)
        : name(name)
        , alive(true)
    {}
    
    friend ostream& operator<<(ostream& os, const Noble& rhs) {
        os << rhs.name << " has an army of " << rhs.army.size();
        for(const Warrior *i : rhs.army)
            os << "\n\t" << *i;
        return os;
    }
    
    const string& get_name() const {
        return name;
    }
    
    bool hire(Warrior* warrior) {
        if(!alive) {
            cerr << "(!) Failed to Hire:  Noble " << name << " Died" << endl;
            return false;
        }
        if(warrior->is_hired()) {
            cerr << "(!) Failed to Hire:  Warrior \"" << warrior->get_name() << "\" Already Employed" << endl;
            return false;
        }
        warrior->hire();
        army.push_back(warrior);
        return true;
    }
    
    bool fire(Warrior* warrior) {
        if(!alive) {
            cerr << "(!) Failed to Fire:  Noble " << name << " Died" << endl;
            return false;
        }
        bool found = false;
        for(size_t i = 0; i < army.size(); i++) {  // Maintain original ordering
            if(!found && army[i] == warrior)
                found = true;
            if(found && i != army.size() - 1)
                army[i] = army[i + 1];
        }
        if(!found) {
            cerr << "(!) Failed to Fire:  Warrior \"" << warrior->get_name() << "\" Not Employed" << endl;
            return false;
        }
        army.pop_back();  // Pop the warrior from vector.
        warrior->fire();  // Update employment status of warrior.
        cout << "You don't work for me anymore " << warrior->get_name() << "! -- " << name << "." << endl;
        return true;
    }
    
    double army_strength() const {
        double sum = 0;
        for(const Warrior *i : army)
            sum += i->get_strength();
        return sum;
    }
    
    void battle(Noble& other) {
        cout << name << " battles " << other.name << endl;
        if(!alive) {
            if(!other.alive) {
                cout << "Oh, NO! They're both dead! Yuck!" << endl;
                return;
            }
            else {
                cout << "He's dead, " << other.name << endl;
                return;
            }
        }
        if(!other.alive) {
            cout << "He's dead, " << name << endl;
            return;
        }
        // Everyone alive, proceeds.
        if(army_strength() == other.army_strength()) {
            cout << "Mutual Annihilation: " << name << " and " << other.name << " die at each other's hands" << endl;
            alive = other.alive = false;
            for(Warrior *i : army)
                i->reduce_strength(1);  // Set warrior strength to 0.
            for(Warrior *i : other.army)
                i->reduce_strength(1);
            return;
        }
        // In case there are winners and losers...
        Noble *winner, *loser;
        if(army_strength() > other.army_strength()) {
            winner = this;
            loser = &other;
        }
        else {
            winner = &other;
            loser = this;
        }
        cout << winner->name << " defeats " << loser->name << endl;
        loser->alive = false;
        for(Warrior *i : winner->army)
            i->reduce_strength(loser->army_strength() / winner->army_strength());
        for(Warrior *i : loser->army)
            i->reduce_strength(1);
    }
    
};

// ----- ----- ----- //

bool open_file(ifstream& fin, const string& fname);

void add_noble(vector<Noble*>&, const string&);

void add_warrior(vector<Warrior*>&, const string&, int);

Noble* noble_query(const vector<Noble*>&, const string&);

Warrior* warrior_query(const vector<Warrior*>&, const string&);

bool hire(const vector<Noble*>&, const vector<Warrior*>&, const string&, const string&);

bool fire(const vector<Noble*>&, const vector<Warrior*>&, const string&, const string&);

void battle(const vector<Noble*>&, const string&, const string&);

void display_status(const vector<Noble*>&, const vector<Warrior*>&);

void clear(vector<Noble*>&, vector<Warrior*>&);

// ----- ----- ----- //

int main() {
    ifstream fin;
    vector<Warrior*> warriors;
    vector<Noble*> nobles;
    if(!open_file(fin, "nobleWarriors.txt"))
        return -1;
    string command, noble_name, warrior_name, opponent;
    int strength;
    while(fin >> command) {  // Reading First Word in Each Line
        if(command == "Noble") {
            fin >> noble_name;
            add_noble(nobles, noble_name);
        }
        else if(command == "Warrior") {
            fin >> warrior_name >> strength;
            add_warrior(warriors, warrior_name, strength);
        }
        else if(command == "Hire") {
            fin >> noble_name >> warrior_name;
            hire(nobles, warriors, noble_name, warrior_name);
        }
        else if(command == "Fire") {
            fin >> noble_name >> warrior_name;
            fire(nobles, warriors, noble_name, warrior_name);
        }
        else if(command == "Battle") {
            fin >> noble_name >> opponent;
            battle(nobles, noble_name, opponent);
        }
        else if(command == "Status") {
            display_status(nobles, warriors);
        }
        else if(command == "Clear") {
            clear(nobles, warriors);
        }
        else {
            cerr << "(!) Format Error:  Bad Input \"" << command << "\"" << endl;
            return -1;
        }
    }
    return 0;
}

// ----- ----- ----- //

bool open_file(ifstream& fin, const string& fname) {
    fin.open(fname);
    if(!fin) {
        cerr << "(!) Failed to Open \"" << fname << "\"" << endl;
        return false;
    }
    return true;  // Successfully Opened
}

void add_noble(vector<Noble*>& nobles, const string& name) {
    if(noble_query(nobles, name)) {
        cerr << "(!) Failed to Add Noble:  \"" << name << "\" Already Exists" << endl;
        return;
    }
    nobles.push_back(new Noble(name));
}

void add_warrior(vector<Warrior*>& warriors, const string& name, int strength) {
    if(warrior_query(warriors, name)) {
        cerr << "(!) Failed to Add Warrior:  \"" << name << "\" Already Exists" << endl;
        return;
    }
    warriors.push_back(new Warrior(name, strength));
}

Noble* noble_query(const vector<Noble*>& nobles, const string& name) {
    for(Noble* i : nobles) {
        if(i->get_name() == name)
            return i;
    }
    return nullptr;  // Not Found
}

Warrior* warrior_query(const vector<Warrior*>& warriors, const string& name) {
    for(Warrior* i : warriors) {
        if(i->get_name() == name)
            return i;
    }
    return nullptr;  // Not Found
}

bool hire(const vector<Noble*>& nobles, const vector<Warrior*>& warriors, const string& noble_name, const string& warrior_name) {
    Noble* noble = noble_query(nobles, noble_name);
    if(noble == nullptr) {
        cerr << "(!) Failed to Hire:  Noble \"" << noble_name << "\" Not Found" << endl;
        return false;
    }
    Warrior* warrior = warrior_query(warriors, warrior_name);
    if(warrior == nullptr) {
        cerr << "(!) Failed to Hire:  Warrior \"" << warrior_name << "\" Not Found" << endl;
        return false;
    }
    return noble->hire(warrior);
}

bool fire(const vector<Noble*>& nobles, const vector<Warrior*>& warriors, const string& noble_name, const string& warrior_name) {
    Noble* noble = noble_query(nobles, noble_name);
    if(noble == nullptr) {
        cerr << "(!) Failed to Fire:  Noble \"" << noble_name << "\" Not Found" << endl;
        return false;
    }
    Warrior* warrior = warrior_query(warriors, warrior_name);
    if(warrior == nullptr) {
        cerr << "(!) Failed to Fire:  Warrior \"" << warrior_name << "\" Not Found" << endl;
        return false;
    }
    return noble->fire(warrior);
}

void battle(const vector<Noble*>& nobles, const string& noble_1_name, const string& noble_2_name) {
    Noble* noble_1 = noble_query(nobles, noble_1_name);
    if(noble_1 == nullptr) {
        cerr << "(!) Attempt to Battle Failed:  Noble \"" << noble_1_name << "\" Not Found" << endl;
        return;
    }
    Noble* noble_2 = noble_query(nobles, noble_2_name);
    if(noble_2 == nullptr) {
        cerr << "(!) Attempt to Battle Failed:  Noble \"" << noble_2_name << "\" Not Found" << endl;
        return;
    }
    noble_1->battle(*noble_2);
}

void display_status(const vector<Noble*>& nobles, const vector<Warrior*>& warriors) {
    cout << "---Status---" << endl;
    cout << "Nobles:" << endl;
    if(nobles.size()) {
        for(const Noble* i : nobles) {
            cout << *i << endl;
        }
    }
    else {
        cout << "NONE" << endl;
    }
    cout << endl << "Unemployed Warriors:" << endl;
    bool unemployment = true;
    for(const Warrior* i : warriors) {
        if(!i->is_hired()) {
            cout << "\t" << *i << endl;
            unemployment = false;
        }
    }
    if(unemployment) {
        cout << "NONE" << endl;
    }
    cout << "----End-----" << endl;
}

void clear(vector<Noble*>& nobles, vector<Warrior*>& warriors) {
    for(Noble* i : nobles)
        delete i;
    nobles.clear();
    for(Warrior* i : warriors)
        delete i;
    warriors.clear();
}
