#include <iostream>
#include <string>
#include <vector>

#include "registrar.h"
#include "student.h"
#include "course.h"

using namespace std;

namespace BrooklynPoly {

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

}
