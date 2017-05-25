#ifndef _OBJECT_HXX_
#define _OBJECT_HXX_

#include <sol.hpp>
#include <vector>
#include <unordered_map>

using namespace sol;
using namespace std;

class gameObject {
public:
	gameObject();
	/* Build an object from a lua table which must have the following:
		* a display name (string),
		* a list of aliases (table where the aliases are values (array string)),
		* a table of properties (table string -> sol::object),
		* a table of verbs (table string -> sol::function) */
	gameObject(sol::table t, string name);

	/* Getters and setters for display name */
	inline string getDisplayName() { return this->displayName; }
	inline void setDisplayName(string s) { this->displayName = s; }

	/* Getter for "official" unique object name */
	inline string getChristianName() { return this->christianName; }


	/* Building object from table */
	/* Used by constructors in child classes to set all of their object
	fields from the table. Those child classes will then read additional
	table values. */
	void setObjectDataFromTable(sol::table t, string name);
	void setPropertiesFromTable(sol::table props);
	void setVerbsFromTable(sol::table verbs);
	void setAliasesFromArray(sol::table aliases);



	/* This will add a new property with the given value if the
	given property does not already exist in this object. */
	void setProperty(string prop, sol::object value);

	/* Returns the value of the given property. Returns nil if
	the object doesn't have an entry for this property. */
	sol::object getProperty(string prop);

	/* Returns the type of the value stored for the given property,
	or nil if the object does not have the property. */
	sol::type getPropertyType(string prop);

	/* Checks if the return value for the given property matches the
	expected type, and returns nil if it does not. */
	sol::object getPropertyExpectType(string prop, sol::type t);


	/* Adds a new verb entry, or overwrites the existing entry if
	one exists. */
	void setVerb(string v, sol::function f);

	/* Returns the function associated with the verb v, or nil if none
	exists. */
	sol::function getVerb(string v);

	/* Executes the verb function and returns 1 if it an entry exists
	for this verb, otherwise returns 0.*/
	int executeVerbFunction(string v);

	/* Add an alias to the array of aliases. */
	inline void addAlias(string s) { this->aliases.push_back(s); }
	/*TODO: remove alias? */

	/* Returns 1 if the object goes by that alias, 0 otherwise. */
	int goesByAlias(string s);

	/* Prints out the value of the given property. This can be used,
	for example, to print descriptions easily. */
	void printProperty(string prop);

	/* Gets the string result from a sol::function in 
	properties with the given name. */
	string getStringFromFunc(string funcName);

	/* Prints the string returned by the function with the given name */
	void printDescription(string funcName);


	/* TODO: reset object fields from table (to allow reloading from
	scripts) */

private:
	/* Name that appears when talkimg about this item in descriptive text */
	string displayName;
	
	/* "Official" name of the item, the string name of the table in the
	objects array. This should be used to refer to the item in functions
	and should not be changed after initalization. */ 
	string christianName;

	/* Names that the player can call the object when interacting with
	it. For example, if we have an alias "lever", then if a user types
	"pull lever" it will call our verb function for pull. The game designer
	must take care that the aliases for every object which can be in the
	same room are distinct. The display name should almost always be an
	alias. */
	/* TODO: make it so the engine replies "I don't know which _ you mean"
	if there are two objects a player can interact with that are referred
	to by the same alias. */
	vector<string> aliases; 

	/* Used to store all stateful information about the object. Pretty much
	everything should be implemented as a property. These can be checked by
	verb functions. 
	
	TODO: abstract this out into a PropertyManager so that Player
	can use it too
	*/
	unordered_map<string, sol::object> properties;

	/* When the user says "pull lever", it calls the function associated
	with "pull" in the lever object. */
	unordered_map<string, sol::function> verbs;
};


#endif