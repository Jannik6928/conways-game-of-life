#pragma once
class Tile
{
private:
	int _age = 0;

public:
	Tile()
	{
		
	}
	void increment_age() 
	{
		++_age;
	}

	int age()
	{
		return _age;
	}

};

