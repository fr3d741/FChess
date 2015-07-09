#ifndef MESSAGEINTERFACE_H
#define MESSAGEINTERFACE_H

#include <QObject>

class MessageInterface
{
public:
    explicit MessageInterface();
    
    virtual void signalMessage( QString );

    virtual void signalError( QString );
    
};

#endif // MESSAGEINTERFACE_H
