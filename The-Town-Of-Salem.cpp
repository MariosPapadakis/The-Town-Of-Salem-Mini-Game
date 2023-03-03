/*READ_ME:

    TITLE: THE TOWN OF SALEM GAME
    AUTHOR: MARIOS PAPADAKIS
    DATE: 01/03/2023
    PURPOSE: TO CREATE A GAME SIMILAR TO THE TOWN OF SALEM
    VERSION: 1.0 */

/*DESCRIPTION: 

    IN THIS GAME THERE ARE 7 PLAYERS WHO EACH HAVE A ROLE.
    THE ROLES ARE:
        1) CITIZEN 
        2) DOCTOR 
        3) GANGSTER.
    AT THE BEGINNING OF THE GAME AN ALGORITHM RANDOMLY DECIDES THE ROLE OF EACH 
    PLAYER. THERE IS ONE DOCTOR, ONE GANGSTER AND THE REST ARE CITIZENS. THE GAME IS DIVIDED INTO 2 
    PHASES, NIGHT AND DAY.

    IN THE NIGHT PHASE THE CIVILIANS "SLEEP" AND THE GANGSTER CHOOSES A PLAYER TO LEAVE 
    FROM THE GAME. THEN THE DOCTOR CHOOSES A PLAYER TO SAVE HIM FROM THE GANGSTER. IF HE CHOOSES 
    THE PLAYER CHOSEN BY THE GANGSTER, NO ONE LEAVES (HE CANNOT SAVE HIMSELF). AT 
    AT THE END OF THE NIGHT IT GETS ANNOUNCED WHICH PLAYER HAS BEEN KILLED. 
    
    IN THE DAY PHASE, PLAYERS VOTE FOR ONE OF THE REMAINING PLAYERS TO RETIRE.
    THE PLAYER WITH THE MOST VOTES LEAVES THE GAME. 

    THIS PROCESS (I.E. THE NIGHT-DAY PHASES) IS REPEATED UNTIL THE 
    GANGSTER OR UNTIL ALL CIVILIANS AND THE DOCTOR LEAVE. 

    IF THE GANGSTER LEAVES WHILE THERE ARE STILL CIVILIANS OR THE DOCTOR, THE CIVILIANS WIN. IF THERE ARE TWO 
    PLAYERS AND ONE OF THEM IS THE GANGSTER, THE GANGSTER WINS THE GAME. */

#include "std_lib_facilities.h"

int aliveplayers = 7; //This is a variable that stores the number of players that are alive
int lastkill = 0;   //This is a variable that stores the last player that was killed

class Players   //This is a class that stores the role, the index and the state of the player
{
    public:     //This makes the variables public
        string role;    //This is a variable that stores the role of the player
        int player_index;   //This is a variable that stores the index of the player
        bool alive;    //This is a variable that stores the state of the player
        bool equal_voted;    //if there is a tie, this variable will be true
};

vector<Players> player;     //This is a vector that stores the players

int gangsterindex()    //This is a function that returns the index of the gangster
{
    for(int i=0; i<7; i++)  //Using a for loop to find the index of the gangster
    {
        if (player[i].role == "GANGSTER")   //If the role of the player is equal to gangster
        {
            return i;   //Return the index of the player
        }
    }
    return 0;   //Return 0 if the player is not found
}

int doctorindex()   //This is a function that returns the index of the doctor
{
    for(int i=0; i<7; i++)  //Using a for loop to find the index of the doctor
    {
        if (player[i].role == "DOCTOR")     //If the role of the player is equal to doctor
        {
            return i;   //Return the index of the player
        }
    }
    return 0;   //Return 0 if the player is not found
}

void initialize()   //This function initialises the players
{
    for(int i=0; i<7; i++)  //Using a for loop to initialise the players
    {
        player.push_back(Players());    //This is where the players are initialised
        player[i].player_index = i+1;   //This is where the index of the player is initialised
        player[i].alive = true;    //This is where the state of the player is initialised
        player[i].equal_voted = false;    //This is where the equal_voted variable is initialised
    }

    srand((unsigned int)time(0));    //This is a function that generates a random number 
    int num = rand() % 7;   //This is a variable that stores the random number

    for (int i = 0; i < 7; i++)        //Using a for loop to assign the roles
    {
        if (i == num)       //If the random number is equal to the index of the player
        {
            player[i].role = "GANGSTER";        //Assign the role of gangster
        }
        else if (i == num % 3 + 1)    // If the random number % 3 + 1 is equal to the index of the player
        {
            player[i].role = "DOCTOR";      //Assign the role of doctor
        }
        else        //If the random number is not equal to the index of the player or the index of the player plus 1
        {
            player[i].role = "CITIZEN";     //Assign the role of citizen
        }
    }
}

