#include <QPainter>
#include <QResizeEvent>
#include <algorithm>

#include "boardwidget.h"

BoardWidget::BoardWidget(QWidget *parent) :
    QWidget(parent)
{
	generateBackground();
	generateImage();
}

void BoardWidget::resizeEvent(QResizeEvent* event)
{
	int s = std::min( event->size().width(), event->size().height());
	s = (s/8)*8;
	_background = QImage(s, s, QImage::Format_ARGB32);
	_screen = QImage(s, s, QImage::Format_ARGB32);

	generateBackground();
	generateImage();
}

void BoardWidget::paintEvent(QPaintEvent*)
{
	QPainter painter(this);
	painter.drawImage(0, 0, _screen);
}

void BoardWidget::generateBackground()
{
	QPainter painter(&_background);
	int w = _background.width()/8;
	int h = _background.height()/8;
	bool reverse = false;

	QBrush blackBrush(Qt::black);
	QBrush whiteBrush(Qt::white);

	for(int j = 0, y = 0; j < 8; ++j, y+=h)
	{
		reverse = !reverse;
		for(int i = 0; i < 8; i+=2)
		{
			if (reverse)
			{
				painter.fillRect(i*w, y, w, h, blackBrush);
				painter.fillRect((i+1)*w, y, w, h, whiteBrush);
			}
			else
			{
				painter.fillRect(i*w, y, w, h, whiteBrush);
				painter.fillRect((i+1)*w, y, w, h, blackBrush);
			}
		}
	}
}

void BoardWidget::generateImage()
{
	QPainter painter(&_screen);
	painter.drawImage(_screen.rect(),_background);
}
