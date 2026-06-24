#include "Cargo.h"

Cargo::Cargo(const double area, const double volume) {
    this->area = area;
    this->volume = volume;
}
double Cargo::getArea() const {
    return this->area;
}

double Cargo::getVolume() const {
    return this->volume;
}
