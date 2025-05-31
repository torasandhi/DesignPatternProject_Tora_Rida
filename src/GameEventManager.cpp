#include "GameEventManager.h"
#include <algorithm>

// Initialize the static instance pointer
GameEventManager *GameEventManager::instance_ = nullptr;

GameEventManager::GameEventManager() : player1Score_(0), player2Score_(0) {}

// Singleton
GameEventManager &GameEventManager::getInstance()
{
    if (instance_ == nullptr)
    {
        instance_ = new GameEventManager();
    }
    return *instance_;
}

// attach
void GameEventManager::attach(IObserver *observer)
{
    observers_.push_back(observer);
}

// detach
void GameEventManager::detach(IObserver *observer)
{
    observers_.erase(std::remove(observers_.begin(), observers_.end(), observer), observers_.end());
}

// notify perubahan skor
void GameEventManager::notifyScoreChanged()
{
    for (auto observer : observers_)
    {
        observer->updateScore(player1Score_, player2Score_);
    }
}

// tambah score player 1
void GameEventManager::incrementPlayer1Score()
{
    player1Score_++;
    notifyScoreChanged();
}

// tambah score player 2
void GameEventManager::incrementPlayer2Score()
{
    player2Score_++;
    notifyScoreChanged();
}

int GameEventManager::getPlayer1Score() const
{
    return player1Score_;
}

int GameEventManager::getPlayer2Score() const
{
    return player2Score_;
}