#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Warrior {
private:
    class Weapon { // Nested Class
    private:
        string name;
        int strength;
    public:
        Weapon(const string& name, int strength)
            : name(name)
            , strength(strength)
        {}
        const string& get_name() const { return name; }
        int get_strength() const { return strength; }
        void set_strength(int new_strength) { strength = new_strength; }
        friend ostream& operator<<(ostream& os, const Weapon& weapon) {
            os << "weapon: " << weapon.name << ", " << weapon.strength;
            return os;
        }
    };
    string name;
    Weapon weapon;
public:
    Warrior(const string& name, const string& weapon_name, int strength)
        : name(name)
        , weapon(weapon_name, strength)
    {}
    const string& get_name() const { return name; }
    const string& get_weapon() const { return weapon.get_name(); }
    int get_strength() const { return weapon.get_strength(); }
    void set_strength(int new_strength) { weapon.set_strength(new_strength); }
    bool alive() const { return get_strength() > 0; }
    void fight(Warrior& opponent) {
        if(!alive())
            if(!opponent.alive()) {  // P1 & P2 Died
                cout << "Oh, NO! They're both dead! Yuck!" << endl;
                return;
            }
            else {  // Only P1 Died
                cout << "He's dead, " << opponent.get_name() << endl;
                return;
            }
        else
            if(!opponent.alive()) {  // Only P2 Died
                cout << "He's dead, " << get_name() << endl;
                return;
            }
        // Both Warriors Alive, Battle Proceeds
        if(get_strength() == opponent.get_strength()) {  // Both Lose
            set_strength(0);
            opponent.set_strength(0);
            cout << "Mutual Annihilation: " << get_name() << " and " <<
                opponent.get_name() << " die at each other's hands" << endl;
        }
        else if(get_strength() > opponent.get_strength()) {  // P1 Wins
            set_strength(get_strength() - opponent.get_strength());
            opponent.set_strength(0);
            cout << get_name() << " defeats " << opponent.get_name() << endl;
        }
        else {  // P2 Wins
            opponent.set_strength(opponent.get_strength() - get_strength());
            set_strength(0);
            cout << opponent.get_name() << " defeats " << get_name() << endl;
        }
    }
    friend ostream& operator<<(ostream& os, const Warrior& warrior) {
        os << "Warrior: " << warrior.name << ", " << warrior.weapon << endl;
        return os;
    }
};

bool open_file(ifstream&, const string&);
size_t warrior_query(const vector<Warrior>&, const string&);
void add_warrior(ifstream&, vector<Warrior>&);
void battle(ifstream&, vector<Warrior>&);
void display_status(const vector<Warrior>&);

int main() {
    ifstream fin;
    vector<Warrior> warriors;
    if(!open_file(fin, "warriors.txt"))
        return -1;
    string command;
    while(fin >> command) {  // Reading First Word in Each Line
        if(command == "Warrior")
            add_warrior(fin, warriors);
        else if(command == "Battle")
            battle(fin, warriors);
        else if(command == "Status")
            display_status(warriors);
        else
            cerr << "Bad Input" << endl;
    }
    fin.close();
    return 0;
}

bool open_file(ifstream& fin, const string& fname) {
    fin.open(fname);
    if(!fin) {
        cerr << "Failure to Open File \"" << fname << "\"" << endl;
        return false;
    }
    return true;  // Successfully Opened
}

size_t warrior_query(const vector<Warrior>& warriors, const string& name) {
    // Find Index in Vector Using Name
    for(size_t i = 0; i < warriors.size(); i++)
        if(warriors[i].get_name() == name)
            return i;  // Return Index
    return warriors.size();  // Not Found
}

void add_warrior(ifstream& fin, vector<Warrior>& warriors) {
    string name, weapon;
    int strength;
    fin >> name >> weapon >> strength;
    if(warrior_query(warriors, name) != warriors.size()) {  // If Already Exists
        cerr << "Warrior \"" << name << "\" Already Exists" << endl;
        return;
    }
    warriors.push_back(Warrior(name, weapon, strength));
}

void battle(ifstream& fin, vector<Warrior>& warriors) {
    string p1_name, p2_name;
    fin >> p1_name >> p2_name;
    cout << p1_name << " battles " << p2_name << endl;
    size_t p1 = warrior_query(warriors, p1_name);
    size_t p2 = warrior_query(warriors, p2_name);
    if(p1 == warriors.size() || p2 == warriors.size()) {
        cerr << "At Least One Warrior(s) Are Undefined" << endl;
        return;
    }
    warriors[p1].fight(warriors[p2]);
    cout << endl;
}

void display_status(const vector<Warrior>& warriors) {
    cout << "There are: " << warriors.size() << " warriors" << endl;
    for(const Warrior& i : warriors)
        cout << i;
    cout << endl;
}