void printplayers()    //This is a function that prints the players
{
    for(int i=0; i<player.size(); i++)  // Using a for loop to print the players
    {   
        if(player[i].alive == true)    //If the player is alive
        {   
            cout << "// PLAYER " << player[i].player_index << " //" << endl;    //Print the player
        }
    }
}

void printroles()   //This is a function that prints the players and their roles
{
    for(int i=0; i<player.size(); i++)  //Using a for loop to print the players and their roles
    {
        if(player[i].alive == true)   //If the player is alive
        {
            cout << "// PLAYER " << player[i].player_index << " IS A " << player[i].role << " //" << endl;  //Print the player and their role
        }
    }
    cout <<endl;    //Print a new line
}

void info_menu()    //This is the function for the info menu
{
    int choice;     //This is the variable that will store the user's choice
    int flag=0;     //This is a flag variable that will be used to check if the player has been killed
    cout << endl << "~~~ INFO MENU ~~~" << endl << endl;        //This is the menu
    
    cout << "- PRESS (1) TO SHOW REMAINING PLAYERS" << endl;        //This is the first option
    cout << "- PRESS (2) TO SHOW THE PLAYER/ROLE LIST" << endl;        //This is the second option
    cout << "- PRESS (3) THE PLAYERS THAT HAVE DIED" << endl;      //This is the third option
    cout << "- PRESS (4) TO SHOW THE MOST RECENT KILL" << endl << endl;        //This is the fourth option

    cin >> choice;      //Gets the user's choice

    try     //Tries a block of code
    {
        if(choice<1 || choice >4)   //If the user enters a number that is not between 1 and 4
        {
            throw choice;   //Throws an error message
        }
    }
    catch(...)  //Catches The Error
    {
         while (choice < 1 || choice > 4)        //Using a while loop to make sure the user enters a valid choice
        {
            cout << endl << "OOPS YOU PRESSED: " << choice << endl << endl;   //This is the error message
            cout << "HAVE ANOTHER GO!" << endl << endl;      
            cout << "- PRESS (1) TO SHOW REMAINING PLAYERS" << endl;        //This is the first option
            cout << "- PRESS (2) TO SHOW THE PLAYER/ROLE LIST" << endl;        //This is the second option
            cout << "- PRESS (3) THE PLAYERS THAT HAVE DIED" << endl;      //This is the third option
            cout << "- PRESS (4) TO SHOW THE MOST RECENT KILL" << endl << endl;        //This is the fourth option
            cin >> choice;    //Gets the user's choice
        }
    }

    switch(choice){
    case 1:
        cout << endl << "~~~ PLAYERS THAT ARE STILL IN THE GAME ~~~" << endl << endl;      //This is where I want to print the players
        printplayers();     //Calls the printplayers function
        cout << endl ;    //Prints a new line
        break;  //Breaks the switch statement
    case 2:
        cout << endl << "~~~ THIS IS THE PLAYER/ROLE LIST !! ~~~" << endl << endl;     //This is where I want to print the players and their roles
        printroles();       //Calls the printroles function
        break;      //Breaks the switch statement
    case 3:
        cout << endl << "~~~ R.I.P. TO THE PLAYERS BELOW ~~~" << endl << endl;      //This is where I want to print the players that have been killed
        for(int i=0; i<player.size(); i++)  //Using a for loop to print the players that have been killed
        {
            if(player[i].alive == false)        //If the player is dead
            {
                flag=1;             //Sets the flag to 1 to show that the player has been killed
                cout << "// PLAYER " << player[i].player_index << " //" << endl << endl ;   //Prints the player that has been killed
            }
        }
        if(flag==0) //If the flag is 0 then no one has been killed
        {
            cout << "NOBODY HAS DIED YET" << endl ;  //Prints a message to show that no one has been killed
        }
        break;
    case 4:
        if(lastkill == 0)       //If the last player that was killed is 0
        {
            cout << endl << "~~~ NOBODY HAS BEEN KILLED YET ~~~" << endl << endl;      //Prints a message to show that no one has been killed
            break;      //Breaks the switch statement
        }
        else{
            cout << endl << "~~~ THE MOST RECENT KILL WAS ~~~" << endl << endl;      //This is where I want to print the last player that was killed
            cout << "// PLAYER " << lastkill << " //" << endl << endl;   //Prints the last player that was killed
        }
        break;      //Breaks the switch statement
    default:
        cout << "OOPS YOU PRESSED: " << choice << endl << endl; //This is the error message
        cout << "HAVE ANOTHER GO" << endl << endl;      //Tells the user to try again
        break;      //Breaks the switch statement
    }
}

