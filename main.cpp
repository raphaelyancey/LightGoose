#include <iostream>
#include <QtCore>
#include <QFile>
#include <QtXml>
#include <QtDebug>
#include <QVector>
#include <QtWidgets>
#include <QApplication>
#include <QLayout>
#include <itunes.h>
#include <window.h>

using namespace std;

int main(int argc, char *argv[]) {

	// initializing the Qt window
	QApplication a(argc, argv);
	Window *w = new Window;

	QVector<QList<QString> > albums; // where the albums will be stored
	QVector<QString> keys(0); // the iTunes XML keys we want to fetch
	iTunes *i = new iTunes;

	keys.append("Artist");
	keys.append("Track ID");
	keys.append("Album");

	// getting the albums
	try {
		albums = i->getAlbums("/Users/wizardman/QtRFIDMusic/Lib.xml", keys);
	}
	catch(QString const& str) {
		cerr << qPrintable(str) << endl;
		return 1;
	}

	qDebug() << albums << endl;

	// adding the albums to the combobox
	if(albums.count() != 0)
	{
		QVector<QString> uniqueAlbumsList; // and the list of these albums

		// Get the unique album list
		uniqueAlbumsList = i->getUniqueAlbumList(albums, keys);
		// Adding items to the list
		w->createAlbumList(uniqueAlbumsList);

	} else {
		cerr << "Aucun album." << endl;
		return 1;
	}

	w->setFields();
	w->show();
	return a.exec();
}
