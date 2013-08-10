#include "window.h"
#include "itunes.h"

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
	QObject::connect(qList, SIGNAL(currentIndexChanged(int)), this, SLOT(getAlbumByIndex(int)));
	QObject::connect(qPlay, SIGNAL(clicked()), this, SLOT(qPlayAlbum()));

	qLayout->addWidget(qList);
	qLayout->addWidget(qPlay);

	setLayout(qLayout);
}

void Window::getAlbumByIndex(int index)
{
	selectedAlbum = index;
	qDebug() << selectedAlbum;
}

void Window::qPlayAlbum()
{
	iTunes *i = new iTunes;
	i->playAlbum(selectedAlbum);
}
