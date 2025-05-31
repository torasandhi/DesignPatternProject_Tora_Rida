#include "ScoreDisplay.h"
#include <string>

ScoreDisplay::ScoreDisplay(int x, int y, int fontSize, Color color)
    : x_(x), y_(y), fontSize_(fontSize), color_(color), player1Score_(0), player2Score_(0) {}

void ScoreDisplay::updateScore(int player1Score, int player2Score)
{
    player1Score_ = player1Score;
    player2Score_ = player2Score;
}

void ScoreDisplay::draw() const
{
    std::string scoreText = "Player 1: " + std::to_string(player1Score_) + "  |  Player 2: " + std::to_string(player2Score_);
    DrawText(scoreText.c_str(), x_, y_, fontSize_, color_);
}