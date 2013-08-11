#ifndef WINDOW_H
#define WINDOW_H

#include <QApplication>
#include <QWidget>
#include <QComboBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QList>
#include <QVector>
#include <QString>
#include <QDebug>
#include <itunes.h>

class Window : public QWidget
{

Q_OBJECT

public:
	Window();
	void createAlbumList(QVector<QString> albums);
	void setFields();
	void ssConnect();
	int selectedAlbum;
	QVector<QString> uniqueAlbumList;
private:
	QComboBox *qList;
	QPushButton *qPlay;
	QHBoxLayout *qLayout;

signals:
	
public slots:
	void getAlbumByIndex(int index);
	void qPlayAlbum();
	
};

#endif // WINDOW_H
