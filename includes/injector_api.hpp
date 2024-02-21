#ifndef ELL_INJECTOR_API_HPP
#define ELL_INJECTOR_API_HPP

#include <string>

namespace ell
{
    typedef void *Library;
    typedef void *Symbol;

    class InjectorInterface
    {
    public:
        virtual Library openLib(const std::string &path) = 0;
        virtual Library openLib(const std::string &path, const std::string &name) = 0;
        virtual Library getLib(const std::string &name) = 0;
        virtual Symbol getSymbol(void *lib, const std::string &function) = 0;
        virtual Symbol getSymbol(const std::string &name, const std::string &function) = 0;
        virtual void closeLib(void *lib) = 0;
    };
}

#endif