#include "Noble.h"
#include "Warrior.h"

#include <iostream>
#include <vector>
#include <string>

using namespace std;

namespace WarriorCraft {

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
        hirer->runaway(this);  // Notify Coresponding Noble
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

}
