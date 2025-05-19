#ifndef GAME_EVENT_MANAGER_H
#define GAME_EVENT_MANAGER_H

#include "ISubject.h"
#include "IObserver.h"
#include <vector> 

class GameEventManager : public ISubject
{
private:
    std::vector<IObserver *> observers_;
    int playerScore_;
    int opponentScore_;

    // Private constructor for singleton
    GameEventManager();

public:
    static GameEventManager &getInstance();

    // Delete copy constructor and assignment operator
    GameEventManager(const GameEventManager &) = delete;
    GameEventManager &operator=(const GameEventManager &) = delete;

    // ISubject interface implementations
    void attach(IObserver *observer) override;
    void detach(IObserver *observer) override;
    void notifyScoreChanged() override;

    // Game-specific methods
    void incrementPlayerScore();
    void incrementOpponentScore();
    int getPlayerScore() const;
    int getOppoentScore() const;
};

#endif