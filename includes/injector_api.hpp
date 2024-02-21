#ifndef ELL_INJECTOR_API_HPP
#define ELL_INJECTOR_API_HPP

#include <string>

namespace ell
{
    using Library = void *;
    using Symbol = void *;

    class InjectorInterface
    {
    public:
        virtual ~InjectorInterface() = default;
        virtual Library openLib(const std::string &path) = 0;
        virtual Library openLib(const std::string &path, const std::string &name) = 0;
        virtual const std::string &getName(Library lib) = 0;
        virtual Library getLib(const std::string &name) = 0;
        virtual Symbol getSymbol(Library lib, const std::string &function) = 0;
        virtual Symbol getSymbol(const std::string &name, const std::string &function) = 0;
        virtual void closeLib(Library lib) = 0;
    };
}

#endif