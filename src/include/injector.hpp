#ifndef ELL_INJECTOR_HPP
#define ELL_INJECTOR_HPP

#include <string>
#include <map>
#include "injector_api.hpp"

namespace ell
{
    struct LibraryDestroyer
    {
        Library lib = nullptr;
        ~LibraryDestroyer();
    };

    class Injector : public ell::InjectorInterface
    {
    private:
        std::map<std::string, LibraryDestroyer, std::less<>> libraries;

    public:
        Injector() = default;
        ~Injector() override;
        Library openLib(const std::string &path) override;
        Library openLib(const std::string &path, const std::string &name) override;
        const std::string &getName(Library lib) override;
        Library getLib(const std::string &name) override;
        Symbol getSymbol(Library lib, const std::string &function) override;
        Symbol getSymbol(const std::string &name, const std::string &function) override;
        void closeAllLib();
        void closeLib(Library lib) override;
    };
}

#endif