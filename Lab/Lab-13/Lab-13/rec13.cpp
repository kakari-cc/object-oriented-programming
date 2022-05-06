//
//  rec13.cpp
//  STL
//
//  Created by Mingxuan Zhang on 2022/04/29.
//

#include <iostream>
#include <fstream>
#include <vector>      // task 1
#include <list>        // task 2
#include <algorithm>   // task 3
#include <string>      // task 21
#include <set>         // task 22
#include <map>         // task 23

using namespace std;

void task_9(const vector<int>& vec) {
    // for(vector<int>::iterator it = vec.begin(); it != vec.end(); it++) cout << *it << " ";
    for(vector<int>::const_iterator it = vec.begin(); it != vec.end(); it++) cout << *it << " ";
}

void task_10(const list<int>& lst) {
    for(int i : lst) cout << i << " ";
}

void task_11(const list<int>& lst) {
    for(auto it = lst.begin(); it != lst.end(); ++ ++it) { cout << *it << " "; }
}

list<int>::const_iterator task_12(const list<int>& lst, int target) {
    for(list<int>::const_iterator it = lst.begin(); it != lst.end(); it++) if(*it == target) return it;
    return lst.end();
}

auto task_13(const list<int>& lst, int target) {
    for(auto it = lst.begin(); it != lst.end(); it++) if(*it == target) return it;
    return lst.end();
}

bool is_even(int x) { return !(x % 2); }

bool is_9999(int x) { return x == 9999; }

class Task_16 {
public:
    bool operator()(int x) { return !(x % 2); }  // is_even
};

//vector<int>::iterator ourFind(vector<int>::iterator begin, vector<int>::iterator end, int target) {  // Task 19
//    cout << "Calling Function" << endl;
//    for(; begin != end; begin++)
//        if(*begin == target) return begin;
//    return end;
//}

template <class ourIterator, class ourTarget>

ourIterator ourFind(ourIterator begin, ourIterator end, const ourTarget& target) {  // Task 20
    cout << "Calling Function Template" << endl;
    for(; begin != end; begin++)
        if(*begin == target) return begin;
    return end;
}

