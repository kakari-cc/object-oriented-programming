//
//  rec05.cpp
//  Lab Grade Management System
//
//  Created by Mingxuan Zhang.
//

#include <iostream>
#include <vector>

using namespace std;

#define AM 0
#define PM 1

class Section {
private:
    
    class TimeSlot {
    private:
        string day;
        short time, hour_12;
    public:
        TimeSlot(const string& day, short hour_24) : day(day) {
            if(hour_24 > 12) {
                time = PM;
                hour_12 = hour_24 % 12;
            }
            else {
                time = AM;
                hour_12 = hour_24;
            }
        }
        friend ostream& operator<<(ostream& os, const TimeSlot& rhs) {
            os << "Day: " << rhs.day << ", Start time: " << rhs.hour_12 << (rhs.time ? "pm" : "am");
            return os;
        }
    };
    
    class StudentRecord {
    private:
        string name;
        vector<int> grades;
    public:
        StudentRecord(const string& name) : name(name) {
            for(int i = 0; i < 14; i++)
                grades.push_back(-1);
        }
        const string& get_name() const {
            return name;
        }
        void addGrade(int grade, size_t week) {
            grades[week - 1] = grade;
        }
        friend ostream& operator<<(ostream& os, const StudentRecord& rhs) {
            os << "Name: " << rhs.name << ", Grades: ";
            for(const int i : rhs.grades)
                os << i << " ";
            return os;
        }
    };
    
    string name;
    TimeSlot time_slot;
    vector<StudentRecord*> students;
public:
    Section(const string& name, const string& day, int hour_24)
        : name(name)
        , time_slot(TimeSlot(day, hour_24)) {}
    Section(const Section& section)
        : name(section.name)
        , time_slot(section.time_slot) {
        for(const StudentRecord* i : section.students)
            students.push_back(new StudentRecord(*i));
    }
    ~Section() {
        clog << "Section " << name << " is being deleted" << endl;
        for(StudentRecord* i : students) {
            clog << "Deleting " << i->get_name() << endl;
            delete i;
        }
        students.clear();
    }
    void addStudent(const string& name) {
        students.push_back(new StudentRecord(name));
    }
    void addGrade(const string& student, int grade, size_t week) {
        for(StudentRecord* i : students) {
            if (i->get_name() == student) {
                i->addGrade(grade, week);
                break;
            }
        }
    }
    friend ostream& operator<<(ostream& os, const Section& rhs) {
        os << "Section: " << rhs.name << ", Time slot: [" << rhs.time_slot << "], Students: ";
        if(rhs.students.size()) {
            for(const StudentRecord* i : rhs.students)
                os << endl << *i;
        }
        else {
            os << "None";
        }
        return os;
    }
};

class LabWorker {
private:
    string name;
    Section *section_ptr;
public:
    LabWorker(const string& name) : name(name) {
        section_ptr = nullptr;
    }
    void addSection(Section& section) {
        section_ptr = &section;
    }
    void addGrade(const string& student, int grade, size_t week) {
        if(section_ptr)
            section_ptr->addGrade(student, grade, week);
        else
            cerr << name << " does not have a section";
    }
    friend ostream& operator<<(ostream& os, const LabWorker& rhs) {
        if(rhs.section_ptr)
            return os << rhs.name << " has " << *rhs.section_ptr;
        else
            return os << rhs.name << " does not have a section";
    }
};

// Test code
void doNothing(Section sec) { cout << sec << endl; }

int main() {

    cout << "Test 1: Defining a section\n";
     Section secA2("A2", "Tuesday", 16);
     cout << secA2 << endl;

    cout << "\nTest 2: Adding students to a section\n";
     secA2.addStudent("John");
     secA2.addStudent("George");
     secA2.addStudent("Paul");
     secA2.addStudent("Ringo");
     cout << secA2 << endl;

    cout << "\nTest 3: Defining a lab worker.\n";
     LabWorker moe( "Moe" );
     cout << moe << endl;

    cout << "\nTest 4: Adding a section to a lab worker.\n";
     moe.addSection( secA2 );
     cout << moe << endl;

    cout << "\nTest 5: Adding a second section and lab worker.\n";
     LabWorker jane( "Jane" );
     Section secB3( "B3", "Thursday", 11 );
     secB3.addStudent("Thorin");
     secB3.addStudent("Dwalin");
     secB3.addStudent("Balin");
     secB3.addStudent("Kili");
     secB3.addStudent("Fili");
     secB3.addStudent("Dori");
     secB3.addStudent("Nori");
     secB3.addStudent("Ori");
     secB3.addStudent("Oin");
     secB3.addStudent("Gloin");
     secB3.addStudent("Bifur");
     secB3.addStudent("Bofur");
     secB3.addStudent("Bombur");
     jane.addSection( secB3 );
     cout << jane << endl;

    cout << "\nTest 6: Adding some grades for week one\n";
     moe.addGrade("John", 17, 1);
     moe.addGrade("Paul", 19, 1);
     moe.addGrade("George", 16, 1);
     moe.addGrade("Ringo", 7, 1);
     cout << moe << endl;

    cout << "\nTest 7: Adding some grades for week three (skipping week 2)\n";
     moe.addGrade("John", 15, 3);
     moe.addGrade("Paul", 20, 3);
     moe.addGrade("Ringo", 0, 3);
     moe.addGrade("George", 16, 3);
     cout << moe << endl;

    cout << "\nTest 8: We're done (almost)! \nWhat should happen to all "
         << "those students (or rather their records?)\n";

    cout << "\nTest 9: Oh, IF you have covered copy constructors in lecture, "
         << "then make sure the following call works:\n";
     doNothing(secA2);
     cout << "Back from doNothing\n\n";

}
