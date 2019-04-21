#pragma once

#include <boost/variant.hpp>

#include "../group_a/item_a.hpp"
#include "../group_a/set_a1.hpp"
#include "../group_a/set_a2.hpp"
#include "../group_a/set_a3.hpp"
#include "../group_a/set_a4.hpp"

#include "../group_b/item_b.hpp"
#include "../group_b/set_b1.hpp"
#include "../group_b/set_b2.hpp"
#include "../group_b/set_b3.hpp"
#include "../group_b/set_b4.hpp"

#include "../group_c/item_c.hpp"
#include "../group_c/set_c1.hpp"
#include "../group_c/set_c2.hpp"
#include "../group_c/set_c3.hpp"
#include "../group_c/set_c4.hpp"

#include "../group_d/item_d.hpp"
#include "../group_d/set_d1.hpp"
#include "../group_d/set_d2.hpp"
#include "../group_d/set_d3.hpp"
#include "../group_d/set_d4.hpp"

namespace dla
{
    typedef boost::variant<
        matrix<item_a>,
        matrix<item_b>,
        matrix<item_c>,
        matrix<item_d>
            > vmatrix;
}