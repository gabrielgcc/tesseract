#include "raylib.h"
#include <array>
#include <cstddef>

using namespace std;

/*
TODO:
- Fix vscodium errors
- Draw the edges (better)
- Animate the points
- Un-hardcode tesseract vertexes
- struct colours to debug
*/

typedef float Matrix3x4[3][4];
typedef struct {

} Colours;

class Tesseract {
public:
    Tesseract() {
        points[0] = {-1.0f, -1.0f, -1.0f, -1.0f};
        points[1] = {-1.0f, -1.0f, -1.0f, 1.0f};
        points[2] = {-1.0f, -1.0f, 1.0f, -1.0f};
        points[3] = {-1.0f, -1.0f, 1.0f, 1.0f};
        points[4] = {-1.0f, 1.0f, -1.0f, -1.0f};
        points[5] = {-1.0f, 1.0f, -1.0f, 1.0f};
        points[6] = {-1.0f, 1.0f, 1.0f, -1.0f};
        points[7] = {-1.0f, 1.0f, 1.0f, 1.0f};
        points[8] = {1.0f, -1.0f, -1.0f, -1.0f};
        points[9] = {1.0f, -1.0f, -1.0f, 1.0f};
        points[10] = {1.0f, -1.0f, 1.0f, -1.0f};
        points[11] = {1.0f, -1.0f, 1.0f, 1.0f};
        points[12] = {1.0f, 1.0f, -1.0f, -1.0f};
        points[13] = {1.0f, 1.0f, -1.0f, 1.0f};
        points[14] = {1.0f, 1.0f, 1.0f, -1.0f};
        points[15] = {1.0f, 1.0f, 1.0f, 1.0f};
    }

    void drawTesseract() {
        array<Vector3, 16> V = projected();
        
        for (int i = 0; i < 16; ++i) {
            DrawCube(V[i], 0.2f, 0.2f, 0.2f, RED);
            for (int d = 0; d < 4; ++d) {
                int j = i ^ (1 << d);
                if (j > i) { 
                    DrawLine3D(V[i], V[j], MAROON);
                }
            }
        }
    }

private:
    array<Vector4, 16> points;

    Vector3 project (Vector4 v) {
        Vector3 result;
        
        float distance = 0.5f;
        float w = 1.0f / (distance - v.w);

        // R4 -> R3 projection matrix
        Matrix3x4 m = {
        {w, 0.0f, 0.0f, 0.0f},
        {0.0f, w, 0.0f, 0.0f},
        {0.0f, 0.0f, w, 0.0f}
        };

        // Multiply vector * matrix
        //----------------------------------------------------------------------------------
        result.x = m[0][0]*v.x + m[0][1]*v.y + m[0][2]*v.z + m[0][3]*v.w;
        result.y = m[1][0]*v.x + m[1][1]*v.y + m[1][2]*v.z + m[1][3]*v.w;
        result.z = m[2][0]*v.x + m[2][1]*v.y + m[2][2]*v.z + m[2][3]*v.w;
        //----------------------------------------------------------------------------------

        return result;
    }

    array<Vector3, 16> projected() {
        array<Vector3, 16> r;

        for (size_t i = 0; i < 16; ++i) {
            r[i] = project(points[i]);
        }

        return r;
    }
};

int main () {
  
  const int screenWidth = 800;
  const int screenHeight= 600;

  InitWindow(screenWidth, screenHeight, "Tesseract simulation");

  // Define the camera to look into our 3d world
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f }; // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type
    
    DisableCursor();

    Tesseract tesseract;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(&camera, CAMERA_FREE);

        if (IsKeyPressed('Z')) camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);

                tesseract.drawTesseract();

            EndMode3D();

            DrawFPS(10, 10);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

  CloseWindow();

  return 0;
}
