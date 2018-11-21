/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** Watcher
*/

#pragma once

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

        std::vector<loaderPtr> getLoaders() {
            return (std::move(_loadedLibs));
        }

    private:
        std::vector<std::string> _loadedLibNames;
        std::vector<loaderPtr> _loadedLibs;
        std::filesystem::path _watchedFolder;
    };
}