void nightphase()       //This is the function that will run the night phase
{
    int choice_g, choice_d;     //These are the variables that will store the choide of the gangster and the doctor

    cout << "~~~ NIGHT PHASE HAS STARTED ~~~" << endl << endl;      //Prints a message to show that the night phase has started
    cout << "SHH... THE GANGSTER IS PLAYER " << gangsterindex() + 1 << endl << endl;        //Reveals the gangster to the players
    cout << "THE GANGSTER IS COMING AFTER YOU!" << endl << endl;        //Cool message
    cout << "THE GANGSTER WANTS TO KILL PLAYER ";       //Prints a message to show that the gangster is coming after the player
    cin >> choice_g;    //Gets the user's choice
    cout << endl;       //Prints a new line

    try     //Tries a block of code
    {
        if(choice_g < 1 || choice_g > 7)        //If he enters a number that is not between 1 and 7
        {
            throw choice_g;     //Throws an error message
        }
        else if(player[choice_g - 1].alive == false)        //If the player is dead
        {
            throw choice_g;     //Throws an error message
        }
        else if(player[choice_g - 1].role == "GANGSTER")        //If the player is the Gangster
        {
            throw choice_g;     //Throws an error message
        }
    }
    catch(...)      //Catches the error
    {
        while(true)     
        {
            if(choice_g < 1 || choice_g > 7)        //If he enters a number that is not between 1 and 7
            {
                cout << "OOPS YOU CHOSE A PLAYER THAT DOESN'T EXIST: (PLAYER " << choice_g << ")"<<  endl;      //Prints the error message
                cout << "HAVE ANOTHER GO!" << endl << endl;     //Tells the user to try again
                cin >> choice_g;    //Gets the user's choice    
                cout << endl;           //Prints a new line
            }
            else if(player[choice_g - 1].alive == false)    //If the player is dead
            {
                cout << "YOU CAN NOT KILL A DEAD PLAYER!" << endl;   //Prints the error message
                cout << "HAVE ANOTHER GO!" << endl;    //Tells the user to try again
                cin >> choice_g;    //Gets the user's choice
                cout << endl;    //Prints a new line
            }
            else if(player[choice_g - 1].role == "GANGSTER")    //If the player is the Gangster
            {
                cout << "GANGSTER YOU CAN NOT SUICIDE." << endl << "FOR THE LOVE OF GOD...CHOOSE PLAYER ";      //Tells the gangster that he can not vote him self
                cin >> choice_g;    //Gets the users choice
                cout << endl;   //Prits a new line
            }
            else
            {
                break;  //Break the switch statement
            }
        }
    }

    for(int i=0; i<7; i++)      //This is a for loop that reveals who the doctor is
    {
        if (player[i].role == "DOCTOR")     //If the role of the player is doctor then,
        {
            cout << "THE DOCTOR IS PLAYER " << player[i].player_index << endl << endl ;     // Prints the index of the doctor
        }
    }

    if(player[doctorindex()].alive == true)     //If the Doctor is Alive
    {
        cout << "THE DOCTOR WANTS TO SAVE PLAYER ";     //Prints a message that prompts the user to input a player to save
        cin >> choice_d;        //Gets the input from the user
        cout << endl;       //Prints a new line (Just to make it Fancy :) )

        try     //This is a try block
        {
            if(player[choice_d - 1].role == "DOCTOR")       //If the player is the doctor
            {
                throw choice_d;     //Throws an error message
            }
        }
        catch(...)      //Catches the error
        {
            while(player[choice_d - 1].role == "DOCTOR")        //If the player is the doctor
            {
                cout << "DOCTOR YOU CAN NOT SAVE YOUR SELF." << endl;       //Prints that the doctor can not save him self
                cout << "HAVE ANOTHER GO!" << endl;     //Tells the user to try again
                cin >> choice_d;        //Gets the user's choice
                cout << endl;       //Prints a new line
            }
        }

        if(choice_g == choice_d && player[choice_d - 1].role != "DOCTOR")       //If the doctor saves the player that the gangster wants to kill
        {
            cout << "THE DOCTOR IS A LEGEND AND SAVED YOU!" << endl;        //Prints a message that the doctor saved the player
        }
        else        //If the doctor does not save the player
        {
            player[choice_g - 1].alive = false;     //Kills the player
            aliveplayers--;     //Decreases the number of alive players
            lastkill = choice_g;        //Stores the last kill
            if(player[choice_g - 1].role == "DOCTOR")       //If the player that the gangster killed is the doctor
            {
                cout << "THE GANGSTER KILLED THE DOCTOR " << endl;      //Prints a message that the gangster killed the doctor
            }
            else        //If the player that the gangster killed is not the doctor
            {
                cout << "THE GANGSTER JUST MURDERED PLAYER " << choice_g << endl;       //Prints a message that the gangster killed the player
            }
        }
    }
    
    else        //If the doctor is dead
    {
        player[choice_g - 1].alive = false;     //Kills the player that the gangster wants to kill
        aliveplayers--;     //Decreases the number of alive players by 1
        lastkill = choice_g;        //Stores the last kill in the variable lastkill
        cout << "OH NO THE DOCTOR IS DEAD! THE GANGSTER KILLED PLAYER " << choice_g << endl;        //Prints a message that the doctor is dead and the gangster killed the player
    }
}

