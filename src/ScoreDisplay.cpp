#include "ScoreDisplay.h"
#include <string>

ScoreDisplay::ScoreDisplay(int x, int y, int fontSize, Color color) : x_(x), y_(y), fontSize_(fontSize), color_(color), playerScore_(0), opponentScore_(0){}

void ScoreDisplay::updateScore(int playerScore, int computerScore)
{
    playerScore_ = playerScore;
    opponentScore_ = computerScore;
}

void ScoreDisplay::draw() const
{
    std::string scoreText = "Player 1: " + std::to_string(playerScore_) + "  |  Player 2: " + std::to_string(opponentScore_);
    DrawText(scoreText.c_str(), x_, y_, fontSize_, color_);
}