#pragma once

/*
 * Base CPU core
 */

#include <stdint.h>

#include "register.hpp"

namespace yae::core
{
    class ICore
    {
    public:
        virtual void Clock() = 0;
    };

    template <typename... R>
    class Core : public ICore
    {
    public:

        
    };
} // namespace yae