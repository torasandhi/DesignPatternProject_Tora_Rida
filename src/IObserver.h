#ifndef IOBSERVER_H
#define IOBSERVER_H


class IObserver
{
public:
    virtual void updateScore(int playerScore, int computerScore) = 0;
    virtual ~IObserver() = default;
};

#endif 