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

	QVector<QString> albums(0);

	QDomNodeList list = n.childNodes();
	int count = list.count();

	for(int i = 0; i <= count; ++i)
	{
		QDomElement node = list.at(i).toElement();

		if(node.tagName().startsWith("dict"))
		{
			node = node.firstChildElement();

			while(!node.isNull())
			{
				QVector<QVector<QString> > = albums(0);

				if(node.tagName() == "key")
				{
					switch(node.text())
					case "Track ID":

						break;
					}
				}

				/*if(node.text() == "Album" && node.tagName() == "key")
				{
					node = node.nextSiblingElement();

					if(!node.isNull() && node.tagName() == "string")
					{
						QString album = node.text();

						if(albums.indexOf(album) == -1)
							albums.append(album);
					}
				}*/

				node = node.nextSiblingElement();
			}
		}
	}

	qDebug() << albums;

	return 0;
}
