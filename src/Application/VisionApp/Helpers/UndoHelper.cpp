#include "UndoHelper.h"

using namespace Core::Interfaces;

namespace VisionApp {

UndoHelper::UndoHelper()
{
}

void UndoHelper::Add(const SharedPtr<IDataImage> & image)
{
	m_redo.clear();
	m_undo.push_back(image);
}

SharedPtr<IDataImage> UndoHelper::Undo()
{
	if(m_undo.size() == 0)
		return m_orig;

	m_redo.push_back(m_undo.back());
	m_undo.pop_back();

	return m_undo.size() ? m_undo.back() : m_orig;
}

SharedPtr<IDataImage> UndoHelper::Redo()
{
	const auto image = m_redo.back();
	m_undo.push_back(image);
	m_redo.pop_back();

	return image;
}

SharedPtr<IDataImage> UndoHelper::Reset()
{
	m_undo.clear();
	m_redo.clear();

	return m_orig;
}

}
