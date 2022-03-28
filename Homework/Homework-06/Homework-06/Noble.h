#ifndef NOBLE_H  // Guard
#define NOBLE_H

#include <iostream>
#include <vector>
#include <string>

namespace WarriorCraft {

    class Warrior;  // Forward Class Declarations

    class Noble {
        
    private:
        const std::string name;
        bool alive;
        std::vector<Warrior*> army;
        
    public:
        Noble(const std::string&);
        friend std::ostream& operator<<(std::ostream&, const Noble&);
        const std::string& get_name() const;
        bool hire(Warrior&);
        bool fire(Warrior&);
        void runaway(Warrior*);
        double army_strength() const;
        void battle(Noble&);
    };

}

#endif
