#include "injector.hpp"
#include <dlfcn.h>
#include <algorithm>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

namespace ell
{
    Injector::~Injector()
    {
        closeAllLib();
    }

    Library Injector::openLib(const std::string &path)
    {
        return openLib(path, fs::path(path).stem());
    }

    Library Injector::openLib(const std::string &path, const std::string &name)
    {
        void *handler = dlopen(path.c_str(), RTLD_LAZY);
        if (!handler)
        {
            return nullptr;
        }
        libraries.try_emplace(name, handler);
        return handler;
    }

    const std::string &Injector::getName(Library lib)
    {
        auto search = [lib](const std::pair<std::string, Library> &p)
        {
            return p.second == lib;
        };
        auto finded = std::ranges::find_if(libraries, search);
        return (*finded).first;
    }

    Library Injector::getLib(const std::string &name)
    {
        return libraries[name];
    }

    Symbol Injector::getSymbol(Library lib, const std::string &symbol_name)
    {
        void *symbol = dlsym(lib, symbol_name.c_str());
        if (dlerror())
        {
            return nullptr;
        }
        return symbol;
    }

    Symbol Injector::getSymbol(const std::string &name, const std::string &function)
    {
        return getSymbol(getLib(name), function);
    }

    void Injector::closeAllLib()
    {
        for (const auto &lib : libraries)
        {
            closeLib(lib.second);
        }
    }

    void Injector::closeLib(Library lib)
    {
        dlclose(lib);
        libraries.erase(getName(lib));
    }
}