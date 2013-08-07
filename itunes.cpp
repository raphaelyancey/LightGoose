#include "itunes.h"
#include <QVector>
#include <QString>
#include <QFile>
#include <QtXml>
#include <QtDebug>
#include <iostream>

QVector<QList<QString> > iTunes::getAlbums(QString filePath, QVector<QString> keys)
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
	}

	return albums;
}
