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

using namespace std;

int main(int argc, char *argv[]) {

	// initializing the Qt window
	QApplication a(argc, argv);
	QWidget w;
	QHBoxLayout *layout = new QHBoxLayout;
	w.setFixedSize(400, 100);

	QVector<QList<QString> > albums; // where the albums will be stored
	QVector<QString> keys(0); // the iTunes XML keys we want to fetch
	iTunes i;

	keys.append("Artist");
	keys.append("Track ID");
	keys.append("Album");
	keys.append("Name");

	// we store the keys position to use (in the case we change the keys later)
	int keyOfAlbum = keys.indexOf("Album");
	int keyOfTrackId = keys.indexOf("Track ID");
	int keyOfArtist = keys.indexOf("Artist");

	for(int i = 0; i < keys.count(); i++)
		qDebug() << "Index of " << keys.at(i) << " : " << keys.indexOf(keys.at(i));

	// getting the albums
	try {
		albums = i.getAlbums("/Users/wizardman/QtRFIDMusic/Lib.xml", keys);
		//qDebug() << albums;
	}
	catch(QString const& str) {
		cerr << qPrintable(str) << endl;
		return 1;
	}

	qDebug() << albums << endl;

	// setting up the widgets
	QComboBox *qAlbumList = new QComboBox;
	QPushButton *qPlay = new QPushButton("Play");

	// adding the albums to the combobox
	if(albums.count() != 0)
	{
		QVector<QList<QString> > uniqueAlbums(0); // storing unique album names with their tracks ID
		QVector<QString> uniqueAlbumsList(0); // and the list of these albums
		int uniqueAlbumIterator = 0;

		for(int i = 0; i < albums.count(); i++)
		{
			if(albums[i].count() == 3) // only fetching complete rows
			{
				if(uniqueAlbumsList.indexOf(albums[i][keyOfAlbum]) == -1) // if the record doesn't exists in the uniques vector
				{
					// we store the album name in the list of uniques
					uniqueAlbumsList.append(albums[i][keyOfAlbum]);

//					// and the album name and first track in the uniques vector
//					uniqueAlbums.resize(uniqueAlbumIterator+1);
//					uniqueAlbums[uniqueAlbumIterator].append(albums[i][keyOfAlbum]);
//					uniqueAlbumIterator++;

					qDebug() << albums[i][keyOfAlbum] << "didn't exist, creating it.";
				}
				else // and if it does
				{
					// we store the track id fetched
//					uniqueAlbums[uniqueAlbumIterator].append(albums[i][keyOfTrackId]);
					qDebug() << albums[i][keyOfAlbum] << "exists, just adding track " << albums[i][keyOfTrackId] << ".";
				}
				//qAlbumList->addItem(albums[i][2]);
			}
		}

		qDebug() << "Unique albums" << endl << "---------" << uniqueAlbums << endl;
		qDebug() << "Unique albums list" << endl << "---------" << uniqueAlbumsList << endl;

	} else {
		cerr << "Aucun album." << endl;
		return 1;
	}

	layout->addWidget(qAlbumList);
	layout->addWidget(qPlay);

	w.setLayout(layout);
	w.show();
	return a.exec();
}
