#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <math.h>
#include <ostream>
#include <memory>

#include "HotDrinkFactory.hpp"
#include "DrinkFactory.hpp"

using namespace std;

int main() {
    DrinkFactory df;
    auto c =  df.make_drink("coffee");
    return 0;
}