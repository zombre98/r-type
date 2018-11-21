/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** Watcher
*/

#include <iostream>
#include <thread>
#include <chrono>

#include "Watcher.hpp"

void lib::Watcher::run() {
    std::thread watcherThread([this] {
                                  while (true) {
                                      _watch();
                                      std::this_thread::sleep_for(std::chrono::seconds(10));
                                  }
                              });

    watcherThread.detach();
}

void lib::Watcher::_watch() {
    for (auto &p : std::filesystem::recursive_directory_iterator(_watchedFolder.string())) {
        if (_loadedNames.find(p.path().string()) != _loadedNames.end())
            continue;
        std::cout << p << std::endl;
        _loadedNames.insert(p.path().string());
        try {
            Loader tmp;
            tmp.loadLib(p.path().string());
            _loadedLibs.push_back(std::make_unique<Loader>(tmp));
        } catch (const std::invalid_argument &e) {
            std::cerr << "Ignoring: " << e.what() << std::endl;
        }
    }
}
