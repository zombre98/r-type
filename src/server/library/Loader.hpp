/*
** EPITECH PROJECT, 2018
** rtype
** File description:
** Loader
*/

#pragma once

#include <string>
#include <dlfcn.h>
#include <stdexcept>

namespace lib {
    class Loader {
    public:
        Loader() noexcept : _handle(nullptr) {};
        ~Loader() noexcept {
            if (_handle)
                dlclose(_handle);
        };

        void loadLib(const std::string &libName);

        void *getHandle() const noexcept {
            return _handle;
        };

        template<typename T>
        T getFunction(const std::string &functionName) const {
            dlerror();
            T func = (T)dlsym(_handle, functionName.c_str());
            const char *dlsym_error = dlerror();
            if (dlsym_error)
                throw std::invalid_argument(std::string("Cannot load symbol: ", dlsym_error));
            return (func);
        };

    private:
        void *_handle;
    };
}
