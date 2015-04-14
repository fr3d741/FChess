#ifndef BOARDWIDGET_H
#define BOARDWIDGET_H

#include <QWidget>
#include <QImage>

class BoardWidget : public QWidget
{
		Q_OBJECT
	public:
		explicit BoardWidget(QWidget *parent = 0);

	signals:

	public slots:

	protected:
		void resizeEvent(QResizeEvent*);
		void paintEvent(QPaintEvent*);

	private:
		void generateBackground();
		void generateImage();

	private:
		QImage _background;
		QImage _screen;
};

#endif // BOARDWIDGET_H
