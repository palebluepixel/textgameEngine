#include "Object.hxx"

gameObject::gameObject()
{

}

/* TODO: verify that user-supplied object data has the expected
type before reading, give helpful error messages */
gameObject::gameObject(sol::table t)
{
	string displayName = t.get<string>("displayName");
	sol::table aliases = t.get<sol::table>("aliases");
	sol::table properties = t.get<sol::table>("properties");
	sol::table verbs = t.get<sol::table>("verbs");

	this->setDisplayName(displayName);
	this->setPropertiesFromTable(properties);
	this->setVerbsFromTable(verbs);
	this->setAliasesFromArray(aliases);
}

void gameObject::setPropertiesFromTable(sol::table props)
{
	props.for_each([&](const sol::object& key, const sol::object& value) 
		{this->setProperty(key.as<string>(), value); });
}

void gameObject::setVerbsFromTable(sol::table verbs)
{
	verbs.for_each([&](const sol::object& key, const sol::object& value) 
		{this->setVerb(key.as<string>(), value.as<sol::function>()); });
}

void gameObject::setAliasesFromArray(sol::table aliases)
{
	aliases.for_each([&](const sol::object& /*unused*/, const sol::object& value) 
		{this->addAlias(value.as<string>()); });
}

int gameObject::goesByAlias(string s) 
{ 
	for(string it : this->aliases ){
		if (it == s) return 1;
	} 
	return 0;
}

/* This will add a new property with the given value if the
given property does not already exist in this object. */
void gameObject::setProperty(string prop, sol::object value)
{
	this->properties[prop] = value;
}

/* Returns the value of the given property. Returns nil if
the object doesn't have an entry for this property. */
sol::object gameObject::getProperty(string prop)
{
	auto result = this->properties.find(prop);
	if(result == this->properties.end()){
		return sol::object(sol::nil);
	}
	return result->second;
}

/* Returns the type of the value stored for the given property,
or nil if the object does not have the property. */
sol::type gameObject::getPropertyType(string prop)
{
	sol::object obj = this->getProperty(prop);
	return obj.get_type();
}

/* Checks if the return value for the given property matches the
expected type, and returns nil if it does not. */
sol::object gameObject::getPropertyExpectType(string prop, sol::type t)
{
	sol::object obj = this->getProperty(prop);
	return obj.get_type() == t ? obj : sol::nil;
}


/* Adds a new verb entry, or overwrites the existing entry if
one exists. */
void gameObject::setVerb(string v, sol::function f)
{
	this->verbs[v] = f;
}

/* Returns the function associated with the verb v, or nil if none
exists. */
sol::function gameObject::getVerb(string v)
{
	return this->verbs[v];
}

/* Executes the verb function. Returns 1 if thhe object has a valid
function entry for this verb, otherwise returns 0. */
int gameObject::executeVerbFunction(string v)
{
	sol::function f = this->getVerb(v);
	if(f == sol::nil)
		return 0;
	f();
	return 1;
}