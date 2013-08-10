#ifndef WINDOW_H
#define WINDOW_H

#include <QApplication>
#include <QWidget>
#include <QComboBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QList>
#include <QDebug>

class Window : public QWidget
{

Q_OBJECT

public:
	Window();
	void createAlbumList(QVector<QString> albums);
	void setFields();
private:
	QComboBox *qList;
	QPushButton *qPlay;
	QHBoxLayout *qLayout;
	
signals:
	
public slots:
	
};

#endif // WINDOW_H
