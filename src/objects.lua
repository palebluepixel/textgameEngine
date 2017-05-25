objectEntries = {
    obj1 = {
        displayName = "lever",
        aliases = {"lever", "wallguy"},
        properties = {
        	coolness = 1;
        	pulled = 0;
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
        aliases = {"button"},
        properties = {
        	coolness = 2;
        	pushed = 0;
    	},
    	verbs = {}
    },
}