#ifndef WARRIOR_H  // Guard
#define WARRIOR_H

#include <iostream>
#include <vector>
#include <string>

namespace WarriorCraft {

    class Noble;  // Forward Class Declarations

    class Warrior {
        
    private:
        const std::string name;
        bool hired;
        double strength;
        Noble* hirer;
        
    public:
        Warrior(const std::string&, double);
        friend std::ostream& operator<<(std::ostream&, const Warrior&);
        const std::string& get_name() const;
        double get_strength() const;
        bool isHired() const;
        void hire(Noble*);  // Being Hired
        void runaway();
        void fired();  // Being Fired
        void reduce_strength(double);  // After Winning a Battle
    };

}

#endif
