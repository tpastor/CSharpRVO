/*
 *  Vector3.h
 *  RVO2-3D Library.
 *
 *  Copyright (C) 2008-11 University of North Carolina at Chapel Hill.
 *  All rights reserved.
 *
 *  Permission to use, copy, modify, and distribute this software and its
 *  documentation for educational, research, and non-profit purposes, without
 *  fee, and without a written agreement is hereby granted, provided that the
 *  above copyright notice, this paragraph, and the following four paragraphs
 *  appear in all copies.
 *
 *  Permission to incorporate this software into commercial products may be
 *  obtained by contacting the University of North Carolina at Chapel Hill.
 *
 *  This software program and documentation are copyrighted by the University of
 *  North Carolina at Chapel Hill. The software program and documentation are
 *  supplied "as is", without any accompanying services from the University of
 *  North Carolina at Chapel Hill or the authors. The University of North
 *  Carolina at Chapel Hill and the authors do not warrant that the operation of
 *  the program will be uninterrupted or error-free. The end-user understands
 *  that the program was developed for research purposes and is advised not to
 *  rely exclusively on the program for any reason.
 *
 *  IN NO EVENT SHALL THE UNIVERSITY OF NORTH CAROLINA AT CHAPEL HILL OR ITS
 *  EMPLOYEES OR THE AUTHORS BE LIABLE TO ANY PARTY FOR DIRECT, INDIRECT,
 *  SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, INCLUDING LOST PROFITS,
 *  ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF THE
 *  UNIVERSITY OF NORTH CAROLINA AT CHAPEL HILL OR THE AUTHORS HAVE BEEN ADVISED
 *  OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *  THE UNIVERSITY OF NORTH CAROLINA AT CHAPEL HILL AND THE AUTHORS SPECIFICALLY
 *  DISCLAIM ANY WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 *  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE AND ANY
 *  STATUTORY WARRANTY OF NON-INFRINGEMENT. THE SOFTWARE PROVIDED HEREUNDER IS
 *  ON AN "AS IS" BASIS, AND THE UNIVERSITY OF NORTH CAROLINA AT CHAPEL HILL AND
 *  THE AUTHORS HAVE NO OBLIGATIONS TO PROVIDE MAINTENANCE, SUPPORT, UPDATES,
 *  ENHANCEMENTS, OR MODIFICATIONS.
 *
 *  Please send all BUG REPORTS to:
 *
 *  geom@cs.unc.edu
 *
 *  The authors may be contacted via:
 *
 *  Jur van den Berg, Stephen J. Guy, Jamie Snape, Ming C. Lin, and
 *  Dinesh Manocha
 *  Dept. of Computer Science
 *  Frederick P. Brooks Jr. Computer Science Bldg.
 *  3175 University of N.C.
 *  Chapel Hill, N.C. 27599-3175
 *  United States of America
 *
 *  http://gamma.cs.unc.edu/RVO2/
 *
 */

/*!
 *  @file		Vector3.h
 *  @brief		Contains the Vector3 class.
 */
#ifndef RVO_VECTOR_3_H
#define RVO_VECTOR_3_H

#include "API.h"

#include <cmath>
#include <ostream>

