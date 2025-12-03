#include "raylib.h"
#include "time.h"

#define STAR_COUNT 300

typedef enum
{
    PANT_MENU,
    PANT_TUTORIAL,
    PANT_NIVEL1,
    PANT_NIVEL2,
    PANT_NIVEL3
} Pantalla;

typedef struct
{
    Vector2 pos;
    float speed;
} Star;

static Star stars[STAR_COUNT];

void iniciar_estrellas(int screenWidth, int screenHeight);
void dibujar_estrellas(float dt, int screenWidth, int screenHeight);
void PantallaMenu(Pantalla *pantallaActual, Texture2D logo, int screenWidth, int screenHeight);
void DibujarAlien1(int x, int y, int pixelSize);
void DibujarAlien2(int x, int y, int pixelSize);
void DibujarAlien3(int x, int y, int pixelSize);
void DibujarAlien4(int x, int y, int pixelSize);
void DibujarJugador(int x, int y, int pixelSize);

int main(void)
{
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "SPACE SURVIVORS");
    InitAudioDevice();
    SetTargetFPS(60);

    Texture2D logo = LoadTexture("assets/images/SPACE_SURVIVORS.png");
    Music musicaMenu = LoadMusicStream("assets/music/menu_intro.mp3");
    PlayMusicStream(musicaMenu);

    iniciar_estrellas(screenWidth, screenHeight);

    Pantalla Pantalla_Actual = PANT_MENU;

    while (!WindowShouldClose())
    {
        UpdateMusicStream(musicaMenu);

        float dt = GetFrameTime();

        BeginDrawing();
        ClearBackground(BLACK);

        dibujar_estrellas(dt, screenWidth, screenHeight);

        switch (Pantalla_Actual)
        {
        case PANT_MENU:
            PantallaMenu(&Pantalla_Actual, logo, screenWidth, screenHeight);
            break;
        }

        EndDrawing();
    }

    UnloadTexture(logo);
    UnloadMusicStream(musicaMenu);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}

void iniciar_estrellas(int screenWidth, int screenHeight)
{
    for (int i = 0; i < STAR_COUNT; i++)
    {
        stars[i].pos.x = (float)GetRandomValue(0, screenWidth);
        stars[i].pos.y = (float)GetRandomValue(0, screenHeight);
        stars[i].speed = (float)GetRandomValue(40, 200) / 10.0f;
    }
}
void dibujar_estrellas(float dt, int screenWidth, int screenHeight)
{
    for (int i = 0; i < STAR_COUNT; i++)
    {
        stars[i].pos.y += stars[i].speed * dt;

        if (stars[i].pos.y > screenHeight)
        {
            stars[i].pos.y = 0;
            stars[i].pos.x = (float)GetRandomValue(0, screenWidth);
        }

        DrawPixelV(stars[i].pos, WHITE);
    }
}
void PantallaMenu(Pantalla *pantallaActual, Texture2D logo, int screenWidth, int screenHeight)
{
    float targetWidth = screenWidth * 0.40f;
    float scale = targetWidth / logo.width;
    static float timer = 0;
    static int frame = 0;

    timer += GetFrameTime();
    if (timer >= 1.0f)
    {
        frame = 1 - frame;
        timer = 0;
    }

    float posX = 0;
    float posY = -70;

    Vector2 mouse = GetMousePosition();
    bool click = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

    DrawTextureEx(logo, (Vector2){posX, posY}, 0.0f, scale, WHITE);

    int fontSize = 65;
    float x = 270;

    if (frame == 0)
    {
        DibujarAlien1(960, 150, 32);
        DibujarAlien3(1460, 120, 32);
    }
    else
    {
        DibujarAlien2(960, 150, 32);
        DibujarAlien4(1460, 120, 32);
    }
    DibujarJugador(1250, 850, 32);

    Rectangle btnJugar = {x, 560, 300, float(fontSize)}; // HITBOX
    Rectangle btnSalir = {x, 720, 300, float(fontSize)};

    bool hitbxJugar = CheckCollisionPointRec(mouse, btnJugar);
    bool hitbxSalir = CheckCollisionPointRec(mouse, btnSalir);

    DrawText("JUGAR", x, 540, fontSize, hitbxJugar ? GREEN : WHITE);
    DrawText("SALIR", x, 700, fontSize, hitbxSalir ? RED : WHITE);

    if (hitbxSalir && click)
    {
        CloseWindow();
    }

    if (hitbxJugar && click)
    {
        *pantallaActual = PANT_TUTORIAL;
    }
}

