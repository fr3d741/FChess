#include <QMessageBox>
#include <QNetworkInterface>

#include "tcpiplayer.h"
#include "../exceptions.h"

#include "ui_networkSettings.h"

#define PORT 32532

TCPIPlayer::TCPIPlayer(Defs::EColors color, QObject *parent )
    :Player(color, parent)
    ,_connect(false)
    ,_listener(0)
    ,_incoming(0)
{
    QWidget* qw = new QWidget();
    ui_network->setupUi(qw);
    qw->show();
    ui_network->portLabel->setText( QString(":%1").arg(PORT) );

    QList<QHostAddress>	addres = QNetworkInterface::allAddresses();
    if ( addres.isEmpty() )
    {
        throw NetworkException();
    }

    while( !addres.isEmpty() )
    {
		QHostAddress ha = addres.takeFirst();
        ui_network->addressComboBox->addItem(ha.toString());
    }

    connect( ui_network->addressComboBox,    SIGNAL( currentIndexChanged(QString) ), SLOT( slotListenOn(QString) ) );
    connect( ui_network->pushButton,         SIGNAL( pressed() ),                    SLOT( slotConnect() ) );
    connect( &_sender,                      SIGNAL( connected() ),                  SLOT( slotConnected() ) );

    slotListenOn( ui_network->addressComboBox->currentText() );
}

void TCPIPlayer::slotListenOn( QString adr )
{
    qDebug("listening");
    if ( _listener )
    {
        delete _listener;
    }

    _listener = new QTcpServer();
    if ( _listener->listen( QHostAddress( adr ), PORT ) )
    {
        QString str = QString("Listening on %1").arg( adr );
        qDebug() << str;
        emit signalMessage( str );
        connect( _listener, SIGNAL( newConnection() ), SLOT( slotIncomingConnection() ) );
    }
    else
    {
        delete _listener;
        _listener = 0;
    }

}

bool TCPIPlayer::isValidCell( Defs::Cell& sourceCell )
{
    if ( sourceCell.figure && ( sourceCell.figure & _playerColor ) )
    {
        return true;
    }

return false;
}

void TCPIPlayer::slotIncomingConnection()
{
    if ( !_incoming )
    {
        _incoming = _listener->nextPendingConnection();
        emit signalMessage( QString("Local: %1, Peer: %2").arg( _incoming->localAddress().toString() ).arg( _incoming->peerAddress().toString() ) );
    }
}

bool TCPIPlayer::isValidCellForTarget( Defs::Cell* targetCell )
{
    if ( targetCell->figure && ( targetCell->figure & _playerColor ) )
    {
        return true;
    }

return false;
}

void TCPIPlayer::slotConnected()
{
    qDebug("Connected!!");
}

void TCPIPlayer::slotConnect()
{
    qDebug("try connect");
    _connect = !_connect;
    if ( _connect )
    {
        QString addr = ui_network->lineEdit->text();
        _sender.connectToHost( QHostAddress( addr ), PORT );
    }
    else
    {
        _sender.abort();
    }

}

std::pair< int, int >& TCPIPlayer::cellOverCursor()
{
    return _cellOverCursor;
}

bool TCPIPlayer::eventFilter( QObject*, QEvent* )
{
return false;
}

