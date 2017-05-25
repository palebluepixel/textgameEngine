#include "Exit.hxx"

Exit::Exit() {}

/* The table must have four entries in addition to the normal object entries:
	* roomFrom : the christian name of the room where the exit starts
	* roomTo : the christian name of the room where the exit takes you
	* cond : a sol::function that returns 1 if it is currently possible
	for the player to move through the exit (used to create locked doors,
	etc) 
	* onPass : a sol::function that triggers whenever the player passes
	through this exit. */
Exit::Exit(sol::table t, string name)
{
	/* Set fields for object parent class */
	this->setObjectDataFromTable(t, name);

	/* Set exit-specific information */
	/* TODO: these probably could have just been properties in
	the object instead of seperate fields? Technically verbs could
	have been properties as well. */
	string roomFrom = t.get<string>("roomFrom");
	string roomTo = t.get<string>("roomTo");
	sol::function cond = t.get<sol::function>("cond");
	sol::function onPass = t.get<sol::function>("onPass");
	sol::function onFail = t.get<sol::function>("onFail");

	this->setRoomFrom(roomFrom);
	this->setRoomTo(roomTo);
	this->setCond(cond);
	this->setOnPass(onPass);
	this->setOnFail(onFail);
	
}