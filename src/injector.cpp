#include "injector.hpp"
#include <dlfcn.h>
#include <algorithm>

namespace ell
{
    Injector::Injector()
    {
    }

    Injector::~Injector()
    {
        closeAllLib();
    }

    void *Injector::openLib(const std::string &path)
    {
        void* handler = dlopen(path.c_str(), RTLD_LAZY);
        if (!handler) {
            return nullptr;
        }
        libraries.push_back(handler);
        return handler;
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