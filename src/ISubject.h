#ifndef ISUBJECT_H
#define ISUBJECT_H

#include "IObserver.h"
#include <vector>

class ISubject
{
public:
    virtual void attach(IObserver *observer) = 0;
    virtual void detach(IObserver *observer) = 0;
    virtual void notifyScoreChanged() = 0;
    virtual ~ISubject() = default;
};

#endif // ISUBJECT_H