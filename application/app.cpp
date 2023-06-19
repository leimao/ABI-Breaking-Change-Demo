#include "library.h"
#include <iostream>
#include <memory>
#include <stdexcept>

int main()
{
    double const width{5.0};
    double const height{3.0};
    std::unique_ptr<Shape> rect{std::make_unique<Rectangle>(width, height)};
    double const area{rect->area()};
    std::cout << "Area: " << area << std::endl;
    if (area != width * height)
    {
        throw std::runtime_error{"Area is not correct."};
    }
    return 0;
}