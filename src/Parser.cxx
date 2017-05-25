#include "Parser.hxx"

Parser::Parser() {}

/* A parser table contains the following:
	* commands : (sol::table) A table mapping strings to functions.
	The parser will call the associated function if it recieves input
	matching a string in the commands table. */
Parser::Parser(sol::table t)
{
	sol::table commands = t.get<sol::table>("commands");
	this->addCommandsFromTable(commands);
}

/* Add commands from the table to out list of script-defined commands*/
void Parser::addCommandsFromTable(sol::table t)
{
	t.for_each([&](const sol::object& key, const sol::object& value) 
		{this->addCommand(key.as<string>(), value.as<sol::function>()); });
}

void tellEm()
{
	printf("Input must be in the following format:\n\"[verb] [noun]\".\n");
}

void dontKnowVerb(string noun, string verb)
{
	printf("I don't know how to %s %s.\n", noun.c_str(), verb.c_str());
}

void dontKnowNoun(string noun)
{
	printf("I don't know what %s is.\n", noun.c_str());
}

/* Follow the procedure outlines above*/
void Parser::handleInput(string inp)
{
	/* Check if we have a scripted command that matches the input */
	sol::function f = this->commands[inp];
	if(f != sol::nil){
		f();
		return;
	}

	/* Attempt to split into proper format */
	int pos = inp.find_first_of(" ");
	if(pos==string::npos) { //no spaces
		tellEm();
		return;
	}
	string verb = inp.substr(0, pos);
	string noun = inp.substr(pos+1);

	/* Get the player's current room so we can look for matches. */
	Room* curRoom = player->getRoomObj(); //player is global

	/* TODO: figure out how to do the typecasting on this so there
	isn't repeated code */
	/* Actually, this might work */

	// /* 1: check exits of current room */
	// if(curRoom->containsExit(noun)){
	// 	Exit *match = exitsLIST->getExit(noun);
	// 	int ret = match->executeVerbFunction(verb);
	// 	if(!ret) dontKnowVerb(noun, verb);
	// 	return;
	// }

	// /* 2: check room itself */
	// if(curRoom->getChristianName() == noun){
	// 	int ret = curRoom->executeVerbFunction(verb);
	// 	if(!ret) dontKnowVerb(noun, verb);
	// 	return;
	// }

	// /* 3: check objects in player's inventory */
	// if(player->hasObject(noun)){
	// 	gameObject *match = objectsLIST->getObject(noun);
	// 	int ret = match->executeVerbFunction()
	// }

	gameObject *match = NULL;

	/* 1: check exits of current room */
	if(curRoom->containsExitByAlias(noun)) 
		match = dynamic_cast<gameObject*>(exitsLIST->getExitByAlias(noun));

	/* 2: check room itself */
	if(curRoom->goesByAlias(noun)) 
		match = dynamic_cast<gameObject*>(curRoom);

	/* 3: check objects in player's inventory */
	if(player->hasObjectByAlias(noun))
		match = objectsLIST->getObjectByAlias(noun);

	/* 4: check items in current room */
	if(curRoom->containsObjectByAlias(noun))
		match = objectsLIST->getObjectByAlias(noun);

	/* If we didn't get a match, reject the input */
	if(!match){
		dontKnowNoun(noun);
		return;
	}

	/* If we did, try to call the verb function. If we get 0 back, 
	there was no entry. */
	int ret = match->executeVerbFunction(verb);
	if(!ret)
	{
		dontKnowVerb(noun, verb);
		return;
	}

	/* If we got here, we successfully executed the function! */

}