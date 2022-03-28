//
//  rec07_single.cpp
//  Student Registrar
//
//  Created by Mingxuan Zhang.
//

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Student;

class Course {
    friend ostream& operator<<(ostream&, const Course&);
public:
    // Course methods needed by Registrar
    Course(const string&);
    const string& getName() const;
    bool addStudent(Student*);
    void removeStudentsFromCourse();

private:
    string name;
    vector<Student*> students;
};

class Student {
    friend ostream& operator<<(ostream&, const Student&);
public:
    // Student methods needed by Registrar
    Student(const string&);
    const string& getName() const;
    bool addCourse(Course*);

    // Student method needed by Course
    void removedFromCourse(Course*);

private:
    string name;
    vector<Course*> courses;
};

class Registrar {
    friend ostream& operator<<(ostream&, const Registrar&);
public:
    Registrar();
    bool addCourse(const string&);
    bool addStudent(const string&);
    bool enrollStudentInCourse(const string&, const string&);
    bool cancelCourse(const string&);
    void purge();

private:
    size_t findStudent(const string&) const;
    size_t findCourse(const string&) const;

    vector<Course*> courses;
    vector<Student*> students;
};

int main() {

    Registrar registrar;

    cout << "No courses or students added yet\n";
    cout << registrar << endl;
     
    cout << "AddCourse CS101.001\n";
    registrar.addCourse("CS101.001");
    cout << registrar << endl;

    cout << "AddStudent FritzTheCat\n";
    registrar.addStudent("FritzTheCat");
    cout << registrar << endl;

    cout << "AddCourse CS102.001\n";
    registrar.addCourse("CS102.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse FritzTheCat CS102.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS102.001");
    cout << "EnrollStudentInCourse FritzTheCat CS101.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS101.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse Bullwinkle CS101.001\n";
    cout << "Should fail, i.e. do nothing, "
         << "since Bullwinkle is not a student.\n";
    registrar.enrollStudentInCourse("Bullwinkle", "CS101.001");
    cout << registrar << endl;

    cout << "CancelCourse CS102.001\n";
    registrar.cancelCourse("CS102.001");
    cout << registrar << endl;
   
    /*
    // [OPTIONAL - do later if time]
    cout << "ChangeStudentName FritzTheCat MightyMouse\n";
    registrar.changeStudentName("FritzTheCat", "MightyMouse");
    cout << registrar << endl;

    cout << "DropStudentFromCourse MightyMouse CS101.001\n";
    registrar.dropStudentFromCourse("MightyMouse", "CS101.001");
    cout << registrar << endl;

    cout << "RemoveStudent FritzTheCat\n";
    registrar.removeStudent("FritzTheCat");
    cout << registrar << endl;
    */

    cout << "Purge for start of next semester\n";
    registrar.purge();
    cout << registrar << endl;
}

//----------------------------------------------------//

Course::Course(const string& courseName)
    : name(courseName) {}

const string& Course::getName() const { return name; }

bool Course::addStudent(Student* student) {
    for(const Student* i : students)
        if(i == student) return false;
    students.push_back(student);
    return true;
}

void Course::removeStudentsFromCourse() {
    for(Student* i : students)
        i->removedFromCourse(this);
    students.clear();
}

ostream& operator<<(ostream& os, const Course& rhs) {
    os << rhs.name << ": ";
    if(rhs.students.size() == 0)
        os << "No Students";
    else
        for(const Student* i : rhs.students)
            os << i->getName() << " ";
    return os;
}

//----------------------------------------------------//

Student::Student(const string& name)
    : name(name) {}

const string& Student::getName() const { return name; }

bool Student::addCourse(Course* course) {
    for(const Course* i : courses)
        if(i == course) return false;
    courses.push_back(course);
    return true;
}

void Student::removedFromCourse(Course* course) {
    for(size_t i = 0; i < courses.size(); i++)
        if(courses[i] == course)
            courses[i] = courses[courses.size() - 1];
    courses.pop_back();
}

ostream& operator<<(ostream& os, const Student& rhs) {
    os << rhs.name << ": ";
    if(rhs.courses.size() == 0)
        os << "No Courses";
    else
        for(const Course* i : rhs.courses)
            os << i->getName() << " ";
    return os;
}

//----------------------------------------------------//

Registrar::Registrar() {}

bool Registrar::addCourse(const string& name) {
    for(const Course* i : courses)
        if(i->getName() == name) return false;
    courses.push_back(new Course(name));
    return true;
}

bool Registrar::addStudent(const string& name) {
    for(const Student* i : students)
        if(i->getName() == name) return false;
    students.push_back(new Student(name));
    return true;
}

bool Registrar::enrollStudentInCourse(const string& studentName,
                                      const string& courseName) {
    Student* student = nullptr;
    for(Student* i : students)
        if(i->getName() == studentName)
            student = i;
    if(student == nullptr) return false;
    Course* course = nullptr;
    for(Course* i : courses)
        if(i->getName() == courseName)
            course = i;
    if(course == nullptr) return false;
    if(student->addCourse(course))
        return course->addStudent(student);
    return false;
}

bool Registrar::cancelCourse(const string& courseName) {
    size_t index = courses.size();
    for(size_t i = 0; i < courses.size(); i++)
        if(courses[i]->getName() == courseName)
            index = i;
    if(index == courses.size()) return false;
    courses[index]->removeStudentsFromCourse();
    courses[index] = courses[courses.size() - 1];
    courses.pop_back();
    return true;
}

void Registrar::purge() {
    for(Student* i : students) delete i;
    for(Course* i : courses) delete i;
    students.clear();
    courses.clear();
}

ostream& operator<<(ostream& os, const Registrar& rhs) {
    os << "Registrar's Report" << endl;
    os << "Courses:";
    for(const Course* i : rhs.courses) {
        os << endl << *i;
    }
    os << endl << "Students:";
    for(const Student* i : rhs.students) {
        os << endl << *i;
    }
    return os << endl;
}
