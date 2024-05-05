#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, const char * argv[]) {
    ifstream fin("encrypted.txt");
    int steps;
    fin >> steps;
    string line;
    getline(fin, line);
    vector<string> lines;
    while (fin.peek() != EOF) {
        // reading rows
        getline(fin, line);
        for (int i = 0; i < line.size(); i++) {
            // reading characters
            if (line[i] >= 'a' && line[i] <= 'z') {
                line[i] -= steps;
                if (line[i] < 'a')
                    line[i] += 26;
            }
        }
        lines.push_back(line);
    }
    fin.close();
    for (size_t i = lines.size(); i > 0; i--)
        cout << lines[i - 1] << endl;
    return 0;
}
