#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime> // for time()
#include <cmath>
#include <time.h>

#include "include/enemy.h"
#include "include/player.h"

using std::cout, std::string, std::cin, std::endl, std::getline;

//temporary variables storage. need to move somewhere else
int choice1;
int choice2;
int choice3;
int choice4;
int choice5;
int attackturns;
int damagetaken;
int damagedone;
int goldgained;
int blockchance;
int counterchance;
int itemselect;
bool inloop;
int check;
int damagedefended;
int time1;
int time2;
int goldloottable[] = {75, 50, 40, 25};
string thing;
Player player;

Enemy goblin(10, 5, 100); //maxattac minattack health
Enemy python(30, 10, 100);
Enemy robot(17, 7, 500);

void spamattacktutorial();
int lvl1();
int lvl2_1();
void lvl2_2();
void lvl3_1();
int lvl3_2();
void lvl4_1();
void lvl4_2();

int main() {
    srand(time(NULL)); // initialize random seed
    inloop = true;
    cout << "*************ADVENTURE GAME*************" << endl;
    string name;
    cout << "What's your name adventurer? ";
    getline(cin,name);
    player.setname(name);
    player.weaponstats(0);
    cout << "Hello " << player.name << "\n";
    char startchoice;
    do {
        cout << "Would you like to start your adventure? (Y/N) ";
        cin >> startchoice;
        if (startchoice == 'N' || startchoice == 'n') {
            cout << "Goodbye";
            return 0;
        } else if (startchoice == 'Y' || startchoice == 'y') {
            inloop = false;
            break;
        } else {
            cout << "Please input only y or n\n";
            break;
        }
    } while (inloop);

    cout << "\n\nAnnouncer: Welcome to ADVENTURE GAME 1.0\n";

    // starthere
    choice1 = lvl1();
    switch (choice1){
        case 1:
            lvl2_1();
            lvl3_1();
            lvl4_1();
            break;
        case 2:
            lvl2_2();
            lvl3_2();
            lvl4_2();
            break;
    }
    cout << "end";
    return 0;
    
}   



int lvl1(){
    inloop = true;
    do{
        cout << "You enter the dungeon and you find a button. Do you push the button? (1) or continue on and see what else you find? (2)\n";
        cin >> choice1;
        switch (choice1) {
            case 1:
                cout << "You push the button and a trap door opens beneath your feet!\n";
                player.damage(damagetaken = rand() % 30 + 10);
                cout << "You take " << damagetaken << " damage. Your health is now " << player.health << "/" << player.maxhealth << "\n";
                inloop = false;
                break;
            case 2:
                cout << "You continue on and find a chest with a healing potion!\n";
                player.heal(rand() % 30 + 10); // random healing between 10 and 40
                cout << "Your health is now " << player.health << "/" << player.maxhealth << "\n";
                inloop = false;
                break;
            default:
                cout << "Please only enter 1 or 2\n";
                break;
        }
    }while(inloop);
    return choice1;
}

int lvl2_1(){
    inloop = true;
    do{
        cout << "After freeing yourself from the trap you find a treasure chest. How do you open it? Smash it with your sword until it opens? (1) Or try pick the lock? (2)  ";
        cin >> choice2;
        switch(choice2){
            case 1:
                cout << "You successfully smashed open the chest, however you damaged some of the treasure inside too...\n";
                cout << "You gained ";
                goldgained = rand() % 15 + 10;
                cout << goldgained << " gold! " << "Total gold: " << (player.gold += goldgained) << "\n";
                inloop = false;
                break;
            case 2:
                if ((rand() % 4 + 1) < 4){
                    cout << "You swiftly picked the lock!\n";
                    cout << "You gained ";
                    goldgained = rand() % 40 + 10;
                    cout << goldgained << " gold! " << "Total gold: " << (player.gold += goldgained) << "\n";
                } else {
                    cout << "You failed to pick the lock and triggered a trap!\n";
                    player.damage(damagetaken = rand() % 30 + 10);
                    cout << "You take " << damagetaken << " damage. Your health is now " << player.health << "/" << player.maxhealth << "\n";
                }
                inloop = false;
                break;
        }
    }while (inloop);
    return choice2;
}

