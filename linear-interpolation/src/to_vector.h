#ifndef TO_VECTOR_H
#define TO_VECTOR_H

#include <ranges>
#include <vector>

template <std::ranges::range R>
auto to_vector(R&& r) {
    std::vector<std::ranges::range_value_t<R>> v;

    // if we can get a size, reserve that much
    if constexpr (requires { std::ranges::size(r); }) {
        v.reserve(std::ranges::size(r));
    }

    // push all the elements
    for (auto&& e : r) {
        v.push_back(static_cast<decltype(e)&&>(e));
    }

    return v;
}

#endif
