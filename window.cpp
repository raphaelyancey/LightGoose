#include "window.h"
#include "itunes.h"

Window::Window(iTunes *instance) : QWidget()
{
	setFixedSize(400, 100);
	qLayout = new QHBoxLayout;
	qList = new QComboBox;
	qPlay = new QPushButton("Play");
	qRefresh = new QPushButton("Refresh");
	i = instance;
}

void Window::createAlbumList()
{
	qSort(i->uniqueAlbumList);
	for(int j = 0; j < i->uniqueAlbumList.count(); j++)
		qList->addItem(i->uniqueAlbumList[j]);
}

void Window::setLinks() // signals & slots connection
{
	QObject::connect(qList, SIGNAL(currentIndexChanged(int)), this, SLOT(getAlbumByIndex(int)));
	QObject::connect(qPlay, SIGNAL(clicked()), this, SLOT(qPlayAlbum()));
	QObject::connect(qRefresh, SIGNAL(clicked()), this, SLOT(refreshList()));
}

void Window::setUi() // adding the UI elements
{
	qLayout->addWidget(qRefresh);
	qLayout->addWidget(qList);
	qLayout->addWidget(qPlay);

	setLayout(qLayout);
}

void Window::getAlbumByIndex(int index)
{
	selectedAlbum = index;
	//qDebug() << selectedAlbum;
}

void Window::qPlayAlbum()
{
	i->playAlbum(selectedAlbum, i->uniqueAlbumList);
}

void Window::refreshList() {

	i->uniqueAlbumList.clear();
	i->uniqueAlbums.clear();

	QVector<QList<QString> > newAlbums = i->getAlbums();
	qDebug() << "newAlbums : " << newAlbums;
	QVector<QString> newList = i->getUniqueAlbumList(newAlbums);
	qDebug() << "newList : " << newList;

	i->uniqueAlbumList = newList;

	qList->clear();
	createAlbumList();
}
