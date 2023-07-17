#ifndef LIBRARY_H
#define LIBRARY_H

class Shape
{
public:
    // Adding the new method here breaks the ABI.
    virtual double perimeter() const = 0;
    virtual double area() const = 0;
    // Adding the new method here does not break the ABI.
    // virtual double perimeter() const = 0;
};

class Rectangle : public Shape
{
private:
    double m_width;
    double m_height;

public:
    Rectangle(double w, double h);
    double perimeter() const override;
    double area() const override;
};

#endif // LIBRARY_H