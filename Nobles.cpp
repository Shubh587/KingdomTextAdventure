//Noble Classes Implementation

#include "Nobles.h"
#include "Protectors.h"
using namespace std;

namespace WarriorCraft {
    //Noble class Implementation
    Noble::Noble(const string& name, double strength) : name(name), strength(strength), isDead(false) {}

    const string& Noble::getName() const {
        return name;
    }

    const bool Noble::getisDead() const {
        return isDead;
    }

    const double Noble::getStrength() const {
        return strength;
    }

    void Noble::setStrength(double new_strength) {
        strength = new_strength;
    }

    void Noble::setIsDead(bool condition) {
        isDead = condition;
    }
    
    void Noble::death() {
        strength = 0;
        isDead = true;
    }

    void Noble::defeats(Noble& opponent, int scenario) {
        if (scenario == 1) { //this beat opponent
            cout << name << " defeats " << opponent.name << endl;
            battle_damage(opponent.strength / strength);
            opponent.death();
        }
        else if (scenario == 2) {//opponent beats this
            cout << opponent.name << " defeats " << name << endl;
            battle_damage(strength / opponent.strength);
            death();
        }
        else {//mutual destruction
            cout << "Mutual Annihalation: " << name << " and " << opponent.name << " die at each other's hands" << endl;
            death();
            opponent.death();
        }
    }

    void Noble::battle(Noble& opponent) {
        //State which nobles are fighting 
        cout << name << " battles " << opponent.name << endl;
        //Call each noble's battle_cry() method
        battle_cry();
        opponent.battle_cry();
        //check whether the nobles are dead or alive
        if (!isDead && opponent.isDead) { //this noble is alive but the opponent is already dead
            cout << "He's dead, " << name << endl;
        }
        else if (isDead && !opponent.isDead) {//this noble is dead but the opponent is alive
            cout << "He's dead, " << opponent.name << endl;
        }
        else if (isDead && opponent.isDead) { //both nobles are dead
            cout << "Oh, NO!  They're both dead!  Yuck!" << endl;
        }
        else { //both the nobles are alive
            if (strength > opponent.strength) {//this noble wins
                defeats(opponent, 1);
            }
            else if (strength < opponent.strength) { //opponent wins
                defeats(opponent, 2);
            }
            else { //both nobles die
                defeats(opponent, 3);
            }
        }
    }

    //Lord Class Implementation
    Lord::Lord(const string& name) : Noble(name, 0) {}

    bool Lord::hires(Protector& recruit) {
        if (!getisDead() && !recruit.isHired() && !recruit.getisDead()) { //check if the noble is alive, protector is a free agent, and the protector is alive
            army.push_back(&recruit);
            setStrength(getStrength() + recruit.getStrength());
            recruit.setNoble(this);
            return true;
        }
        return false;
    }

    size_t Lord::find_protector(const Protector& aProtector) const {
        size_t fired_protector_ind = army.size();
        for (size_t protector_ptr = 0; protector_ptr < army.size(); ++protector_ptr) {
            if (army[protector_ptr] == &aProtector) {//compares the addresses of the two protectors (instead of their fields)
                fired_protector_ind = protector_ptr;
                break;
            }
        }
        return fired_protector_ind;
    }

    void Lord::remove_protector(size_t protector_index) {
        for (size_t protector_ptr = protector_index; protector_ptr < army.size() - 1; ++protector_ptr) {
            army[protector_ptr] = army[protector_ptr + 1];
        }
        army.pop_back(); //removes a copy of the last protector in the army
    }

    bool Lord::fire(Protector& aProtector) {
        if (!getisDead()) { //if the noble is alive
        //find the index of the correct protector
            size_t fired_protector_ind = find_protector(aProtector);
            if (fired_protector_ind == army.size()) {//check if the function protector is in the army
                cout << "Protector is not part of army" << endl;
            }
            else { //protector is found
                //Adjust the noble's strength
                setStrength(getStrength() - army[fired_protector_ind]->getStrength());
                //output who is being fired, which noble fired the protector, and the new status of the noble
                cout << "You don't work for me anymore " << army[fired_protector_ind]->getName() << "! -- " << getName() << endl;
                remove_protector(fired_protector_ind);
                return true;
            }
        }
        return false;
    }

    void Lord::battle_damage(double ratio) {
        for (size_t protector_ptr = 0; protector_ptr < army.size(); ++protector_ptr) {
            if (army[protector_ptr]->getStrength() < (getStrength() - (ratio * getStrength()))) { //check if the warrior will die from this battle
                army[protector_ptr]->death();
            }
            else {
                army[protector_ptr]->setStrength(getStrength() - ratio * getStrength());
            }
        }
    }

    void Lord::battle_cry() const {
        for (size_t ind = 0; ind < army.size(); ++ind) {
            army[ind]->battle_cry();
        }
    }

    //PersonWithStrengthToFight Class Implementation
    PersonWithStrengthToFight::PersonWithStrengthToFight(const string& name, double strength) : Noble(name, strength) {}

    void PersonWithStrengthToFight::battle_cry() const {
        cout << "UGH!!!" << endl;
    }

    void PersonWithStrengthToFight::battle_damage(double ratio) {
        if (getStrength() < (getStrength() - (ratio * getStrength()))) { //check if the noble will die from this battle
            death();
        }
        else {
            setStrength(getStrength() - ratio * getStrength());
        }
    }

    void PersonWithStrengthToFight::battle(Noble& opponent) {
        battle_cry();
        Noble::battle(opponent);
    }

}