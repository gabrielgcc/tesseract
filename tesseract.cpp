#include "raylib.h"
#include <array>

using namespace std;

/*

TODO:
- Fix vscodium errors
- Update tesseract
*/

class Point {
public:
    void setCoords(float x, float y, float z) {
        coordx = x;
        coordy = y;
        coordz = z;
    }

    Vector3 returnCoords() const {  // Ahora es const
        return (Vector3){ coordx, coordy, coordz };
    }

private:
    float coordx, coordy, coordz;
};

class Tesseract {
public:
    Tesseract() {
        constexpr float scales[] = {1.0f, 2.0f}; // Para el cubo pequeño y grande

        int idx = 0;
        for (float scale : scales) {
            for (int i = 0; i < 8; ++i) {
                float x = ((i & 1) ? -1.0f : 1.0f) * scale;
                float y = ((i & 2) ? -1.0f : 1.0f) * scale;
                float z = ((i & 4) ? -1.0f : 1.0f) * scale;
                points[idx++].setCoords(x, y, z);
            }
        }
    }


    void drawTesseract() {
        // 1) Aristas del cubo pequeño (índices 0–7)
        for (int i = 0; i < 8; ++i) {
            // Recorre las 3 dimensiones: 0=x, 1=y, 2=z
            for (int axis = 0; axis < 3; ++axis) {
                int j = i ^ (1 << axis);          // Muta el bit correspondiente
                if (i < j)                        // Para no dibujar cada arista dos veces
                    drawLine(points[i], points[j]);
            }
        }

        // 2) Aristas del cubo grande (índices 8–15)
        for (int i = 8; i < 16; ++i) {
            for (int axis = 0; axis < 3; ++axis) {
                int j = (i ^ (1 << axis));
                // Asegúrate de que j también esté en [8..15]
                if (j > i && j < 16)
                    drawLine(points[i], points[j]);
            }
        }

        // 3) Aristas que unen cada vértice pequeño con el vértice grande correspondiente
        //    (i con i+8 para i = 0..7)
        for (int i = 0; i < 8; ++i) {
            drawLine(points[i], points[i + 8]);
        }
    }

private:
    array<Point, 16> points;

    void drawLine(const Point& a, const Point& b) {
        DrawLine3D(a.returnCoords(), b.returnCoords(), MAROON);
    }
};

int main (int argc, char *argv[]) {
  
  const int screenWidth = 800;
  const int screenHeight= 600;

  InitWindow(screenWidth, screenHeight, "Tesseract simulation");

  // Define the camera to look into our 3d world
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f };  // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type

    Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };
    Tesseract tesseract;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
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
