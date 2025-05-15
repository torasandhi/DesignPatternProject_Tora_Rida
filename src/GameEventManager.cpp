#include "GameEventManager.h"
#include "IObserver.h"
#include <algorithm>

GameEventManager::GameEventManager() : playerScore_(0), opponentScore_(0){}

GameEventManager& GameEventManager::getInstance()
{
    static GameEventManager instance;
    return instance;
}

void GameEventManager::attach(IObserver* observer)
{
    observers_.push_back(observer);
}

void GameEventManager::detach(IObserver* observer)
{
    observers_.erase(std::remove(observers_.begin(), observers_.end(), observer), observers_.end());
}

void GameEventManager::notifyScoreChanged()
{
    for (auto observer : observers_)
    {
        observer->updateScore(playerScore_, opponentScore_);
    }
}

void GameEventManager::incrementPlayerScore()
{
    playerScore_++;
    notifyScoreChanged();
}

void GameEventManager::incrementOpponentScore()
{
    opponentScore_++;
    notifyScoreChanged();
}

int GameEventManager::getPlayerScore() const
{
    return playerScore_;
}

int GameEventManager::getOppoentScore() const
{
    return opponentScore_;
}