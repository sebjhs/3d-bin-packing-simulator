#include "CargoCube.h"

#include "CargoSphere.h"

constexpr int CUBE_FACES = 6;

CargoCube::CargoCube(const double sideLength) :
Cargo(sideLength * sideLength * CUBE_FACES, sideLength * sideLength * sideLength) {
    this->sideLength = sideLength;
}

std::string CargoCube::getType() const {
    return "Cube";
}

double CargoCube::getSideLength() const {
    return this->sideLength;
}
