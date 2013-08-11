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
	Window *w = new Window;

	QVector<QList<QString> > albums; // where the albums will be stored
	iTunes *i = new iTunes;

	// getting the albums
	try {
		albums = i->getAlbums("/Users/wizardman/QtRFIDMusic/Lib.xml");
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
			w->uniqueAlbumList = uniqueAlbumList;
		}
		catch(QString const& str) {
			cerr << qPrintable(str) << endl;
			return 1;
		}

		// Adding items to the list
		w->createAlbumList(uniqueAlbumList);

	} else {
		cerr << "Can't find any album." << endl;
		return 1;
	}

	w->ssConnect();
	w->setFields();
	w->show();
	return a.exec();
}
