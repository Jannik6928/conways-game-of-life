#pragma once


#include <map>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>

#include "Tile.h"
#include "Camera.h"

#include <SFML/Graphics.hpp>

template<typename A, typename B>
std::pair<A,B> operator+(const std::pair<A,B> &first, const std::pair<A,B> &second) {
	return std::pair<A, B>(first.first + second.first, first.second + second.second);
}
template <typename A>
bool in_range(A const& val, A const& min, A const& max)
{
	return !(val < min) && !(max < val);
}

class Grid
{
private:
	std::map<std::pair<int, int>, Tile> _map;
	double _tile_length = 0;

public:
	Grid() 
	{
	}
	Grid(double tile_length)
	{
		_tile_length = tile_length;
	}
	
	int count_neighbors(std::pair<int, int> const& key)
	{
		int adj_count = 0;
		for (int i = -1; i <= 1; ++i)
		{
			for (int j = -1; j <= 1; ++j)
			{
				if (i || j) {
					if (_map.count(std::pair<int, int>(i, j) + key))
					{
						++adj_count;
					}
				}
			}

		}
		return adj_count;

	}
	void make_step() 
	{
		std::vector<std::pair<int, int>> dead_keys;
		std::vector<std::pair<int, int>> new_keys;

		for (auto const& x : _map)
		{
			int adj_count = count_neighbors(x.first);
			if (!(adj_count == 2 || adj_count == 3)) 
			{
				dead_keys.push_back(x.first);
			}

			for (int i = -1; i <= 1; ++i)
			{
				for (int j = -1; j <= 1; ++j)
				{
					if (i || j) 
					{
						std::pair<int, int> neighbor = std::pair<int, int>(i, j) + x.first;
						if (!_map.count(neighbor))
						{
							int adj_count = count_neighbors(neighbor);
							if (adj_count == 3) 
							{
								new_keys.push_back(neighbor);
							}
						}

					}
				}

			}

		}

		for (auto& key : dead_keys)
		{
			_map.erase(key);
		}
		for (auto& x : _map)
		{
			x.second.increment_age();
		}
		for (auto const& key : new_keys)
		{
			_map.insert({ key, Tile() });
		}

	}

	void toggle(std::pair<int, int> key)
	{
		if (_map.count(key)) 
		{
			_map.erase(key);
		}
		else
		{
			_map.insert_or_assign(key, Tile());
		}
	}
	void remove_tile(std::pair<int, int> key)
	{
		if (_map.count(key))
		{
			_map.erase(key);
		}
	}
	void insert_tile(std::pair<int, int> key)
	{
		_map.insert_or_assign(key, Tile());
	}

	std::pair<int, int> to_grid_coordinates(Vector2<double> global_pos, Camera& camera)
	{
		return std::pair<int, int>(std::floor((global_pos.x() / _tile_length)),
			std::floor((global_pos.y() / _tile_length)));
	}

	void toggle(Vector2<double> pos, Camera& camera)
	{
		toggle(to_grid_coordinates(pos, camera));
	}
	void remove_tile(Vector2<double> pos, Camera& camera)
	{
		remove_tile(to_grid_coordinates(pos, camera));
	}
	void insert_tile(Vector2<double> pos, Camera& camera)
	{
		insert_tile(to_grid_coordinates(pos, camera));
	}

	void clear() {
		_map.clear();
	}

	void draw(sf::RenderWindow &window, Camera &camera)
	{
		
		double tile_len = _tile_length * camera.zoom();
		double offset_x = fmod(camera.position().x() * camera.zoom(), tile_len);
		double offset_y = fmod(camera.position().y() * camera.zoom(), tile_len);
		for (double i = -offset_x; i < -offset_x + camera.dimensions().x() * camera.zoom() + tile_len; i += tile_len)
		{
			sf::RectangleShape line(sf::Vector2f(1, camera.dimensions().y() * camera.zoom()));
			line.setFillColor(sf::Color(128, 128, 128, 255));
			line.setPosition(sf::Vector2f(i, 0));
			window.draw(line);
		}
		for (double i = -offset_y; i < -offset_y + camera.dimensions().y() * camera.zoom() + tile_len; i += tile_len)
		{
			sf::RectangleShape line(sf::Vector2f(camera.dimensions().x() * camera.zoom(), 1));
			line.setFillColor(sf::Color(128, 128, 128, 255));
			line.setPosition(sf::Vector2f(0, i));
			window.draw(line);
		}

		for (auto& [key, val] : _map)
		{

			if (tile_len * key.first - camera.position().x() * camera.zoom() > -tile_len && tile_len * key.first - camera.position().x() * camera.zoom() < camera.dimensions().x() * camera.zoom() + tile_len)
			{
				if (tile_len * key.second - camera.position().y() * camera.zoom() > -tile_len && tile_len * key.second - camera.position().y() * camera.zoom() < camera.dimensions().y() * camera.zoom() + tile_len)
				{
					sf::RectangleShape tile_sprite(sf::Vector2f(tile_len, tile_len));

					tile_sprite.setPosition(tile_len * key.first - camera.position().x() * camera.zoom(), tile_len * key.second - camera.position().y() * camera.zoom());
					window.draw(tile_sprite);
				}
			}

		}

	}

};

