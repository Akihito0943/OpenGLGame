/**
 * @file Math.h
 */


#pragma once

#include <math.h>


 /**
 * vec2
 */
struct vec2
{
	float x, y;
	vec2() = default;
	vec2(float x, float y) { this->x = x; this->y = y; }

	// vec2 と vec2
	vec2& operator+= (const vec2& b)
	{
		x += b.x;
		y += b.y;
		return *this;
	}

	vec2& operator-= (const vec2& b)
	{
		x -= b.x;
		y -= b.y;
		return *this;
	}

	vec2& operator*= (const vec2& b)
	{
		x *= b.x;
		y *= b.y;
		return *this;
	}

	vec2& operator/= (const vec2& b)
	{
		x /= b.x;
		y /= b.y;
		return *this;
	}
};


/**
* vec3
*/
struct vec3
{
	float x, y, z;
	vec3() = default;
	vec3(float x, float y, float z) { this->x = x; this->y = y; this->z = z; }
	explicit vec3(float a) { x = a; y = a; z = a; }
	explicit vec3(const struct vec4& v);

	// 添字演算子
	float& operator[](size_t index) { return (&x)[index]; } // xのアドレスを基準に順番にアクセス
	const float& operator[](size_t index) const { return (&x)[index]; }

	// -vec3
	vec3 operator-() const 
	{ 
		return vec3(-x, -y, -z);
	}

	// vec3 と vec3
	vec3& operator+= (const vec3& b)
	{
		x += b.x;
		y += b.y;
		z += b.z;
		return *this;
	}

	vec3& operator-= (const vec3& b)
	{
		x -= b.x;
		y -= b.y;
		z -= b.z;
		return *this;
	}

	vec3& operator*= (const vec3& b)
	{
		x *= b.x;
		y *= b.y;
		z *= b.z;
		return *this;
	}

	vec3& operator/= (const vec3& b)
	{
		x /= b.x;
		y /= b.y;
		z /= b.z;
		return *this;
	}

	// vec3 と float
	vec3& operator+=(float a)
	{
		x += a;
		y += a;
		z += a;
		return *this;
	}

	vec3& operator-=(float a)
	{
		x -= a;
		y -= a;
		z -= a;
		return *this;
	}

	vec3& operator*=(float a)
	{
		x *= a;
		y *= a;
		z *= a;
		return *this;
	}

	vec3& operator/=(float a)
	{
		x /= a;
		y /= a;
		z /= a;
		return *this;
	}

};

// vec3 と vec3
inline vec3 operator+ (vec3 a, const vec3& b)
{
	return a += b;
}

inline vec3 operator- (vec3 a, const vec3& b)
{
	return a -= b;
}

inline vec3 operator* (vec3 a, const vec3& b)
{
	return a *= b;
}

inline vec3 operator/ (vec3 a, const vec3& b)
{
	return a /= b;
}

// vec3 と float
inline vec3 operator+ (vec3 v, float a)
{
	return v += a;
}

inline vec3 operator- (vec3 v, float a)
{
	return v -= a;
}

inline vec3 operator* (vec3 v, float a)
{
	return v *= a;
}

inline vec3 operator/ (vec3 v, float a)
{
	return v /= a;
}


/**
* vec4
*/
struct vec4
{
	float x, y, z, w;

	vec4() = default;
	vec4(float x, float y, float z, float w) { this->x = x; this->y = y; this->z = z; this->w = w; }
	explicit vec4(float a) { x = a; y = a; z = a; w = a; }
	explicit vec4(const vec3& v, float w = 1.0)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		this->w = w;
	}

	// vec4 と vec4
	vec4& operator+= (const vec4& b)
	{
		x += b.x;
		y += b.y;
		z += b.z;
		w += b.w;
		return *this;
	}

	vec4& operator-= (const vec4& b)
	{
		x -= b.x;
		y -= b.y;
		z -= b.z;
		w -= b.w;
		return *this;
	}

	vec4& operator*= (const vec4& b)
	{
		x *= b.x;
		y *= b.y;
		z *= b.z;
		w *= b.w;
		return *this;
	}

	vec4& operator/= (const vec4& b)
	{
		x /= b.x;
		y /= b.y;
		z /= b.z;
		w /= b.w;
		return *this;
	}

	// vec4 と float
	vec4& operator+= (float a)
	{
		x += a;
		y += a;
		z += a;
		w += a;
		return *this;
	}

	vec4& operator-= (float a)
	{
		x -= a;
		y -= a;
		z -= a;
		w -= a;
		return *this;
	}

	vec4& operator*= (float a)
	{
		x *= a;
		y *= a;
		z *= a;
		w *= a;
		return *this;
	}

	vec4& operator/= (float a)
	{
		x /= a;
		y /= a;
		z /= a;
		w /= a;
		return *this;
	}
};

// vec4 と vec4
inline vec4 operator+ (vec4 a, const vec4& b)
{
	return a += b;
}

