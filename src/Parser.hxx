#ifndef _PARSER_HXX_
#define _PARSER_HXX_

#include <sol.hpp>
#include <unordered_map>
#include "Object.hxx"
#include "Room.hxx"
#include "Exit.hxx"
#include "ObjectList.hxx"
#include "Player.hxx"

using namespace std;
using namespace sol;

/* Globals */
extern ObjectList *objectsLIST;
extern RoomList *roomsLIST;
extern ExitList *exitsLIST;
extern Player *player;

/* Takes user input as a std::string and calls the relevant functions. 
By default, a parser has the functionality described below, but this can
be extended by adding scripts mapping input words to functions. 

For simplicity, all non-scripted input handling is constrained to operate
only input of the form "[verb] [gameObject name]". Scripted input
can handle any string. 

The parser first checks if the input string matches any custom commands
defined in the scripts used to intialize it. If it finds a match, it 
calls the associated command from that script.

Next, the parser checks if the input is in the format 
"[verb] [gameObject name]". If it is not, the parser rejects the input.
If it is, the parser searches for a gameObject or child class with the
christian name (unique ID) [gameObject name] in the following places, 
in this order:
	1. Exits in the current room
	2. The room object itself
	3. Objects in the player's inventory
	4. Objects in the current room
If it finds a match, it checks if the gameObject has a verb entry for 
[verb]. If it does find a verb entry, it calls it, otherwise it rejects 
the input. If it finds no gameObject match, it rejects the input.
*/

class Parser {
public:
	Parser();

	/* A parser table contains the following:
		* commands : (sol::table) A table mapping strings to functions.
		The parser will call the associated function if it recieves input
		matching a string in the commands table. */
	Parser(sol::table t);

	/* Add commands from the table to out list of script-defined commands*/
	void addCommandsFromTable(sol::table t);

	inline void addCommand(string s, sol::function f) {this->commands[s] = f;}

	/* Follow the procedure outlines above*/
	void handleInput(string inp);

private:

	unordered_map<string, sol::function> commands;

};

#endif