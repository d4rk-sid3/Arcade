/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-arcade-amour.guidi
** File description:
** loader
*/

#ifndef DLLOADER_HPP
#define DLLOADER_HPP

#include <dlfcn.h>
#include <stdexcept>
#include <string>

template <typename T>
class DLLoader {
private:
    void* handle;
    T* instance;

public:
    DLLoader(const std::string& libraryPath) : handle(nullptr), instance(nullptr) {
        handle = dlopen(libraryPath.c_str(), RTLD_LAZY);
        if (!handle) {
            throw std::runtime_error("Failed to open library: " + std::string(dlerror()));
        }
        
        using CreateInstanceFunc = T*();
        auto createInstance = (CreateInstanceFunc*) dlsym(handle, "createInstance");
        if (!createInstance) {
            throw std::runtime_error("Failed to load symbol: " + std::string(dlerror()));
            std::cout << "L" << std::endl;
        }
        instance = createInstance();
    }

    ~DLLoader() {
        if (handle) {
            using DestroyInstanceFunc = void(T*);
            auto destroyInstance = (DestroyInstanceFunc*) dlsym(handle, "destroyInstance");
            if (destroyInstance && instance) {
                destroyInstance(instance);
            }
            dlclose(handle);
        }
    }

    T* getInstance() {
        return instance;
    }
};

#endif