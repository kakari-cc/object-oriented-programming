#include <iostream>
#include <string>
#include <vector>

#include "course.h"
#include "student.h"

using namespace std;

namespace BrooklynPoly {

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

}