/************************************************* DIBUJAR ALIENS **************************************************************/
void DibujarAlien1(int x, int y, int pixelSize)
{
    int alien1[15][4] = {{-2, 0, 1, 1}, {3, 0, 1, 1}, {-1, 1, 1, 1}, {2, 1, 1, 1}, {-2, 2, 6, 1}, {-4, 1, 1, 4}, {5, 1, 1, 4}, {-3, 3, 2, 3}, {3, 3, 2, 3}, {0, 3, 2, 1}, {-1, 4, 4, 2}, {-2, 6, 1, 1}, {-1, 7, 1, 1}, {3, 6, 1, 1}, {2, 7, 1, 1}};

    for (int i = 0; i < 15; i++)
    {
        DrawRectangle(x + alien1[i][0] * pixelSize, y + alien1[i][1] * pixelSize, alien1[i][2] * pixelSize, alien1[i][3] * pixelSize, GREEN);
    }
}
void DibujarAlien2(int x, int y, int pixelSize)
{
    int alien2[15][4] = {{-2, 0, 1, 1}, {3, 0, 1, 1}, {-1, 1, 1, 1}, {2, 1, 1, 1}, {-2, 2, 6, 1}, {-4, 4, 1, 4}, {5, 4, 1, 4}, {-3, 3, 2, 3}, {3, 3, 2, 3}, {0, 3, 2, 1}, {-1, 4, 4, 2}, {-2, 6, 1, 1}, {-1, 7, 1, 1}, {3, 6, 1, 1}, {2, 7, 1, 1}};

    for (int i = 0; i < 15; i++)
    {
        DrawRectangle(x + alien2[i][0] * pixelSize, y + alien2[i][1] * pixelSize, alien2[i][2] * pixelSize, alien2[i][3] * pixelSize, GREEN);
    }
}
void DibujarAlien3(int x, int y, int pixelSize)
{
    int alien3[14][4] = {{-4, 0, 1, 1}, {5, 0, 1, 1}, {-1, 1, 4, 2}, {-2, 2, 1, 5}, {-3, 1, 1, 6}, {5, 0, 1, 1}, {-4, 6, 1, 2}, {-1, 7, 1, 1}, {-1, 4, 4, 2}, {0, 3, 2, 1}, {3, 2, 1, 5}, {4, 1, 1, 6}, {2, 7, 1, 1}, {5, 6, 1, 2}};

    for (int i = 0; i < 14; i++)
    {
        DrawRectangle(x + alien3[i][0] * pixelSize, y + alien3[i][1] * pixelSize, alien3[i][2] * pixelSize, alien3[i][3] * pixelSize, BLUE);
    }
}
void DibujarAlien4(int x, int y, int pixelSize)
{
    int alien4[9][4] = {{-2, 1, 1, 6}, {-3, 0, 1, 6}, {-1, 0, 4, 2}, {-1, 6, 1, 2}, {-1, 3, 4, 2}, {0, 2, 2, 1}, {3, 1, 1, 6}, {4, 0, 1, 6}, {2, 6, 1, 2}};

    for (int i = 0; i < 9; i++)
    {
        DrawRectangle(x + alien4[i][0] * pixelSize, y + alien4[i][1] * pixelSize, alien4[i][2] * pixelSize, alien4[i][3] * pixelSize, BLUE);
    }
}
void DibujarJugador(int x, int y, int pixelSize)
{
    int jugador[15][4] = {{+1, +5, 2, 1}, {-2, +5, 2, 1}, {-5, +4, 11, 1}, {-6, +2, 13, 2}, {-1, -3, 3, 5}, {-6, +1, 4, 1}, {+3, +1, 4, 1}, {-5, -2, 3, 3}, {-4, -3, 1, 1}, {+3, -2, 3, 3}, {+4, -3, 1, 1}, {-1, -4, 1, 1}, {+1, -4, 1, 1}, {-1, -5, 3, 1}, {0, -6, 1, 1}};

    for (int i = 0; i < 15; i++)
    {
        DrawRectangle(x + jugador[i][0] * pixelSize, y + jugador[i][1] * pixelSize, jugador[i][2] * pixelSize, jugador[i][3] * pixelSize, RED);
    }
}
