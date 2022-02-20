#pragma once

#include "Scene.h"
#include "Mat3.h"
#include "PubeScreenTransformer.h"
#include "Cube.h"

class SolidCubeScene :public Scene
{
public:
	SolidCubeScene() = default;
	virtual void Update( Keyboard& kbd, Mouse& mouse, float dt ) override
	{
		if ( kbd.KeyIsPressed( 'Q' ) )
		{
			theta_x += wrap_angle( dTheta * dt );
		}
		if ( kbd.KeyIsPressed( 'W' ) )
		{
			theta_y += wrap_angle( dTheta * dt );
		}
		if ( kbd.KeyIsPressed( 'E' ) )
		{
			theta_z += wrap_angle( dTheta * dt );
		}
		if ( kbd.KeyIsPressed( 'A' ) )
		{
			theta_x -= wrap_angle( dTheta * dt );
		}
		if ( kbd.KeyIsPressed( 'S' ) )
		{
			theta_y -= wrap_angle( dTheta * dt );
		}
		if ( kbd.KeyIsPressed( 'D' ) )
		{
			theta_z -= wrap_angle( dTheta * dt );
		}
		if ( kbd.KeyIsPressed( 'R' ) )
		{
			offset_z += dt * 0.5f;
		}
		if ( kbd.KeyIsPressed( 'F' ) )
		{
			offset_z -= dt * 0.5f;
		}
	}
	virtual void Draw( Graphics& gfx ) const override
	{
		auto triangles = cube.GetTriangles();
		const Mat3 rotation = Mat3::RotationX( theta_x ) * Mat3::RotationY( theta_y ) * Mat3::RotationZ( theta_z );
		// Transform from Model space -> world space
		for ( auto& v : triangles.vertices )
		{
			v *= rotation;
			v += {0.0f, 0.0f, 2.0f + offset_z};
		}
		// Culling 
		for ( size_t i = 0, end = triangles.indices.size() / 3; i < end; i++ )
		{
			const Vec3& v0 = triangles.vertices[triangles.indices[i * 3]];
			const Vec3& v1 = triangles.vertices[triangles.indices[i * 3 + 1]];
			const Vec3& v2 = triangles.vertices[triangles.indices[i * 3 + 2]];

			triangles.cullFlags[i] = Vec3::GetCrossProduct( (v1 - v0), (v2 - v0) ) * v0 < 0.0f;
		}
		// transform to screen space
		for ( auto& v : triangles.vertices )
		{
			pst.Transform( v );
		}
		// draw triangle
		for ( size_t i = 0, end = triangles.indices.size() / 3; i < end; i++ )
		{
			if ( triangles.cullFlags[i] )
			{
				gfx.DrawTriangle(
					triangles.vertices[triangles.indices[i * 3]],
					triangles.vertices[triangles.indices[i * 3 + 1]],
					triangles.vertices[triangles.indices[i * 3 + 2]],
					colors[i]
				);
			}
		}
	}

private:
	static constexpr Color colors[12] = {
		Colors::White,
		Colors::Blue,
		Colors::Cyan,
		Colors::Gray,
		Colors::Green,
		Colors::Magenta,
		Colors::LightGray,
		Colors::Red,
		Colors::Yellow,
		Colors::White,
		Colors::Blue,
		Colors::Cyan
	};
	static constexpr float dTheta = PI;
	Cube cube = Cube(1.0f);
	PubeScreenTransformer pst;
	float theta_x = 0.0f;
	float theta_y = 0.0f;
	float theta_z = 0.0f;
	float offset_z = 0.0f;
};