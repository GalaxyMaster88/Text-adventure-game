#pragma once // include guard

#include <string>
#include <iostream>
#include "player.h"

using std::cout, std::string, std::cin, std::endl, std::getline;

extern Player player;

class Enemy {
public:
    int maxhealth;
    int health;
    int maxattack;
    int minattack;
    int damagedone;

    Enemy(int a, int b, int c) {
        maxattack = a;
        minattack = b;
        maxhealth = c;
        health = maxhealth;
    }

    int damage(int n, string enemy) {
        damagedone = player.crit(n);
        health -= damagedone;
        if (health <= 0) {
            health = 0;
            die(enemy);
        }
        return damagedone;
    }

    void die(string enemy){
        cout << "congratulations you defeated the " << enemy << "!";
    }
};