/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** LuaSystem
*/

#pragma once

#include "sol.hpp"
#include "System.hpp"

namespace ecs {
  class LuaSystem : public System {
  public:
    static constexpr char LUA_FOLDER_PATH[] = "assets/lua/";

	LuaSystem(entityVector allEntities, const std::string &fileName);

	void update(double delta) override final;

  private:
	void _defineClasses();

	sol::state _lua;
	sol::function _luaUpdate;
	std::string _fileName;
  };
}
