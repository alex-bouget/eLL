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
        return openLib(path, fs::path(path).stem());
    }

    Library Injector::openLib(const std::string &path, const std::string &name)
    {
        void *handler = dlopen(path.c_str(), RTLD_LAZY);
        if (!handler)
        {
            return nullptr;
        }
        libraries.insert(std::pair<std::string, Library>(name, handler));
        return handler;
    }

    const std::string &Injector::getName(Library lib)
    {
        auto finded = std::find_if(
            libraries.begin(),
            libraries.end(),
            [lib](const std::pair<std::string, void *> &p)
            {
                return p.second == lib;
            });
        if (finded == libraries.end())
        {
            return "";
        }
        return (*finded).first;
    }

    Library Injector::getLib(const std::string &name)
    {
        return libraries[name];
    }

    Symbol Injector::getSymbol(Library lib, const std::string &symbol_name)
    {
        void *symbol = dlsym(lib, symbol_name.c_str());
        const char *dlsym_error = dlerror();
        if (dlsym_error)
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
        for (auto &lib : libraries)
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