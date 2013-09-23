//[]------------------------------------------------------------------------[]
//|                                                                          |
//|                        Small Size League software                        |
//|                             Version 1.0                                  |
//|                     Laboratório de Inteligencia Artificial				 |
//| 				 Universidade Federal de Mato Grosso do Sul              |
//|					 Author: Bruno H. Gouveia, Yuri Claure					 |
//|																			 |
//[]------------------------------------------------------------------------[]
//
//  OVERVIEW: Vector.cpp
//  ========
//  Source file for vector 2D.

#ifndef VECTOR_H_
#include "Vector.h"
#endif

#include <math.h>

//////////////////////////////////////////////////////////
//
// Vector2D implementation
// ==========
Vector2D::Vector2D()
//[]----------------------------------------------------[]
//|  Constructor                                         |
//[]----------------------------------------------------[]
{
}

Vector2D::Vector2D(float x, float y) :
		TargetFixed(x, y)
//[]----------------------------------------------------[]
//|  Constructor                                         |
//[]----------------------------------------------------[]
{
}
Vector2D::~Vector2D()
//[]----------------------------------------------------[]
//|  Destructor                                          |
//[]----------------------------------------------------[]
{
}

void Vector2D::normalize(float norm)
//[]----------------------------------------------------[]
//|  Normalize                                           |
//[]----------------------------------------------------[]
{
	float n = sqrt(_x * _x + _y * _y);
	_x *= norm / n;
	_y *= norm / n;
}

float Vector2D::norm()
//[]----------------------------------------------------[]
//|  Norm	                                             |
//[]----------------------------------------------------[]
{
	return sqrt(_x * _x + _y * _y);
}

Vector2D Vector2D::rotateLeft(float angleRad)
//[]----------------------------------------------------[]
//|  Rotate Left                                         |
//[]----------------------------------------------------[]
{
	float x = (_x * cos(angleRad)) - (_y * sin(angleRad));
	float y = (_y * cos(angleRad)) + (_x * sin(angleRad));
	return Vector2D(x, y);
}

Vector2D Vector2D::rotateRight(float angleRad)
//[]----------------------------------------------------[]
//|  Rotate Right                                        |
//[]----------------------------------------------------[]
{
	float x = (_x * cos(angleRad)) + (_y * sin(angleRad));
	float y = (_y * cos(angleRad)) - (_x * sin(angleRad));
	return Vector2D(x, y);
}

float Vector2D::operator*(Vector2D & vector)
//[]----------------------------------------------------[]
//|  Operator *                                          |
//[]----------------------------------------------------[]
{
	return (_x * vector._x + _y * vector._y);
}

double Vector2D::findAngle()
//[]----------------------------------------------------[]
//|  Find angle                                          |
//[]----------------------------------------------------[]
{
	return atan2(_y, _x);
}

float Vector2D::angle(Vector2D & vec1, Vector2D & vec2)
//[]----------------------------------------------------[]
//|  Angle	 	                                         |
//[]----------------------------------------------------[]
{
	return angleDiff(vec1.findAngle(),vec2.findAngle());
}

float Vector2D::angleDiff(float angle1, float angle2)
//[]----------------------------------------------------[]
//|  Angle Diff                                          |
//[]----------------------------------------------------[]
{
	float angleDiff;

	if (angle1 > angle2) {
		angleDiff = angle1 - angle2;

		if (angleDiff > M_PI) {
			angleDiff = float(M_PI - angle1) + float(M_PI + angle2);
			return -angleDiff;
		}
		return angleDiff;
	} else {
		angleDiff = angle2 - angle1;
		if (angleDiff > M_PI) {
			angleDiff = float(M_PI - angle2) + float(M_PI + angle1);
			return angleDiff;
		}
		return -angleDiff;
	}

}

void Vector2D::set(Vector2D & vector) {
	_x = vector.x();
	_y = vector.y();

}
