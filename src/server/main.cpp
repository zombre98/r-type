//
// Created by armandmgt on 11/5/18.
//

#include <iostream>
#include "LuaSystem.hpp"

int main(int argc, char *argv[]) {
  ecs::entityVector v = std::make_shared<std::vector<ecs::entityPtr>>();
  v->push_back(std::make_unique<ecs::Entity>());
  (*v)[0]->addComponent<ecs::Velocity>(1.5f, 4.f);

  std::cout << (*v)[0]->getComponent<ecs::Velocity>().x << std::endl;

  ecs::LuaSystem testSystem(v, "test_system.lua");

  testSystem.update(102);

  std::cout << (*v)[0]->getComponent<ecs::Velocity>().x << std::endl;
  if (argc == 2) {
	std::cout << "Server started on port: " << argv[1] << std::endl;
  }
  return 0;
}
