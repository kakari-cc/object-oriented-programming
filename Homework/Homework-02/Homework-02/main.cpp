//
// hw02.cpp
//
// Created by Mingxuan Zhang
// Warriors
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Warrior {
    string name;
    int strength;
};

bool open_file(ifstream&, string);
int warrior_query(const vector<Warrior>&, const string name);
void add_warrior(ifstream&, vector<Warrior>&);
bool check_alive(vector<Warrior>&, int, int);
void battle(ifstream&, vector<Warrior>&);
void display_status(ifstream&, const vector<Warrior>&);

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
            display_status(fin, warriors);
        else
            cerr << "Bad Input" << endl;
    }
    return 0;
}

bool open_file(ifstream& fin, string fname) {
    fin.open(fname);
    if(!fin) {
        cerr << "Failure to Open File \"" << fname << "\"" << endl;
        return false;
    }
    return true;  // Successfully Opened
}

int warrior_query(const vector<Warrior>& warriors, const string name) {
    // Find Index in Vector Using Name
    for(int i = 0; i < warriors.size(); i++)
        if(warriors[i].name == name)
            return i;  // Return Index
    return -1;  // Not Found
}

void add_warrior(ifstream& fin, vector<Warrior>& warriors) {
    Warrior new_warrior;
    fin >> new_warrior.name >> new_warrior.strength;
    if(warrior_query(warriors, new_warrior.name) != -1) { // Already Exists
        cerr << "Warrior \"" << new_warrior.name << "\" Already Exists" << endl;
        return;
    }
    warriors.push_back(new_warrior);
}

bool check_alive(vector<Warrior>& warriors, int p1, int p2) {
    if(!warriors[p1].strength)
        if(!warriors[p2].strength) {  // P1 & P2 Died
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
            return false;
        }
        else {  // Only P1 Died
            cout << "He's dead, " << warriors[p2].name << endl;
            return false;
        }
    else
        if(!warriors[p2].strength) {  // Only P2 Died
            cout << "He's dead, " << warriors[p1].name << endl;
            return false;
        }
    // Both Warriors Alive, Battle Proceeds
    return true;
}

void battle(ifstream& fin, vector<Warrior>& warriors) {
    string p1_name, p2_name;
    fin >> p1_name >> p2_name;
    cout << p1_name << " battles " << p2_name << endl;
    int p1 = warrior_query(warriors, p1_name);
    int p2 = warrior_query(warriors, p2_name);
    if(p1 == -1 || p2 == -1) {
        cerr << "At Least One Warrior(s) Are Undefined" << endl;
        return;
    }
    if(check_alive(warriors, p1, p2)) {
        if(warriors[p1].strength == warriors[p2].strength) {  // Both Lose
            warriors[p1].strength = warriors[p2].strength = 0;
            cout << "Mutual Annihilation: Arthur and Lancelot die at each other's hands" << endl;
        }
        else if(warriors[p1].strength > warriors[p2].strength) {  // P1 Wins
            warriors[p1].strength -= warriors[p2].strength;
            warriors[p2].strength = 0;
            cout << p1_name << " defeats " << p2_name << endl;
        }
        else {  // P2 Wins
            warriors[p2].strength -= warriors[p1].strength;
            warriors[p1].strength = 0;
            cout << p2_name << " defeats " << p1_name << endl;
        }
    }
    cout << endl;
}

void display_status(ifstream& fin, const vector<Warrior>& warriors) {
    cout << "There are: " << warriors.size() << " warriors" << endl;
    for(Warrior i : warriors)
        cout << "Warrior: " << i.name << ", strength: " << i.strength << "\n";
    cout << endl;
}
