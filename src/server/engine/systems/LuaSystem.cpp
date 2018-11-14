/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** LuaSystem source file
*/

#include "LuaSystem.hpp"

namespace ecs {
  LuaSystem::LuaSystem(entityVector allEntities, const std::string &fileName)
	: System{allEntities}, _fileName{fileName} {
	  _lua.open_libraries();
	  _defineClasses();
	  _lua["entities"] = getEntities(COMP_VELOCITY);
	  _lua.script_file(LUA_FOLDER_PATH + _fileName);
	  _luaUpdate = _lua["update"];
	}

  void LuaSystem::update(double delta) {
	_luaUpdate(delta);
  }

  void LuaSystem::_defineClasses() {
	_lua.new_usertype<Entity>("Entity",
							  sol::constructors<Entity()>(),
							  "getComponentVelocity", sol::resolve<Velocity &()>(&Entity::getComponent<Velocity>)// ,
							  // "addComponentVelocity", &Entity::addComponent<Velocity>
							  );

	_lua.new_usertype<Component>("", sol::constructors<Component()>());

	_lua.new_usertype<Velocity>("Velocity",
								sol::constructors<Velocity(float, float)>(),
								"x", &Velocity::x,
								"y", &Velocity::y
								);
  }
}
