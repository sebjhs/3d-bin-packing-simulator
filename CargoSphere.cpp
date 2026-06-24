#include "CargoSphere.h"
#include <cmath>

constexpr double PI = 3.14159;
constexpr double SPHERE_AREA_MULT = 4.0;
constexpr double SPHERE_VOL_FRAC = 4.0 / 3.0;

CargoSphere::CargoSphere(const double radius) :
Cargo(SPHERE_AREA_MULT * PI * pow(radius, 2), SPHERE_VOL_FRAC * PI * pow(radius, 3)){
    this->radius = radius;
}

std::string CargoSphere::getType() const {
    return "Sphere";
}

double CargoSphere::getRadius() const {
    return this->radius;
}


