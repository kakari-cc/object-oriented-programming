//
//  rec12.cpp
//  Doubly Linked List
//
//  Created by Mingxuan Zhang.
//

#include <cstdlib>
#include <iostream>

using namespace std;

class List {
    friend ostream& operator<<(ostream& os, const List& rhs) {
        Node* cur = rhs.header->next;
        while(cur != rhs.trailer) {
            os << cur->data << " ";
            cur = cur->next;
        }
        return os;
    }
private:
    struct Node {
        Node(int data, Node* prev = nullptr, Node* next = nullptr)
            : prev(prev)
            , next(next)
            , data(data)
        {};
        int data;
        Node *prev, *next;
    };
    Node *header, *trailer;
    size_t length;
public:
    List() : length(0) {
        header = new Node(NULL, nullptr, nullptr);
        trailer = new Node(NULL, header, nullptr);
        header->next = trailer;
    };
    List(const List&);
    ~List() {
        clear();
        cout << "~List()" << endl;
    }
    List& operator=(const List&);
    class iterator {
        friend List;
        friend bool operator==(const iterator& lhs, const iterator& rhs) { return lhs.ptr == rhs.ptr; }
        // operator== @ Line 138
    private:
        Node* ptr;
    public:
        iterator(Node* ptr = nullptr)
            : ptr(ptr)
        {};
        iterator& operator++() {
            ptr = ptr->next;
            return *this;
        }
        iterator& operator--() {
            ptr = ptr->prev;
            return *this;
        }
        int& operator*() const {
            return ptr->data;
        }
    };
    void push_back(int data) {
        Node* new_node = trailer->prev->next = new Node(data, trailer->prev, trailer);
        trailer->prev = new_node;
        length++;
    }
    void push_front(int data) {
        Node* new_node = header->next->prev = new Node(data, header, header->next);
        header->next = new_node;
        length++;
    }
    int pop_back() {
        if(length == 0) return NULL;
        Node* to_delete = trailer->prev;
        trailer->prev = trailer->prev->prev;
        trailer->prev->next = trailer;
        length--;
        int val = to_delete->data;
        delete to_delete;
        return val;
    }
    int pop_front() {
        if(length == 0) return NULL;
        Node* to_delete = header->next;
        header->next = header->next->next;
        header->next->prev = header;
        length--;
        int val = to_delete->data;
        delete to_delete;
        return val;
    }
    int& front() { return header->next->data; }
    int front() const { return header->next->data; }
    int& back() { return trailer->prev->data; }
    int back() const { return trailer->prev->data; }
    int& operator[] (size_t index) {
        Node* cur = header->next;
        for(size_t i = 0; i < index; i++)
            cur = cur->next;
        return cur->data;
    }
    int operator[] (size_t index) const {
        Node* cur = header->next;
        for(size_t i = 0; i < index; i++)
            cur = cur->next;
        return cur->data;
    }
    void clear() {
        Node* cur = header->next;
        while(cur != trailer) {
            Node* next = cur->next;
            delete cur;
            cur = next;
        }
        length = 0;
        header->next = trailer;
        trailer->prev = header;
    }
    size_t size() const { return length; }
    iterator begin() const { return iterator(header->next); }
    iterator end() const { return iterator(trailer); }
    iterator insert(iterator loc, int data) {
        Node* new_node = new Node(data, loc.ptr->prev, loc.ptr);
        loc.ptr->prev->next = new_node;
        loc.ptr->prev = new_node;
        length++;
        return --loc;
    }
    iterator erase(iterator loc) {
        Node* to_delete = loc.ptr;
        loc.ptr->prev->next = loc.ptr->next;
        loc.ptr->next->prev = loc.ptr->prev;
        --loc;
        delete to_delete;
        length--;
        return loc;
    }
};

bool operator!=(const List::iterator& lhs, const List::iterator& rhs) { return !(lhs == rhs); }

List::List(const List& other) {
    cout << "List(List)" << endl;
    header = new Node(NULL, nullptr, nullptr);
    trailer = new Node(NULL, header, nullptr);
    header->next = trailer;
    length = 0;
    for(int i : other)
        push_back(i);
}

