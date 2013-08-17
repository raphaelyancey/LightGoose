#include <iostream>
#include <QtDebug>
#include <QVector>
#include <QList>
#include <QApplication>
#include <itunes.h>
#include <window.h>

using namespace std;

int main(int argc, char *argv[]) {

	// initializing the Qt window
	QApplication a(argc, argv);
	iTunes *i = new iTunes("/Users/wizardman/QtRFIDMusic/Lib.xml");
	Window *w = new Window(i); // passing the iTunes instance

	QVector<QList<QString> > albums; // where the albums will be stored

	// getting the albums
	try {
		albums = i->getAlbums();
	}
	catch(QString const& str) {
		cerr << qPrintable(str) << endl;
		return 1;
	}

	qDebug() << albums << endl;

	// adding the albums to the combobox
	if(albums.count() != 0)
	{
		QVector<QString> uniqueAlbumList; // the list of these albums

		// Get the unique album list
		try {
			uniqueAlbumList = i->getUniqueAlbumList(albums);
		}
		catch(QString const& str) {
			cerr << qPrintable(str) << endl;
			return 1;
		}

		// Adding items to the list
		w->createAlbumList();

	} else {
		cerr << "Can't find any album." << endl;
		return 1;
	}

	w->setLinks();
	w->setUi();
	w->show();
	return a.exec();
}
