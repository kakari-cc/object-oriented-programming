#ifndef NOBLE_H  // Guard
#define NOBLE_H

#include <iostream>
#include <vector>
#include <string>

namespace WarriorCraft {

    class Protector;  // Forward Class Declarations

    class Noble {
    private:
        std::string name;
        bool alive;
    public:
        Noble(const std::string& name);
        bool is_alive() const;
        const std::string& get_name() const;
        virtual double battle_strength() const = 0;
        virtual void battle(Noble& other);
        virtual void defend() const = 0;
        virtual void lost();
        virtual void won(double ratio) = 0;
    };

    class Lord : public Noble {
    private:
        std::vector<Protector*> army;
    public:
        Lord(const std::string& name);
        bool hires(Protector& protector);
        bool fires(Protector& protector);
        void notify_leave(Protector* protector);
        double battle_strength() const;
        void defend() const;
        void lost();
        void won(double ratio);
        friend std::ostream& operator<<(std::ostream&, const Lord&);
    };

    class PersonWithStrengthToFight : public Noble {
    private:
        double strength;
    public:
        PersonWithStrengthToFight(const std::string& name, double strength);
        double battle_strength() const;
        void defend() const;
        void won(double ratio);
        friend std::ostream& operator<<(std::ostream&, const PersonWithStrengthToFight&);
    };

}

#endif
