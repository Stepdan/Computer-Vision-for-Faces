#include "Scene.h"

#include <cassert>

#include <QList>

#include <QGraphicsPixmapItem>

Scene::Scene(QWidget *parent)
	: QGraphicsView(parent)
	, m_scene(new QGraphicsScene(parent))
{
	setScene(m_scene.get());
}

Scene::~Scene()
{
}

void Scene::SetImage(const QImage& image)
{
	QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(image));

	m_scene->clear();
	m_scene->addItem(item);

	m_scene->update();
	update();
}

QPixmap Scene::GetImage() const
{
	const auto itemsList = m_scene->items();
	assert(itemsList.size() < 2);

	return dynamic_cast<QGraphicsPixmapItem*>(itemsList[0])->pixmap();
}
