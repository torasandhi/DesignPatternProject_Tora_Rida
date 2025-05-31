#ifndef SCORE_DISPLAY_H
#define SCORE_DISPLAY_H

#include "IObserver.h"
#include "raylib.h"

class ScoreDisplay : public IObserver
{
public:
    ScoreDisplay(int x, int y, int fontSize, Color color);
    void updateScore(int player1Score, int player2Score) override;
    void draw() const;

private:
    int x_;
    int y_;
    int fontSize_;
    Color color_;
    int player1Score_;
    int player2Score_;
};

#endif // SCORE_DISPLAY_H