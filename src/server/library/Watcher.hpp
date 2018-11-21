/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** Watcher
*/

#pragma once

#include <set>
#include <vector>
#include <memory>
#include <filesystem>

#include "Loader.hpp"

namespace lib {
    using loaderPtr = std::unique_ptr<Loader>;

    class Watcher {
    public:
        Watcher(const std::string &folderName)
            : _watchedFolder(folderName)
        {};
        ~Watcher() {};

        void run();

        const std::vector<loaderPtr> &getLoaders() {
            // auto v = std::move(_loadedLibs);
            // _loadedLibs.clear();
            return (_loadedLibs);
        }

    private:
        void _watch();

        std::set<std::string> _loadedNames;
        std::vector<loaderPtr> _loadedLibs;
        std::filesystem::path _watchedFolder;
    };
}
