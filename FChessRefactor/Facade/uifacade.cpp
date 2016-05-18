#include "uifacade.h"

#include "../Observers/messenger.h"
#include "../Visual/display.h"
#include "../Interfaces/player.h"

UiFacade::UiFacade()
    :QObject()
{

}

QWidget *UiFacade::CreateDisplayWidget(QWidget* parent)
{
    if (!_display)
    {
        _display = new chessVisialization::Display(parent);
        _display->setMinimumSize( 10, 10 );
        _display->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
        connect(_display, SIGNAL(signalMessage(QString)), Messenger::Instance().get(), SIGNAL(signalMessageToGUI(QString)));
    }

    return _display;
}

void UiFacade::NextPlayer(std::shared_ptr<Player> player)
{
    _display->installEventFilter(player.get());
    _display->update();
}

void UiFacade::UpdateUi()
{
    _display->update();
}
