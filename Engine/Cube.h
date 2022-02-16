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
				0,1, 0,2, 1,3, 2,3,
				2,4, 3,5, 4,5, 4,6,
				5,7, 6,7, 6,0, 7,1
			}
		};
	}
private:
	std::vector<Vec3> vertices;
};