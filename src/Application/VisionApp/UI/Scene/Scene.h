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

private:
	UniquePtr<QGraphicsScene> m_scene;
};
