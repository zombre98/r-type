//
// Created by armandmgt on 11/5/18.
//

#include <iostream>
#include "LuaSystem.hpp"

int main(int argc, char *argv[]) {
  //creating an entityVector with a default Velocity component
  ecs::entityVector v = std::make_shared<std::vector<ecs::entityPtr>>();
  v->push_back(std::make_unique<ecs::Entity>());
  (*v)[0]->addComponent<ecs::Velocity>(1.5f, 4.f);

  std::cout << "Base velocity component x: " << (*v)[0]->getComponent<ecs::Velocity>().x << std::endl;

  // creating LuaSystem with the entityVector and the file name (will check in assets/lua)
  ecs::LuaSystem testSystem(v, "test_system.lua");
  //updating the system with a custom delta
  testSystem.update(102);

  std::cout << "Checking velocity x changed (should be 5.6):" << (*v)[0]->getComponent<ecs::Velocity>().x << std::endl;

  if (argc == 2) {
	std::cout << "Server started on port: " << argv[1] << std::endl;
  }
  return 0;
}
