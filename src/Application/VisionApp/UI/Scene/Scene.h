#pragma once

#include <QGraphicsView>
#include <QGraphicsScene>

#include "Types/Pointers.h"
#include "Types/Face.h"

/*
Режимы работы сцены:
1. Default - обычное отображениею
2. Training - Режим работы тренировщика. Можно изменять положения найденных landmark-ов лиц.
Обработка событий мыши.
*/
enum class SceneMode
{
	Default,
	Training
};

class Scene : public QGraphicsView
{
	Q_OBJECT

public:
	explicit Scene(QWidget *parent = 0);
	~Scene();

public:
	void wheelEvent(QWheelEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;

public:
	void SetSceneMode(SceneMode mode) { m_mode = mode; }
	SceneMode GetSceneMode() const { return m_mode; }

public:
	void SetImage(const QImage& image);

	// Training mode
signals:
	void landmarkPosChanged();
	void mousePressPosChanged(const QString &);

private:
	void OnTrainingMousePress(QMouseEvent *event);
	void OnTrainingMouseRelease(QMouseEvent *event);
	void OnTrainingMouseMove(QMouseEvent *event);

private slots:
	void OnEnableTrainingMode(bool);
	void OnTrainingFaceChanged(const SharedPtr<Types::Face> &);

private:
	UniquePtr<QGraphicsScene> m_scene;

	SceneMode m_mode = SceneMode::Default;

	SharedPtr<Types::Face> m_face;
	Types::Contour m_landmarks;
	bool m_editLandmark = false;
	size_t m_landmarkIndex;
};
