#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>
#include <vector>

namespace BrooklynPoly {

    class Course;

    class Student {
        friend std::ostream& operator<<(std::ostream&, const Student&);
    public:
        // Student methods needed by Registrar
        Student(const std::string&);
        const std::string& getName() const;
        bool addCourse(Course*);

        // Student method needed by Course
        void removedFromCourse(Course*);

    private:
        std::string name;
        std::vector<Course*> courses;
    };

}

#endif
