#include "Builder.h"

//template<typename T, typename U>
//Builder<T, U>::Builder()
//{
//}
//
//template<typename T, typename U>
//Builder<T, U>::~Builder()
//{
//}

template<typename T, typename U>
Builder<T, U>& Builder<T, U>::Position(glm::vec3& position)
{
	Pos = position;
	return *this;
}

template<typename T, typename U>
Builder<T, U>& Builder<T, U>::Position(glm::vec3&& position)
{
	Pos = std::move(position);
	return *this;
}

template<typename T, typename U>
Builder<T, U>& Builder<T, U>::Rotation(glm::vec3& position)
{
	return *this;
}

template<typename T, typename U>
Builder<T, U>& Builder<T, U>::Scale(glm::vec3& scale)
{
	return *this;
}
