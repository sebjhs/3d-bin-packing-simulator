//
// Created by Sebastian Hinchey on 24/06/2026.
//

#include "raylib.h"
#include <vector>
#include <memory>

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "raymath.h"

#include "Shape.h"
#include "Cube.h"

int main() {
    // window initialisation
    constexpr int screenWidth = 1280;
    constexpr int screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "3D Bin Packing Simulator");

    // initial box dimensions
    float boxWidth = 6.0f;
    float boxHeight = 4.0f;
    float boxDepth = 5.0f;

    // 3D Camera
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 12.0f, 10.0f, 12.0f };
    camera.target = (Vector3){ 0.0f, 2.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    float cameraAngleX = 0.78f;
    float cameraAngleY = 0.60f;
    float cameraRadius = 15.0f;

    SetTargetFPS(60);

    std::vector<std::unique_ptr<Shape>> spawnedShapes;

    // main simulation loop
    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_SPACE)) {
            const float randX = static_cast<float>(GetRandomValue(-200, 200)) / 100.0f;
            const float randZ = static_cast<float>(GetRandomValue(-200, 200)) / 100.0f;
            spawnedShapes.push_back(std::make_unique<Cube>(1.5f, (Vector3){ randX, boxHeight + 2.0f, randZ}));
        }

        float dt = GetFrameTime();
        for (auto& shape : spawnedShapes) {
            shape->updatePhysics(dt, boxHeight);
        }
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT) && GetMouseX() > 300) {
            auto [x, y] = GetMouseDelta();

            cameraAngleX -= x * 0.005f;
            cameraAngleY += y * 0.005f;

            if (cameraAngleY > 1.4f) cameraAngleY = 1.4f;
            if (cameraAngleY < 0.1f) cameraAngleY = 0.1f;
        }

        if (GetMouseX() > 300) {
            const float wheelMove = GetMouseWheelMove();
            cameraRadius -= wheelMove * 0.8f;

            if (cameraRadius < 3.0f) cameraRadius = 3.0f;
            if (cameraRadius > 35.0f) cameraRadius = 35.0f;
        }

        camera.position.x = camera.target.x + cameraRadius * cosf(cameraAngleY) * sinf(cameraAngleX);
        camera.position.y = camera.target.y + cameraRadius * sinf(cameraAngleY);
        camera.position.z = camera.target.z + cameraRadius * cosf(cameraAngleY) * cosf(cameraAngleX);


        // 3D Graphics
        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode3D(camera);
        for (const auto& shape : spawnedShapes) {
            shape->draw();
        }
        DrawGrid(20, 1.0f);
        const Vector3 boxCenter = { 0.0f, boxHeight / 2.0f, 0.0f};
        DrawCubeWires(boxCenter, boxWidth, boxHeight, boxDepth, GRAY);
        DrawCube(boxCenter, boxWidth, boxHeight, boxDepth, Fade(SKYBLUE, 0.15f));
        EndMode3D();

        // UI Interface overlay (2D)
        DrawRectangle(0, 0, 300, screenHeight, Fade(LIGHTGRAY, 0.6f));
        DrawRectangleLines(300, 0, 1, screenHeight, GRAY);
        DrawText("CONTAINER CONTROL PANEL", 20, 20, 18, DARKGRAY);

        // width slider
        DrawText("Container Width (X):", 20, 70, 14, DARKGRAY);
        GuiSlider((Rectangle){ 20, 90, 200, 20 }, NULL, TextFormat("%.2fm", boxWidth), &boxWidth, 1.0f, 15.0f);

        // height slider
        DrawText("Container Height (Y):", 20, 130, 14, DARKGRAY);
        GuiSlider((Rectangle){ 20, 150, 200, 20 }, NULL, TextFormat("%.2fm", boxHeight), &boxHeight, 1.0f, 10.0f);

        // depth slider
        DrawText("Container Depth (Z):", 20, 190, 14, DARKGRAY);
        GuiSlider((Rectangle){ 20, 210, 200, 20 }, NULL, TextFormat("%.2fm", boxDepth), &boxDepth, 1.0f, 15.0f);

        // display calculated capacity metrics
        float totalVolume = boxWidth * boxHeight * boxDepth;
        DrawText("Engine Metrics:", 20, 280, 16, DARKGRAY);
        DrawText(TextFormat("Total Capacity: %.2f m³", totalVolume), 20, 310, 14, BLUE);

        // instruction help
        DrawText("Controls:", 20, screenHeight - 60, 14, DARKGRAY);
        DrawText("Right-click & drag to rotate camera", 20, screenHeight - 40, 12, GRAY);
        DrawText("Scroll mouse wheel to zoom in/out", 20, screenHeight - 40, 12, GRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