void votingsystem2()        //If there is a tie in Voting system 1 then this gets called
{
    int choice;     //Stores the choice of the player
    int votes[7] = {0,0,0,0,0,0,0};    //Stores the number of votes for each player
    int max = 0;    //Stores the maximum number of votes
    int counter = 0;        //Stores the number of players that have the maximum number of votes
    int maxindex = 0;       //Stores the index of the player that has the maximum number of votes


    for(int i=0; i<7; i++)    //This is a for loop that prints the players that are alive and have not been equal voted      
    {
        if(player[i].alive == true && player[i].equal_voted == false)   //If the player is alive and has not been equal voted
        {
            cout << "PLAYER " << player[i].player_index << " VOTES FOR PLAYER ";    //Prints a message that prompts the user to input a player to vote for     
            cin >> choice;          //Gets the user's choice
            cout << endl;        //Prints a new line

            try     //This is a try block
            {
                if(choice < 1 || choice > 7)    //If the choice is not between 1 and 7
                {
                    throw choice;       //Throws an error message
                }
                else if(player[choice - 1].equal_voted == false)    //If the player that the user wants to vote for has not been equal voted
                {
                    throw choice;    //Throws an error message
                }
                else if(player[choice - 1].alive == false)  //If the player that the user wants to vote for is dead
                {
                    throw choice;   //Throws an error message
                }
                else    //If the player that the user wants to vote for is alive and has been equal voted
                {
                    votes[choice - 1]++;        //Increases the number of votes for the player that the user wants to vote for
                }
            }
            catch(...)    //Catches the error
            {
                while(true)    //This is a while loop
                {
                    if(choice < 1 || choice > 7)    //If the choice is not between 1 and 7     
                    {
                        cout << "OOPS YOU CHOSE A PLAYER THAT DOESN'T EXIST: (PLAYER " << choice << ")" << endl;    //Prints a message that the player does not exist 
                        cout << "HAVE ANOTHER GO!" << endl;     //Tells the user to try again 
                        cin >> choice;    //Gets the user's choice
                    }
                    else if(player[choice - 1].equal_voted == false )   //If the player that the user wants to vote for has not been equal voted
                    {
                        cout << "YOU CAN NOT VOTE FOR A PLAYER THAT HAS NOT BEEN EQUAL VOTED" << endl;  //Prints a message that the player has not been equal voted
                        cout << "HAVE ANOTHER GO!" << endl;    //Tells the user to try again
                        cin >> choice;  //Gets the user's choice
                    }
                    else if(player[choice - 1].alive == false)      //If the player that the user wants to vote for is dead
                    {
                        cout << "YOU CAN NOT VOTE FOR A DEAD PLAYER" << endl;       //Prints a message that the player is dead
                        cout << "HAVE ANOTHER GO!" << endl;     //Tells the user to try again
                        cin >> choice;      //Gets the user's choice
                    }
                    else    //If the player that the user wants to vote for is alive and has been equal voted
                    {
                        votes[choice - 1]++;    //Increases the number of votes for the player that the user wants to vote for          
                        break;    //Breaks the loop
                    }
                }
            }
        }
    }
    

    for(int i=0; i<7; i++)      //This is a for loop that finds the maximum number of votes
    {
        if(votes[i] > max)    //If the number of votes for the player is greater than the maximum number of votes
        {
            max = votes[i];    //Stores the number of votes for the player in the variable max
            maxindex = i;   //Stores the index of the player in the variable maxindex
        }
    }

    for(int i=0; i<7; i++)    //This is a for loop that finds the number of players that have the maximum number of votes
    {
        if(votes[i] == max)   //If the number of votes for the player is equal to the maximum number of votes
        {
            counter++;  //Increases the counter by 1 
        }
    }

    if(counter > 1 && counter < aliveplayers)   //If there is a tie and there are more than 1 player that have the maximum number of votes
    {
        cout << endl << "THERE IS A TIE BETWEEN: " << endl << endl;   //Prints a message that there is a tie between the players
        for(int i=0; i<7; i++)  //This is a for loop that prints the players that have the maximum number of votes
        {
            if(votes[i] == max)  //If the number of votes for the player is equal to the maximum number of votes
            {
                cout << "PLAYER " << i + 1 << endl;     //Prints the player that has the maximum number of votes
                player[i].equal_voted = true;   //Sets the equal voted variable of the player to true
            }
        }
        cout << endl << "THERE IS A TIE AGAIN AND NO ONE WILL BE KILLED" << endl;   //Prints that there is a tie again and no one will be killed.
    }
    else if(counter == aliveplayers)      //If all alive players have the same amount of votes
    {
        cout << endl << "ALL PLAYERS HAVE 1 VOTE. THERE IS A TIE AND NO ONE WILL BE KILLED."; //If all alive players have the same amount of votes then prints this message.  
    }
    else    
    {
        player[maxindex].alive = false;  //Make the player dead   
        aliveplayers--;     //Decrement the ammount of alive players by 1
        lastkill = maxindex + 1;    //Makes the last kill, the player wiwth most votes
        cout << endl << "PLAYER " << maxindex + 1 << " GOT MURDERED!";      //Prints  a message to show which player got killed
    }

    for(int i=0; i<7; i++)      //Using a for loop to make every players equal vote to be false
    {
        if(player[i].equal_voted == true)   //If a player has the variable equal voted = true
        {
            player[i].equal_voted = false;  //Make the variable = false
        }
    }
}

