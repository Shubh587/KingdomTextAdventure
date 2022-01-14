//Protector Classes Implementation

#include "Nobles.h"
#include "Protectors.h"
using namespace std;

namespace WarriorCraft {
    //Protector Class Implementation
    Protector::Protector(const string& name, double strength) : name(name), strength(strength), isDead(false), noble(nullptr) {}

    bool Protector::isHired() const {
        return noble != nullptr;
    }

    bool Protector::getisDead() const {
        return isDead;
    }

    double Protector::getStrength() const {
        return strength;
    }

    const string& Protector::getName() const {
        return name;
    }

    const Noble* Protector::getLord() const {
        return noble;
    }

    void Protector::setNoble(Noble* aNoble) {
        noble = aNoble;
    }

    void Protector::setIsDead(bool condition) {
        isDead = condition;
    }

    void Protector::setStrength(double new_strength) {
        strength = new_strength;
    }

    void Protector::death() {
        isDead = true;
        strength = 0;
        noble = nullptr;
    }

    //Wizard Class Implementation
    Wizard::Wizard(const string& name, double strength) : Protector(name, strength) {}

    void Wizard::battle_cry() const {
        cout << "POOF" << endl;
    }

    //Warrior Class Implementation
    Warrior::Warrior(const string& name, double strength) : Protector(name, strength) {}

    void Warrior::battle_cry() const {
        cout << getName() << " says: Take that in the name of my lord, " << getLord()->getName() << endl;
    }

    //Archer Class Implementation
    Archer::Archer(const string& name, double strength) : Warrior(name, strength) {}

    void Archer::battle_cry() const {
        cout << "TWANG! ";
        Warrior::battle_cry();
    }

    //Swordsman Class Implementation
    Swordsman::Swordsman(const string& name, double strength) : Warrior(name, strength) {}

    void Swordsman::battle_cry() const {
        cout << "CLANG! ";
        Warrior::battle_cry();
    }
}