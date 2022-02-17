#pragma once

#include "Vec3.h"
#include "IndexedLineList.h"
#include <vector>

class Cube
{
public:
	Cube( float size )
	{
		const float side = size / 2.0f;
		vertices.reserve( 8 );
		vertices.emplace_back( side, side, side );
		vertices.emplace_back( side, -side, side );
		vertices.emplace_back( -side, side, side );
		vertices.emplace_back( -side, -side, side );
		vertices.emplace_back( side, side, -side );
		vertices.emplace_back( side, -side, -side );
		vertices.emplace_back( -side, side, -side );
		vertices.emplace_back( -side, -side, -side );
	}
	IndexedLineList GetLines() const
	{
		return
		{
			vertices,
			{
				0,2, 0,4, 2,6, 4,6,
				4,5, 6,7, 5,7, 5,1,
				7,3, 1,3, 1,0, 3,2
			}
		};
	}
private:
	std::vector<Vec3> vertices;
};