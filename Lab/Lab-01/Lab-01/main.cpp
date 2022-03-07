/*
  rec01_start.cpp
  spring 2022
  jbs
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Task 15. Function to display a vector of ints
void print_vector(const vector<int>& vec) {
    for (int value : vec)
        cout << value << " ";
    cout << endl;
}


// Task 16. Function to modify the vector, using indices
void double_vector(vector<int>& vec) {
    for (size_t i = 0; i < vec.size(); i++)
        vec[i] *= 2;
}


// Task 17. Function to modify the vector, using a ranged for
void double_vector_ranged(vector<int>& vec) {
    for (int& value : vec)
        value *= 2;
}


//
// main
//
int main() { // Yes, it has to have an int for the return type
    //
    // Output
    //
    
    // Task 1. Printing hello ...  No use of "using namespace"
    std::cout << "hello cs2124" << std::endl;

    // Task 2  Printing hello ...  Using "using namespace"
    cout << "hello cs2124" << endl;


    //
    // Types and variables
    //

    // Task 3  Displaying uninitialized variable
    int x;
    cout << "x: " << x << endl;

    
    // Task 4 Use the sizeof function to see the size in bytes of
    //        different types on your machine.
    int y = 17;
    int z = 2000000017;
    double pie = 3.14159;
    cout << "sizeof(y): " << sizeof(y) << endl;
    cout << "sizeof(z): " << sizeof(z) << endl;
    cout << "sizeof(pie): " << sizeof(pie) << endl;

    
    // Task 5  Attempt to assign the wrong type of thing to a variable
    // x = "felix";"
    // Compile Error: Assigning to 'int' from incompatible type 'const char [6]'


    //
    // Conditions
    //

    // Task 6  Testing for a range
    if (y > 10 && y < 20)
        cout << "Yes, y is between 10 and 20" << endl;
    else
        cout << "No, y is not between 10 and 20" << endl;
    

    //
    // Loops and files
    //

    // Task 7  Looping, printing values 10 to 20 inclusive

    // First with a for loop
    for (int i = 10; i < 21; i++)
        cout << i << " ";
    cout << endl;
    
    // Then with a while loop
    int j = 10;
    while (j < 21)
        cout << j++ << " ";
    cout << endl;

    // Finally with a do-while loop
    int k = 10;
    do
        cout << k++ << " ";
    while (k < 21);
    cout << endl;


    // Task 8  Looping to successfully open a file, asking user for the name
    ifstream ifs;
    string fname;
    do {
        cout << "Filename? ";
        cin >> fname;
        ifs.open(fname);
    } while (!ifs);

    // Task 9  Looping, reading file word by "word".
    string text;
    while (ifs >> text)
        cout << text << endl;
    ifs.close();

    // Task 10 Open a file of integers, read it in, and display the sum.
    ifs.open("integers.txt");
    if (!ifs)
        cerr << "\"intergers.txt\" failed to open.";
    int sum = 0;
    int tmp;
    while (ifs >> tmp)
        sum += tmp;
    ifs.close();
    cout << "sum: " << sum << endl;

    // Taks 11 Open and read a file of integers and words. Display the sum.
    ifs.open("mixed.txt");
    if (!ifs)
        cerr << "\"mixed.txt\" failed to open.";
    sum = 0;
    while (ifs >> tmp)
        sum += tmp;
    ifs.close();
    cout << "sum: " << sum << endl;

    //
    // Vectors
    //

    // Task 12 Filling a vector of ints
    vector<int> v;
    for (int i = 10; i < 101; i++)
        v.push_back(i);
    
    // Task 13 Displaying the vector THREE times
    //         a) using the indices,
    for (size_t i = 0; i < v.size(); i++)
        cout << v[i] << " ";
    cout << endl;

    //         b) using a "ranged for"
    for (int value : v)
        cout << value << " ";
    cout << endl;

    //         c) using indices again but backwards
    for (size_t i = v.size(); i != 0; i--)
        cout << v[i-1] << " ";
    cout << endl;


    // Task 14. Initialize a vector with the primes less than 20.
    vector<int> prime{2, 3, 5, 7, 11, 13, 17, 19};
    for (int value : prime)
        cout << value << " ";
    cout << endl;

    //
    // Functions
    //
    
    // Task 15  Function to print a vector
    print_vector(prime);

    // Task 16  Function to double the values in a vector
    double_vector(prime);
    print_vector(prime);


    // Task 17  Function to double the values in a vector, using a ranged for
    double_vector_ranged(prime);
    print_vector(prime);
    
}
