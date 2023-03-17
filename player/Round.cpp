#include "player.h"

void Round::setround(int round)    //Sets the round number
{
    roundNumber = round;
}
int Round::getround()      //Gets the round number
{
    return roundNumber;
}
void Round::setgangsterkill(std::string gangkill)    //Sets the gangster kill
{
    gangsterkill = gangkill;
}
std::string Round::getgangsterkill()    //Gets the gangster kill
{
    return gangsterkill;
}
void Round::setvotekill(std::string voteKill)   //Sets the vote kill
{
    votekill = voteKill;
}
std::string Round::getvotekill()    //Gets the vote kill
{
    return votekill;
}

Round::Round(int round, string gangkill, string voteKill)      //constructor with parameters (round number, gangster kill, vote kill)
{
    roundNumber = round;        //round number
    gangsterkill = gangkill;        //gangster kill
    votekill = voteKill;        //vote kill 
}

Round::Round()        //default constructor 
{
    roundNumber = 0;    
    gangsterkill = "";
    votekill = ""; 
}
