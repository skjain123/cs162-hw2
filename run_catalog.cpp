/******************************************************
** Program: run_catalog.cpp
** Author: Sunil Jain
** Date: 10/30/2023
** Description: This is a program that searches through a user-specified database file 
**              that stores basketball teams and players from the BBA
** Input: name of the file to read from, file, selection (1-4), team name, player nationality, selection (1-2), 
**        the name of the file to write to.
** Output: Team and player information based on the user's search parameters, writing to a file or to the console... 
******************************************************/

#ifndef DEFINED
#define DEFINED

#include "catalog.cpp"
#include "catalog.h"

using namespace std;

int main() {
    Team* team_array; //store all arrays
    int team_num;

    team_array = open_file(&team_num); //fill the array and make it dynamic

    int choice_num;

    bool play = true; //does the player want to exit
    while (play) search_selections(&choice_num, team_array, team_num, &play); // give the player options on what to do
    delete_info(team_array, team_num); //delete the dynamic arrays
    
    return 0;
}

#endif