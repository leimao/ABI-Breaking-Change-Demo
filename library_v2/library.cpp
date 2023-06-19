#include "library.h"

Rectangle::Rectangle(double w, double h) : m_width(w), m_height(h) {}

double Rectangle::area() const { return m_width * m_height; }

double Rectangle::perimeter() const { return 2 * (m_width + m_height); }