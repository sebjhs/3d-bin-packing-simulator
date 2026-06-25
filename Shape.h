//
// Created by Sebastian Hinchey on 24/06/2026.
//

#ifndef INC_3D_BIN_PACKING_SIMULATOR_SHAPE_H
#define INC_3D_BIN_PACKING_SIMULATOR_SHAPE_H

#include <string>
#include "raylib.h"


class Shape {
protected:
    Vector3 position = {0.0f, 0.0f, 0.0f};
    Vector3 velocity = {0.0f, 0.0f, 0.0f};
    Color displayColor;
    bool isGrounded = false;
public:
    Shape() {
        displayColor = (Color){ static_cast<unsigned char>(GetRandomValue(40, 220)),
                                static_cast<unsigned char>(GetRandomValue(40, 220)),
                                static_cast<unsigned char>(GetRandomValue(40, 220)),
                                255};
    }
    virtual ~Shape() = default;

    [[nodiscard]] virtual std::string getType() const = 0;
    [[nodiscard]] virtual float getVolume() const = 0;

    [[nodiscard]] virtual float getBoundingWidth() const = 0;
    [[nodiscard]] virtual float getBoundingLength() const = 0;
    [[nodiscard]] virtual float getBoundingHeight() const = 0;

    [[nodiscard]] Vector3 getPosition() const { return position; }
    void setPosition(Vector3 pos) { position = pos; }

    [[nodiscard]] Vector3 getVelocity() const { return velocity; }
    void setVelocity(Vector3 vel) { velocity = vel; }

    [[nodiscard]] bool getGrounded() const { return isGrounded; }
    void setGrounded(bool grounded) { isGrounded = grounded; }

    [[nodiscard]] Color getColor() const { return displayColor; }

    void updatePhysics(float deltaTime, float containerHeight) {
        if (!isGrounded) {
            velocity.y -= 9.81f * deltaTime;
            position.y += velocity.y * deltaTime;

            if (position.y <= 0.0f) {
                position.y = 0.0f;
                velocity.y = 0.0f;
                isGrounded = true;
            }
        }
    }

    virtual void draw() const = 0;
};


#endif //INC_3D_BIN_PACKING_SIMULATOR_SHAPE_H
