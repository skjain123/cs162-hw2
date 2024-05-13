#include <iostream>
#include <fstream>

using namespace std;

//a struct to hold info of a team
struct Team {
  string name;        //name of the team
  string owner;       //owner of the team
  int market_value;   //market value of the team
  int num_player;     //number of players in the team
  struct Player *p;   //an array that holds all players
  float total_ppg;    //total points per game
};

//a struct to hold info of a player
struct Player {
  string name;      //name of the player
  int age;          //age of the player
  string nation;    //nationality of the player
  float ppg;        //points per game of the player
  float fg;         //field goal percentage
};


/**************************************************
 * Name: create_teams()
 * Description: This function will dynamically allocate
                an array of teams (of the requested size)
 * Parameters: int - size of the array
 * Pre-conditions: none
 * Post-conditions: a Team array of requested size is created and return
 ***********************************************/
Team* create_teams(int);


/**************************************************
 * Name: populate_team_data()
 * Description: This function will fill a single team struct 
                with information that is read in from the file
 * Parameters:  Team* - pointer to the Team array
                int - index of the Team in the array to be filled 
                ifstream& - input file to get information from
 * Pre-conditions: Team array has been allocated; 
                   provided index is less than the array size
 * Post-conditions: a Team at provided index is populated
 ***********************************************/
void populate_team_data(Team*, int, ifstream &); 


/**************************************************
 * Name: create_players()
 * Description: This function will dynamically allocate
                an array of players (of the requested size)
 * Parameters: int - size of the array
 * Pre-conditions: none
 * Post-conditions: a Player array of requested size is created and return
 ***********************************************/
Player* create_players(int);


/**************************************************
 * Name: populate_player_data()
 * Description: This function will fill a single player struct 
                with information that is read in from the file
 * Parameters:  Player* - pointer to the Player array
                int - index of the Player in the array to be filled 
                ifstream& - input file to get information from
 * Pre-conditions: Player array has been allocated; 
                   provided index is less than the array size
 * Post-conditions: a Player at provided index is populated
 ***********************************************/
void populate_player_data(Player*, int, ifstream &); 


/**************************************************
 * Name: delete_info()
 * Description: This function will  delete all the memory that was dynamically allocated
 * Parameters: Team* - the Team array
 * Pre-conditions: the provided Team array hasn't been freed yet
 * Post-conditions: the Team array, with all Players inside, is freed
 ***********************************************/
void delete_info(Team*, int);

/**************************************************
 * Function Name: isNum
 * Description: checks the user input for any characters that is not a number to determine 
 * if it can be converted to an int usin stoi()
 * Parameters: the user input
 * Pre-Conditions: used correctly within the play_again loop
 * Post-Conditions: outputs clearly
 ***********************************************/
bool isNum(string input, int len);

/**************************************************
 * Function Name: search_input
 * Description: checks if the user input is a number and within the specified limits
 * Parameters: the user input variable to edit in the function, the prompt asking for input,
 *             the lower num limit, the higher num limit.
 * Pre-Conditions: used correctly in a loop, prompt is correct, limits are correct for intended use.
 * Post-Conditions: edits choice_num correctly and error handles accordingly
 ***********************************************/
bool search_input(int* choice_num, string prompt, int lower, int upper);

/**************************************************
 * Function Name: team_by_name
 * Description: searches the database using a user inputted string that looks for a team name 
 *              and outputs the team's and its players' information
 * Parameters: the team array (database data stored in) and the number of teams in that array
 * Pre-Conditions: data inputted correctly, number of teams is correct
 * Post-Conditions: returns a clear string of information containing team and player information
 * *                error handles correctly
 ***********************************************/
string team_by_name(Team* array, int size);

/**************************************************
 * Function Name: team_top_scorer
 * Description: returns a string of all teams and thier top scoring player (ppg)
 * Parameters: the team array (database data stored in) and the number of teams in that array
 * Pre-Conditions: data inputted correctly, number of teams is correct
 * Post-Conditions: returns a clear string of information containing each team and thier top scoring player (ppg)
 *                  error handles correctly
 ***********************************************/
string team_top_scorer(Team* array, int size);

/**************************************************
 * Function Name: player_by_nationality
 * Description: returns a string of all players matching a user inputted nationality
 * Parameters: the team array (database data stored in) and the number of teams in that array
 * Pre-Conditions: data inputted correctly, number of teams is correct
 * Post-Conditions: returns a clear string of information containing each team and thier top scoring player (ppg)
 *                  error handles correctly
 ***********************************************/
string player_by_nationality(Team* array, int size);

/**************************************************
 * Function Name: open_file
 * Description: opens a user inputted file and reads the data to a passed array
 * Parameters: a pointer to the array that will store all the data and a pointer to the amount of teams
 * Pre-Conditions: data formatted correctly, only ran once at beginning of program
 * Post-Conditions: edits the passed array and integer appropriately to the database file's information.
 ***********************************************/
Team* open_file(int* team_num);

/**************************************************
 * Function Name: choices_1
 * Description: based on the user input and error handling, run one of the following functions:
 *              team_by_name(), team_top_scorer(), player_by_nationality(), exit()
 * Parameters: array that stores file data, the number of teams, and the user input
 * Pre-Conditions: data inputted correctly, number of teams is correct, user input has already been error handled and is correct.
 * Post-Conditions: runs correct file that matches the prompt given in error handling.
 ***********************************************/
string choices_1(Team* team_array, int team_num, int choice_num, bool *play);

/**************************************************
 * Function Name: choices_2
 * Description: based on the user input and error handling, either print to console or to a new user specified file
 * Parameters: array that stores file data, the number of teams, and the user input
 * Pre-Conditions: data inputted correctly, number of teams is correct, user input has already been error handled and is correct.
 * Post-Conditions: runs correct file that matches the prompt given in error handling.
 ***********************************************/
void choices_2(int choice_num, string output);

void search_selections(int* choice_num, Team* team_array, int team_num, bool *play);

