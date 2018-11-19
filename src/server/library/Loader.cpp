/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** Loader
*/

#include <iostream>
#include "Loader.hpp"

void lib::Loader::loadLib(const std::string &libName) {
  _handle = dlopen(("./" + libName).c_str(), RTLD_LAZY);
  if (!_handle)
	throw std::invalid_argument("Can not open library: " + libName);
}
