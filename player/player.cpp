#include "player.h"


void Player::setname(std::string n)  //Sets the name of the player 
{
    name = n;   
}
std::string Player::getname()    //Gets the name of the player
{
    return name;    
}
void Player::setalive(bool a)   //Sets the status of the player
{ 
    alive = a;
}
bool Player::getalive()     //Gets the status of the player
{
    return alive;   
}
void Player::setrole(std::string r)  //Sets the role of the player
{
    role = r;
}
std::string Player::getrole()    //Gets the role of the player
{
    return role;
}
void Player::setcurrentvotes(int votes)    //Sets the current votes of the player
{
    currentvotes = votes;
}
void Player::incrementvotes()   //Increments the current votes of the player
{
    currentvotes++;
}
int Player::getcurrentvotes()   //Gets the current votes of the player
{
    return currentvotes;
}
int Player::getindex()  //Gets the index of the player
{
    return index + 1;
}
void Player::setindex(int i)    //Sets the index of the player
{
    index = i;
}
void Player::setequal(bool e)   //Sets the equalvoted variable
{
    equalvoted = e;
}
bool Player::getequal()     //Gets the equalvoted variable
{
    return equalvoted;
}

void Player::vote(Player &p)    //Player votes for another player
{
    p.currentvotes++;   //increments the current votes of the player
}

Player::Player(string Name, bool isAlive, string Role, int Index)      //constructor with parameters 
{
    name = Name;        //name
    alive = isAlive;    //alive
    role = Role;            //role
    index = Index;      //index
}

Player::Player()        //default constructor 
{
    name = " ";     //default name
    alive = true;       //default alive     
    role = " ";     //default role
}

