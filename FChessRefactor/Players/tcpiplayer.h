#ifndef TCPIPLAYER_H
#define TCPIPLAYER_H

namespace Ui
{
    class NetowrkSettings;
}

#include <QTcpSocket>
#include <QTcpServer>

#include "../Interfaces/player.h"
#include "../messageinterface.h"

class TCPIPlayer : public Player
{
    Q_OBJECT

    enum EProtocol
    {
        NewPlayer,
        Move,
        MoveFallback,
        Resign,
        Disconnect
    };

public:
    explicit TCPIPlayer(Defs::EColors color, QObject *parent = 0);
    
    virtual bool isValidCell( Defs::Cell& cell );

    virtual bool isValidCellForTarget( Defs::Cell* cell );

    virtual bool eventFilter(QObject *, QEvent *);

    virtual std::pair< int, int >& cellOverCursor();

    bool IsHuman() override { return false; }
signals:

public slots:
    void slotListenOn( QString );

	void slotIncomingConnection();

    void slotConnect();

    void slotConnected();

protected:
    bool                _connect;
    Ui::NetowrkSettings* ui_network;
    QTcpServer*         _listener;
    QTcpSocket*         _incoming;
    QTcpSocket          _sender;
    std::pair< int, int >   _cellOverCursor;
};

#endif // TCPIPLAYER_H
