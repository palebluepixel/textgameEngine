#ifndef _EXIT_HXX_
#define _EXIT_HXX_

#include <sol.hpp>
#include "Object.hxx"

using namespace sol;
using namespace std;

/* A link between two rooms. Unidirectional, and only passable if a
given condition is met. */

class Exit : public gameObject {
public:
	Exit();

	/* The table must have four entries in addition to the normal object entries:
		* roomFrom : the christian name of the room where the exit starts
		* roomTo : the christian name of the room where the exit takes you
		* cond : a sol::function that returns 1 if it is currently possible
		for the player to move through the exit (used to create locked doors,
		etc) 
		* onPass : a sol::function that triggers whenever the player passes
		through this exit. 
		*onFail : (sol:function) called when the player tries to pass, but
		can't because the condition is not met.*/
	Exit(sol::table t, string name);

	inline void setRoomFrom(string r) {this->roomFrom = r;}
	inline void setRoomTo(string r) {this->roomTo = r;}
	inline void setCond(sol::function f) {this->cond = f;}
	inline void setOnPass(sol::function f) {this->onPass = f;}
	inline void setOnFail(sol::function f) {this->onFail = f;}

	inline string getRoomFrom() { return this->roomFrom; }
	inline string getRoomTo() { return this->roomTo; }

	inline sol::function getCond() { return this->cond; }
	inline sol::function getOnPass() { return this->onPass; }
	inline sol::function getOnFail() { return this->onFail; }

	/* Returns the value returned by cond */
	inline bool executeCond() { return this->cond(); }

	inline void executeOnPass() { this->onPass(); }
	inline void executeOnFail() { this->onFail(); }

private:
	string roomFrom;
	string roomTo;
	sol::function cond;
	sol::function onPass;
	sol::function onFail;

};

#endif