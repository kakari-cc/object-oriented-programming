//
//  hw04.cpp
//  Nobles and Warriors
//
//  Created by Mingxuan Zhang.
//

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Warrior {
    
private:
    const string name;
    bool hired;
    double strength;
    
public:
    Warrior(string name, double strength)
        : name(name)
        , strength(strength)
    { hired=false; }
    
    friend ostream& operator<<(ostream& os, const Warrior& rhs) {
        os << rhs.name << ": " << rhs.strength;
        return os;
    }
    
    string get_name() const {
        return name;
    }
    
    double get_strength() const {
        return strength;
    }
    
    bool is_hired() {
        // This function is pulled only when a noble is trying to hire me...
        if(!hired) {  // Not hired? Will take the job.
            hired = true;
            return false;
        }
        return hired;  // Already working for someone else.
    }
    
    void fire() {  // Being Fired
        hired = false;
    }
    
    void reduce_strength(double ratio) {
        strength *= (1 - ratio);
    }
    
};

class Noble {
    
private:
    const string name;
    bool alive;
    vector<Warrior*> army;
    double army_strength;
    
public:
    Noble(string name)
        : name(name)
    { alive = true; }
    
    friend ostream& operator<<(ostream& os, const Noble& rhs) {
        os << rhs.name << " has an army of " << rhs.army.size();
        for(const Warrior *i : rhs.army)
            os << "\n\t" << *i;
        return os;
    }
    
    bool hire(Warrior& warrior) {
        if(!alive) {
            cerr << "(!) Failed to Hire:  Noble Died." << endl;
            return false;
        }
        if(warrior.is_hired()) {
            cerr << "(!) Failed to Hire:  Already Employed." << endl;
            return false;
        }
        army.push_back(&warrior);
        return true;
    }
    
    bool fire(Warrior& warrior) {
        if(!alive) {
            cerr << "(!) Failed to Fire:  Noble Died." << endl;
            return false;
        }
        bool found = false;
        for(size_t i = 0; i < army.size(); i++) {  // Maintain original ordering
            if(!found && army[i] == &warrior)
                found = true;
            if(found && i != army.size() - 1)
                swap(army[i], army[i + 1]);
        }
        if(!found) {
            cerr << "(!) Failed to Fire:  Not Employed." << endl;
            return false;
        }
        army.pop_back();  // Pop the warrior from vector.
        warrior.fire();  // Update employment status of warrior.
        cout << "You don't work for me anymore " << warrior.get_name() << "! -- " << name << "." << endl;
        return true;
    }
    
    double update_army_strength() {
        army_strength = 0;
        for(const Warrior *i : army)
            army_strength += i->get_strength();
        return army_strength;
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
        if(update_army_strength() == other.update_army_strength()) {
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
        if(army_strength > other.army_strength) {
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
            i->reduce_strength(loser->army_strength / winner->army_strength);
        for(Warrior *i : loser->army)
            i->reduce_strength(1);
    }
    
};

int main() {
    // Test code...
    return 0;
}
