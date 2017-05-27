objectEntries = {

    obj1 = {
        displayName = "lever",
        aliases = {"wallguy"},
        properties = {
        	pulled = false,
        	descInRoom = function () 
        		pulledstr = ""
				if objects:getObject("obj1"):getProperty("pulled") then
					pulledstr = "pulled. " 
				else pulledstr = "not pulled. "
				end
        	return "There is a rusty lever on the ground that is " .. pulledstr end
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
            drop = function() genericDrop(player, "egg_grue") end,
            eat = function() player:removeObject("egg_grue"); print("You eat the egg. It tastes bad.") end
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


    --[[ = {
        displayName = "",
        aliases = {},
        properties = {},
        verbs = {}
    }--]]


}