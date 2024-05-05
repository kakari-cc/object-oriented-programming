// Comment out these two includes for the single file solution
// #include "Noble.h"
// #include "Warrior.h"

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Comment out this using namespace for the single file solution
// using namespace WarriorCraft;

// ----- ----- ----- //

class Noble;

class Warrior {
    
private:
    const string name;
    bool hired;
    double strength;
    Noble* hirer;
    
public:
    Warrior(const string&, double);
    friend ostream& operator<<(ostream&, const Warrior&);
    const string& get_name() const;
    double get_strength() const;
    bool isHired() const;
    void hire(Noble*);  // Being Hired
    void runaway();
    void fired();  // Being Fired
    void reduce_strength(double);  // After Winning a Battle
};

// ----- ----- ----- //

class Noble {
    
private:
    const string name;
    bool alive;
    vector<Warrior*> army;
    
public:
    Noble(const string&);
    friend ostream& operator<<(ostream&, const Noble&);
    const string& get_name() const;
    bool hire(Warrior&);
    bool fire(Warrior&);
    void runaway(Warrior*);
    double army_strength() const;
    void battle(Noble&);
};

// ----- ----- ----- //

int main() {
    Noble art("King Arthur");
    Noble lance("Lancelot du Lac");
    Noble jim("Jim");
    Noble linus("Linus Torvalds");
    Noble billie("Bill Gates");

    Warrior cheetah("Tarzan", 4);
    Warrior sky("Leia", 6);
    Warrior wizard("Merlin", 9);
    Warrior jaffa("Teal'c", 9);
    Warrior theGovernator("Conan", 12);
    Warrior nimoy("Spock", 15);
    Warrior lawless("Xena", 20);
    Warrior mrGreen("Hulk", 8);
    Warrior dylan("Hercules", 3);

    jim.hire(nimoy);
    lance.hire(theGovernator);
    art.hire(jaffa);
    art.hire(cheetah);
    art.hire(wizard);
    art.hire(sky);
    lance.hire(dylan);
    linus.hire(lawless);
    billie.hire(mrGreen);
    art.hire(nimoy);

    cout << "================ Initial Status ===============" << endl;
    cout << art << endl
         << lance << endl
         << jim << endl
         << linus << endl
         << billie << endl;
    cout << "===============================================\n\n";

    art.fire(cheetah);
    wizard.runaway();
    cout << endl << art << endl;

    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);

    cout << "\n================ Final Status ===============" << endl;
    cout << art << endl
         << lance << endl
         << jim << endl
         << linus << endl
         << billie << endl;

    // Tarzan and Merlin should be unemployed
    cout << "Tarzan's Hire Status: " << boolalpha
         << cheetah.isHired() << endl;
    cout << "Merlin's Hire Status: " << boolalpha
         << wizard.isHired() << endl;
    cout << "===============================================\n\n";
}

// ----- ----- ----- //

Warrior::Warrior(const string& name, double strength)
    : name(name)
    , strength(strength)
    , hired(false)
    , hirer(nullptr)
{}

ostream& operator<<(ostream& os, const Warrior& rhs) {
    os << rhs.name << ": " << rhs.strength;
    return os;
}

const string& Warrior::get_name() const {
    return name;
}

double Warrior::get_strength() const {
    return strength;
}

bool Warrior::isHired() const {
    return hired;
}

void Warrior::hire(Noble* noble) {  // Being Hired
    hired = true;
    hirer = noble;
}

void Warrior::runaway() {
    hired = false;
    hirer->runaway(this);
    cout << name << " flees in terror, abandoning his lord, " << hirer->get_name() << endl;
    hirer = nullptr;
}

void Warrior::fired() {  // Being Fired
    hired = false;
    hirer = nullptr;
}

void Warrior::reduce_strength(double ratio) {  // After Winning a Battle
    strength *= (1 - ratio);
}

// ----- ----- ----- //

Noble::Noble(const string& name)
    : name(name)
    , alive(true)
{}

ostream& operator<<(ostream& os, const Noble& rhs) {
    os << rhs.name << " has an army of " << rhs.army.size();
    for(const Warrior *i : rhs.army)
        os << "\n\t" << *i;
    return os;
}

const string& Noble::get_name() const {
    return name;
}

bool Noble::hire(Warrior& warrior) {
    if(!alive) {
        cerr << "(!) Failed to Hire:  Noble " << name << " Died" << endl;
        return false;
    }
    if(warrior.isHired()) {
        cerr << "(!) Failed to Hire:  Warrior \"" << warrior.get_name() << "\" Already Employed" << endl;
        return false;
    }
    warrior.hire(this);
    army.push_back(&warrior);
    return true;
}

bool Noble::fire(Warrior& warrior) {
    if(!alive) {
        cerr << "(!) Failed to Fire:  Noble " << name << " Died" << endl;
        return false;
    }
    bool found = false;
    for(size_t i = 0; i < army.size(); i++) {  // Maintain original ordering
        if(!found && army[i] == &warrior)
            found = true;
        if(found && i < army.size() - 1) // Need Attention
            army[i] = army[i + 1];
    }
    if(!found) {
        cerr << "(!) Failed to Fire:  Warrior \"" << warrior.get_name() << "\" Not Employed" << endl;
        return false;
    }
    army.pop_back();  // Pop the warrior from vector.
    warrior.fired();  // Update employment status of warrior.
    cout << "You don't work for me anymore " << warrior.get_name() << "! -- " << name << "." << endl;
    return true;
}

void Noble::runaway(Warrior* warrior) {
    bool found = false;
    for(size_t i = 0; i < army.size(); i++) {  // Maintain original ordering
        if(!found && army[i] == warrior)
            found = true;
        if(found && i < army.size() - 1) // Need Attention
            army[i] = army[i + 1];
    }
    army.pop_back();
}

double Noble::army_strength() const {
    double sum = 0;
    for(const Warrior *i : army)
        sum += i->get_strength();
    return sum;
}

void Noble::battle(Noble& other) {
    cout << name << " battles " << other.name << endl;
    if(!alive) {
        if(!other.alive) {  // Both dead.
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
            return;
        }
        else {  //  `other` dead.
            cout << "He's dead, " << other.name << endl;
            return;
        }
    }
    if(!other.alive) {  // `*this` dead.
        cout << "He's dead, " << name << endl;
        return;
    }
    // Everyone alive, proceeds.
    // If both lose...
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
