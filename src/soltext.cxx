#include <sol.hpp> // or #include "sol.hpp", whichever suits your needs

using namespace sol;

int main (int argc, char* argv[]) {

        state lua;
        lua.open_libraries( sol::lib::base );

        lua.script( "print('bark bark bark!')" );

        return 0;
}