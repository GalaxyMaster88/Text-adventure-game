#pragma once // include guard

#include <string>
#include <iostream>
#include <cmath>

using std::cout, std::string, std::cin, std::endl, std::getline;


class Player {
public:
    string name;
    int health = 100;
    const int maxhealth = 100;
    const int starting_gold = 50;
    int gold = starting_gold;
    int maxattack;
    int minattack;
    int maxcounter;
    int mincounter;
    int weapon = 0;
    int armor;
    bool critchance;


    Player() {};

    void setname(string n){
        name = n;
    }

    int damage(int n) {
        health -= n;
        health += armor;
        if (health <= 0) {
            health = 0;
            die();
        }
        return health;
    }

    int heal(int n) {
        if (health == 100) {
            cout << "You're already at max health. You gained " << (round(n*0.75)) << " gold\n";
            gold += n;
        }
        health += n;
        if (health > maxhealth) {
            health = maxhealth;
        }
        return health;
    }

    void die() {
        cout << "you died! GAME OVER\n";
        exit(1);
    }

    int crit(int n) {
        bool chance = rand() % 3;
        if (chance == 0 && critchance == true) {
            n = n*2;
        }
        return n;
    }

    void weaponstats(int n) {
        weapon = n;
        if (weapon == 0) {
            maxattack = 15;
            minattack = 5;
            maxcounter = 10;
            mincounter = 5;
            critchance = false;
        } else if (weapon == 1) {
            maxattack = 15;
            minattack = 5;
            maxcounter = 10;
            mincounter = 5;
            critchance = true;
        } else if (weapon == 2) {
            maxattack = 20;
            minattack = 10;
            maxcounter = 15;
            mincounter = 10;
            critchance = false;
        }
    }
    void armorstats(int n) {
        armor = n;
        if (armor == 1) {
            armor = 5;
        } else if (armor == 2) {
            armor = 10;
        }
    }
};
