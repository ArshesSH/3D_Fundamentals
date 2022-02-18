#pragma once

#include "Vec3.h"
#include "Graphics.h"

class PubeScreenTransformer
{
public:
	PubeScreenTransformer()
		:
		xFactor( float( Graphics::ScreenWidth / 2.0f ) ),
		yFactor( float( Graphics::ScreenHeight / 2.0f ) )
	{}
	Vec3& Transform( Vec3& v ) const
	{
		const float devZ = 1 / v.z;
		v.x = (v.x * devZ + 1) * xFactor;
		v.y = (v.y * devZ + 1) * yFactor;
		return v;
	}
	Vec3 GetTransformed( const Vec3& v ) const
	{
		return Transform( Vec3( v ) );
	}
private:
	float xFactor;
	float yFactor;
};