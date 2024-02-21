#ifndef ELL_INJECTOR_API_HPP
#define ELL_INJECTOR_API_HPP

#include <string>

namespace ell
{
    class injectorInterface
    {
    public:
        virtual void *openLib(const std::string &path) = 0;
        virtual void *getSymbol(void *lib, const std::string &function) = 0;
        virtual void closeLib(void *lib) = 0;
    };
}

#endif