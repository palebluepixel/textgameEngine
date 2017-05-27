
roomEntries = {
	room1 = {
		displayName = "field of grass",
		aliases = {},
		properties = {
			descLong = function () return "You are standing in a field of grass. " end
		},
		verbs = {},
		objects = {"egg_grue", "obj1"},
		exits = {"exit_room1_room2"},
		onEnter = function () genericEnter(rooms,"room1") end,
		onLeave = function () end
	},

	room2 = {
		displayName = "house wall",
		aliases = {},
		properties = {
			descLong = function () return "You are standing next to the wall of a house. " end
		},
		verbs = {},
		objects = {--[[ --]]},
		exits = {"exit_room2_room1", "exit_room2_insideHouse"},
		onEnter = function() genericEnter(rooms, "room2") end,
		onLeave = function () end
	},

	insideHouse = {
		displayName = "inside the house",
		aliases = {"inside"},
		properties = {
			descLong = function () return "You are inside the house. " end
		},
		verbs = {},
		objects = {"fireplace"},
		exits = {"exit_insideHouse_room2"},
		onEnter = function () genericEnter(rooms, "insideHouse") end,
		onLeave = function() end
	}
}




exitEntries = {
	exit_room1_room2 = {
		displayName = "east",
		aliases = {},
		properties = {
			descInRoom = function () return "You see the wall of a house to the east. " end
		},
		verbs = {
			go = function() genericMoveThrough(player, "exit_room1_room2") end
		},
		roomFrom = "room1",
		roomTo = "room2",
		cond = function () 
			return true 
		end,
		onPass = function () end,
		onFail = function () print("You can't go that way rn. ") end
	},

	exit_room2_room1 = {
		displayName = "west",
		aliases = {},
		properties = {
			descInRoom = function () return "There is an open field of grass to the west. " end
		},
		verbs = {
			go = function() genericMoveThrough(player, "exit_room2_room1") end
		},
		roomFrom = "room2",
		roomTo = "room1",
		cond = function () 
			return true
		end,
		onPass = function () end,
		onFail = function () print("You can't go that way rn. ") end
	},

	exit_room2_insideHouse = {
		displayName = "door",
		aliases = {"inside", "doorway"},
		properties = {
			descInRoom = function () 
				locked = not exits:getExit("exit_room2_insideHouse"):executeCond()
				lockedstr = ""
				if locked then lockedstr = "locked. " else lockedstr = "unlocked. " end
				return "A door on the wall leads inside; " .. "it appears to be " .. lockedstr
			end
		},
		verbs = {
			go = function() genericMoveThrough(player, "exit_room2_insideHouse") end,
			enter = function() genericMoveThrough(player, "exit_room2_insideHouse") end,
			open = function() genericMoveThrough(player, "exit_room2_insideHouse") end
		},
		roomFrom = "room2",
		roomTo = "insideHouse",
		cond = function ()
			lever = objects:getObject("obj1")
			leverPulled = lever:getProperty("pulled")
			--[[ --]]
			return leverPulled --[[ --]]
		end,
		onPass = function () print("You move through the door. ") end,
		onFail = function () print("The door appears to be locked. ") end
	},

	exit_insideHouse_room2 = {
		displayName = "outside",
		aliases = {},
		properties = {
			descInRoom = function()
				locked = not exits:getExit("exit_room2_insideHouse"):executeCond()
				lockedstr = ""
				if locked then lockedstr = "The door appears to be locked, and it doesn't look like there is a way to unlock it from the inside. " else lockedstr = "" end
				return "There is a door that leads outside. " .. lockedstr
			end
		},
		verbs = {
			go = function() genericMoveThrough(player, "exit_insideHouse_room2") end
		},
		roomFrom = "insideHouse",
		roomTo = "room2",
		cond = function ()
			lever = objects:getObject("obj1")
			leverPulled = lever:getProperty("pulled")
			return leverPulled
		end,
		onPass = function () print("You move through the door. ") end,
		onFail = function () print("The door appears to be locked. ") end
	}

}