inline vec4 operator- (vec4 a, const vec4& b)
{
	return a -= b;
}

inline vec4 operator* (vec4 a, const vec4& b)
{
	return a *= b;
}

inline vec4 operator/ (vec4 a, const vec4& b)
{
	return a /= b;
}

// vec4 と float
inline vec4 operator+ (vec4 v, float a)
{
	return v += a;
}

inline vec4 operator- (vec4 v, float a)
{
	return v -= a;
}

inline vec4 operator* (vec4 v, float a)
{
	return v *= a;
}

inline vec4 operator/ (vec4 v, float a)
{
	return v /= a;
}


// vec4 -> vec3
inline vec3::vec3(const vec4& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}


/**
* mat3
*/
struct mat3
{
	vec3 data[3];

	mat3() = default;
	mat3(const vec3& v0, const vec3& v1, const vec3& v2)
	{
		data[0] = v0;
		data[1] = v1;
		data[2] = v2;
	}
	explicit mat3(float f)
	{
		data[0] = { f, 0, 0 };
		data[1] = { 0, f, 0 };
		data[2] = { 0, 0, f };
	}
	explicit mat3(const struct mat4& m);
};

// mat3 * vec3
inline vec3 operator* (const mat3& m, const vec3& v)
{
	return m.data[0] * v.x + m.data[1] * v.y + m.data[2] * v.z;
}

// mat3 * mat3
inline mat3 operator* (const mat3& a, const mat3& b)
{
	mat3 m;
	m.data[0] = a * b.data[0];
	m.data[1] = a * b.data[1];
	m.data[2] = a * b.data[2];
	return m;
}

inline mat3& operator*= (mat3& a, const mat3& b)
{
	a = a * b;
	return a;
}


/**
* mat4
*/
struct mat4
{
	vec4 data[4];

	mat4() = default;
	mat4(const vec4& v0, const vec4& v1, const vec4& v2, const vec4& v3)
	{
		data[0] = v0;
		data[1] = v1;
		data[2] = v2;
		data[3] = v3;
	}
	explicit mat4(float f)
	{
		data[0] = { f, 0, 0, 0 };
		data[1] = { 0, f, 0, 0 };
		data[2] = { 0, 0, f, 0 };
		data[3] = { 0, 0, 0, f };
	}
	explicit mat4(const mat3& m)
	{
		data[0] = vec4(m.data[0], 0);
		data[1] = vec4(m.data[1], 0);
		data[2] = vec4(m.data[2], 0);
		data[3] = vec4(0, 0, 0, 1);
	}
};

// mat4 から mat3 への変換
inline mat3::mat3(const mat4& m)
{
	data[0] = vec3(m.data[0]);
	data[1] = vec3(m.data[1]);
	data[2] = vec3(m.data[2]);
}

// mat4 * vec4
inline vec4 operator* (const mat4& m, const vec4& v)
{
	return m.data[0] * v.x + m.data[1] * v.y + m.data[2] * v.z + m.data[3] * v.w;
}

// mat4 * mat4
inline mat4 operator* (const mat4& a, const mat4& b)
{
	mat4 m;
	m.data[0] = a * b.data[0];
	m.data[1] = a * b.data[1];
	m.data[2] = a * b.data[2];
	m.data[3] = a * b.data[3];
	return m;
}

inline mat4& operator*=(mat4& a, const mat4& b)
{
	a = a * b;
	return a;
}


/// <summary>
/// 回転角度から回転行列を作成（Y-X-Z回転）
/// </summary>
/// <param name="rotation">回転角度</param>
/// <returns>回転行列</returns>
inline mat3 GetRotationMatrix(const vec3& rotation)
{
	const float sinX = sinf(rotation.x);
	const float cosX = cosf(rotation.x);
	const float sinY = sinf(rotation.y);
	const float cosY = cosf(rotation.y);
	const float sinZ = sinf(rotation.z);
	const float cosZ = cosf(rotation.z);

	return mat3(
		vec3(cosY * cosZ - sinY * sinX * sinZ, -cosX * sinZ, sinY * cosZ + cosY * sinX * sinZ),
		vec3(cosY * sinZ + sinY * sinX * cosZ, cosX * cosZ, sinY * sinZ - cosY * sinX * cosZ),
		vec3(-sinY * cosX, sinX, cosY * cosX)
	);
}


/// <summary>
/// 座標変換行列を作成する
/// </summary>
/// <param name="scale">拡大率</param>
/// <param name="rotation">回転角度</param>
/// <param name="position">平行移動</param>
/// <returns></returns>
inline mat4 GetTransformMatrix(const vec3& scale, const vec3& rotation, const vec3& position)
{
	mat3 matRotation = GetRotationMatrix(rotation);
	return mat4(
		vec4(matRotation.data[0] * scale.x, 0),
		vec4(matRotation.data[1] * scale.y, 0),
		vec4(matRotation.data[2] * scale.z, 0),
		vec4(position, 1)
	);
}