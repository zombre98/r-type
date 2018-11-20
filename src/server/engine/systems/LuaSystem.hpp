/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** LuaSystem
*/

#pragma once

#define GET_COMPONENT(Type) "getComponent" #Type, sol::resolve<Type &()>(&Entity::getComponent<Type>)
#define GET_CONST_COMPONENT(Type) "getConstComponent" #Type, sol::resolve<const Type &() const>(&Entity::getComponent<Type>)
#define REMOVE_COMPONENT(Type) "removeComponent" #Type, &Entity::removeComponent<Type>
#define ADD_COMPONENT(Type, ...) "addComponent" #Type, &Entity::addComponent<Type, __VA_ARGS__>
#define HAS_COMPONENT(Type) "hasComponent" #Type, &Entity::hasComponent<Type>
#define COMPONENT_FUNC(Type, ...) GET_COMPONENT(Type), GET_CONST_COMPONENT(Type), REMOVE_COMPONENT(Type), \
	ADD_COMPONENT(Type, __VA_ARGS__), HAS_COMPONENT(Type)

#include <filesystem>

#include "sol.hpp"
#include "System.hpp"

 namespace ecs {

   template <typename... Types>
   class LuaSystem : public System {
   public:
	 static constexpr char LUA_FOLDER_PATH[] = "assets/lua/";

	 LuaSystem(entityVector allEntities, const std::string &fileName)
	   : System{allEntities}, _scriptPath(LUA_FOLDER_PATH) {
		 _scriptPath += fileName;
		 _lua.open_libraries();
		 _defineClasses();
		 _lua["entities"] = getEntities<Types...>();
		 _lua.script_file(_scriptPath.string());
		 _luaUpdate = _lua["update"];
	   }

	 void update(double delta) override final {
	   _luaUpdate(delta);
	 };

   private:
	 sol::state _lua;
	 sol::function _luaUpdate;
	 std::filesystem::path _scriptPath;

	 void _defineClasses() {
	   _lua.new_usertype<Entity>("Entity",
								 sol::constructors<Entity()>(),
								 COMPONENT_FUNC(Velocity, float, float),
								 COMPONENT_FUNC(Orientation, float),
								 COMPONENT_FUNC(Position, float, float)
								 );

	   // [COMPONENTS]
	   _lua.new_usertype<Component>("", sol::constructors<Component()>());

	   _lua.new_usertype<Velocity>("Velocity",
								   sol::constructors<Velocity(float, float)>(),
								   "x", &Velocity::x,
								   "y", &Velocity::y);

	   _lua.new_usertype<Orientation>("Orientation",
									  sol::constructors<Orientation(float)>(),
									  "orientation", &Orientation::orientation);

	   _lua.new_usertype<Position>("Position",
								   sol::constructors<Position(float, float)>(),
								   "x", &Position::x,
								   "y", &Position::y);
	 }
   };
 }
