#include <sol.hpp> // or #include "sol.hpp", whichever suits your needs

using namespace sol;

int add(int a, int b) { return a+b; }


class my_class {
public:
        int a = 0;

        inline my_class(int x) : a(x) {

        }

        inline int func() {
                ++a; // increment a by 1
                return a;
        }
};


int main (int argc, char* argv[]) {

        state lua;
        lua.open_libraries( sol::lib::base );

        /* Two ways, in one we bind to an instance now, in the second
        we bind to the instance later */
        my_class inst = my_class(0);
        inst.func();
        inst.func();
        lua.set_function("my_class_func", &my_class::func, &inst);
        lua.set_function("my_class_func_2", &my_class::func);

        lua.script(R"(
                first_value = my_class_func()
                second_value = my_class_func()
        )");

        // With no bound instance:
        my_class inst2 = my_class(24);
        lua.set("obj", &inst2); //just "inst2" passes a copy
        // Calls "func" on the class instance
        // referenced by "obj" in Lua
        lua.script(R"(
                third_value = my_class_func_2(obj)
                fourth_value = my_class_func_2(obj)
        )");

        // Have to mantually go back and get data from lua if we didn't
        // pass it as a reference
        //inst2.a = lua.get<my_class>("obj").a;

        my_class inst3 = my_class(69);

        lua.new_usertype<my_class>( "my_class",
            constructors<my_class(int)>(),
            "func", &my_class::func,
            "a", property(&my_class::a) //would add getter and setter here if private
        );
        lua.set("real", &inst3);
        lua.script(R"(
            fifth_value = real:func()
            sixth_value = real:func()
        )");

        printf("Instance 1: %d\nInstance2: %d\nInstance3: %d\n", inst.a, inst2.a, inst3.a);
        printf("Lua sees %d %d %d %d %d %d\n", 
            lua.get<int>("first_value"),
            lua.get<int>("second_value"),
            lua.get<int>("third_value"),
            lua.get<int>("fourth_value"),
            lua.get<int>("fifth_value"),
            lua.get<int>("sixth_value"));


        lua["add_func"] = add;

        lua.script_file( "../src/script.lua" );

        lua.script_file("../src/script2.lua");

        int width = lua["window"]["width"];
        std::string name = lua["window"]["title"];
        printf("%s width: %d number : %d\n", name.c_str(), width, lua.get<int>("number"));

        lua["newtable"] = lua.create_table_with(
            "key0", 24,
            "key1", 25
        );

        int key0 = lua["newtable"]["key0"];
        printf("key0: %d\n", key0);


        // Functions
        function inc = lua.get<function>("inc");
        int x = 0;
        int xinc = inc(x);
        printf("Increment test %d %d\n", x, xinc);

        printf("Done.\n");

        return 0;
}