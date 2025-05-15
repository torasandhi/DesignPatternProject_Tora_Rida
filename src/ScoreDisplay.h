#ifndef SCORE_DISPLAY_H
#define SCORE_DISPLAY_H

#include "IObserver.h"
#include "raylib.h"

class ScoreDisplay : public IObserver
{
public:
    ScoreDisplay(int x, int y, int fontSize, Color color);
    void updateScore(int playerScore, int computerScore) override;
    void draw() const;

private:
    int x_;
    int y_;
    int fontSize_;
    Color color_;
    int playerScore_;
    int computerScore_;
};

#endif // SCORE_DISPLAY_