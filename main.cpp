#include <iostream>
#include <QtCore>
#include <QFile>
#include <QtXml>
#include <QtDebug>
#include <QVector>

using namespace std;

int main() {

	QDomDocument doc("Lib");
	QFile file("/Users/wizardman/QtRFIDMusic/Lib.xml");
	if(!file.open(QIODevice::ReadOnly))
		return 1;
	if(!doc.setContent(&file)) {
		file.close();
		return 1;
	}
	file.close();

	// Root element
	QDomElement docElem = doc.documentElement();

	// <plist> -> <dict>
	QDomNode n = docElem.firstChild().firstChildElement("dict");

	cout << endl << "Album list" << endl;
	cout << "------------------------------------" << endl;

	// Get the children nodes of the first dict
	QDomNodeList list = n.childNodes();
	int count = list.count();

	// Init the albums storage
	QVector<QVector<QString> > albums(0);
	int albumIterator(0);

	// And the keys we want
	QVector<QString> keys(0);
	keys.append("Album");
	keys.append("Track ID");
	keys.append("Name");

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
									albums[albumIterator].append(value);
							}
						}
					}
				}

				node = node.nextSiblingElement();
			}

			albumIterator = albumIterator+1;

		}
	}

	qDebug() << albums;

	return 0;
}