namespace RVO
{
/*!
 *  @brief		Defines a three-dimensional vector.
 */
__declspec(dllexport) class Vector3
{
public:
	/*!
	 *  @brief		Constructs and initializes a three-dimensional vector instance to zero.
	 */
	RVO_API inline Vector3()
	{
		val_[0] = 0.0f;
		val_[1] = 0.0f;
		val_[2] = 0.0f;
	}

	/*!
	 *  @brief		Constructs and initializes a three-dimensional vector from the specified three-dimensional vector.
	 *  @param		vector		The three-dimensional vector containing the xyz-coordinates.
	 */
	RVO_API inline Vector3(const Vector3& vector)
	{
		val_[0] = vector[0];
		val_[1] = vector[1];
		val_[2] = vector[2];
	}

	/*!
	 *  @brief		Constructs and initializes a three-dimensional vector from the specified three-element array.
	 *  @param		val		The three-element array containing the xyz-coordinates.
	 */
	RVO_API inline explicit Vector3(const float val[3])
	{
		val_[0] = val[0];
		val_[1] = val[1];
		val_[2] = val[2];
	}

	/*!
	 *  @brief		Constructs and initializes a three-dimensional vector from the specified xyz-coordinates.
	 *  @param		vx		The x-coordinate of the three-dimensional vector.
	 *  @param		vy		The y-coordinate of the three-dimensional vector.
	 *  @param		vz		The z-coordinate of the three-dimensional vector.
	 */
	RVO_API inline Vector3(float vx, float vy, float vz)
	{
		val_[0] = vx;
		val_[1] = vy;
		val_[2] = vz;
	}

	/*!
	 *  @brief		Returns the x-coordinate of this three-dimensional vector.
	 *  @returns	The x-coordinate of the three-dimensional vector.
	 */
	RVO_API inline float x() const
	{
		return val_[0];
	}

	/*!
	 *  @brief		Returns the y-coordinate of this three-dimensional vector.
	 *  @returns	The y-coordinate of the three-dimensional vector.
	 */
	RVO_API inline float y() const
	{
		return val_[1];
	}

	/*!
	 *  @brief		Returns the z-coordinate of this three-dimensional vector.
	 *  @returns	The z-coordinate of the three-dimensional vector.
	 */
	RVO_API inline float z() const
	{
		return val_[2];
	}

	/*!
	 *  @brief		Returns the specified coordinate of this three-dimensional vector.
	 *  @param		i		The coordinate that should be returned (0 <= i < 3).
	 *  @returns    The specified coordinate of the three-dimensional vector.
	 */
	RVO_API inline float operator[](size_t i) const
	{
		return val_[i];
	}

	/*!
	 *  @brief		Returns a reference to the specified coordinate of this three-dimensional vector.
	 *  @param		i		The coordinate to which a reference should be returned (0 <= i < 3).
	 *  @returns	A reference to the specified coordinate of the three-dimensional vector.
	 */
	RVO_API inline float& operator[](size_t i)
	{
		return val_[i];
	}

	/*!
	 *  @brief		Computes the negation of this three-dimensional vector.
	 *  @returns	The negation of this three-dimensional vector.
	 */
	RVO_API inline Vector3 operator-() const
	{
		return Vector3(-val_[0], -val_[1], -val_[2]);
	}

	/*!
	 *  @brief		Computes the dot product of this three-dimensional vector with the specified three-dimensional vector.
	 *  @param		vector		The three-dimensional vector with which the dot product should be computed.
	 *  @returns	The dot product of this three-dimensional vector with a specified three-dimensional vector.
	 */
	RVO_API inline float operator*(const Vector3& vector) const
	{
		return val_[0] * vector[0] + val_[1] * vector[1] + val_[2] * vector[2];
	}

	/*!
	 *  @brief		Computes the scalar multiplication of this three-dimensional vector with the specified scalar value.
	 *  @param		scalar		The scalar value with which the scalar multiplication should be computed.
	 *  @returns	The scalar multiplication of this three-dimensional vector with a specified scalar value.
	 */
	RVO_API inline Vector3 operator*(float scalar) const
	{
		return Vector3(val_[0] * scalar, val_[1] * scalar, val_[2] * scalar);
	}

	/*!
	 *  @brief		Computes the scalar division of this three-dimensional vector
	 *              with the specified scalar value.
	 *  @param		scalar		The scalar value with which the scalar division should be computed.
	 *  @returns	The scalar division of this three-dimensional vector with a specified scalar value.
	 */
	RVO_API inline Vector3 operator/(float scalar) const
	{
		const float invScalar = 1.0f / scalar;

		return Vector3(val_[0] * invScalar, val_[1] * invScalar, val_[2] * invScalar);
	}

	/*!
	 *  @brief		Computes the vector sum of this three-dimensional vector with the specified three-dimensional vector.
	 *  @param		vector	The three-dimensional vector with which the vector sum should be computed.
	 *  @returns	The vector sum of this three-dimensional vector with a specified three-dimensional vector.
	 */
	RVO_API inline Vector3 operator+(const Vector3& vector) const
	{
		return Vector3(val_[0] + vector[0], val_[1] + vector[1], val_[2] + vector[2]);
	}

	/*!
	 *  @brief		Computes the vector difference of this three-dimensional vector with the specified three-dimensional vector.
	 *  @param		vector		The three-dimensional vector with which the vector difference should be computed.
	 *  @returns	The vector difference of this three-dimensional vector with a specified three-dimensional vector.
	 */
	RVO_API inline Vector3 operator-(const Vector3& vector) const
	{
		return Vector3(val_[0] - vector[0], val_[1] - vector[1], val_[2] - vector[2]);
	}

	/*!
	 *  @brief		Tests this three-dimensional vector for equality with the specified three-dimensional vector.
	 *  @param		vector		The three-dimensional vector with which to test for equality.
	 *  @returns	True if the three-dimensional vectors are equal.
	 */
	RVO_API inline bool operator==(const Vector3& vector) const
	{
		return val_[0] == vector[0] && val_[1] == vector[1] && val_[2] == vector[2];
	}

	/*!
	 *  @brief		Tests this three-dimensional vector for inequality with the specified three-dimensional vector.
	 *  @param		vector		The three-dimensional vector with which to test for inequality.
	 *  @returns	True if the three-dimensional vectors are not equal.
	 */
	RVO_API inline bool operator!=(const Vector3& vector) const
	{
		return val_[0] != vector[0] || val_[1] != vector[1] || val_[2] != vector[2];
	}

	/*!
	 *  @brief		Sets the value of this three-dimensional vector to the scalar multiplication of itself with the specified scalar value.
	 *  @param		scalar		The scalar value with which the scalar multiplication should be computed.
	 *  @returns	A reference to this three-dimensional vector.
	 */
	RVO_API inline Vector3& operator*=(float scalar)
	{
		val_[0] *= scalar;
		val_[1] *= scalar;
		val_[2] *= scalar;

		return *this;
	}

	/*!
	 *  @brief		Sets the value of this three-dimensional vector to the scalar division of itself with the specified scalar value.
	 *  @param		scalar		The scalar value with which the scalar division should be computed.
	 *  @returns	A reference to this three-dimensional vector.
	 */
	RVO_API inline Vector3& operator/=(float scalar)
	{
		const float invScalar = 1.0f / scalar;

		val_[0] *= invScalar;
		val_[1] *= invScalar;
		val_[2] *= invScalar;

		return *this;
	}

	/*!
	 *  @brief		Sets the value of this three-dimensional vector to the vector
	 *              sum of itself with the specified three-dimensional vector.
	 *  @param		vector		The three-dimensional vector with which the vector sum should be computed.
	 *  @returns	A reference to this three-dimensional vector.
	 */
	RVO_API inline Vector3& operator+=(const Vector3& vector)
	{
		val_[0] += vector[0];
		val_[1] += vector[1];
		val_[2] += vector[2];

		return *this;
	}

	/*!
	 *  @brief		Sets the value of this three-dimensional vector to the vector difference of itself with the specified three-dimensional vector.
	 *  @param		vector	The three-dimensional vector with which the vector difference should be computed.
	 *  @returns	A reference to this three-dimensional vector.
	 */
	RVO_API inline Vector3& operator-=(const Vector3& vector)
	{
		val_[0] -= vector[0];
		val_[1] -= vector[1];
		val_[2] -= vector[2];

		return *this;
	}

private:
	float val_[3];
};


/*!
 *  @brief		Computes the scalar multiplication of the specified three-dimensional vector with the specified scalar value.
 *  @param		scalar		The scalar value with which the scalar multiplication should be computed.
 *  @param      vector		The three-dimensional vector with which the scalar multiplication should be computed.
 *  @returns    The scalar multiplication of the three-dimensional vector with the scalar value.
 */
inline Vector3 operator*(float scalar, const Vector3& vector)
{
	return Vector3(scalar * vector[0], scalar * vector[1], scalar * vector[2]);
}

/*!
 *  @brief		Computes the cross product of the specified three-dimensional vectors.
 *  @param		vector1		The first vector with which the cross product should be computed.
 *  @param		vector2		The second vector with which the cross product should be computed.
 *  @returns	The cross product of the two specified vectors.
 */
inline Vector3 cross(const Vector3& vector1, const Vector3& vector2)
{
	return Vector3(vector1[1] * vector2[2] - vector1[2] * vector2[1], vector1[2] * vector2[0] - vector1[0] * vector2[2], vector1[0] * vector2[1] - vector1[1] * vector2[0]);
}

/*!
 *  @brief		Inserts the specified three-dimensional vector into the specified output stream.
 *  @param		os			The output stream into which the three-dimensional vector should be inserted.
 *  @param		vector		The three-dimensional vector which to insert into the output stream.
 *  @returns	A reference to the output stream.
 */
inline std::ostream& operator<<(std::ostream& os, const Vector3& vector)
{
	os << "(" << vector[0] << "," << vector[1] << "," << vector[2] << ")";

	return os;
}

/*!
 *  @brief		Computes the length of a specified three-dimensional vector.
 *  @param		vector		The three-dimensional vector whose length is to be computed.
 *  @returns	The length of the three-dimensional vector.
 */
inline float abs(const Vector3& vector)
{
	return std::sqrt(vector * vector);
}

/*!
 *  @brief		Computes the squared length of a specified three-dimensional vector.
 *  @param      vector		The three-dimensional vector whose squared length is to be computed.
 *  @returns    The squared length of the three-dimensional vector.
 */
inline float absSq(const Vector3& vector)
{
	return vector * vector;
}

/*!
 *  @brief		Computes the normalization of the specified three-dimensional vector.
 *  @param		vector		The three-dimensional vector whose normalization is to be computed.
 *  @returns	The normalization of the three-dimensional vector.
 */
inline Vector3 normalize(const Vector3& vector)
{
	return vector / abs(vector);
}
}

#endif
