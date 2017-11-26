#include "UndoHelper.h"

namespace {

constexpr int SIZE = 3;

}

namespace VisionApp {

UndoHelper::UndoHelper()
{
}

void UndoHelper::Add(const QImage & image)
{
	m_redo.clear();

	if(m_undo.size() < SIZE)
		m_undo.push_back(image);
	else
	{
		m_undo.pop_front();
		m_undo.push_back(image);
	}
}

QImage UndoHelper::Undo()
{
	if(m_undo.size() == 0)
		return m_orig;

	m_redo.push_back(m_undo.back());
	m_undo.pop_back();

	return m_undo.size() ? m_undo.back() : m_orig;
}

QImage UndoHelper::Redo()
{
	const auto image = m_redo.back();
	m_undo.push_back(image);
	m_redo.pop_back();

	return image;
}

QImage UndoHelper::Reset()
{
	m_undo.clear();
	m_redo.clear();

	return m_orig;
}

}
