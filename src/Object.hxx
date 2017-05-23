#ifndef _OBJECT_HXX_
#define _OBJECT_HXX_

#include <sol.hpp>
#include <vector>
#include <unordered_map>

using namespace sol;
using namespace std;

/* Globally availible script state */
extern state luastate;

class gameObject {
public:
	gameObject();

	inline string getDisplayName() { return this->displayName; }
	inline void setDisplayName(string s) { this->displayName = s; }

	inline void addAlias(string s) { this->aliases.push_back(s); }
	int goesByAlias(string s);


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
	sol::function getVerbFunction(string v);

	/* Executes the verb function and returns 1 if it an entry exists
	for this verb, otherwise returns 0. */
	int executeVerbFunction(string v);


private:
	string displayName;
	vector<string> aliases; 
	unordered_map<string, sol::object> properties;
	unordered_map<string, sol::function> verbs;
};


#endif