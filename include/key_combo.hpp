#pragma once
#include <iterator>
#include <phys_key.hpp>
#include <concepts>
#include <ranges>

struct KeyCombo {
    std::array<std::optional<PhysKey>, 3> keys;

    template <std::convertible_to<PhysKey>... Ts>
    requires (0 < sizeof...(Ts)) && (sizeof...(Ts) <= 3)
    constexpr KeyCombo(Ts&&... keys)
        : keys{std::forward<Ts>(keys)...}
    {
    }

    PhysKey& operator[](int index) { return keys.at(index).value(); }
    const PhysKey& operator[](int index) const { return keys.at(index).value(); }

    auto key_list() {
        return keys
            | std::ranges::views::take_while([](std::optional<PhysKey> key) { return key.has_value(); })
            | std::ranges::views::transform([](std::optional<PhysKey> key) { return key.value(); });
    }
};
