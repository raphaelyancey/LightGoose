#include "itunes.h"
#include <QVector>
#include <QString>
#include <QFile>
#include <QtXml>
#include <QtDebug>
#include <iostream>
#include <sstream>
#include <QProcess>

iTunes::iTunes(QString path)
{
	keys.append("Artist");
	keys.append("Track ID");
	keys.append("Album");

	playCommand = "osascript";

	filePath = path;
}

QVector<QList<QString> > iTunes::getAlbums()
{
	QDomDocument doc("Lib");
	QFile file(filePath);

	if(!file.open(QIODevice::ReadOnly))
		throw QString("Erreur lors de l'ouverture du fichier.");
	if(!doc.setContent(&file))
		throw QString("Erreur lors de l'initialisation du XML.");

	file.close();

	// Root element
	QDomElement docElem = doc.documentElement();

	// <plist> -> <dict>
	QDomNode n = docElem.firstChild().firstChildElement("dict");

	// Get the children nodes of the first dict
	QDomNodeList list = n.childNodes();
	int count = list.count();

	// Init the albums storage
	QVector<QList<QString> > albums(0);
	int albumIterator(0);

	// For each child
	for(int nodeIterator = 0; nodeIterator <= count; nodeIterator++)
	{
		QDomElement node = list.at(nodeIterator).toElement();

		// If it is a <dict>
		if(node.tagName().startsWith("dict"))
		{
			node = node.firstChildElement();

			// We go through its children
			while(!node.isNull())
			{
				// Get the key tag
				if(node.tagName() == "key")
				{
					// For each tag we want to store
					for(int keyIterator = 0; keyIterator < keys.count(); keyIterator++)
					{
						// We check if the current tag is one of them
						if(node.text() == keys.at(keyIterator) && node.tagName() == "key")
						{
							// The value is stored in the next element
							node = node.nextSiblingElement();

							if(!node.isNull())
							{
								albums.resize(albumIterator+1);

								QString value = node.text();

								if(albums[albumIterator].indexOf(value) == -1)
									albums[albumIterator].insert(keys.indexOf(keys.at(keyIterator)), value);
							}
						}
					}
				}

				node = node.nextSiblingElement();
			}

			albumIterator = albumIterator+1;

		}
		QCoreApplication::processEvents();
	}

	if(albums.isEmpty())
		throw QString("Aucun album retourné.");

	return albums;
}

QVector<QString> iTunes::getUniqueAlbumList(QVector<QList<QString> > albums)
{
	keyOfAlbum = keys.indexOf("Album");
	keyOfTrackId = keys.indexOf("Track ID");
	keyOfArtist = keys.indexOf("Artist");
	uniqueAlbumIterator = 0;

	for(int i=0;i<keys.count();i++)
		qDebug() << "Position de " << keys.at(i) << " : " << keys.indexOf(keys.at(i));

	for(int i = 0; i < albums.count(); i++)
	{
		if(albums[i].count() == 3) // only fetching complete rows
		{
			if(uniqueAlbumList.indexOf(albums[i][keyOfAlbum]) == -1) // if the record doesn't exists in the uniques vector
			{
				// we store the album name in the list of uniques
				uniqueAlbumList.append(albums[i][keyOfAlbum]);

				// and the album name and first track in the uniques vector
				uniqueAlbums.resize(uniqueAlbumIterator+1);
				qDebug() << "[-] Taille de uniqueAlbums : " << uniqueAlbums.count();
				uniqueAlbums[uniqueAlbumIterator].append(albums[i][keyOfAlbum]);
				uniqueAlbums[uniqueAlbumIterator].append(albums[i][keyOfTrackId]);
				uniqueAlbumIterator++;
				qDebug() << "    " << albums[i][keyOfAlbum] << "didn't exist, creating it.";
			}
			else // and if it does
			{
				qDebug() << "[+] " << albums[i][keyOfAlbum] << " trouvé dans la liste des albums uniques";

				// we store the track id fetched in the right row of uniqueAlbums

				for(int k = 0; k < uniqueAlbums.count(); k++)
				{
					if(uniqueAlbums[k][0] == albums[i][keyOfAlbum])
					{
						uniqueAlbums[k].append(albums[i][keyOfTrackId]);
						qDebug() << albums[i][keyOfAlbum] << "exists, just adding track " << albums[i][keyOfTrackId] << ".";
					}
				}
			}
		}
	}

	return uniqueAlbumList;
}

void iTunes::playAlbum(int uniqueAlbumIndex, QVector<QString> uniqueAlbumListCopy)
{
	qDebug() << "Lancement de l'album n°" << uniqueAlbumIndex;
	qDebug() << "Nom : " << uniqueAlbumListCopy.at(uniqueAlbumIndex);

	QProcess *p = new QProcess;
	QString program = "/usr/bin/osascript";
	QStringList args;
	args << "/Users/wizardman/QtRFIDMusic/playAlbum.scpt";
	args << uniqueAlbumListCopy.at(uniqueAlbumIndex);
	p->start(program, args);

}
