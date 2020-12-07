#pragma once

#include <string>

#include "breakpoint_provider.hpp"

namespace yae
{
    class Debugger
    {
    public:
        static Debugger &getInstance();

        int registerBreakpoint(const std::string &breakpointName);
        bool needToBreak(int breakpointId);

        void listenBreakpoint(int breakpointId, void (*breakpointHitFunction)(const IBreakpointProvider &));
        void notifyBreakpoint(int breakpointId, const IBreakpointProvider &);
    };
} // namespace yae