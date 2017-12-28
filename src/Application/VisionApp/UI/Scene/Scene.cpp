#include "Scene.h"

#include <cassert>

#include <QList>
#include <QWheelEvent>
#include <QGraphicsPixmapItem>

#include "Utils/ObjectsConnector.h"
#include "Utils/ObjectsConnectorID.h"

namespace {

constexpr double SCALE_UP_FACTOR = 1.1;
constexpr double SCALE_DOWN_FACTOR = 0.9;

}

Scene::Scene(QWidget *parent)
	: QGraphicsView(parent)
	, m_scene(new QGraphicsScene(parent))
{
	setScene(m_scene.get());

	Utils::ObjectsConnector::registerEmitter(IObjectsConnectorID::UPDATE_INFO_TEXT, this, SIGNAL(mousePressPosChanged(const QString &)));
	Utils::ObjectsConnector::registerEmitter(IObjectsConnectorID::TRAINING_LANDMARK_CHANGED, this, SIGNAL(landmarkPosChanged()));

	Utils::ObjectsConnector::registerReceiver(IObjectsConnectorID::ENABLE_TRAINING_MODE, this, SLOT(OnEnableTrainingMode(bool)));
	Utils::ObjectsConnector::registerReceiver(IObjectsConnectorID::TRAINING_FACE_CHANGED, this, SLOT(OnTrainingFaceChanged(const SharedPtr<Types::Face> &)));
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

void Scene::mousePressEvent(QMouseEvent* event)
{
	switch(m_mode)
	{
	case SceneMode::Training:
		OnTrainingMousePress(event);
	case SceneMode::Default:
	default:
		break;
	}

	QGraphicsView::mousePressEvent(event);
}

void Scene::mouseReleaseEvent(QMouseEvent *event)
{
	switch(m_mode)
	{
	case SceneMode::Training:
		OnTrainingMouseRelease(event);
	case SceneMode::Default:
	default:
		break;
	}

	QGraphicsView::mouseReleaseEvent(event);
}

void Scene::SetImage(const QImage& image)
{
	QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(image));

	m_scene->clear();
	m_scene->addItem(item);

	m_scene->update();
	update();
}

/* Training mode */

void Scene::OnTrainingMousePress(QMouseEvent *event)
{
	if(event->button() == Qt::RightButton)
	{
		const auto pos = mapToScene(event->pos());

		if(!m_editLandmark)
		{
			const auto it = std::find_if(m_landmarks.cbegin(), m_landmarks.cend(), [&pos](const Types::Point & pnt){
				return static_cast<int>(pos.x()) == pnt.x && static_cast<int>(pos.y()) == pnt.y;
			});

			if(it != m_landmarks.cend())
			{
				m_editLandmark = true;
				m_landmarkIndex = distance(m_landmarks.cbegin(), it);
			}
		}
		else
		{
			const auto landmark = Types::Point(static_cast<int>(pos.x()), static_cast<int>(pos.y()));
			m_face->SetLandmark(m_landmarkIndex, landmark);
			m_landmarks[m_landmarkIndex] = landmark;
			m_editLandmark = false;

			emit landmarkPosChanged();
		}

		emit mousePressPosChanged("Training mode. Mouse click at ( " +
								  QString::number(pos.x())+", " + QString::number(pos.y()) + " )");
	}

}

void Scene::OnTrainingMouseRelease(QMouseEvent *event)
{

}

//--------------------------------------------

void Scene::OnEnableTrainingMode(bool enabled)
{
	m_mode = enabled ? SceneMode::Training : SceneMode::Default;
}

void Scene::OnTrainingFaceChanged(const SharedPtr<Types::Face> & face)
{
	m_face = face;
	m_landmarks = m_face->GetAllPoints();
}
