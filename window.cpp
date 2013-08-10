#include "window.h"

Window::Window() : QWidget()
{
	setFixedSize(400, 100);
	qLayout = new QHBoxLayout;
	qList = new QComboBox;
	qPlay = new QPushButton("Play");
}

void Window::createAlbumList(QVector<QString> albums)
{
	for(int i = 0; i < albums.count(); i++)
		qList->addItem(albums[i]);
}

void Window::setFields()
{
	QObject::connect(qPlay, SIGNAL(clicked()), qApp, SLOT(quit()));

	qLayout->addWidget(qList);
	qLayout->addWidget(qPlay);

	setLayout(qLayout);
}
