#ifndef ISERIALIZABLE_H
#define ISERIALIZABLE_H

#include <QString>

class ISerializable
{
public:
    virtual QString SaveState() = 0;

    virtual void LoadState(QString state) = 0;
};

#endif // ISERIALIZABLE_H
