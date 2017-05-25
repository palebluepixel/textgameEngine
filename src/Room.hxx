#ifndef _ROOM_HXX_
#define _ROOM_HXX_ 

#include <sol.hpp>
#include "Exit.hxx"
#include "Object.hxx"
#include <unordered_set>

using namespace sol;
using namespace std;

/* A room has all the things an object has, but it also has a vector of
all exits leading from this room and another vector of all objects
curently in the room. (The string identifiers are christian names, that
is, unique IDs)

A room also contains an onEnter function that triggers when the player
enters the room (usually this just prints out text).*/

class ObjectList;
class ExitList;

extern ObjectList *objectsLIST;
extern ExitList *exitsLIST;

class Room : public gameObject {
public:
	Room();

	/* A room must have the following fields, in addition to the normal
	object fields:
		* objects : (sol::table) an array of strings of the names of
		objects which spawn starting in this room
		* exits : (sol::table) an array of strings of the names of 
		exits which leave this room. 
		* onEnter : (sol::function) a function that will trigger whenever
		the player enters the room. 
		* onLeave : (sol::function) a function that will trigger whenever
		the player leaves the room. */ 
	Room(sol::table t, string name);

	/* Construct room contents from table */
	void addObjectsFromArray(sol::table t);
	void addExitsFromArray(sol::table t);

	inline void addObject(string s) {this->objects.insert(s);}
	inline void addExit(string s) {this->exits.insert(s);}

	inline void removeObject(string s) {this->objects.erase(s);}
	inline void removeExit(string s) {this->exits.erase(s);}

	inline int containsObject(string s) {return this->objects.find(s) != this->objects.end();}
	inline int containsExit(string s) {return this->exits.find(s) != this->exits.end();}

	int containsObjectByAlias(string alias);
	gameObject *getObjectfromRoomByAlias(string alias);
	int containsExitByAlias(string alias);
	Exit *getExitFromRoomByAlias(string alias);

	/* Print out a description of all objects and exits in the room. */
	void describeRoomContents();
	void describeObjects();
	void describeExits();

	inline void setOnEnter(sol::function f) {this->onEnter = f;}
	inline void executeOnEnter() {this->onEnter();}

	inline void setOnLeave(sol::function f) {this->onLeave = f;}
	inline void executeOnLeave() {this->onLeave();}

private:

	unordered_set<string> objects;
	unordered_set<string> exits;

	sol::function onEnter;
	sol::function onLeave;

};


#endif