void lvl2_2(){
    inloop = true;
    cout << "Continuing down the dungeon you encounter an small goblin,";
    do{
        cout << "attack?(1) or try block its attack?(2)";
        cin >> choice2;
        switch(choice2){
            case 1:
                //attack
                damagedone = goblin.damage(rand() % (player.maxattack-player.minattack) + player.minattack, "goblin");
                cout << "You did " << damagedone << " damage to the goblin" << " | " << goblin.health << "/" << goblin.maxhealth << "\n";    
                //counter by goblin
                counterchance = rand() % 2;
                if(counterchance == 0){
                    player.damage(damagetaken = rand() % (goblin.maxattack-goblin.minattack+1) + goblin.minattack);
                    cout << "You take " << damagetaken << " damage. Your health is now " << player.health << "/" << player.maxhealth << "\n";
                }
                inloop = false;
                break;
            case 2:
                //block
                blockchance = rand() % 4 + 1;
                cout << blockchance;
                if(blockchance < 4){
                    damagedone = goblin.damage(rand() % (player.maxcounter-player.mincounter+1) + player.mincounter, "goblin");
                    cout << "you successfully blocked the goblins attack and do " << damagedone << "to it" << " | " << goblin.health << "/" << goblin.maxhealth;
                }else{
                    cout << "you failed to block the goblins attack";
                    damagedone = player.damage(rand() % (goblin.maxattack-goblin.minattack+1) + goblin.minattack);
                    cout << "You take " << damagetaken << " damage. Your health is now " << player.health << "/" << player.maxhealth << "\n";
                }
                inloop = false;
                break;
            default:
                cout << "please only enter 1 or 2";
                break;

        }
    } while (goblin.health > 0);
}

void lvl3_1(){
    //after getting a chest you find a shop
    inloop = true;
    do{ 
        cout << "A shop has appeared! what would you like to buy" << " Current balance:" << player.gold << " gold" << endl;
        cout << "************SHOP KEEPER************\n1. Great sword || 75g\n2. Healing potion (50hp) || 30g" << "\n***********************************";
        cin >> itemselect;
        switch(itemselect){
            case 1:
                if (player.gold < 75){
                    cout << "you dont have enough money to buy that";
                    break;
                }
                cout << "You now have a great sword. Which has slightly higher damage";
                cout << "New balance is " << (player.gold -=75) << " gold";
                
                player.weaponstats(2);
                inloop = false;
                break;
            case 2:
                if (player.gold < 30){
                    cout << "you dont have enough money to buy that";
                    break;
                }
                cout << "New balance is " << (player.gold -=30) << " gold";
                player.heal(50);
                cout << "You healed 50 health! Your health is now " << player.health << "/" << player.maxhealth << "\n";
                inloop = false;
                break;
            default:
                cout << "Please only enter 1 or 2";
                break;
        }
    }while(inloop);
}

