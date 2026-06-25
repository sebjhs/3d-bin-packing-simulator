//
// Created by Sebastian Hinchey on 24/06/2026.
//

#ifndef INC_3D_BIN_PACKING_SIMULATOR_CUBE_H
#define INC_3D_BIN_PACKING_SIMULATOR_CUBE_H

#include "Shape.h"

class Cube : public Shape {
private:
    float side;
public:
    Cube(float size, Vector3 spawnPos) : side(size) {
        position = spawnPos;
    }

    std::string getType() const override { return "Cube"; }
    float getVolume() const override { return side * side * side; }

    float getBoundingWidth() const override { return side; }
    float getBoundingLength() const override { return side; }
    float getBoundingHeight() const override { return side; }

    void draw() const override {
        Vector3 renderCenter = { position.x, position.y + (side / 2.0f), position.z };
        DrawCube(renderCenter, side, side, side, displayColor);
        DrawCubeWires(renderCenter, side, side, side, DARKGRAY);
    }

};


#endif //INC_3D_BIN_PACKING_SIMULATOR_CUBE_H
