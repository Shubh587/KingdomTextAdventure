/*
* Noble Classes Header File
*/

#ifndef NOBLES_H
#define NOBLES_H

#include <iostream>
#include <string>
#include <vector>

namespace WarriorCraft {

    class Protector;

    class Noble { //base class for the two types of Nobles
    public:
        virtual void battle(Noble& opponent);

        const std::string& getName() const;
    protected:
        Noble(const std::string& name, double strength);

        const bool getisDead() const;

        const double getStrength() const;

        void setStrength(double strength);

        void setIsDead(bool condition);

        virtual void death();

        virtual void battle_damage(double ratio) = 0;

        void defeats(Noble& opponent, int scenario);

        virtual void battle_cry() const = 0;

    private:
        std::string name;
        double strength;
        bool isDead;
    };

    class Lord : public Noble {
    public:
        Lord(const std::string& name);

        bool hires(Protector& recruit);

        size_t find_protector(const Protector& aProtector) const;

        void remove_protector(size_t protector_index);

        bool fire(Protector& aProtector);

        void battle_damage(double ratio);

        void battle_cry() const;

    private:
        std::vector<Protector*> army;
    };

    class PersonWithStrengthToFight : public Noble {
    public:
        PersonWithStrengthToFight(const std::string& name, double strength);

        void battle_cry() const;

        void battle_damage(double ratio);

        void battle(Noble& opponent);

    private:
    };
}

#endif