int main() {
    // 1. Create a vector with some values and display using ranged for
    cout << "Task 1:\n";
    vector<int> vec;
    for(int i = 8; i > 0; i--) vec.push_back(i);
    for(int i : vec) cout << i << " ";
    cout << "\n=======\n";

    // 2. Initalize a list as a copy of values from the vector
    cout << "Task 2:\n";
    list<int> lst(vec.begin(), vec.end());
    for(int i : lst) cout << i << " ";
    cout << "\n=======\n";

    // 3. Sort the original vector.  Display both the vector and the list
    cout << "Task 3:\n";
    sort(vec.begin(), vec.end());
    for(int i : vec) cout << i << " ";
    cout << endl;
    for(int i : lst) cout << i << " ";
    cout << "\n=======\n";

    // 4. print every other element of the vector. ASSUMING the length is odd.
    cout << "Task 4:\n";
    for(size_t i = 0; i < vec.size(); i += 2) cout << vec[i] << " ";
    cout << "\n=======\n";

    // 5. Attempt to print every other element of the list using the
    //    same technique.
    cout << "Task 5:\n";
    // for(size_t i = 0; i < lst.size(); i += 2) cout << lst[i] << " ";
    cout << "\n=======\n";

    //
    // Iterators
    //

    // 6. Repeat task 4 using iterators.  Do not use auto;
    cout << "Task 6:\n";
    for(vector<int>::iterator it = vec.begin(); it != vec.end(); it += 2) cout << *it << " ";
    cout << "\n=======\n";

    // 7. Repeat the previous task using the list.  Again, do not use auto.
    //    Note that you cannot use the same simple mechanism to bump
    //    the iterator as in task 6.
    cout << "Task 7:\n";
    for(list<int>::iterator it = lst.begin(); it != lst.end(); ++ ++it) { cout << *it << " "; }
    cout << "\n=======\n";

    // 8. Sorting a list
    cout << "Task 8:\n";
    lst.sort();
    for(int i : lst) cout << i << " ";
    cout << "\n=======\n";

    // 9. Calling the function to print the list
    cout << "Task 9:\n";
    task_9(vec);
    cout << "\n=======\n";

    // 10. Calling the function that prints the list, using ranged-for
    cout << "Task 10:\n";
    task_10(lst);
    cout << "\n=======\n";

    //
    // Auto
    //

    // 11. Calling the function that, using auto, prints alterate
    // items in the list
    cout << "Task 11:\n";
    task_11(lst);
    cout << "\n=======\n";

    
    // 12.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 12:\n";
    cout << *task_12(lst, 3);
    cout << "\n=======\n";

    // 13.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 13:\n";
    cout << *task_13(lst, 3);
    cout << "\n=======\n";

    //
    // Generic Algorithms
    //

    // 14. Generic algorithms: find
    cout << "Task 14:\n";
    if(lst.end() == find(lst.begin(), lst.end(), 3)) cout << "NOT FOUND";
    else cout << *find(lst.begin(), lst.end(), 3);
    cout << endl;
    if(lst.end() == find(lst.begin(), lst.end(), 9999)) cout << "NOT FOUND";
    else cout << *find(lst.begin(), lst.end(), 9999);
    cout << "\n=======\n";

    // 15. Generic algorithms: find_if
    cout << "Task 15:\n";
    if(lst.end() == find_if(lst.begin(), lst.end(), is_even)) cout << "NOT FOUND";
    else cout << *find_if(lst.begin(), lst.end(), is_even);
    cout << endl;
    if(lst.end() == find_if(lst.begin(), lst.end(), is_9999)) cout << "NOT FOUND";
    else cout << *find_if(lst.begin(), lst.end(), is_9999);
    cout << "\n=======\n";

    // 16. Functor
    cout << "Task 16:\n";
    Task_16 functor;
    if(lst.end() == find_if(lst.begin(), lst.end(), functor)) cout << "NOT FOUND";
    else cout << *find_if(lst.begin(), lst.end(), functor);
    cout << "\n=======\n";
    
    // 17. Lambda
    cout << "Task 17:\n";
    if(lst.end() == find_if(lst.begin(), lst.end(), [] (int x) { return !(x%2); })) cout << "NOT FOUND";
    else cout << *find_if(lst.begin(), lst.end(), [] (int x) { return !(x%2); });
    cout << "\n=======\n";

    // 18. Generic algorithms: copy to an array
    cout << "Task 18:\n";
    int* arr = new int[8];
    copy(vec.begin(), vec.end(), arr);
    for(int i = 0; i < 8; i++) cout << arr[i] << " ";
    cout << endl;
    if(arr + 8 == find_if(arr, arr + 8, is_even)) cout << "NOT FOUND";
    else cout << *find_if(arr, arr + 8, is_even);
    cout << "\n=======\n";
    delete[] arr;
    
    //
    // Templated Functions
    //

    // 19. Implement find as a function for lists
    cout << "Task 19:\n";
    vector<int>::iterator res_19 = ourFind(vec.begin(), vec.end(), 3);
    if(res_19 == vec.end()) cout << "NOT FOUND";
    else cout << *res_19;
    cout << "\n=======\n";
    
    // 20. Implement find as a templated function
    cout << "Task 20:\n";
    list<int>::iterator res_20 = ourFind(lst.begin(), lst.end(), 3);
    if(res_20 == lst.end()) cout << "NOT FOUND";
    else cout << *res_20;
    cout << "\n=======\n";

    //
    // Associative collections
    //

    // 21. Using a vector of strings, print a line showing the number
    //     of distinct words and the words themselves.
    cout << "Task 21:\n";
    ifstream fin("pooh-nopunc.txt");
    vector<string> v_tokens;
    string token;
    while(fin) {
        fin >> token;
        if(find(v_tokens.begin(), v_tokens.end(), token) == v_tokens.end())
            v_tokens.push_back(token);
    }
    fin.close();
    cout << v_tokens.size();
    for(const string& str : v_tokens)
        cout << str << " ";
    cout << "\n=======\n";

    // 22. Repeating previous step, but using the set
    cout << "Task 22:\n";
    fin.open("pooh-nopunc.txt");
    set<string> s_tokens;
    while(fin) {
        fin >> token;
        s_tokens.insert(token);
    }
    fin.close();
    cout << s_tokens.size();
    for(const string& str : s_tokens)
        cout << str << " ";
    cout << "\n=======\n";

    // 23. Word co-occurence using map
    cout << "Task 23:\n";
    fin.open("pooh-nopunc.txt");
    map<string, vector<int>> wordMap;
    for(int count = 0; fin; count++) {
        fin >> token;
        wordMap[token].push_back(count);
    }
    fin.close();
    cout << wordMap.size();
    for(const auto& pair : wordMap) {
        cout << pair.first;
        for(const auto i : pair.second) cout << " " << i;
        cout << endl;
    }
    cout << "\n=======\n";
}
