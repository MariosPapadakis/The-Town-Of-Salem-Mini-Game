#pragma once
#include "std_lib_facilities.h"

class Player        //This is the class that stores the information of each player
{
    private:        //private variables
        string name;    //name of the player
        bool alive;     //alive or dead
        string role;    // role of the player (citizen, doctor, gangster)
        int currentvotes = 0;       //current votes of the player (used in the day phase)
        int index;      //index of the player 
        bool equalvoted = false;        //variable that stores if the player has been equalvoted or not (used in the day phase)
    
    public:     //public functions
        void setname(string n); //Sets the name of the player 
        string getname();    //Gets the name of the player
        void setalive(bool a);   //Sets the status of the player
        bool getalive();     //Gets the status of the player
        void setrole(string r); //Sets the role of the player
        string getrole();    //Gets the role of the player
        void setcurrentvotes(int votes);    //Sets the current votes of the player
        void incrementvotes();   //Increments the current votes of the player
        int getcurrentvotes();   //Gets the current votes of the player
        int getindex();  //Gets the index of the player
        void setindex(int i);    //Sets the index of the player
        void setequal(bool e);   //Sets the equalvoted variable
        bool getequal();     //Gets the equalvoted variable

        void vote(Player &p);    //Player votes for another player

        Player(string Name, bool isAlive, string Role, int Index);      //constructor with parameters 

        Player();        //default constructor 
};

class Round     //This is the class that stores the information of each round
{
    private:        //private variables
        int roundNumber;        //This is a variable that stores the number of the round
        string gangsterkill;    
        string votekill; 

    public:
        void setround(int round);    //Sets the round number
        int getround();      //Gets the round number
        void setgangsterkill(string gangkill);    //Sets the gangster kill
        string getgangsterkill();    //Gets the gangster kill
        void setvotekill(string voteKill);   //Sets the vote kill
        string getvotekill();    //Gets the vote kill

        Round(int round, string gangkill, string voteKill);      //constructor with parameters (round number, gangster kill, vote kill)

        Round();       //default constructor 
};