#pragma once

#include <list>

#include <QImage>

namespace VisionApp {

class UndoHelper
{
public:
	UndoHelper();
	~UndoHelper() = default;

	void SetOriginal(const QImage & image) { m_orig = image; }
	const QImage & GetOriginal() const { return m_orig; }

	void Add(const QImage & image);

	QImage Undo();
	QImage Redo();
	QImage Reset();

public:
	std::list<QImage> m_undo;
	std::list<QImage> m_redo;

	QImage m_orig;
};

}
