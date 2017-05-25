roomEntries = {
	room1 = {
		displayName = "Field of Grass",
		aliases = {"Field of Grass"},
		properties = {},
		verbs = {},
		objects = {},
		exits = {"exit_room1_room2"},
		onEnter = function () print("enter 1") end,
		onLeave = function () print("leave 1")end
	},
	room2 = {
		displayName = "House wall",
		aliases = {"House wall"},
		properties = {},
		verbs = {},
		objects = {"obj1"},
		exits = {},
		onEnter = function () print("enter 2") end,
		onLeave = function () print("leave 2") end
	}
}




exitEntries = {
	exit_room1_room2 = {
		displayName = "East",
		aliases = {"East"},
		properties = {},
		verbs = {},
		roomFrom = "room1",
		roomTo = "room2",
		cond = function () 
			return rooms:getRoom("room1"):hasObject("obj1") 
		end,
		onPass = function () print("passing to room 2") end,
		onFail = function () print("You can't go that way rn") end
	}
}