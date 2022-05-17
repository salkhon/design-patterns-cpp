#pragma once

#include "HotDrink.hpp"

/**
 * @brief Abstract Factory from which we inherit and make vertain products.
 * 
 */
struct HotDrinkFactory {
    virtual std::unique_ptr<HotDrink> make() const = 0;
};

struct TeaFactory : HotDrinkFactory {
    std::unique_ptr<HotDrink> make() const override {
        return std::make_unique<Tea>();
    }
};

struct CoffeeFactory : HotDrinkFactory {
    std::unique_ptr<HotDrink> make() const override {
        return std::make_unique<Coffee>();
    }
};