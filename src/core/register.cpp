#include <utility>

#include "register.hpp"

using namespace yae;

Register::RegisterFlags yae::operator|(Register::RegisterFlags x, Register::RegisterFlags y)
{
    return static_cast<Register::RegisterFlags>(static_cast<ushort>(x) | static_cast<ushort>(y));
}
Register::RegisterFlags yae::operator&(Register::RegisterFlags x, Register::RegisterFlags y)
{
    return static_cast<Register::RegisterFlags>(static_cast<ushort>(x) & static_cast<ushort>(y));
}
Register::RegisterFlags yae::operator~(Register::RegisterFlags x)
{
    return static_cast<Register::RegisterFlags>(~static_cast<ushort>(x));
}

Register::Register(std::string name, ushort width, bool useFlags) : Register(name, width, 0, useFlags) {}
Register::Register(std::string name, ushort width, size_t value, bool useFlags)
{
    this->useFlags = useFlags;
    this->localFlags = static_cast<RegisterFlags>(0);
    this->debugName = name;
    setWidth(width);
    setValue(value);
}
Register::Register(Register &&other)
{
    this->useFlags = other.useFlags;
    this->width = other.width;
    this->mask = other.mask;
    this->value = other.value;
    this->localFlags = other.localFlags;

    this->debugName = std::move(other.debugName);
}
Register::Register(const Register &other)
{
    this->useFlags = other.useFlags;
    this->width = other.width;
    this->mask = other.mask;
    this->value = other.value;
    this->localFlags = other.localFlags;

    this->debugName = other.debugName;
}

Register::RegisterFlags Register::getArithmeticOperationFlags(size_t x, size_t y, size_t res)
{
    size_t negativeMask = this->mask & ~(this->mask >> 1);
    RegisterFlags resultFlags = static_cast<RegisterFlags>(0);

    /* Check carry */
    if (res > this->mask)
        resultFlags = resultFlags | RegisterFlags::CARRY;
    /* Check overflow */
    if ((~(x ^ y)) & (x ^ res) & negativeMask)
        resultFlags = resultFlags | RegisterFlags::OVERFLOW;
    /* Check zero */
    if (!(res & this->mask))
        resultFlags = resultFlags | RegisterFlags::ZERO;
    /* Check negative */
    if (res & negativeMask)
        resultFlags = resultFlags | RegisterFlags::NEGATIVE;

    return resultFlags;
}

void Register::setWidth(ushort width)
{
    if (this->width == width)
        return;

    /* Set the mask */
    this->width = width;
    this->mask = 0;
    for (ushort i = 0; i < width; i++)
        this->mask = (this->mask << 1) | 0b1;
}
void Register::setValue(size_t value)
{
    this->value = value & mask;

    if (!this->useFlags)
        return;

    /* Update flags */
    if (!this->value)
        this->localFlags = this->localFlags | Register::RegisterFlags::ZERO;
    else
        this->localFlags = this->localFlags & ~Register::RegisterFlags::ZERO;

    if (this->value & ~(this->mask >> 1))
        this->localFlags = this->localFlags | Register::RegisterFlags::NEGATIVE;
    else
        this->localFlags = this->localFlags & ~Register::RegisterFlags::NEGATIVE;
}

Register &Register::operator=(const Register &other)
{
    this->value = other.value & this->mask;

    if (this->useFlags)
    {
        /* Update flags */
        if (!this->value)
            this->localFlags = this->localFlags | Register::RegisterFlags::ZERO;
        else
            this->localFlags = this->localFlags & ~Register::RegisterFlags::ZERO;

        if (this->value & ~(this->mask >> 1))
            this->localFlags = this->localFlags | Register::RegisterFlags::NEGATIVE;
        else
            this->localFlags = this->localFlags & ~Register::RegisterFlags::NEGATIVE;
    }

    return *this;
}
Register &Register::operator=(size_t value)
{
    this->value = value & mask;

    if (this->useFlags)
    {
        /* Update flags */
        if (!this->value)
            this->localFlags = this->localFlags | Register::RegisterFlags::ZERO;
        else
            this->localFlags = this->localFlags & ~Register::RegisterFlags::ZERO;

        if (this->value & ~(this->mask >> 1))
            this->localFlags = this->localFlags | Register::RegisterFlags::NEGATIVE;
        else
            this->localFlags = this->localFlags & ~Register::RegisterFlags::NEGATIVE;
    }

    return *this;
}
Register::operator size_t() { return this->value; }

Register &Register::operator+(size_t value)
{
    size_t res = value + this->value;
    if (this->useFlags)
        this->localFlags = getArithmeticOperationFlags(this->localFlags, value, res);
    this->value = res & this->mask;
    return *this;
}
Register &Register::operator++() { return *this += 1; }
Register &Register::operator++(int) { return *this += 1; }
Register &Register::operator+=(size_t value)
{
    /* Find the result */
    size_t result = this->value + value;

    /* Update flags */
    if (this->useFlags)
        this->localFlags = getArithmeticOperationFlags(this->localFlags, value, result);
    /* Set the result */
    this->value = result & this->mask;

    return *this;
}

Register &Register::operator-(size_t value)
{
    size_t res = value - this->value;
    if (this->useFlags)
        this->localFlags = getArithmeticOperationFlags(this->localFlags, value, res);
    this->value = res & this->mask;
    return *this;
}
Register &Register::operator--() { return *this -= 1; }
Register &Register::operator--(int) { return *this -= 1; }
Register &Register::operator-=(size_t value)
{
    /* Find the result */
    size_t result = this->value - value;

    /* Update flags */
    if (this->useFlags)
        this->localFlags = getArithmeticOperationFlags(this->localFlags, value, result);
    /* Set the result */
    this->value = result & this->mask;

    return *this;
}