void votingsystem()     //This is the function wher the voting happens
{   
    int choice; //Initialises an int variable that holds the choice of the user    
    int votes[7] = {0,0,0,0,0,0,0};    //Stores the number of votes for each player
    int max = 0;    //Stores the maximum number of votes
    int counter = 0;        //Stores the number of players that have the maximum number of votes
    int maxindex = 0;       //Stores the index of the player that has the maximum number of votes


    for(int i=0; i<7; i++)  //This is a for loop that gets the user's choice
    {   
        if(player[i].alive == true) //If the player is alive
        {
            cout << "PLAYER " << player[i].player_index << " VOTES FOR PLAYER ";    //Prints a message that asks the user to choose a player to vote for 
            cin >> choice;  //Gets the user's choice
            cout << endl;   //Prints a new line

            try     //This is a try block
            {
                if(choice < 1 || choice > 7)    //If the choice is not between 1 and 7 
                {
                    throw choice;   //Throws the choice variable
                }
                else if(player[choice - 1].alive == false)  
                {
                    throw choice;   //Throws the choice variable    
                }
            }
            catch(...)  //This is a catch block
            {
                while(choice < 1 || choice > 7)     //If the choice is not between 1 and 7
                {
                    cout << "OOPS YOU CHOSE A PLAYER THAT DOESN'T EXIST: (PLAYER " << choice << ")" << endl;    //Prints a message that the player doesn't exist
                    cout << "HAVE ANOTHER GO!" << endl;   //Tells the user to try again
                    cin >> choice;  //Gets the user's choice
                    cout << endl;    //Prints a new line
                }
                while(player[choice - 1].alive == false)    //If the player that the user wants to vote for is dead
                {
                    cout << "YOU CAN NOT VOTE FOR A DEAD PLAYER" << endl;   //Prints a message that the player is dead
                    cout << "HAVE ANOTHER GO!" << endl ;    //Tells the user to try again
                    cin >> choice;  //Gets the user's choice
                    cout << endl;   //Prints a new line
                }
            }
            votes[choice - 1]++;    //Increases the number of votes for the player that the user wants to vote for  
        }
    }
    
    for(int i=0; i<7; i++)    //This is a for loop that finds the maximum number of votes
    {
        if(votes[i] > max)      //If the number of votes for the player is greater than the maximum number of votes
        {
            max = votes[i];     //Stores the number of votes for the player in the variable max
            maxindex = i;       //Stores the index of the player in the variable maxindex
        }
    }

    for(int i=0; i<7; i++)      //This is a for loop that finds the number of players that have the maximum number of votes
    {
        if(votes[i] == max)     //If the number of votes for the player is equal to the maximum number of votes
        {
            counter++;      //Increases the counter by 1
        }
    }

    if(counter > 1 && counter < aliveplayers)       //If there is a tie and there are more than 1 player that have the maximum number of votes
    {
        cout << endl << "THERE IS A TIE BETWEEN: " << endl << endl;     //Prints a message that there is a tie between the players
        for(int i=0; i<7; i++)      //This is a for loop that prints all the players that have a tie
        {
            if(votes[i] == max)     //If the player has the same amount of votes with the max votes
            {
                cout << "// PLAYER " << i + 1 << " //" << endl;     //Prints the player that has the maximum number of votes
                player[i].equal_voted = true;    //Sets the equal voted variable of the player to true
            }
        }
        cout << endl << "THE PLAYERS THAT WERE TIED WILL BE VOTED AGAIN!" << endl << endl;  //Prints that the players that were tied will be voted again
        votingsystem2();    //Calls the votingsystem2 function
        return;     
    }
    else if(counter == aliveplayers)    //If all the alive players have the same amount of votes
    {
        cout << endl << "ALL PLAYERS HAVE 1 VOTE AND NO ONE WILL BE KILLED.";   //Prints a message
        return;
    }
    else    //If there is no tie then kill the player with the most votes
    {
        player[maxindex].alive = false;     //Make the player state = Dead
        aliveplayers--;     //Decrement The amount of alive players by one
        lastkill = maxindex + 1;        //Assign the player to be the last player that was killed
        cout << "PLAYER " << maxindex + 1 << " GOT KILLED!" << endl;        //Prints who was killed from the voting
    }
    
}

