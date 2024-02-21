#ifndef ELL_INJECTOR_HPP
#define ELL_INJECTOR_HPP

#include <string>
#include <vector>
#include "injector_api.hpp"

namespace ell
{
    class Injector : public ell::injectorInterface
    {
    private:
        std::vector<void *> libraries;

    public:
        Injector();
        ~Injector();
        void *openLib(const std::string &path);
        void *getSymbol(void *lib, const std::string &function);
        void closeAllLib();
        void closeLib(void *lib);
    };
}

#endif