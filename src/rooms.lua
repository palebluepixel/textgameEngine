roomEntries = {
	room1 = {
		displayName = "field of grass",
		aliases = {},
		properties = {},
		verbs = {},
		objects = {},
		exits = {"exit_room1_room2"},
		onEnter = function () print("enter 1") end,
		onLeave = function () print("leave 1")end
	},
	room2 = {
		displayName = "house wall",
		aliases = {},
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
		displayName = "east",
		aliases = {},
		properties = {},
		verbs = {
			go = function() player:moveThrough(exit_room1_room2) end
		},
		roomFrom = "room1",
		roomTo = "room2",
		cond = function () 
			return rooms:getRoom("room1"):hasObject("obj1") 
		end,
		onPass = function () print("passing to room 2") end,
		onFail = function () print("You can't go that way rn") end
	},
	exit_room2_room1 = {
		displayName = "west",
		aliases = {},
		properties = {},
		verbs = {
			go = function() player:moveThrough(exit_room2_room1) end
		},
		roomFrom = "room2",
		roomTo = "room1",
		cond = function () 
			return rooms:getRoom("room1"):hasObject("obj1") 
		end,
		onPass = function () print("passing to room 2") end,
		onFail = function () print("You can't go that way rn") end
	}
}