void dayphase()     //This is the function of the day phase
{
    cout << endl << "~~~ DAY PHASE HAS STARTED ~~~" << endl << endl ;    //It prints that the day phase has started   

    votingsystem();     //It calls the voting system function
}

int main()  //This is the Main function of the program
{
        initialize();   //Calls the function to initialise the players
        

        while(aliveplayers>2 && player[gangsterindex()].alive == true)  //Run while the gangster is alive thre are more than 2 players alive
        {
            info_menu();        //Calls the info menu
            nightphase();       //Calls the night phase
            if(aliveplayers <= 2 && player[gangsterindex()].alive == true)  //If there are 2 or less players alive and the gangster is alive
            {
                break;    //Breaks the loop
            }
            else    //If there are more than 2 players alive and the gangster is alive
            {
            dayphase();    //Calls the day phase
            }
        }

        if(player[gangsterindex()].alive == false)  //If the gangster is dead then the town wins
        {
            cout << endl << endl << "~~~ THE GANGSTER WAS KILLED. THE TOWN WON THE GAME ~~~" << endl << endl;   //Prints that the gangster was killed and the town won the game 
            cout << "~~~ +-+-+-+-+ +-+-+-+-+ ~~~\n~~~ |G|A|M|E| |O|V|E|R| ~~~\n~~~ +-+-+-+-+ +-+-+-+-+ ~~~" << endl << endl;    //Prints the game over message 
            keep_window_open();
        }
        else if(aliveplayers <= 2 && player[gangsterindex()].alive == true) //If there are 2 or less players alive and the gangster is alive    
        {
            cout << endl << endl << "~~~ THE GANGSTER WON THE GAME ~~~" << endl << endl;    //Prints that the gangster won the game
            cout << "~~~ +-+-+-+-+ +-+-+-+-+ ~~~\n~~~ |G|A|M|E| |O|V|E|R| ~~~\n~~~ +-+-+-+-+ +-+-+-+-+ ~~~" << endl << endl;    //Prints the game over message
            keep_window_open();
        }
}