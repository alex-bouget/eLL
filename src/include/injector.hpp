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
        const std::string &getName(Library lib);
        Library getLib(const std::string &name);
        Symbol getSymbol(Library lib, const std::string &function);
        Symbol getSymbol(const std::string &name, const std::string &function);
        void closeAllLib();
        void closeLib(Library lib);
    };
}

#endif