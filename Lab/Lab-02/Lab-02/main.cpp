//
// rec02.cpp
//
// Created by Mingxuan Zhang
// Sort Hydrocarbs
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

//const size_t NOT_FOUND = 0 - 1;

using namespace std;

struct hydrocarb {
    vector<string> names;
    int carbon_count;
    int hydrogen_count;
};

void open_file(ifstream &fin);

void fill_vector(vector<hydrocarb> &hydrocarbs, ifstream &fin);

void fill_info(vector<hydrocarb> &hydrocarbs, const string &new_name, int carbon_count, int hydrogen_count);

size_t find_isochemical(const vector<hydrocarb> &hydrocarbs, int carbon_count, int hydrogen_count);

void sort_vector(vector<hydrocarb> &hydrocarbs);

void display_formula(const hydrocarb& hydrocarb);

void display_vector(const vector<hydrocarb> &hydrocarbs);

int main() {
    ifstream fin;
    vector<hydrocarb> hydrocarbs;
    open_file(fin);
    fill_vector(hydrocarbs, fin);
    sort_vector(hydrocarbs);
    display_vector(hydrocarbs);
}

void open_file(ifstream &fin) {
    string filename;
    do {
        fin.clear();
        cout << "Input File Name... ";
        cin >> filename;
        fin.open(filename);
    }
    while(!fin);
}

void fill_vector(vector<hydrocarb> &hydrocarbs, ifstream &fin) {
    string new_name;
    char dispose;
    int carbon_count, hydrogen_count;
    while(fin >> new_name >> dispose >> carbon_count >> dispose >> hydrogen_count) {
        fill_info(hydrocarbs, new_name, carbon_count, hydrogen_count);
    }
}

void fill_info(vector<hydrocarb> &hydrocarbs, const string &new_name, int carbon_count, int hydrogen_count) {
    size_t found = find_isochemical(hydrocarbs, carbon_count, hydrogen_count);
    if(found != hydrocarbs.size()) {
        hydrocarbs[found].names.push_back(new_name);
    }
    else {
        hydrocarb new_hydrocarb;
        new_hydrocarb.names.push_back(new_name);
        new_hydrocarb.carbon_count = carbon_count;
        new_hydrocarb.hydrogen_count = hydrogen_count;
        hydrocarbs.push_back(new_hydrocarb);
    }
}

size_t find_isochemical(const vector<hydrocarb> &hydrocarbs, int carbon_count, int hydrogen_count) {
    for(size_t i = 0; i < hydrocarbs.size(); i++)
        if(hydrocarbs[i].carbon_count == carbon_count && hydrocarbs[i].hydrogen_count == hydrogen_count)
            return i;
    return hydrocarbs.size();
}

void sort_vector(vector<hydrocarb> &hydrocarbs) {
    for(size_t i = 0; i < hydrocarbs.size() - 1; i++) {
        for(size_t j = i; j < hydrocarbs.size() - 1; j++) {
            if(hydrocarbs[j].carbon_count > hydrocarbs[j+1].carbon_count)
                swap(hydrocarbs[j], hydrocarbs[j+1]);
            else if(hydrocarbs[j].carbon_count == hydrocarbs[j+1].carbon_count &&
                    hydrocarbs[j].hydrogen_count > hydrocarbs[j+1].hydrogen_count)
                swap(hydrocarbs[j], hydrocarbs[j+1]);
        }
    }
}

void display_formula(const hydrocarb& chemical) {
    cout << "C" << chemical.carbon_count << "H" << chemical.hydrogen_count;
    for(const string& i : chemical.names)
        cout << " " << i;
    cout << endl;
}

void display_vector(const vector<hydrocarb> &hydrocarbs) {
    for(const hydrocarb& i : hydrocarbs) {
        display_formula(i);
    }
}
