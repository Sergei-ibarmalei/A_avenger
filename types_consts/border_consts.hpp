#ifndef BORDER_CONSTS_HPP
#define BORDER_CONSTS_HPP

#define to_float static_cast<float>

#include "graph_consts.hpp"

namespace border_consts
{
    using namespace graph_consts;

    constexpr float BORDER_LEFT   {0.0f};
    constexpr float BORDER_RIGHT  {to_float(S_W - 1)};
    constexpr float BORDER_UP     {50.0f};
    constexpr float BORDER_DOWN   {to_float(S_H - 1)};
}

#endif