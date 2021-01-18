#pragma once


template <typename A>
class Vector2
{
private:
	A _x = 0;
	A _y = 0;

public:
	Vector2<A>() 
	{
	}
	Vector2<A>(A const& x, A const& y)
	{
		_x = x;
		_y = y;
	}

	A x()
	{
		return _x;
	}
	A y()
	{
		return _y;
	}

	Vector2 operator-(Vector2<A> const& vec)
	{
		return Vector2<A>(this->_x - vec._x, this->_y - vec._y);
	}

	Vector2 operator+(Vector2<A> const& vec)
	{
		return Vector2<A>(this->_x + vec._x, this->_y + vec._y);
	}
};

