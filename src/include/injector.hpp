#ifndef ELL_INJECTOR_HPP
#define ELL_INJECTOR_HPP

#include <string>
#include <map>
#include "injector_api.hpp"

namespace ell
{
    class Injector : public ell::InjectorInterface
    {
    private:
        std::map<std::string, Library> libraries;

    public:
        Injector();
        ~Injector();
        Library openLib(const std::string &path);
        Library openLib(const std::string &path, const std::string &name);
        Library getLib(const std::string &name);
        Symbol getSymbol(void *lib, const std::string &function);
        Symbol getSymbol(const std::string &name, const std::string &function);
        void closeAllLib();
        void closeLib(void *lib);
    };
}

#endif