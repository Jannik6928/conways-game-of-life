#pragma once

#include <iostream>

#include "Vector2.h"

#include <SFML/Graphics.hpp>

class Camera
{
private:
	Vector2<double> _position;
	Vector2<double> _dimensions;

	int _zoom_level = 0;
	int _max_zoom = 0;
	int _min_zoom = 0;
	double _zoom_scale = 0;

public:
	Camera() 
	{
	}
	Camera(Vector2<double> position, Vector2<double> dimensions, int max, int min, double scale)
	{
		_position = position;
		_dimensions = dimensions;
		_max_zoom = max;
		_min_zoom = min;
		_zoom_scale = scale;
	}

	Vector2<double> position()
	{
		return _position;
	}
	Vector2<double> dimensions() {
		return _dimensions;
	}

	double max_zoom()
	{
		return _max_zoom;
	}
	double min_zoom()
	{
		return _min_zoom;
	}

	double zoom()
	{
		return std::pow(_zoom_scale, _zoom_level);
	}

	void change_zoom_level(int delta)
	{
		_zoom_level += delta;
		_zoom_level = std::clamp(_zoom_level, _max_zoom, _min_zoom);
	}

	void change_position(Vector2<double> delta_pos)
	{
		_position = _position + delta_pos;
	}

	void zoom_in(int delta, sf::Vector2i local_pos)
	{
		int initial_zoom_level = _zoom_level;
		_zoom_level = std::clamp(_zoom_level + delta, _max_zoom, _min_zoom);
		int delta_zoom_level = _zoom_level - initial_zoom_level;

		double initial_zoom = pow(_zoom_scale, initial_zoom_level);
		double delta_zoom = pow(_zoom_scale, delta_zoom_level);

		double delta_x = local_pos.x / initial_zoom * (1 - 1 / delta_zoom);
		double delta_y = local_pos.y / initial_zoom * (1 - 1 / delta_zoom);

		_position = Vector2<double>(_position.x() + delta_x, _position.y() + delta_y);
		_dimensions = Vector2<double>(_dimensions.x() / delta_zoom, _dimensions.y() / delta_zoom);
	}

	// returns sum of camera position and local mouse position vectors
	Vector2<double> click(sf::Vector2i mouse_pos)
	{
		return Vector2<double>(mouse_pos.x / zoom() + _position.x(), mouse_pos.y / zoom() + _position.y());;
	}

};