int lvl3_2(){
    inloop = true;
    do{
        cout << "Continuing on, you find a fork in the path. which way do you go? left?(1) or right?(2)";
        cin >> choice3; 
        switch(choice3){
            case 1:
                //weapon with heal
                cout << "You go left and find a skeleton, leaning in to inspect it you find it has a shiny sword\n Bone sword unlocked! This sword allows *crits*";
                player.weaponstats(1);
                inloop = false;
                break;
            case 2:
                //boss fight thing 
                cout << "Going down the right path you find a big room, it's completely empty aside from one chest at the back of the room, opening the chest you find only a healing potion";
                //bossfight
                cout << "\n*hss hs s hssss hsss* A massive python dropped from the ceiling! you must have triggered a trap!";
                attackturns = 1;
                do{
                    cout << "\nWhere do you attack the snake first? eye(1) nose(2) mouth(3) body(4) tail?(5)";
                    cin >> choice4;
                    switch(choice4){
                        case 1:
                            if (attackturns == 3){
                                python.damage(25, "python");
                                cout << "You attack landed perfectly, do did 25 damage!" << python.health << "/" << python.maxhealth;                           
                            }else{
                                damagedone = python.damage(rand() % (player.maxattack - player.minattack + 1)+player.minattack, "python");
                                cout << "\nYour attack landed but it didn't seem to do very much, You did " << damagedone << " damage to the python " << python.health << "/" << python.maxhealth; 
                                if(python.health <= 0){break;}
                                player.damage(damagetaken = rand() % (python.maxattack - python.minattack + 1)+python.minattack);
                                cout << "\n The python recovered quickly and pulled off a counter attack! you took " << damagetaken << " damage" << "\nYour health is now " << player.health << "/" << player.maxhealth;                            
                            }
                            attackturns++;
                            break;
                        case 2:
                            if (attackturns == 2){
                                python.damage(25, "python");
                                cout << "You attack landed perfectly, do did 25 damage!" << python.health << "/" << python.maxhealth;                            
                            }else{
                                damagedone = python.damage(rand() % (player.maxattack - player.minattack + 1)+player.minattack, "python");
                                cout << "\nYour attack landed but it didn't seem to do very much, You did " << damagedone << " damage to the python " << python.health << "/" << python.maxhealth; 
                                if(python.health <= 0){break;}
                                player.damage(damagetaken = rand() % (python.maxattack - python.minattack + 1)+python.minattack);
                                cout << "\n The python recovered quickly and pulled off a counter attack! you took " << damagetaken << " damage" << "\nYour health is now " << player.health << "/" << player.maxhealth;
                            }                            
                            attackturns++; 
                            break;                           
                        case 3:
                            if (attackturns == 1){
                                python.damage(25, "python");
                                cout << "You attack landed perfectly, do did 25 damage!" << python.health << "/" << python.maxhealth;
                            }else{
                                damagedone = python.damage(rand() % (player.maxattack - player.minattack + 1)+player.minattack, "python");
                                cout << "\nYour attack landed but it didn't seem to do very much, You did " << damagedone << " damage to the python " << python.health << "/" << python.maxhealth; 
                                if(python.health <= 0){break;}
                                player.damage(damagetaken = rand() % (python.maxattack - python.minattack + 1)+python.minattack);
                                cout << "\n The python recovered quickly and pulled off a counter attack! you took " << damagetaken << " damage" << "\nYour health is now " << player.health << "/" << player.maxhealth;
                            }                        
                            attackturns++;
                            break;
                        case 4:
                            if (attackturns == 5){
                                python.damage(25, "python");
                                cout << "You attack landed perfectly, do did 25 damage!" << python.health << "/" << python.maxhealth;
                            }else{
                                damagedone = python.damage(rand() % (player.maxattack - player.minattack + 1)+player.minattack, "python");
                                cout << "\nYour attack landed but it didn't seem to do very much, You did " << damagedone << " damage to the python " << python.health << "/" << python.maxhealth; 
                                if(python.health <= 0){break;}
                                player.damage(damagetaken = rand() % (python.maxattack - python.minattack + 1)+python.minattack);
                                cout << "\n The python recovered quickly and pulled off a counter attack! you took " << damagetaken << " damage" << "\nYour health is now " << player.health << "/" << player.maxhealth;
                            }
                            attackturns++;
                            break;
                        case 5:
                            if (attackturns == 4){
                                python.damage(25, "python");
                                cout << "You attack landed perfectly, do did 25 damage!" << python.health << "/" << python.maxhealth;
                            }else{
                                damagedone = python.damage(rand() % (player.maxattack - player.minattack + 1)+player.minattack, "python");
                                cout << "\nYour attack landed but it didn't seem to do very much, You did " << damagedone << " damage to the python " << python.health << "/" << python.maxhealth; 
                                if(python.health <= 0){break;}
                                player.damage(damagetaken = rand() % (python.maxattack - python.minattack + 1)+python.minattack);
                                cout << "\n The python recovered quickly and pulled off a counter attack! you took " << damagetaken << " damage" << "\nYour health is now " << player.health << "/" << player.maxhealth;
                            }                        
                            attackturns++;
                            break;
                        default:
                            cout << "only input numbers 1-5";
                            break;
                    }
                }while (!(attackturns > 5 || python.health <= 0));
                if (attackturns > 5){
                    cout << "\nsome reason how the snake killed you because of time";
                }else{
                    cout << "good job on defeating snek! you gained 50 gold. current gold balance: " << (player.gold+=50) << "gold";
                }
                inloop = false;
                break;
            default:
                cout << "please only input 1 or 2";
                break;
        }
    }while(inloop);
    return choice3;
}

