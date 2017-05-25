#include "Player.hxx"

extern ExitList *exitsLIST;

Player::Player() {}


/* The player's table should have the following entries:
	* StartRoom : (string) An initial Room
	* Inventory : (sol::table) Names of items in players inv
	* TODO: properties
*/
Player::Player(sol::table t)
{
	string startRoom = t.get<string>("startRoom");
	sol::table inv = t.get<table>("inv");

	this->setRoom(startRoom);
	inv.for_each([&](const sol::object& /*key*/, const sol::object& value) 
		{this->addObject(value.as<string>());});
}

/* Remove an item from the room it is currently in and place it in
our inventory. Checking whether the item can be taken and any other
gameplay consequences should be implemented in the lua script calling
this function. If the item is not in the current room, this function 
does nothing.
*/
void Player::takeItem(string item)
{
	Room* r = this->getRoomObj();
	if(!r){
		printf("Warning, player room NULL: %s\n", this->getRoom().c_str());
		return;
	}
	if(!r->containsObject(item)) return;

	r->removeObject(item);
	this->addObject(item);
}

/* Remove an item from our inventory if it exists and place it in the
room we are currently in. Again, any validity checking / side effects
of dropping it should be done script-side. If the item is not in our 
inventory, this function does nothing.
*/
void Player::dropItem(string item)
{
	if(!this->hasObject(item)) return;

	this->removeObject(item);
	Room* r = this->getRoomObj();
	r->addObject(item);
}

/* Checks if the player can move through the current exit, if not 
calls onFail and returns. Otherwise, changes the current room to 
the new room, and calls in order:
	* The onLeave function of the current room
	* The onPass function of the exit we are taking
	* Places the player in the new room
	* The onEnter function of the room we are entering
*/
void Player::moveThrough(string exit)
{
	/* Get rooms and do error checking */
	Exit *e = exitsLIST->getExit(exit);
	if(!e){
		printf("warning, nonexistant exit: %s\n", exit.c_str());
		return;
	}
	if(!e->executeCond()){
		e->executeOnFail();
		return;
	}

	Room *from = this->getRoomObj();
	if(!from){
		printf("Warning, player room NULL: %s\n", this->getRoom().c_str());
		return;
	}
	if(from->getChristianName() != e->getRoomFrom()){
		printf("Warning, player trying to go through impossible exit %s from room %s, needs to be in %s\n", exit.c_str(), 
			from->getChristianName().c_str(), e->getRoomFrom().c_str());
		return;
	}
	Room *to = roomsLIST->getRoom(e->getRoomTo());
	if(!to){
		printf("Exit %s endpoint does not exist %s\n", exit.c_str(),
			e->getRoomTo().c_str());
	}

	/* Actually call the functions */
	from->executeOnLeave();
	e->executeOnPass();
	this->setRoom(to->getChristianName());
	to->executeOnEnter();

}


int Player::hasObjectByAlias(string alias)
{
	gameObject *obj = objectsLIST->getObjectByAlias(alias);
	return (obj && this->hasObject(obj->getChristianName()));
}