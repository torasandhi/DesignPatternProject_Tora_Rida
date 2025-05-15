#include "raylib.h"
#include "GameEventManager.h"
#include "ScoreDisplay.h"
#include <cstdlib>
#include <ctime>

// Constants
const int screenWidth = 800;
const int screenHeight = 600;
const int paddleWidth = 10;
const int paddleHeight = 80;
const int ballRadius = 10;
const int paddleSpeed = 400;
const int ballSpeed = 300;

int main()
{
    // Seed random number generator
    std::srand(std::time(nullptr));

    // inisialisasi screen tinggi layar
    InitWindow(screenWidth, screenHeight, "Pong Game");
    SetTargetFPS(60);

    // Initialize Game Event Manager and Score Display
    GameEventManager &eventManager = GameEventManager::getInstance();
    ScoreDisplay scoreDisplay(screenWidth / 2 - 150, 20, 20, WHITE); // Centered at the top
    eventManager.attach(&scoreDisplay);

    // Initialize Player and opponent Paddles
    float playerX = 30; 
    float playerY = screenHeight / 2 - paddleHeight / 2;
    float opponentX = screenWidth - 30 - paddleWidth;
    float opponentY = screenHeight / 2 - paddleHeight / 2;

    // Initialize Ball
    float ballX = screenWidth / 2;
    float ballY = screenHeight / 2;
    float ballSpeedX = ballSpeed;
    float ballSpeedY = ballSpeed;

    // Game Loop
    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();

        // Input Handling (Player)
        if (IsKeyDown(KEY_W))
        {
            playerY -= paddleSpeed * deltaTime;
            if (playerY < 0)
                playerY = 0;
        }
        if (IsKeyDown(KEY_S))
        {
            playerY += paddleSpeed * deltaTime;
            if (playerY > screenHeight - paddleHeight)
                playerY = screenHeight - paddleHeight;
        }

        // AI Control (opponent) - Simple AI
        // else if (ballY < opponentY + paddleHeight / 2)
        if (IsKeyDown(KEY_UP))
        {
            opponentY -= paddleSpeed * deltaTime * 0.8f;
            if (opponentY < 0)
                opponentY = 0;
        }
        // if (ballY > opponentY + paddleHeight / 2)
        else if (IsKeyDown(KEY_DOWN))
        {
            opponentY += paddleSpeed * deltaTime * 0.8f; // Slightly slower than player
            if (opponentY > screenHeight - paddleHeight)
                opponentY = screenHeight - paddleHeight;
        }

        // Ball Movement
        ballX += ballSpeedX * deltaTime;
        ballY += ballSpeedY * deltaTime;

        // Ball Collision with Top/Bottom Walls
        if (ballY < ballRadius || ballY > screenHeight - ballRadius)
        {
            ballSpeedY *= -1;
        }

        // Ball Collision with Paddles
        if (ballX - ballRadius < playerX + paddleWidth &&
            ballX + ballRadius > playerX &&
            ballY + ballRadius > playerY &&
            ballY - ballRadius < playerY + paddleHeight)
        {
            // Only bounce if moving toward paddle (prevents getting stuck)
            if (ballSpeedX < 0)
            {
                ballSpeedX *= -1.05f; // Slightly increase speed on bounce
                // Add a small random change to Y velocity for more dynamic gameplay
                ballSpeedY += (float)(GetRandomValue(-100, 100) / 100.0f) * ballSpeed * 0.25f;
            }
        }
        else if (ballX + ballRadius > opponentX &&
                 ballX - ballRadius < opponentX + paddleWidth &&
                 ballY + ballRadius > opponentY &&
                 ballY - ballRadius < opponentY + paddleHeight)
        {
            // Only bounce if moving toward paddle
            if (ballSpeedX > 0)
            {
                ballSpeedX *= -1.05f;
                ballSpeedY += (float)(GetRandomValue(-100, 100) / 100.0f) * ballSpeed * 0.25f;
            }
        }

        // jika bola keluar layar di bagian kiri window/layar
        if (ballX < 0) 
        {
            ballX = screenWidth / 2;
            ballY = screenHeight / 2;
            ballSpeedX = ballSpeed;
            ballSpeedY = (float)(GetRandomValue(-100, 100) / 100.0f) * ballSpeed * 0.5f;
            eventManager.incrementOpponentScore();
        }
        //jika keluar layar di bagian kanan window/layar
        else if (ballX > screenWidth)
        {
            ballX = screenWidth / 2;
            ballY = screenHeight / 2;
            ballSpeedX = -ballSpeed;
            ballSpeedY = (float)(GetRandomValue(-100, 100) / 100.0f) * ballSpeed * 0.5f;
            eventManager.incrementPlayerScore();
        }

        // start draw
        BeginDrawing();
        ClearBackground({20, 160, 133, 255}); // Green background

        // draw garis tengah
        DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, Fade(WHITE, 0.2f));
        DrawCircle(screenWidth / 2, screenHeight / 2, 70, Fade(WHITE, 0.05f));

        // draw paddle player 1 dan 2
        DrawRectangle(playerX, playerY, paddleWidth, paddleHeight, WHITE);
        DrawRectangle(opponentX, opponentY, paddleWidth, paddleHeight, WHITE);

        // draw ball
        DrawCircle(ballX, ballY, ballRadius, WHITE);

        // draw score display
        scoreDisplay.draw();

        EndDrawing();
    }

    // Clean up
    CloseWindow();
    return 0;
}