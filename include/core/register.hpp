#pragma once

/* 
 * Register used by the emulation core
 */

#include <stdint.h>
#include <string>

namespace yae::core
{
    class IRegister
    {
    public:
        virtual std::string getName() = 0;

        virtual void setValue(size_t) = 0;
        virtual size_t getValue() = 0;

        virtual size_t shiftLeft(size_t) = 0;
        virtual size_t shiftRight(size_t) = 0;
        virtual size_t rotateLeft() = 0;
        virtual size_t rotateRight() = 0;

        virtual operator size_t() const = 0;
        virtual IRegister &operator=(size_t) = 0;
        virtual size_t operator|(size_t) = 0;
        virtual size_t operator&(size_t) = 0;

        virtual size_t operator<<(int) = 0;
        virtual size_t operator>>(int) = 0;
        virtual size_t operator<<(size_t) = 0;
        virtual size_t operator>>(size_t) = 0;

        virtual void setOnModifyWatchpoint(void (*)(IRegister &)) = 0;
    };

    template <size_t W>
    class Register : public IRegister
    {
    public:
        Register() : Register("NONAME") {}
        Register(std::string name)
        {
            this->name = name;

            for (size_t i = 0; i < W; i++)
                this->mask = this->mask | (0b1 << i);
        }

        inline std::string getName() { return name; }

        inline void setValue(size_t v)
        {
            this->value = v & mask;
            if (this->onRegisterSet)
                this->onRegisterSet(*this);
        }
        inline size_t getValue() { return this->value; }

        inline size_t rotateLeft()
        {
            this->value = ((this->value << 1) | (this->value >> (W - 1))) & this->mask;
            if (this->onRegisterSet)
                this->onRegisterSet(*this);
            return this->value;
        }
        inline size_t rotateRight()
        {
            this->value = ((this->value >> 1) | (this->value << (W - 1))) & this->mask;
            if (this->onRegisterSet)
                this->onRegisterSet(*this);
            return this->value;
        }
        inline size_t shiftLeft(size_t v)
        {
            this->value = (this->value << v) & this->mask;
            if (this->onRegisterSet)
                this->onRegisterSet(*this);
            return this->value;
        }
        inline size_t shiftRight(size_t v)
        {
            this->value = (this->value >> v) & this->mask;
            if (this->onRegisterSet)
                this->onRegisterSet(*this);
            return this->value;
        }

        inline operator size_t() const { return this->value; };
        inline Register &operator=(size_t v)
        {
            this->value = v & mask;
            if (this->onRegisterSet)
                this->onRegisterSet(*this);
            return *this;
        }
        inline size_t operator|(size_t v) { return (this->value | v) & this->mask; }
        inline size_t operator&(size_t v) { return this->value & v; }

        inline size_t operator<<(int v) { return (this->value << v) & this->mask; }
        inline size_t operator>>(int v) { return (this->value >> v) & this->mask; }
        inline size_t operator<<(size_t v) { return (this->value << v) & this->mask; }
        inline size_t operator>>(size_t v) { return (this->value >> v) & this->mask; }

        inline void setOnModifyWatchpoint(void (*f)(IRegister &)) { this->onRegisterSet = f; }

    private:
        size_t mask = 0;
        size_t value = 0;
        std::string name;

        void (*onRegisterSet)(IRegister &) = nullptr;
    };
} // namespace yae::core