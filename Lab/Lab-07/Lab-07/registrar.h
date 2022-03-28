#ifndef REGISTRAR_H
#define REGISTRAR_H

#include <iostream>
#include <string>
#include <vector>

namespace BrooklynPoly {

    class Course;

    class Student;

    class Registrar {
        friend std::ostream& operator<<(std::ostream&, const Registrar&);
    public:
        Registrar();
        bool addCourse(const std::string&);
        bool addStudent(const std::string&);
        bool enrollStudentInCourse(const std::string&, const std::string&);
        bool cancelCourse(const std::string&);
        void purge();

    private:
        size_t findStudent(const std::string&) const;
        size_t findCourse(const std::string&) const;

        std::vector<Course*> courses;
        std::vector<Student*> students;
    };

}

#endif
