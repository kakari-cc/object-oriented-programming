#include "Noble.h"
#include "Protector.h"

#include <iostream>
#include <vector>
#include <string>

using namespace std;

namespace WarriorCraft {

    // ----- Noble -----

    Noble::Noble(const string& name)
        : name(name)
        , alive(true)
    {}

    bool Noble::is_alive() const {
        return alive;
    }

    const string& Noble::get_name() const {
        return name;
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
        defend();
        other.defend();
        // If both lose...
        if(battle_strength() == other.battle_strength()) {
            cout << "Mutual Annihilation: " << name << " and " << other.name << " die at each other's hands" << endl;
            lost();
            other.lost();
            return;
        }
        // In case there are winners and losers...
        Noble *winner, *loser;
        if(battle_strength() > other.battle_strength()) {
            winner = this;
            loser = &other;
        }
        else {
            winner = &other;
            loser = this;
        }
        cout << winner->name << " defeats " << loser->name << endl;
        loser->lost();
        double penalty_ratio = loser->battle_strength() / winner->battle_strength();
        winner->won(penalty_ratio);
        
    }

    void Noble::lost() {
        alive = false;
    }

    // ----- Lord -----

    Lord::Lord(const string& name)
        : Noble::Noble(name)
    {}

    bool Lord::hires(Protector& protector) {
        if(!is_alive()) {
            cerr << "(!) Failed to Hire:  Lord " << get_name() << " Died" << endl;
            return false;
        }
        if(protector.is_hired()) {
            cerr << "(!) Failed to Hire:  Protector \"" << protector.get_name() << "\" Already Employed" << endl;
            return false;
        }
        protector.hire_process(this);
        army.push_back(&protector);
        return true;
    }

    bool Lord::fires(Protector& protector) {
        if(!is_alive()) {
            cerr << "(!) Failed to Fire:  Lord " << get_name() << " Died" << endl;
            return false;
        }
        bool found = false;
        for(size_t i = 0; i < army.size(); i++) {  // Maintain original ordering
            if(!found && army[i] == &protector)
                found = true;
            if(found && i < army.size() - 1) // Need Attention
                army[i] = army[i + 1];
        }
        if(!found) {
            cerr << "(!) Failed to Fire:  Protector \"" << protector.get_name() << "\" Not Employed" << endl;
            return false;
        }
        army.pop_back();  // Pop the protector from vector.
        protector.fire_process();  // Update employment status of protector.
        cout << "You don't work for me anymore " << protector.get_name() << "! -- " << get_name() << "." << endl;
        return true;
    }

    void Lord::notify_leave(Protector* protector) {
        bool found = false;
        for(size_t i = 0; i < army.size(); i++) {  // Maintain original ordering
            if(!found && army[i] == protector)
                found = true;
            if(found && i < army.size() - 1)
                army[i] = army[i + 1];
        }
        army.pop_back();
    }

    double Lord::battle_strength() const {
        double sum = 0;
        for(const Protector *i : army) {
            sum += i->get_strength();
            i->defends();
        }
        return sum;
    }

    void Lord::defend() const {
        for(const Protector *i : army) {
            i->defends();
        }
    }

    void Lord::lost() {
        Noble::lost();
        for(Protector* i : army)
            i->reduce_strength(1);
    }

    void Lord::won(double ratio) {
        for(Protector* i : army)
            i->reduce_strength(ratio);
    }

    ostream& operator<<(ostream& os, const Lord& rhs) {
        os << rhs.get_name() << " has an army of " << rhs.army.size();
        for(const Protector *i : rhs.army)
            os << "\n\t" << *i;
        return os;
    }

    // ----- PersonWithStrengthToFight -----

    PersonWithStrengthToFight::PersonWithStrengthToFight(const string& name, double strength)
        : Noble::Noble(name)
        , strength(strength)
    {}

    double PersonWithStrengthToFight::battle_strength() const {
        return strength;
    }

    void PersonWithStrengthToFight::defend() const {
        cout << "Ugh!" << endl;
    }

    void PersonWithStrengthToFight::won(double ratio) {
        strength *= (1 - ratio);
    }

    ostream& operator<<(ostream& os, const PersonWithStrengthToFight& rhs) {
        os << rhs.get_name() << " has strength of " << rhs.strength;
        return os;
    }

}
