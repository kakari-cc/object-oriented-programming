#ifndef PROTECTOR_H  // Guard
#define PROTECTOR_H

#include <iostream>
#include <vector>
#include <string>

namespace WarriorCraft {

    class Noble;  // Forward Class Declarations

    class Protector {
    private:
        std::string name;
        double strength;
        Lord* hirer;
    protected:
        Lord* get_hirer() const { return hirer; }
    public:
        Protector(const std::string& name, double strength);
        std::string get_name() const;
        double get_strength() const;
        bool is_hired() const;
        void hire_process(Lord* lord);
        void runaway();
        void fire_process();
        void reduce_strength(double);
        virtual void defends() const = 0;
        friend std::ostream& operator<<(std::ostream&, const Protector&);
    };

    class Wizard : public Protector {
        using Protector::Protector;
    public:
        void defends() const;
    };

    class Warrior : public Protector {
        using Protector::Protector;
    public:
        void defends() const = 0;
    };

    class Archer : public Warrior {
        using Warrior::Warrior;
    public:
        void defends() const;
    };

    class Swordsman : public Warrior {
        using Warrior::Warrior;
    public:
        void defends() const;
    };

}

#endif
