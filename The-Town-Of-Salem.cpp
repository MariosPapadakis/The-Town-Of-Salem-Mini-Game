/*READ_ME:
    TITLE: THE T0WN OF SALEM GAME
    AUTHOR: MARIOS PAPADAKIS
    DATE: 17/03/2023
    PURPOSE: TO CREATE A GAME SIMILAR TO THE TOWN OF SALEM
    VERSION: 2.0 */
/*DESCRIPTION: 

    IN THIS GAME THERE ARE 7 PLAYERS WHO EACH HAVE A ROLE.
    THE ROLES ARE:
        1) CITIZEN 
        2) DOCTOR 
        3) GANGSTER.
    AT THE BEGINNING OF THE GAME THE PLAYERS ARE INITIALLIZED FROM A .TXT FILE THAT 
    CONTAINS THE PLAYERS (USERNAME,ROLE) THE GAME IS DIVIDED INTO 2 PHASES, NIGHT AND DAY.

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

#include "player/player.h"

int aliveplayers = 100; //This is a variable that stores the number of players that are alive
int lastkill = 0;   //This is a variable that stores the last player that was killed
int x=0;        //This is a variable that stores the number of players
int votekill;       //This is a variable that stores the index of the player that was voted to leave
int gangkill;       //This is a variable that stores the index of the player that was killed by the gangster
int INDEXROUND;         //This is a variable that stores the index of the round that is currently being played

vector<Player> player;     //This is a vector that stores the players

vector<Round> rd;    //This is a vector that stores the rounds

int doctorindex()   //This is a function that returns the index of the doctor
{
    for(int i=0; i<x; i++)  //Using a for loop to find the index of the doctor
    {
        if (player[i].getrole() == "DOCTOR")     //If the role of the player is equal to doctor
        {
            return player[i].getindex()-1;   //Return the index of the player
        }
    }
    return 0;   //Return 0 if the player is not found
}

int gangsterindex()    //This is a function that returns the index of the gangster
{
    for(int i=0; i<x; i++)  //Using a for loop to find the index of the gangster
    {
        if (player[i].getrole() == "GANGSTER")   //If the role of the player is equal to gangster
        {
            return player[i].getindex()-1;   //Return the index of the player
        }
    }
    return 0;   //Return 0 if the player is not found
}

void MakeFile()     //This is a function that creates a file and prints the information of the game
{
    ofstream Myfile("TownOfSalem_output.txt"); //Creates a file called TownOfSalem_output.txt
    Myfile << endl << ">>> THIS IS AN OVERVIEW OF THE GAME! <<<" << endl  ; 
    Myfile << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    Myfile << "- THE NUMBER OF PLAYERS IN THE GAME: " << x << endl;    //Prints the number of players
    Myfile << "- THE NUMBER OF ROUNDS: " << INDEXROUND+1 << endl;    //Prints the number of rounds
    Myfile << "- THE GANGSTER'S NAME: " << player[gangsterindex()].getname() << endl;    //Prints the name of the gangster
    Myfile << "- THE DOCTOR'S NAME: " << player[doctorindex()].getname() << endl;    //Prints the name of the doctor
    Myfile << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
    for(int i=0; i<INDEXROUND+1;i++)
    {
        Myfile << "/// ROUND " << rd[i].getround() << " ///" << endl << endl;
        Myfile << "THE GANGSTER KILLED: " << rd[i].getgangsterkill() << endl << endl;    //Prints who the gangster killed last night
        Myfile << "THE TOWN VOTED TO KILL: " << rd[i].getvotekill() << endl << endl;    //Prints who the town voted to kill last night
    }
    if(player[gangsterindex()].getalive() == false)     //If the gangster is dead then the town won the game
    {
        Myfile << endl << ">>> THE GANGSTER WAS KILLED. THE TOWN WON THE GAME <<<" << endl << endl;     //Prints that the town won the game
    }
    else if(aliveplayers <= 2 && player[gangsterindex()].getalive() == true)        //If the number of alive players is less than or equal to 2 and the gangster is alive then the gangster won the game
    {
        Myfile << endl << ">>> THE GANGSTER WON THE GAME <<<" << endl << endl;      //Prints that the gangster won the game 
    }
    
    Myfile << "~~~ +-+-+-+-+ +-+-+-+-+ ~~~\n~~~ |G|A|M|E| |O|V|E|R| ~~~\n~~~ +-+-+-+-+ +-+-+-+-+ ~~~" << endl << endl;
    Myfile.close();     //Closes the file
}

void initialize()   //This function initialises the players
{

    ifstream myfile;        //This is a variable that stores the file that we are going to read
    myfile.open("Players.txt");     //Open the file 

    if ( myfile.is_open() )     //If the file is open 
    {
        string my;      //This is a variable that stores the line that we are going to read
        string onoma;       //This is a variable that stores the name of the player
        string rolos;       //This is a variable that stores the role of the player

        int i = 0;      //This is the index of the player 
        while ( myfile >> onoma >> rolos)       //While we are reading the file 
        {
            my = myfile.get();      //Get the line
            player.push_back(Player(onoma,true,rolos,i));       //Add the player to the vector with the name, alive, role and index
            i++;        //Increment the index
        }

        aliveplayers = i;       //Sets the number of alive players to the number of players
        x=i;        //Sets the number of total players to x
    }
    else
    {
        cout << "Couldn't open file!";      //If the file is not open, print this message
    }
    
    for(int i=0;i<x;i++)        //Using a for loop to add the rounds to the vector
    {
        rd.push_back(Round());      //Add a round to the vector
    }

    myfile.close();     //Close the file

}

void printplayers()    //This is a function that prints the players
{
    for(int i=0; i<player.size(); i++)  // Using a for loop to print the players
    {   
        if(player[i].getalive() == true)    //If the player is alive
        {   
            cout << "// PLAYER " << player[i].getindex() << " ("<< player[i].getname() << ") //" << endl;    //Print the player
        }
    }
}

void printroles()   //This is a function that prints the players and their roles
{
    for(int i=0; i<player.size(); i++)  //Using a for loop to print the players and their roles
    {
        if(player[i].getalive() == true)   //If the player is alive
        {
            cout << "// PLAYER " << player[i].getindex() << " ("<< player[i].getname() << ")  IS A " << player[i].getrole() << " //" << endl;  //Print the player and their role
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
            cout << "TRY AGAIN!" << endl << endl;        //This is the error message
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
        cout << endl <<"THERE ARE: "<< aliveplayers << " ALIVE" << endl;
        cout << endl ;    //Prints a new line
        break;  //Breaks the switch statement
    case 2:
        cout << endl << "~~~ THIS IS THE PLAYER/ROLE LIST !! ~~~" << endl << endl;     //This is where I want to print the players and their roles
        printroles();       //Calls the printroles function
        cout << "THERE ARE: "<< aliveplayers << " ALIVE" << endl << endl;
        break;      //Breaks the switch statement
    case 3:
        cout << endl << "~~~ R.I.P. TO THE PLAYERS BELOW ~~~" << endl << endl;      //This is where I want to print the players that have been killed
        for(int i=0; i<player.size(); i++)  //Using a for loop to print the players that have been killed
        {
            if(player[i].getalive() == false)        //If the player is dead
            {
                flag=1;             //Sets the flag to 1 to show that the player has been killed
                cout << "// PLAYER " << player[i].getindex() << " (" << player[i].getname() << ") " << " //" << endl << endl;     //Prints the player that has been killed
            }
        }
        if(flag==1)     //If the flag is 1 then someone has been killed and the number of alive players is printed
        {
            cout << "THERE ARE: "<< aliveplayers << " ALIVE" << endl << endl;       
        }
        if(flag==0) //If the flag is 0 then no one has been killed
        {
            cout << "NOBODY HAS DIED YET" << endl << endl;  //Prints a message to show that no one has been killed
            cout << "THERE ARE: "<< aliveplayers << " ALIVE" << endl << endl;       //Prints the number of alive players
        }
        break;
    case 4:
        if(lastkill == 0)       //If the last player that was killed is 0
        {
            cout << endl << "~~~ NOBODY HAS BEEN KILLED YET ~~~" << endl << endl;      //Prints a message to show that no one has been killed
            cout << "THERE ARE: "<< aliveplayers << " ALIVE" << endl << endl;       //Prints the number of alive players
            break;      //Breaks the switch statement
        }
        else{
            cout << endl << "~~~ THE MOST RECENT KILL WAS ~~~" << endl << endl;      //This is where I want to print the last player that was killed
            cout << "// PLAYER " << lastkill << " (" << player[lastkill-1].getname() << ") //" << endl << endl;      //Prints the last player that was killed
            cout << "THERE ARE:  "<< aliveplayers << " ALIVE" << endl << endl;      //Prints the number of alive players
        }
        break;      //Breaks the switch statement
    default:
        cout << "OOPS YOU PRESSED: " << choice << endl << endl; //This is the error message
        cout << "TRY AGAIN! ";      //Tells the user to try again
        break;      //Breaks the switch statement
    }
}

void nightphase()       //This is the function that will run the night phase
{
    int choice_g, choice_d;     //These are the variables that will store the choide of the gangster and the doctor

    cout << "~~~ NIGHT PHASE HAS STARTED ~~~" << endl << endl;      //Prints a message to show that the night phase has started
    cout << "SHH... THE GANGSTER IS PLAYER " << gangsterindex() + 1 << " (" << player[gangsterindex()].getname() << ")" << endl << endl;      //Prints a message to show that the gangster is coming after the player
    cout << "THE GANGSTER IS COMING AFTER YOU!" << endl << endl;        //Cool message
    cout << "THE GANGSTER WANTS TO KILL PLAYER ";       //Prints a message to show that the gangster is coming after the player
    cin >> choice_g;    //Gets the user's choice
    cout << endl;       //Prints a new line

    try     //Tries a block of code
    {
        if(choice_g < 1 || choice_g > x)        //If he enters a number that is not between 1 and 7
        {
            throw choice_g;     //Throws an error message
        }
        else if(player[choice_g - 1].getalive() == false)        //If the player is dead
        {
            throw choice_g;     //Throws an error message
        }
        else if(player[choice_g - 1].getrole() == "GANGSTER")        //If the player is the Gangster
        {
            throw choice_g;     //Throws an error message
        }
    }
    catch(...)      //Catches the error
    {
        while(true)     
        {
            if(choice_g < 1 || choice_g > x)        //If he enters a number that is not between 1 and 7
            {
                cout << "OOPS YOU CHOSE A PLAYER THAT DOESN'T EXIST: (PLAYER " << choice_g << ")"<<  endl;      //Prints the error message
                cout << "KILL PLAYER ";     //Tells the user to try again
                cin >> choice_g;    //Gets the user's choice    
                cout << endl;           //Prints a new line
            }
            else if(player[choice_g - 1].getalive() == false)    //If the player is dead
            {
                cout << "YOU CAN NOT KILL A DEAD PLAYER!" << endl;   //Prints the error message
                cout << "KILL PLAYER ";    //Tells the user to try again
                cin >> choice_g;    //Gets the user's choice
                cout << endl;    //Prints a new line
            }
            else if(player[choice_g - 1].getrole() == "GANGSTER")    //If the player is the Gangster
            {
                cout << "GANGSTER YOU CAN NOT SUICIDE." << endl << "FOR THE LOVE OF GOD...CHOOSE PLAYER ";      //Tells the gangster that he can not vote him self
                cin >> choice_g;    //Gts the users choice
                cout << endl;   //Prits a new line
            }
            else
            {
                break;  //Break the switch statement
            }
        }
    }

    for(int i=0; i<x; i++)      //This is a for loop that reveals who the doctor is
    {
        if (player[i].getrole() == "DOCTOR")     //If the role of the player is doctor then,
        {
            cout << "THE DOCTOR IS PLAYER " << player[i].getindex() << " ("<< player[i].getname() << ")" << endl << endl ;     // Prints the index of the doctor
        }
    }

    if(player[doctorindex()].getalive() == true)     //If the Doctor is Alive
    {
        cout << "THE DOCTOR WANTS TO SAVE PLAYER ";     //Prints a message that prompts the user to input a player to save
        cin >> choice_d;        //Gets the input from the user
        cout << endl;       //Prints a new line (Just to make it Fancy :) )

        try     //This is a try block
        {
            if(choice_d < 1 || choice_d > x)
            {
                throw choice_d;
            }
            else if(player[choice_d - 1].getrole() == "DOCTOR")       //If the player is the doctor
            {
                throw choice_d;     //Throws an error message
            }
        }
        catch(...)      //Catches the error
        {
            while(true)
            {
                if(choice_d < 1 || choice_d > x)
                {
                    cout << "OOPS... DOCTOR TRIED TO CURE A PLAYER THAT DOESN'T EXIST: (PLAYER " << choice_d<< ")"<<  endl;      //Prints the error message
                    cout << "CURE PLAYER ";     //Tells the user to try again
                    cin >> choice_d;    //Gets the user's choice    
                    cout << endl;           //Prints a new line
                }
                else if(player[choice_d - 1].getrole() == "DOCTOR")        //If the player is the doctor
                {
                    cout << "DOCTOR, YOU CAN NOT SAVE YOUR SELF." << endl;       //Prints that the doctor can not save him self
                    cout << "CURE PLAYER ";     //Tells the user to try again
                    cin >> choice_d;        //Gets the user's choice
                    cout << endl;       //Prints a new line
                }
                else
                {
                    break;    
                }
            }
        }

        if(choice_g == choice_d && player[choice_d - 1].getrole() != "DOCTOR")       //If the doctor saves the player that the gangster wants to kill
        {
            cout << "THE DOCTOR IS A LEGEND AND SAVED PLAYER " << choice_d << " (" << player[choice_d-1].getname() << ")" << endl;        //Prints a message that the doctor saved the player
            gangkill = -1;      //Sets the variable gangkill to -1 to show that the gangster did not kill anyone
        }
        else        //If the doctor does not save the player
        {
            player[choice_g - 1].setalive(false);     //Kills the player
            aliveplayers--;     //Decreases the number of alive players
            lastkill = choice_g;        //Stores the last kill
            gangkill = choice_g - 1;        //Stores the last kill in the variable gangkill
            if(player[choice_g - 1].getrole() == "DOCTOR")       //If the player that the gangster killed is the doctor
            {
                cout << "THE GANGSTER KILLED THE DOCTOR (PLAYER " << doctorindex() << ") " << endl;      //Prints a message that the gangster killed the doctor
            }
            else        //If the player that the gangster killed is not the doctor
            {
                cout << "THE GANGSTER JUST MURDERED PLAYER " << choice_g << " (" << player[choice_g-1].getname() << ")" << endl;       //Prints a message that the gangster killed the player
            }
        }
    }
    
    else        //If the doctor is dead
    {
        player[choice_g - 1].setalive(false);     //Kills the player that the gangster wants to kill
        aliveplayers--;     //Decreases the number of alive players by 1
        lastkill = choice_g;        //Stores the last kill in the variable lastkill
        gangkill = choice_g - 1;        //Stores the last kill in the variable gangkill
        cout << "OH NO THE DOCTOR IS DEAD! THE GANGSTER KILLED PLAYER " << choice_g << " (" << player[choice_g-1].getname() << ")" << endl;    //Prints a message that the doctor is dead and the gangster killed the player
    } 
}

void votingsystem2()        //If there is a tie in Voting system 1 then this gets called
{
    int choice;     //Stores the choice of the player
    int max = 0;    //Stores the maximum number of votes
    int counter = 0;        //Stores the number of players that have the maximum number of votes
    int maxindex = 0;       //Stores the index of the player that has the maximum number of votes

    for(int i=0; i<x; i++)  //This is a for loop that makes the votes array equal to 0
    {
        player[i].setcurrentvotes(0);   //Makes the votes array equal to 0
    }

    for(int i=0; i<x; i++)    //This is a for loop that prints the players that are alive and have not been equal voted      
    {
        if(player[i].getalive() == true && player[i].getequal() == false)   //If the player is alive and has not been equal voted
        {
            cout << "PLAYER " << player[i].getindex() << " (" << player[i].getname() << ")" << " VOTES FOR PLAYER ";    //Prints a message that asks the user to choose a player to vote for      
            cin >> choice;          //Gets the user's choice
            cout << endl;        //Prints a new line

            try     //This is a try block
            {
                if(choice < 1 || choice > x)    //If the choice is not between 1 and 7
                {
                    throw choice;       //Throws an error message
                }
                else if(player[choice - 1].getequal() == false)    //If the player that the user wants to vote for has not been equal voted
                {
                    throw choice;    //Throws an error message
                }
                else if(player[choice - 1].getalive() == false)  //If the player that the user wants to vote for is dead
                {
                    throw choice;   //Throws an error message
                }
                else    //If the player that the user wants to vote for is alive and has been equal voted
                {
                    player[choice - 1].incrementvotes();        //Increases the number of votes for the player that the user wants to vote for
                }
            }
            catch(...)    //Catches the error
            {
                while(true)    //This is a while loop
                {
                    if(choice < 1 || choice > x)    //If the choice is not between 1 and 7     
                    {
                        cout << "OOPS YOU CHOSE A PLAYER THAT DOESN'T EXIST: (PLAYER " << choice << ")" << endl;    //Prints a message that the player does not exist 
                        cout << "TRY TO VOTE PLAYER ";     //Tells the user to try again 
                        cin >> choice;    //Gets the user's choice
                        cout << endl;   //Prints a new line
                    }
                    else if(player[choice - 1].getequal() == false )   //If the player that the user wants to vote for has not been equal voted
                    {
                        cout << "YOU CAN NOT VOTE FOR A PLAYER THAT HAS NOT BEEN EQUAL VOTED" << endl;  //Prints a message that the player has not been equal voted
                        cout << "TRY TO VOTE PLAYER ";    //Tells the user to try again
                        cin >> choice;  //Gets the user's choice
                        cout << endl;   //Prints a new line
                    }
                    else if(player[choice - 1].getalive() == false)      //If the player that the user wants to vote for is dead
                    {
                        cout << "YOU CAN NOT VOTE FOR A DEAD PLAYER" << endl;       //Prints a message that the player is dead
                        cout << "TRY TO VOTE PLAYER ";     //Tells the user to try again
                        cin >> choice;      //Gets the user's choice
                        cout << endl;       //Prints a new line
                    }
                    else    //If the player that the user wants to vote for is alive and has been equal voted
                    {
                        player[choice - 1].incrementvotes();    //Increases the number of votes for the player that the user wants to vote for          
                        break;    //Breaks the loop
                    }
                }
            }
        }
    }
    

    for(int i=0; i<x; i++)      //This is a for loop that finds the maximum number of votes
    {
        if(player[i].getcurrentvotes() > max)    //If the number of votes for the player is greater than the maximum number of votes
        {
            max = player[i].getcurrentvotes();    //Stores the number of votes for the player in the variable max
            maxindex = i;   //Stores the index of the player in the variable maxindex
        }
    }

    for(int i=0; i<x; i++)    //This is a for loop that finds the number of players that have the maximum number of votes
    {
        if(player[i].getcurrentvotes() == max)   //If the number of votes for the player is equal to the maximum number of votes
        {
            counter++;  //Increases the counter by 1 
        }
    }

    if(counter > 1 && counter < aliveplayers)   //If there is a tie and there are more than 1 player that have the maximum number of votes
    {
        cout << endl << "THERE IS A TIE BETWEEN: " << endl << endl;   //Prints a message that there is a tie between the players
        for(int i=0; i<x; i++)  //This is a for loop that prints the players that have the maximum number of votes
        {
            if(player[i].getcurrentvotes() == max)  //If the number of votes for the player is equal to the maximum number of votes
            {
                cout << " // PLAYER " << player[i].getindex() << " (" << player[i].getname() << ") " << " //" << endl;     //Prints the player that has the maximum number of votes
                player[i].setequal(true);   //Sets the equal voted variable of the player to true
            }
        }
        cout << endl << "THERE IS A TIE AGAIN AND NO ONE WILL BE KILLED" << endl;   //Prints that there is a tie again and no one will be killed.
        votekill=-1;        
    }
    else if(counter == aliveplayers)      //If all alive players have the same amount of votes
    {
        cout << endl << "ALL PLAYERS HAVE 1 VOTE. THERE IS A TIE AND NO ONE WILL BE KILLED." << endl; //If all alive players have the same amount of votes then prints this message.  
        votekill=-1;        //Sets the votekill variable to -1
    }
    else    
    {
        player[maxindex].setalive(false);  //Make the player dead   
        aliveplayers--;     //Decrement the ammount of alive players by 1
        lastkill = maxindex + 1;    //Makes the last kill, the player wiwth most votes
        votekill = maxindex;        
        cout << "PLAYER " << maxindex + 1 << " (" << player[maxindex].getname() << ")" << " GOT MURDERED WITH " << player[maxindex].getcurrentvotes() << " VOTES!" << endl;      //Prints  a message to show which player got killed
    }

    for(int i=0; i<x; i++)      //Using a for loop to make every players equal vote to be false
    {
        if(player[i].getequal() == true)   //If a player has the variable equal voted = true
        {
            player[i].setequal(false);  //Make the variable = false
        }
    }
}

void votingsystem()     //This is the function wher the voting happens
{   
    int choice; //Initialises an int variable that holds the choice of the user    
    int max = 0;    //Stores the maximum number of votes
    int counter = 0;        //Stores the number of players that have the maximum number of votes
    int maxindex = 0;       //Stores the index of the player that has the maximum number of votes

    for(int i=0; i<x; i++)  //This is a for loop that makes the votes array equal to 0
    {
        player[i].setcurrentvotes(0);   //Makes the votes array equal to 0
    }

    for(int i=0; i<x; i++)  //This is a for loop that gets the user's choice
    {   
        if(player[i].getalive() == true) //If the player is alive
        {
            cout << "PLAYER " << player[i].getindex() << " (" << player[i].getname() << ")" << " VOTES FOR PLAYER ";    //Prints a message that asks the user to choose a player to vote for 
            cin >> choice;  //Gets the user's choice
            cout << endl;   //Prints a new line

            try     //This is a try block
            {
                if(choice < 1 || choice > x)    //If the choice is not between 1 and 7 
                {
                    throw choice;   //Throws the choice variable
                }
                else if(player[choice - 1].getalive() == false)  
                {
                    throw choice;   //Throws the choice variable    
                }
            }
            catch(...)  //This is a catch block
            {
                while(choice < 1 || choice > x)     //If the choice is not between 1 and 7
                {
                    cout << "OOPS YOU CHOSE A PLAYER THAT DOESN'T EXIST: PLAYER " << choice << endl;    //Prints a message that the player doesn't exist
                    cout << "TRY TO VOTE PLAYER ";   //Tells the user to try again
                    cin >> choice;  //Gets the user's choice
                    cout << endl;    //Prints a new line
                }
                while(player[choice - 1].getalive() == false)    //If the player that the user wants to vote for is dead
                {
                    cout << "YOU CAN NOT VOTE FOR A DEAD PLAYER: PLAYER " << choice << endl;   //Prints a message that the player is dead
                    cout << "TRY TO VOTE PLAYER ";    //Tells the user to try again
                    cin >> choice;  //Gets the user's choice
                    cout << endl;   //Prints a new line
                }
            }
            player[i].vote(player[choice-1]);    //Increases the number of votes for the player that the user wants to vote for  
        }
    }
    
    for(int i=0; i<x; i++)    //This is a for loop that finds the maximum number of votes
    {
        if(player[i].getcurrentvotes() > max)      //If the number of votes for the player is greater than the maximum number of votes
        {
            max = player[i].getcurrentvotes();     //Stores the number of votes for the player in the variable max
            maxindex = i;       //Stores the index of the player in the variable maxindex
        }
    }

    for(int i=0; i<x; i++)      //This is a for loop that finds the number of players that have the maximum number of votes
    {
        if(player[i].getcurrentvotes() == max)     //If the number of votes for the player is equal to the maximum number of votes
        {
            counter++;      //Increases the counter by 1
        }
    }

    if(counter > 1 && counter < aliveplayers)       //If there is a tie and there are more than 1 player that have the maximum number of votes
    {
        cout << endl << "THERE IS A TIE BETWEEN: " << endl << endl;     //Prints a message that there is a tie between the players
        for(int i=0; i<x; i++)      //This is a for loop that prints all the players that have a tie
        {
            if(player[i].getcurrentvotes() == max)     //If the player has the same amount of votes with the max votes
            {
                cout << "// PLAYER " << i + 1 << " (" << player[i].getname() << ") " << " //" << endl;     //Prints the player that has the maximum number of votes
                player[i].setequal(true);    //Sets the equal voted variable of the player to true
            }
        }
        cout << endl << "THE PLAYERS THAT WERE TIED WILL BE VOTED AGAIN!" << endl << endl;  //Prints that the players that were tied will be voted again
        votingsystem2();    //Calls the votingsystem2 function
        return;     
    }
    else if(counter == aliveplayers)    //If all the alive players have the same amount of votes
    {
        cout << endl << "ALL PLAYERS HAVE 1 VOTE AND NO ONE WILL BE KILLED.";   //Prints a message
        votekill = -1;
        return;
    }
    else    //If there is no tie then kill the player with the most votes
    {
        player[maxindex].setalive(false);     //Make the player state = Dead
        aliveplayers--;     //Decrement The amount of alive players by one
        lastkill = maxindex + 1;        //Assign the player to be the last player that was killed
        cout << "PLAYER " << maxindex + 1 << " (" << player[maxindex].getname() <<  ") GOT KILLED WITH " << player[maxindex].getcurrentvotes() << " VOTES!" << endl << endl;
        votekill = maxindex;
    }
    
}

void dayphase()     //This is the function of the day phase
{
    cout << endl << "~~~ DAY PHASE HAS STARTED ~~~" << endl << endl ;    //It prints that the day phase has started   

    votingsystem();     //It calls the voting system function
}

int main()  //This is the Main function of the program
{
    initialize();
    int i=0;
    while(aliveplayers>2 && player[gangsterindex()].getalive() == true)  //Run while the gangster is alive thre are more than 2 players alive
    {
        rd[i].setround(i+1);    //Sets the round number
        INDEXROUND = i;     //Stores the index of the round in the variable INDEXROUND
        info_menu();        //Calls the info menu   
        nightphase();       //Calls the night phase
        if(gangkill==-1)
        {
            rd[i].setgangsterkill(" --- ");    //Stores the name of the player that was killed in the round class
        }
        else
        {
            rd[i].setgangsterkill(player[gangkill].getname());    //Stores the name of the player that was killed in the round class
        }
        if(aliveplayers <= 2 && player[gangsterindex()-1].getalive() == true)  //If there are 2 or less players alive and the gangster is alive
        {
            break;    //Breaks the loop
        }
        else    //If there are more than 2 players alive and the gangster is alive
        {
            dayphase();    //Calls the day phase
            if(votekill==-1)
            {
                rd[i].setvotekill(" --- ");
            }
            else
            {
                rd[i].setvotekill(player[votekill].getname());    //Stores the name of the player that was killed in the round class
            }
        }

        cout << endl << "ROUND " << rd[i].getround() << " HAS ENDED!" << endl << endl;    //Prints that the round has ended
        cout << endl << "THE GANGSTER KILLED: " << rd[i].getgangsterkill() << endl << endl;    //Prints who the gangster killed last night
        cout << endl << "THE TOWN VOTED TO KILL: " << rd[i].getvotekill()  << endl << endl;    //Prints who the town voted to kill last night
        i++;    //Increments the round number
    }

    
    if(player[gangsterindex()].getalive() == false)  //If the gangster is dead then the town wins
    {
        cout << endl << endl << ">>> THE GANGSTER WAS KILLED. THE TOWN WON THE GAME <<<" << endl << endl;   //Prints that the gangster was killed and the town won the game 
        cout << "~~~ +-+-+-+-+ +-+-+-+-+ ~~~\n~~~ |G|A|M|E| |O|V|E|R| ~~~\n~~~ +-+-+-+-+ +-+-+-+-+ ~~~" << endl << endl;    //Prints the game over message 
        
        MakeFile();

        keep_window_open();         //Keeps the window open until the user presses a key
    }
    else if(aliveplayers <= 2 && player[gangsterindex()].getalive() == true) //If there are 2 or less players alive and the gangster is alive    
    {
        cout << endl << endl << ">>> THE GANGSTER WON THE GAME <<<" << endl << endl;    //Prints that the gangster won the game
        cout << "~~~ +-+-+-+-+ +-+-+-+-+ ~~~\n~~~ |G|A|M|E| |O|V|E|R| ~~~\n~~~ +-+-+-+-+ +-+-+-+-+ ~~~" << endl << endl;    //Prints the game over message

        MakeFile();

        keep_window_open();     //Keeps the window open until the user presses a key
    }
}