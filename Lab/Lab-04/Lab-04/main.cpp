//
//  rec04.cpp
//  Lab-04
//
//  Created by Mingxuan Z. on 2022/02/18.
//

#include <iostream>
#include <vector>

using namespace std;

int main() {
    // Task 2
    int x;
    x = 10;
    cout << "x = " << x << endl;
    
    // Task 8
    int* p;
    // p = 0x7ffeefbff568;
    p = &x;
    cout << "p = " << p << endl;
    
    //Task 10
    cout << "p points to where " << *p << " is stored\n";
    cout << "*p contains " << *p << endl;
    
    // Task 11
    *p = -2763;
    cout << "p points to where " << *p << " is      stored\n";
    cout << "*p now contains " << *p << endl;
    cout << "x now contains " << x << endl;
    
    // Task 12
    int y(13);
    cout << "y contains " << y << endl;
    p = &y;
    cout << "p now points to where " << *p << " is stored\n";
    cout << "*p now contains " << *p << endl;
    *p = 980;
    cout << "p points to where " << *p << " is stored\n";
    cout << "*p now contains " << *p << endl;
    cout << "y now contains " << y << endl;
    
    // Task 13
    int* q;
    q = p;
    cout << "q points to where " << *q << " is stored\n";
    cout << "*q contains " << *q << endl;
    
    // Task 14
    double d(33.44);
    double* pD(&d);
    *pD = *p;
    *pD = 73.2343;
    *p  = *pD;
    *q  = *p;
    // pD  = p; // NO COERCION between any pointer types
    // p   = pD;
    
    // Task 15
    int joe = 24;
    const int sal = 19;
    int*  pI;
    pI = &joe;
    *pI = 234;
    // pI = &sal; // Assigning to 'int *' from incompatible type 'const int *'
    // *pI = 7623;

    const int* pcI;
    pcI = &joe;
    // *pcI = 234; // Read-only variable is not assignable
    pcI = &sal;
    // *pcI = 7623;

    // int* const cpI; // Default initialization of an object of const type 'int *const'
    int* const cpI(&joe);
    // int* const cpI(&sal);
    // Cannot initialize a variable of type 'int *const' with an rvalue of type 'const int *'
    // cpI = &joe;
    // Cannot assign to variable 'cpI' with const-qualified type 'int *const'
    *cpI = 234;
    // cpI = &sal;
    *cpI = 7623;

    // const int* const cpcI; // Default initialization of an object of const type 'const int *const'
    const int* const cpcI(&joe);
    // const int* const cpcI(&sal); // Also OK, commented out to prevent redefinition
    // cpcI = &joe; // Cannot assign to variable 'cpcI' with const-qualified type 'const int *const'
    // *cpcI = 234; // Read-only variable is not assignable
    // cpcI = &sal;
    // *cpcI = 7623;
    
    // Task 16
    struct Complex {
       double real;
       double img;
    };
    Complex c = {11.23,45.67};
    Complex* pC(&c);
    cout << pC->real << "+" << pC->img << "i" << endl;
    // cout << "real: " << *pC.real << "\nimaginary: " << *pC.img << endl; // no
    cout << "real: " << (*pC).real << "\nimaginary: " << (*pC).img << endl;
    cout << "real: " << pC->real << "\nimaginary: " << pC->img << endl;
    
    // Task 17
    class PlainOldClass {
    public:
       PlainOldClass() : x(-72) {}
       int getX() const { return x; }
       void setX( int val )  { x = val; }
    private:
       int x;
    };
    PlainOldClass poc;
    PlainOldClass* ppoc( &poc );
    cout << ppoc->getX() << endl;
    ppoc->setX( 2837 );
    cout << ppoc->getX() << endl;
    
    // Task 18
    class PlainOldClassV2 {
    public:
        PlainOldClassV2() : x(-72) {}
        int getX() const { return x; }
        // void setX( int x )  { x = x; } // HMMMM???
        void setX( int x )  { this->x = x; } // No confusion!
    private:
        int x;
    };
    PlainOldClassV2 poc2;
    PlainOldClassV2* ppoc2( &poc2 );
    cout << ppoc2->getX() << endl;
    ppoc2->setX( 2837 );
    cout << ppoc2->getX() << endl;
    
    // Task 19
    int* pDyn = new int(3); // p points to an int initialized to 3 on the heap
    *pDyn = 17;
    cout << "The " << *pDyn
         << " is stored at address " << pDyn
         << " which is in the heap\n";
    
    // Task 20
    cout << pDyn << endl;
    delete pDyn;
    cout << pDyn << endl;
    cout << "The 17 might STILL be stored at address " << pDyn<< " even though we deleted pDyn\n";
    // cout << "But can we dereference pDyn?  We can try.  This might crash... " << *pDyn << ".  Still here?\n"; // Commented out
    
    // Task 21
    pDyn = nullptr;
    double* pDouble = nullptr;
    
    // Task 22
    // cout << "Can we dereference nullptr?  " << *pDyn << endl; // Thread 1: EXC_BAD_ACCESS (code=1, address=0x0)
    // cout << "Can we dereference nullptr?  " << *pDouble << endl;
    
    // Task 24
    double* pTest = new double(12);
    delete pTest;
    pTest = nullptr;
    delete pTest; // safe
    
    // Task 25
    short* pShrt = new short(5);
    delete pShrt;
    // delete pShrt; // Thread 1: signal SIGABRT
    
    // Task 26
    long jumper = 12238743;
    // delete jumper; // Cannot delete expression of type 'long'
    long* ptrTolong = &jumper;
    // delete ptrTolong; // Lab-04(4178,0x1000e7dc0) malloc: *** error for object 0x7ffeefbff4b8: pointer being freed was not allocated
    Complex cmplx;
    // delete cmplx; // Cannot delete expression of type 'Complex'
    
    // Task 27
    vector<Complex*> complV; // can hold pointers to Complex objects
    Complex* tmpPCmplx;      // space for a Complex pointer
    for (size_t ndx = 0; ndx < 3; ++ndx) {
       tmpPCmplx = new Complex; // create a new Complex object on the heap
       tmpPCmplx->real = ndx;   // set real and img to be the
       tmpPCmplx->img  = ndx;   // value of the current ndx
       complV.push_back(tmpPCmplx); // store the ADDRESS of the object in a vector or pointer to Complex
    }
    // display the objects using the pointers stored in the vector
    for (size_t ndx = 0; ndx < 3; ++ndx) {
        cout << complV[ ndx ]->real << endl;
        cout << complV[ ndx ]->img  << endl;
    }
    // release the heap space pointed at by the pointers in the vector
    for (size_t ndx = 0; ndx < 3; ++ndx) {
        delete complV[ndx];
    }
    // clear the vector
    complV.clear();
    
    // Task 28
    class Colour {
    public:
        Colour(const string& name, unsigned r, unsigned g, unsigned b)
            : name(name), r(r), g(g), b(b) {}
        void display() const {
            cout << name << " (RBG: " << r << "," << g<< "," << b << ")";
        }
    private:
        string name;      // what we call this colour
        unsigned r, g, b; // red/green/blue values for displaying
    };
    vector<Colour*> colours;
    string inputName;
    unsigned inputR, inputG, inputB;

    // fill vector with Colours from the file
    // this could be from an actual file but here we are using the keyboard instead of a file
    // (so we don't have to create an actual file)
    // Do you remember the keystroke combination to indicate "end of file" at the keyboard?
    // somehow the while's test has to fail - from keyboard input
//    while (cin >> inputName >> inputR >> inputG >> inputB) {
//        colours.push_back(new Colour(inputName, inputR, inputG, inputB));
//    }

    // display all the Colours in the vector:
    for (size_t ndx = 0; ndx < colours.size(); ++ndx) {
        colours[ndx]->display();
        cout << endl;
    }
    /*
     Black 255 255 255
     White 0 0 0
     Azure 10 110 237
     DeepPurple 240 72 261
     */
    for (size_t ndx = 0; ndx < colours.size(); ++ndx) {
        delete colours[ndx];
    }
    
    // Task 29
    class SpeakerSystem {
       public:
       void vibrateSpeakerCones(unsigned signal) const {

          cout << "Playing: " << signal << "Hz sound..." << endl;
          cout << "Buzz, buzzy, buzzer, bzap!!!\n";
       }
    };

    class Amplifier {
    public:
      void attachSpeakers(const SpeakerSystem& spkrs)
       {
          if(attachedSpeakers)
             cout << "already have speakers attached!\n";
          else
            attachedSpeakers = &spkrs;
       }
      
       void detachSpeakers() { // should there be an "error" message if not attached?
          attachedSpeakers = nullptr;
       }
      
       void playMusic( ) const {
          if (attachedSpeakers)
             attachedSpeakers -> vibrateSpeakerCones(440);
          else
             cout << "No speakers attached\n";
       }
    private:
        // SpeakerSystem* attachedSpeakers = nullptr;
        const SpeakerSystem* attachedSpeakers = nullptr;
    };
    Amplifier amp1;
     SpeakerSystem spk1;
    Amplifier amp2;
     SpeakerSystem spk2;
    
    amp1.playMusic();
    amp1.attachSpeakers(spk1);
    amp1.playMusic();
    amp1.attachSpeakers(spk2);
    
    amp2.attachSpeakers(spk1);
    amp2.playMusic();

    // Task 30
    class Person {
    public:
        Person(const string& name) : name(name) {}
        void movesInWith(Person& newRoomate) {
            if(!roomie && !newRoomate.roomie) { // Change
                roomie = &newRoomate;        // now I have a new roomie
                newRoomate.roomie = this;    // and now they do too
            }
        }
        const string& getName() const { return name; }
        // Don't need to use getName() below, just there for you to use in debugging.
        const string& getRoomiesName() const { return roomie->getName(); }
    private:
        Person* roomie = nullptr;
        string name;
    };

    // write code to model two people in this world
    Person joeBob("Joe Bob"), billyJane("Billy Jane");

    // now model these two becoming roommates
    joeBob.movesInWith(billyJane);

    // did this work out?
    cout << joeBob.getName() << " lives with " << joeBob.getRoomiesName() << endl;
    cout << billyJane.getName() << " lives with " << billyJane.getRoomiesName() << endl;
    
    return 0;
}
