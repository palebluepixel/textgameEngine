objectEntries = {
    obj1 = {
        displayName = "lever",
        aliases = {"wallguy"},
        properties = {
        	coolness = 1,
        	pulled = 0,
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
				if p==0 then p=1 else p=0 end
				l:setProperty("pulled", p)
				print("You pulled the lever.")
			end,
			eat = function ()
				print("You can't eat that!")
			end
    	}
    },
    obj2 = {
        displayName = "button",
        aliases = {},
        properties = {
        	coolness = 2,
        	pushed = 0,
        	descInRoom = function () return "A shiny new button sits on the wall. " end
    	},
    	verbs = {}
    },
}