#ifndef _PLAYER_HXX_
#define _PLAYER_HXX_

#include <sol.hpp>
#include <unordered_set>
#include "Object.hxx"
#include "Room.hxx"
#include "Exit.hxx"
#include "ObjectList.hxx"

using namespace sol;
using namespace std;

/* Contains information on the active player, such as room location,
inventory, properties, etc. 

Also contains the C++ engine side of taking items, placing items, 
and moving between rooms.
*/

/* Globally available lists */
extern RoomList *roomsLIST;

class Player {
public:
	Player();

	/* The player's table should have the following entries:
		* StartRoom : (string) An initial Room
		* Inventory : (sol::table) Names of items in players inv
		* TODO: properties
	*/
	Player(sol::table t);

	inline void setRoom(string room) { this->curRoom = room; }
	inline string getRoom() { return this->curRoom; }
	inline Room* getRoomObj() { return roomsLIST->getRoom(this->curRoom); }

	inline void addObject(string s) {this->objects.insert(s);}
	inline void removeObject(string s) {this->objects.erase(s);}
	inline int  hasObject(string s) {return this->objects.find(s) != this->objects.end();}

	/* TODO: give items onDrop and onTake functions that get called here? */

	/* Remove an item from the room it is currently in and place it in
	our inventory. Checking whether the item can be taken and any other
	gameplay consequences should be implemented in the lua script calling
	this function. If the item is not in the current room, this function 
	does nothing.
	*/
	void takeItem(string item);

	/* Remove an item from our inventory if it exists and place it in the
	room we are currently in. Again, any validity checking / side effects
	of dropping it should be done script-side. If the item is not in our 
	inventory, this function does nothing.
	*/
	void dropItem(string item);

	/* Checks whether the player can pass through the current exit,
	and does nothing if it can't. Otherwise, changes the current room 
	to the new room, and calls in order:
		* The onLeave function of the current room
		* The onPass function of the exit we are taking
		* The onEnter function of the room we are entering */
	void moveThrough(string exit);
	

private:
	/* List of christian names of all items the player has. This could
	be an ObjectManager if I abstracted that stuff out of the Room class */
	unordered_set<string> objects;

	/* Name of room we are currently in */
	string curRoom;

	/* Map of properties to values */
	/*TODO: give player properties. I could copy paste this from object,
	but I'd rather make a PropertyManager class instead */

};


#endif