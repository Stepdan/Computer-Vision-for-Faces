#pragma once

#include <list>

#include "Core/Interfaces/IDataImage.h"

using namespace Core::Interfaces;

namespace VisionApp {

class UndoHelper
{
public:
	UndoHelper();
	~UndoHelper() = default;

    void SetOriginal(const SharedPtr<IDataImage> & image) { m_orig = image; }
    const SharedPtr<IDataImage> & GetOriginal() const { return m_orig; }

    void Add(const SharedPtr<IDataImage> & image);

    SharedPtr<IDataImage> Undo();
    SharedPtr<IDataImage> Redo();
    SharedPtr<IDataImage> Reset();

	size_t UndoSize() const { return m_undo.size(); }
	size_t RedoSize() const { return m_redo.size(); }

public:
    std::list<SharedPtr<IDataImage>> m_undo;
    std::list<SharedPtr<IDataImage>> m_redo;

    SharedPtr<IDataImage> m_orig;
};

}
