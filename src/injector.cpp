#include "injector.hpp"
#include <dlfcn.h>
#include <algorithm>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

namespace ell
{
    Injector::Injector()
    {
    }

    Injector::~Injector()
    {
        closeAllLib();
    }

    Library Injector::openLib(const std::string &path)
    {
        return openLib(path, fs::path(path).filename());
    }

    Library Injector::openLib(const std::string &path, const std::string &name)
    {
        void* handler = dlopen(path.c_str(), RTLD_LAZY);
        if (!handler) {
            return nullptr;
        }
        libraries.insert(std::pair<std::string, Library>(name, handler));
        return handler;

    }
    Library getLib(const std::string &name)
    {
    }

    void *Injector::getSymbol(void *lib, const std::string &symbol_name)
    {
        void *symbol = dlsym(lib, symbol_name.c_str());
        const char *dlsym_error = dlerror();
        if (dlsym_error)
        {
            return nullptr;
        }
        return symbol;
    }

    void Injector::closeAllLib()
    {
        for (auto &lib : libraries)
        {
            closeLib(lib);
        }
    }

    void Injector::closeLib(void *lib)
    {
        dlclose(lib);
        std::vector<void*>::iterator position = std::find(libraries.begin(), libraries.end(), lib);
        if (position != libraries.end()) {
            libraries.erase(position);
        }
    }
}