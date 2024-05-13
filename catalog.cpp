#ifndef DEFINED
#define DEFINED

#include "catalog.h"
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

Team* create_teams(int size) {
    return new Team[size];
}

Player* create_players(int size) {
    return new Player[size];
}

void populate_player_data(Player* players, int num_player, ifstream& fin) { //pulling player data
    for (int j = 0; j < num_player; j++) 
        fin >> players[j].name >> players[j].age >> players[j].nation >> players[j].ppg >> players[j].fg;
}

void populate_team_data(Team* array, int size, ifstream& fin) { //pulling team data
    for (int i = 0; i < size; i++) {
        fin >> array[i].name >> array[i].owner >> array[i].market_value >> array[i].num_player;

        array[i].p = create_players(array[i].num_player);
        populate_player_data(array[i].p, array[i].num_player, fin);
    }
}

bool isNum(string input, int len) {
    for (int i = 0; i < len; i++) {
        if (!isdigit(input.at(i))) return false; //is entire user input a digit?
    }

    return true;
}

bool search_input(int* choice_num, string prompt, int lower, int upper) {
    string choice;

    cout << prompt;
    cin >> choice;
    
    if (isNum(choice, choice.length())) { //if the input is a digit, convert it to a number
        *choice_num = stoi(choice);
    } else return false;

    //if user input is not within the upper/lower limits its bad
    if (!(lower <= *choice_num && *choice_num <= upper)) return false;

    return true;
}

string team_by_name(Team* array, int size) {
    string name_input;
    string output = "";

    cout << endl << "Enter the team name you want to search for: "; //get name from user
    cin >> name_input;

    bool found = false;

    for (int i = 0; i < size; i++) {
        if (array[i].name == name_input) { //if a team name matches the input then pull that team's information
            found = true;
            output += "Team: "+array[i].name+" "+array[i].owner+" "+to_string(array[i].market_value)+" "+to_string(array[i].num_player)+"\n";
            for (int j = 0; j < array[i].num_player; j++) output += "Player "+ to_string(j+1)+": "+array[i].p[j].name+" "+to_string(array[i].p[j].age)+" "+array[i].p[j].nation+" "+to_string(array[i].p[j].ppg)+" "+to_string(array[i].p[j].fg)+"\n";
        }
    }

    if (!found) { //if no teams had that name, then print error message and notify to not output
        cout << "No teams by that name found!" << endl;
        return "-1";
    }
    return output;
}

string team_top_scorer(Team* array, int size) {
    string output;

    float high_score; //keep track of high score
    string high_name;
    for (int i = 0; i < size; i++) {
        
        //for each team, initialize the first player's score and name
        high_score = array[i].p[0].ppg;
        high_name = array[i].p[0].name;

        for (int j = 0; j < array[i].num_player; j++) {
            if (high_score < array[i].p[j].ppg) { //if theres a player with a higher score then replace it
                high_score = array[i].p[j].ppg;
                high_name = array[i].p[j].name;
            }
        }
        output += array[i].name+": "+high_name+" "+to_string(high_score)+"\n"; //build output for each team
    }
    return output;
}

string player_by_nationality(Team* array, int size) {
    string output;

    string nationality;
    cout << "Enter the nationality you want to search by: ";
    cin >> nationality; //get user input for nationality search

    bool found;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < array[i].num_player; j++) {
            if (array[i].p[j].nation == nationality) { //for each team's player check if their nationality matches
                output += array[i].p[j].name+" "+to_string(array[i].p[j].age)+" "+array[i].p[j].nation+" "+to_string(array[i].p[j].ppg)+" "+to_string(array[i].p[j].fg)+"\n";
                found = true; //if so then pull player information
            }
        }
    }
    if (!found) { //if no player has that nationality then print error message and notify to not output
        cout << "No player by that nationality found!" << endl;
        return "-1";
    }
    return output;
}

void delete_info(Team* array, int size) {
    for (int i = 0; i < size; i++) delete [] array[i].p; //delete the player arrays
    delete[] array; //delete the actual team array
}

Team* open_file(int *team_num) {
    ifstream fin;
    string file_name;
    Team* array;

    do { //check if the inputted file name exists in dir if not then print error message and reprompt
        cout << "Please enter the name of the file you would like to read from: "; //user input (requires .txt)
        cin >> file_name;

        fin.open(file_name);

        if (!fin.is_open()) cout << "Error opening file type in a different file name: " << endl;
        
    } while (!fin.is_open());

    fin >> *team_num; //get # of teams
    array = create_teams(*team_num); //create dynamic array
    populate_team_data(array, *team_num, fin); //fill that array with data from the file
    
    fin.close(); //close the file

    return array; // return the filled array
}

string choices_1(Team* team_array, int team_num, int choice_num, bool* play) {
    if (choice_num == 1) {
        return team_by_name(team_array, team_num);
    } else if (choice_num == 2) {
        return team_top_scorer(team_array, team_num);
    } else if (choice_num == 3) {
        return player_by_nationality(team_array, team_num);
    } else if (choice_num == 4) {
        *play = false; //end program loop in run_catalog.cpp
    } else cout << endl << "Invalid input, please input a number between 1-4." << endl;
    return "";
}

void choices_2(int choice_num, string output) {
    if (choice_num == 1) { //print to console
        cout << endl << output << endl;
    } else if (choice_num == 2) { //print to file
        string output_name;
        cout << endl << "Please enter the name of the file you would like to print to: ";
        cin >> output_name; //get output file name

        ofstream fout;
        fout.open(output_name, ios::app); //open file (appends if it doesnt exist)
        fout << output << "\n"; //send information to that file
        fout.close();
        
    } else cout << endl << "Invalid input, please input a number between 1-2." << endl; //error message

}

void search_selections(int* choice_num, Team* team_array, int team_num, bool* play) {
    //give choices on what to search for
    string prompt = "\nWhich option would you like to choose?\n1. Search team by its name\n2. Display the top scorer of each team\n3. Search players by nationality\n4. Quit\nYour Choice: ";
    while (!search_input(choice_num, prompt, 1, 4)) cout << endl << "Please enter an integer between 1-4." << endl;

    string output;
    output = choices_1(team_array, team_num, *choice_num, play);
    prompt = "\nWhich option would you like to choose?\n1. Print to screen (Press 1)\n2. Print to file (Press 2)\nYour Choice: ";

    //if user did not decide to exit the program or if there are search matches, then run the following
    if (*play && output != "-1") {
        while (!search_input(choice_num, prompt, 1, 2)) cout << endl << "Please enter an integer between 1-2." << endl;
        choices_2(*choice_num, output);
    }
}

#endif