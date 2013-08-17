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
	Window(iTunes *instance);
	void createAlbumList();
	void setUi();
	void setLinks();
	int selectedAlbum;
private:
	QComboBox *qList;
	QPushButton *qPlay;
	QHBoxLayout *qLayout;
	QPushButton *qRefresh;
	iTunes *i;

signals:
	
public slots:
	void getAlbumByIndex(int index);
	void qPlayAlbum();
	void refreshList();
};

#endif // WINDOW_H
