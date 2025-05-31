#include "raylib.h"
#include "GameEventManager.h"
#include "ScoreDisplay.h"
#include <cstdlib>
#include <ctime>

const int screenWidth = 800;
const int screenHeight = 600;
const int paddleWidth = 10;
const int paddleHeight = 80;
const int ballRadius = 10;
const float paddleSpeed = 400;
const float initialBallSpeed = 300;

int main()
{

#pragma region inisialisasi
    // initialize screen
    InitWindow(screenWidth, screenHeight, "Pong Game");
    SetTargetFPS(60);

    // Singleton
    GameEventManager &eventManager = GameEventManager::getInstance();
    // Display UI
    ScoreDisplay scoreDisplay(screenWidth / 2 - 150, 20, 20, WHITE);
    eventManager.attach(&scoreDisplay);

    float player1X = 30;
    float player1Y = screenHeight / 2 - paddleHeight / 2;

    float player2X = screenWidth - 30 - paddleWidth;
    float player2Y = screenHeight / 2 - paddleHeight / 2;

    float ballX = screenWidth / 2;
    float ballY = screenHeight / 2;
    float ballSpeedX = initialBallSpeed * (GetRandomValue(0, 1) * 2 - 1);
    float ballSpeedY = initialBallSpeed * (GetRandomValue(-100, 100) / 100.0f);
#pragma endregion

    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();

#pragma region input
        if (IsKeyDown(KEY_W))
        {
            player1Y -= paddleSpeed * deltaTime;
            if (player1Y < 0)
                player1Y = 0;
        }
        if (IsKeyDown(KEY_S))
        {
            player1Y += paddleSpeed * deltaTime;
            if (player1Y > screenHeight - paddleHeight)
                player1Y = screenHeight - paddleHeight;
        }

        if (IsKeyDown(KEY_UP))
        {
            player2Y -= paddleSpeed * deltaTime;
            if (player2Y < 0)
                player2Y = 0;
        }
        if (IsKeyDown(KEY_DOWN))
        {
            player2Y += paddleSpeed * deltaTime;
            if (player2Y > screenHeight - paddleHeight)
                player2Y = screenHeight - paddleHeight;
        }
#pragma endregion

#pragma region collision
        ballX += ballSpeedX * deltaTime;
        ballY += ballSpeedY * deltaTime;

        // bounce ball if y-axis out of bounds
        if (ballY - ballRadius < 0 || ballY + ballRadius > screenHeight)
        {
            ballSpeedY *= -1;
        }

        // collision dengan paddle player 1
        if (ballX - ballRadius < player1X + paddleWidth &&
            ballX + ballRadius > player1X &&
            ballY + ballRadius > player1Y &&
            ballY - ballRadius < player1Y + paddleHeight)
        {
            if (ballSpeedX < 0)
            {
                ballSpeedX *= -1.05f; // increase speed sedikit setelah collision
                ballSpeedY = (ballY - (player1Y + paddleHeight / 2)) / (paddleHeight / 2) * initialBallSpeed * 0.75f;
            }
        }

        // collision dengan paddle player 2
        else if (ballX + ballRadius > player2X &&
                 ballX - ballRadius < player2X + paddleWidth &&
                 ballY + ballRadius > player2Y &&
                 ballY - ballRadius < player2Y + paddleHeight)
        {
            if (ballSpeedX > 0)
            {
                ballSpeedX *= -1.05f; // increase speed sedikit setelah collision
                ballSpeedY = (ballY - (player2Y + paddleHeight / 2)) / (paddleHeight / 2) * initialBallSpeed * 0.75f;
            }
        }
#pragma endregion

#pragma region scoring
        if (ballX < 0)
        {
            eventManager.incrementPlayer2Score();

            ballX = screenWidth / 2;
            ballY = screenHeight / 2;

            ballSpeedX = initialBallSpeed;
            ballSpeedY = (float)(GetRandomValue(-100, 100) / 100.0f) * initialBallSpeed * 0.5f;
        }
        else if (ballX > screenWidth)
        {
            eventManager.incrementPlayer1Score();

            ballX = screenWidth / 2;
            ballY = screenHeight / 2;

            ballSpeedX = -initialBallSpeed;
            ballSpeedY = (float)(GetRandomValue(-100, 100) / 100.0f) * initialBallSpeed * 0.5f;
        }
#pragma endregion

        BeginDrawing();
        ClearBackground({20, 160, 133, 255});

        for (int i = 0; i < screenHeight; i += 20)
        {
            DrawRectangle(screenWidth / 2 - 1, i, 2, 10, Fade(WHITE, 0.5f));
        }
        DrawCircle(screenWidth / 2, screenHeight / 2, 70, Fade(WHITE, 0.05f));

        DrawRectangle(player1X, player1Y, paddleWidth, paddleHeight, WHITE);
        DrawRectangle(player2X, player2Y, paddleWidth, paddleHeight, WHITE);

        DrawCircle(ballX, ballY, ballRadius, WHITE);

        scoreDisplay.draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}