#include "Noble.h"
#include "Warrior.h"

#include <iostream>
#include <vector>
#include <string>

using namespace std;

namespace WarriorCraft {

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

}
