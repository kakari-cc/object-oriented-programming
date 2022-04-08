//
//  main.cpp
//  Inheritance tutorial
//
//  Created by Mingxuan Zhang.
//

#include <iostream>
#include <vector>

using namespace std;

class PrintedMaterial {
public:
    PrintedMaterial(unsigned numPages)
    : numOfPages(numPages)
    {}
    virtual void displayNumPages() const = 0;
    friend ostream& operator<<(ostream& os, const PrintedMaterial& rhs) {
        return os << "Page: " << rhs.numOfPages;
    }
private:
    unsigned numOfPages;
};

class Magazine : public PrintedMaterial {
public:
    Magazine(unsigned numPages)
    : PrintedMaterial(numPages)
    {}
    void displayNumPages() const {
        cout << "Magazine:";
        PrintedMaterial::displayNumPages();
    }
private:
};

class Book : public PrintedMaterial {
public:
    Book(unsigned numPages)
    : PrintedMaterial(numPages)
    {}
    // Abstract
private:
};

class TextBook : public Book {
public:
    TextBook(unsigned numPages, unsigned numIndxPgs )
    : Book(numPages),
      numOfIndexPages(numIndxPgs)
    {}
    void displayNumPages() const {
        cout << "Textbook Index = " << numOfIndexPages << ", ";
        PrintedMaterial::displayNumPages();
    }
private:
    unsigned numOfIndexPages;
};

class Novel : public Book {
public:
    Novel(unsigned numPages)
    : Book(numPages)
    {}
    void displayNumPages() const {
        cout << "Novel: ";
        PrintedMaterial::displayNumPages();
    }
private:
};

void PrintedMaterial::displayNumPages() const {
    cout << numOfPages << endl;
}

void displayNumberOfPages(const PrintedMaterial& obj){
//    PrintedMaterial* ptr = &obj;
    obj.displayNumPages();
}

// tester/modeler code
int main() {
    TextBook text(5430, 23);
    Novel novel(213);
    Magazine mag(6);

    text.displayNumPages();
    novel.displayNumPages();
    mag.displayNumPages();
    cout << "===========\n";
    
//    PrintedMaterial pm = text; // kind of like copying text into a vector of PrintedMaterials
//    pm.displayNumPages();
//    cout << "===========\n";
    
    PrintedMaterial* pmPtr;
    pmPtr = &text;
    // instead of putting an actual PrintedMaterial
    // object into the vector, we put the address of
    // a PrintedMaterial object (text) into a vector
    // of pointers-to-PrintedMaterial
    // (that is, pointers to the Base class)
    // we'll be "managing" our objects by using
    // pointers to PrintedMaterial values.
    pmPtr->displayNumPages();
    cout << "===========\n";
    
    displayNumberOfPages(text);
    cout << "\n<VECTOR>\n";
    vector<PrintedMaterial*> v_pm;
    v_pm.push_back(&text);
    v_pm.push_back(&novel);
    v_pm.push_back(&mag);
    for(PrintedMaterial* i : v_pm) {
        i->displayNumPages();
    }
}
