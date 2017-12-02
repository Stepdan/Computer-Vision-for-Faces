#include "Scene.h"

#include <cassert>

#include <QList>
#include <QWheelEvent>

#include <QGraphicsPixmapItem>

namespace {

constexpr double SCALE_UP_FACTOR = 1.1;
constexpr double SCALE_DOWN_FACTOR = 0.9;

}

Scene::Scene(QWidget *parent)
	: QGraphicsView(parent)
	, m_scene(new QGraphicsScene(parent))
{
	setScene(m_scene.get());
}

Scene::~Scene()
{
}

void Scene::wheelEvent(QWheelEvent* event)
{
	static double factor;

	factor = (event->delta() > 0) ? SCALE_UP_FACTOR : SCALE_DOWN_FACTOR;

	const QPointF viewportPos = underMouse() ? mapFromGlobal(QCursor::pos()) : QPointF();
	const QPointF scenePos = mapToScene(viewportPos.toPoint());

	scale(factor, factor);

	if(!viewportPos.isNull())
	{
		centerOn(scenePos);
		QPointF viewportDelta = viewportPos - QPointF(viewport()->width() / 2., viewport()->height() / 2.);
		QPointF viewportCenter = mapFromScene(scenePos) - viewportDelta;
		centerOn(mapToScene(viewportCenter.toPoint()));
	}

	update();
}

void Scene::SetImage(const QImage& image)
{
	QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(image));

	m_scene->clear();
	m_scene->addItem(item);

	m_scene->update();
	update();
}
