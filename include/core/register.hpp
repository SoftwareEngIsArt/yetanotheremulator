#pragma once

#include "debugger/breakpoint_provider.hpp"

#include <stdint.h>
#include <string>

namespace yae
{
    class Register : public IBreakpointProvider
    {
    public:
        enum RegisterFlags
        {
            ZERO,
            CARRY,
            OVERFLOW,
            NEGATIVE,
        };

        Register() = delete;
        Register(std::string name, ushort width, bool useFlags = true);
        Register(std::string name, ushort width, size_t value, bool useFlags = true);
        Register(Register &&other);
        Register(const Register &other);

        void setWidth(ushort width);
        void setValue(size_t value);

        Register &operator=(const Register &other);
        Register &operator=(size_t value);
        operator size_t();

        Register &operator+(size_t value);
        Register &operator++();
        Register &operator++(int);
        Register &operator+=(size_t value);

        Register &operator-(size_t value);
        Register &operator--();
        Register &operator--(int);
        Register &operator-=(size_t value);

    protected:
        RegisterFlags getArithmeticOperationFlags(size_t x, size_t y, size_t res);

        bool useFlags;
        RegisterFlags localFlags;

        ushort width;
        size_t mask;

        size_t value;

        std::string debugName;
    };

    Register::RegisterFlags operator|(Register::RegisterFlags x, Register::RegisterFlags y);
    Register::RegisterFlags operator&(Register::RegisterFlags x, Register::RegisterFlags y);
    Register::RegisterFlags operator~(Register::RegisterFlags x);

} // namespace yae