void lvl4_1(){ //not finished yet
    //boss fight
    cout << "Seems that there was an ancient sleeping robot under the skeleton and you accidently woke it up\n";
    spamattacktutorial(); //to show the user how to use the attack system 
    attackturns = 7;
    do{
        cout << "do you try attack(1) or block its attack(2)";
        cin >> choice5;
        switch(choice5){
            case 1:
                time1 = time(NULL);
                cout << "\nAttack:  ";
                cin >> thing;
                time2 = time(NULL);
                if((time2-time1) > 5){
                    cout << "you took too long\n";
                    break;
                }
                damagedone = 0;
                for(char c : thing){
                    (c=='z') ? damagedone++ : damagedone;
                }
                robot.damage(damagedone, "robot");
                cout << "You did "<< damagedone << " damage  " << robot.health << "/" << robot.maxhealth;
                counterchance = rand() % 3;
                if (counterchance > 0){
                    player.damage(damagetaken = rand() % (robot.maxattack-robot.minattack+1) + robot.minattack);
                    cout << "You left yourself wide open for an attack! You took " << damagetaken << " damage  " << player.health << "/" << player.maxhealth;
                }
                attackturns--;
                cout << "\n" << attackturns << " turns left\n"; 
                break;
            case 2:
                time1 = time(NULL);
                cout << "\nDefend:  ";
                cin >> thing;
                time2 = time(NULL);
                if((time2-time1) > 5){
                    cout << "you took too long\n";
                    break;
                }
                damagedone = 0;
                damagedefended = 0;
                for(char c : thing){
                    (c=='x') ? damagedefended++: damagedefended;
                }
                damagedone = (damagedefended/5);
                robot.damage(damagedone, "robot");
                cout << "You did "<< damagedone << " damage  " << robot.health << "/" << robot.maxhealth;
                attackturns--;
                cout << "\n" << attackturns << " turns left\n"; 
                break;
            default:
                cout << "pleas only input 1 or 2";
                break;
        }
        cout << robot.health << " " << attackturns;
    }while(attackturns != 0 || robot.health > 0);
    if (attackturns == 0){
        cout << "\nyou ran out of time";
    }
}

void lvl4_2(){
    //shop
    inloop = true;
    do{ 
        cout << "A shop has appeared! what would you like to buy" << " Current balance:" << player.gold << " gold" << endl;
        cout << "************SHOP KEEPER************\n1. Great sword || 75g\n2. Healing potion (75hp) || 35g\n3. Knights armor || 100g" << "\n***********************************";
        cin >> itemselect;
        switch(itemselect){
            case 1:
                if (player.gold < 75){
                    cout << "you dont have enough money to buy that";
                    break;
                }
                cout << "You now have a great sword. Which has slightly higher damage";
                cout << "New balance is " << (player.gold -=75) << " gold";
                player.weaponstats(2);
                inloop = false;
                break;
            case 2:
                if (player.gold < 35){
                    cout << "you dont have enough money to buy that";
                    break;
                }
                cout << "New balance is " << (player.gold -=35) << " gold";
                player.heal(75);
                cout << "You healed 75 health! Your health is now " << player.health << "/" << player.maxhealth << "\n";
                inloop = false;
                break;
            case 3:
                if (player.gold < 100){
                    cout << "you dont have enough money to buy that";
                    break;
                }
                cout << "New balance is " << (player.gold -=100) << " gold";
                player.armor=5;
                cout << "You now have armor! congratulations 5 damage you take will be negated";
                inloop = false;
                break;
            default:
                cout << "Please only enter 1 or 2";
                break;
        }
    }while(inloop);
}





void spamattacktutorial(){

}