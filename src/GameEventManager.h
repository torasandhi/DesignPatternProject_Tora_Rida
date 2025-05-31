#ifndef GAME_EVENT_MANAGER_H
#define GAME_EVENT_MANAGER_H

#include "ISubject.h"
#include "IObserver.h"
#include <vector>

class GameEventManager : public ISubject
{
private:
    std::vector<IObserver *> observers_;
    int player1Score_;
    int player2Score_;
    static GameEventManager *instance_; // Add static instance pointer

    GameEventManager();

public:
    static GameEventManager &getInstance();

    void attach(IObserver *observer) override;
    void detach(IObserver *observer) override;
    void notifyScoreChanged() override;

    void incrementPlayer1Score();
    void incrementPlayer2Score();

    int getPlayer1Score() const;
    int getPlayer2Score() const;
};

#endif // GAME_EVENT_MANAGER_H