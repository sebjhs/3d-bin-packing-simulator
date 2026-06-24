#ifndef HELLOWORLD_CARGO_H
#define HELLOWORLD_CARGO_H
#include <string>

class Cargo {
protected:
    double area = 0;
    double volume = 0;
public:
    explicit Cargo(double area, double volume);
    virtual ~Cargo() = default;

    [[nodiscard]] virtual std::string getType() const = 0;
    [[nodiscard]] virtual double getArea() const;
    [[nodiscard]] virtual double getVolume() const;
};

#endif
