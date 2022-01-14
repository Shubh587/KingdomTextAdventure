/*
* Protector Classes Header File
*/

#ifndef PROTECTORS_H
#define PROTECTORS_H

#include <iostream>
#include <vector>
#include <string>

namespace WarriorCraft {

    class Noble;

    class Protector { //base class for the two types of protectors
    public:
        bool isHired() const;

        bool getisDead() const;

        double getStrength() const;

        const std::string& getName() const;

        void setNoble(Noble* aNoble);

        void death();

        void setStrength(double new_strength);

        virtual void battle_cry() const = 0;

    protected:
        Protector(const std::string& name, double strength);

        const Noble* getLord() const;

        void setIsDead(bool condition);

    private:
        std::string name;
        double strength;
        bool isDead;
        Noble* noble;
    };

    class Wizard : public Protector {
    public:
        Wizard(const std::string& name, double strength);

        void battle_cry() const;

    private:
    };

    class Warrior : public Protector {
    public:
        Warrior(const std::string& name, double strength);

        void battle_cry() const;
    private:
    };

    class Archer : public Warrior {
    public:
        Archer(const std::string& name, double strength);

        void battle_cry() const;
    private:
    };

    class Swordsman : public Warrior {
    public:
        Swordsman(const std::string& name, double strength);

        void battle_cry() const;
    private:
    };

}

#endif
