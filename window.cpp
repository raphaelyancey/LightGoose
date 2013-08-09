#include "window.h"

Window::Window() : QWidget()
{
	setFixedSize(400, 100);
	qLayout = new QHBoxLayout;
	qList = new QComboBox;
	qPlay = new QPushButton("Play");
}

void Window::albumList(QVector<QString> albums)
{
	for(int i = 0; i < albums.count(); i++)
		qList->addItem(albums[i]);
}

void Window::setFields()
{
	qLayout->addWidget(qList);
	qLayout->addWidget(qPlay);

	setLayout(qLayout);
}
