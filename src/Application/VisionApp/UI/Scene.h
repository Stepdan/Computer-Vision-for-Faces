#pragma once

#include <QGraphicsView>
#include <QGraphicsScene>

#include "Types/Pointers.h"

class Scene : public QGraphicsView
{
	Q_OBJECT

public:
	explicit Scene(QWidget *parent = 0);
	~Scene();

public:
	void wheelEvent(QWheelEvent* event);

public:
	void SetImage(const QImage& image);
	QPixmap GetImage() const;

private:
	UniquePtr<QGraphicsScene> m_scene;
};
