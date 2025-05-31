#ifndef IOBSERVER_H
#define IOBSERVER_H

class IObserver
{
public:
    virtual void updateScore(int player1Score, int player2Score) = 0;
    virtual ~IObserver() = default;
};

#endif // IOBSERVER_H