//
// Created by armandmgt on 11/5/18.
//

#include <SFML/Graphics.hpp>
#include <iostream>
#include "sol.hpp"

int main() {
	std::cout << "=== running lua code ===" << std::endl;
	sol::state lua;
	lua.open_libraries(sol::lib::base);
    lua.script_file("a_lua_script.lua");
	sol::function luaFactorial = lua["fact"];
    int value = luaFactorial(5);
	std::cout << value << std::endl;


	sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

	while (window.isOpen()) {
		sf::Event event{};
		while (window.pollEvent(event))
		  if (event.type == sf::Event::Closed)
			window.close();
		window.clear(sf::Color::Black);
		// do things
		window.display();
	}
	return 0;
}
