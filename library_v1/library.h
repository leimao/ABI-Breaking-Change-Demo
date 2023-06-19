#ifndef LIBRARY_H
#define LIBRARY_H

class Shape
{
public:
    virtual double area() const = 0;
};

class Rectangle : public Shape
{
private:
    double m_width;
    double m_height;

public:
    Rectangle(double w, double h);
    double area() const override;
};

#endif // LIBRARY_H