List& List::operator=(const List& other) {
    cout << "List::op=(List)" << endl;
    clear();
    //header = new Node(NULL, nullptr, nullptr);
    //trailer = new Node(NULL, header, nullptr);
    //header->next = trailer;
    length = 0;
    for(int i : other)
        push_back(i);
    return *this;
}

// Task 1
void printListInfo(const List& myList) {
        cout << "size: " << myList.size()
             << ", front: " << myList.front()
             << ", back(): " << myList.back()
             << ", list: " << myList << endl;
}

// The following should not compile. Check that it does not.
// void changeFrontAndBackConst(const List& theList){
//     theList.front() = 17;
//     theList.back() = 42;
// }

void changeFrontAndBack(List& theList){
    theList.front() = 17;
    theList.back() = 42;
}

// Task 4
void printListSlow(const List& myList) {
    for (size_t i = 0; i < myList.size(); ++i) {
        cout << myList[i] << ' ';
    }
    cout << endl;
}

// Task 8
void doNothing(List aList) {
    cout << "In doNothing\n";
    printListInfo(aList);
    cout << endl;
    cout << "Leaving doNothing\n";
}

int main() {
    // Task 1
    cout << "\n------Task One------\n";
    List myList;
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList.push_back(" << i*i << ");\n";
        myList.push_back(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";
    
    cout << "Modify the first and last items, and display the results\n";
    changeFrontAndBack(myList);
    printListInfo(myList);
    cout << "===================\n";

    cout << "Remove the items with pop_back\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_back();
    }
    cout << "===================\n";

    // Task 2
    cout << "\n------Task Two------\n";
    cout << "Fill empty list with push_front: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList2.push_front(" << i*i << ");\n";
        myList.push_front(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";
    cout << "Remove the items with pop_front\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_front();
    }
    printListInfo(myList);
    cout << "===================\n";

    // Task 3
    cout << "\n------Task Three------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        myList.push_back(i*i);
    }
    printListInfo(myList);
    cout << "Now clear\n";
    myList.clear();
    cout << "Size: " << myList.size() << ", list: " << myList << endl;
    cout << "===================\n";

    // Task 4
    cout << "\n------Task Four------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    cout << "Display elements with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;
    cout << "Add one to each element with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) myList[i] += 1;
    cout << "And print it out again with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;
    cout << "Now calling a function, printListSlow, to do the same thing\n";
    printListSlow(myList);
    cout << "Finally, for this task, using the index operator to modify\n"
         << "the data in the third item in the list\n"
         << "and then using printListSlow to display it again\n";
    myList[2] = 42;
    printListSlow(myList);


    // Task 5
    cout << "\n------Task Five------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    printListInfo(myList);
    cout << "Now display the elements in a ranged for\n";
    for (int x : myList) cout << x << ' ';
    cout << endl;
    cout << "And again using the iterator type directly:\n";
    // Note you can choose to nest the iterator class or not, your choice.
    //for (iterator iter = myList.begin(); iter != myList.end(); ++iter) {
    for (List::iterator iter = myList.begin(); iter != myList.end(); ++iter) {
        cout << *iter << ' ';
    }
    cout << endl;
    cout << "WOW!!! (I thought it was cool.)\n";

    // Task 6
    cout << "\n------Task Six------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    printListInfo(myList);
    cout << "Filling an empty list with insert at begin(): "
         << "i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.begin(), i*i);
    printListInfo(myList);
    // ***Need test for insert other than begin/end***
    cout << "===================\n";

    // Task 7
    cout << "\n------Task Seven------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    cout << "Erasing the elements in the list, starting from the beginning\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.erase(myList.begin());
    }
    // ***Need test for erase other than begin/end***
    cout << "===================\n";

    // Task 8
    cout << "\n------Task Eight------\n";
    cout << "Copy control\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    printListInfo(myList);
    cout << "Calling doNothing(myList)\n";
    doNothing(myList);
    cout << "Back from doNothing(myList)\n";
    printListInfo(myList);

    cout << "Filling listTwo with insert at begin: i*i for i from 0 to 9\n";
    List listTwo;
    for (int i = 0; i < 10; ++i) listTwo.insert(listTwo.begin(), i*i);
    printListInfo(listTwo);
    cout << "listTwo = myList\n";
    listTwo = myList;
    cout << "myList: ";
    printListInfo(myList);
    cout << "listTwo: ";
    printListInfo(listTwo);
    cout << "===================\n";
}
