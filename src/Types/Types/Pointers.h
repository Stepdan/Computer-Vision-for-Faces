#pragma once

#include <memory>

template<typename T> using SharedPtr = std::shared_ptr<T>;
template<typename T> using UniquePtr = std::unique_ptr<T>;
template<typename T> using WeakPtr   = std::weak_ptr<T>;

template<typename T, typename ...ARGS> inline
SharedPtr<T> MakeShared(ARGS&&... args)
{
	return std::make_shared<T>(std::forward<ARGS>(args)...);
}
