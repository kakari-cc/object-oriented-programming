#include "Noble.h"
#include "Protector.h"

#include <iostream>
#include <vector>
#include <string>

using namespace std;

namespace WarriorCraft {

    // ----- Protector -----

    Protector::Protector(const string& name, double strength)
        : name(name)
        , strength(strength)
        , hirer(nullptr)
    {}

    string Protector::get_name() const { return name; }

    double Protector::get_strength() const { return strength; }

    bool Protector::is_hired() const { return hirer!=nullptr; }

    void Protector::hire_process(Lord* lord) {
        hirer = lord;
    }

    void Protector::runaway() {
        hirer->notify_leave(this);  // Notify Coresponding Noble
        cout << name << " flees in terror, abandoning his lord, " << hirer->get_name() << endl;
        hirer = nullptr;
    }

    void Protector::fire_process() {
        hirer = nullptr;
    }

    void Protector::reduce_strength(double ratio) {
        strength *= (1 - ratio);
    }

    ostream& operator<<(ostream& os, const Protector& rhs) {
        os << rhs.name << ": " << rhs.strength;
        return os;
    }

    // ----- Wizard -----

    void Wizard::defends() const {
        cout << "POOF" << endl;
    }

    // ----- Warrior -----

    void Warrior::defends() const {
        cout << get_name() << " says: Take that in the name of my lord, " << get_hirer()->get_name() << endl;
    }

    // ----- Archer -----

    void Archer::defends() const {
        cout << "TWANG! ";
        Warrior::defends();
    }

    // ----- Swordsman -----

    void Swordsman::defends() const {
        cout << "CLANG! ";
        Warrior::defends();
    }

}

