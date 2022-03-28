#include <iostream>
#include <string>
#include <vector>

#include "course.h"
#include "student.h"

using namespace std;

namespace BrooklynPoly {

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

}
