objectEntries = {
    obj1 = {
        displayName = "lever",
        aliases = {"wallguy"},
        properties = {
        	pulled = false,
        	descInRoom = function () 
        		pulledstr = ""
				if objects:getObject("obj1"):getProperty("pulled") == 1 then
					pulledstr = "pulled. " 
				else pulledstr = "not pulled. "
				end
        	return "There is a rusty lever on the wall that is " .. pulledstr end
    	},
    	verbs = {
    		pull = function ()
				l = objects:getObject("obj1")
				p = l:getProperty("pulled")
				l:setProperty("pulled", not p)
				print("You pulled the lever.")
			end,
			eat = function ()
				print("You can't eat that!")
			end,
			take = function()
				print("you can't take the lever.")
			end
    	}
    },


    egg_grue = {
        displayName = "egg",
        aliases = {},
        properties = {
            descInRoom = function()
                return "A simple egg rests among the blades. "
            end
        },
        verbs = {
            take = function() genericTake(player, "egg_grue") end,
            drop = function() genericDrop(player, "egg_grue") end
        }
    },


    fireplace = {
        displayName = "fireplace",
        aliases = {"fire"},
        properties = {
            burning = true,
            descInRoom = function()
                return "A fireplace cackles warmly. You have the sneaking suspicion that if you touch the fireplace, you will win the demo game. "
            end
        },
        verbs = {
            touch = function()
                winGame()
            end
        }
    },

    npc_gatekeeper = {
        displayName = "Eustace",
        aliases = {"friend", "man"},
        properties = {
            timesTalkedTo = 0,
            descInRoom = function()
                return "A man stands in the corner. He appears to be guarding the door. "
            end
        },
        verbs = {
            talk = function()
                io.write("Eustace:  \"")
                man = objects:getObject("npc_gatekeeper")
                ttt = man:getProperty("timesTalkedTo")
                if ttt == 0 then
                    io.write("Talk to me again and I'll let you through.")
                end if ttt==1 then
                    io.write("I'll let you through.")
                end
                io.write("\"\n")
                man:setProperty("timesTalkedTo", ttt+1)
            end,
            hug = function()
                print("He thanks you for your kindness.")
            end
        }
    }
}