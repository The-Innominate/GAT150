#pragma once
#include <cmath>
#include <sstream>

namespace kda {
	class Vector2 {
	public:
		float x, y;
	public:
		Vector2() : x{ 0 }, y{ 0 } {};
		Vector2(float v) : x{ v }, y{ v } {};
		Vector2(float x, float y) : x{ x }, y{ y } {};
		Vector2(int x, int y) : x{ (float)x }, y{ (float)y } {};

		float operator [] (size_t index) const { return (&x)[index]; }
		float& operator [] (size_t index) { return (&x)[index]; }

		Vector2 operator - () const { return Vector2(-x, -y); }
		
		Vector2 operator + (const Vector2& v) const { return Vector2(x + v.x, y + v.y); }
		Vector2 operator - (const Vector2& v) const { return Vector2(x - v.x, y - v.y); }
		Vector2 operator * (const Vector2& v) const { return Vector2(x * v.x, y * v.y); }
		Vector2 operator / (const Vector2& v) const { return Vector2(x / v.x, y / v.y); }

		Vector2 operator + (float s) const { return Vector2(x + s, y + s); }
		Vector2 operator - (float s) const { return Vector2(x - s, y - s); }
		Vector2 operator * (float s) const { return Vector2(x * s, y * s); }
		Vector2 operator / (float s) const { return Vector2(x / s, y / s); }

		Vector2& operator += (const Vector2& v) { x += v.x, y += v.y; return *this; }
		Vector2& operator -= (const Vector2& v) { x -= v.x, y -= v.y; return *this; }
		Vector2& operator *= (const Vector2& v) { x *= v.x, y *= v.y; return *this; }
		Vector2& operator /= (const Vector2& v) { x /= v.x, y /= v.y; return *this; }

		float lengthSqr() const { return (x * x) + (y * y); }
		float length() const { return sqrt(lengthSqr()); }

		float distanceSqr(const Vector2 v) const { return (v - *this).lengthSqr(); }
		float distance(const Vector2 v) const { return (v - *this).length(); }

		Vector2 Normalized() const { return *this / length(); }
		void Normalize() { *this /= length(); }

		float angle() const { return std::atan2f(y, x); }
		Vector2 Rotate(float radians) const;

		static float SignedAngle(const Vector2& v1, const Vector2& v2);

	};

	inline Vector2 Vector2::Rotate(float radians) const {
		float _x = x * std::cos(radians) - y * std::sin(radians);
		float _y = x * std::sin(radians) + y * std::cos(radians);

		return {_x, _y};
	}

	inline float Vector2::SignedAngle(const Vector2& v1, const Vector2& v2)
	{
		float y = v1.x * v2.y - v1.y * v2.x;
		float x = v1.x * v2.x + v1.y * v2.y;

		return std::atan2(y, x);
	}

	inline std::istream& operator >> (std::istream& stream, Vector2& v) {
		std::string line;
		std::getline(stream, line);

		// { ##, ## }
		std::string xs = line.substr(line.find("{") + 1, line.find(",") - (line.find("{") + 1));
		v.x = std::stof(xs);

		std::string ys = line.substr(line.find(",") + 1, line.find("}") - (line.find(",") + 1));
		v.y = std::stof(ys);

		return stream;
	}

	inline std::ostream& operator<<(std::ostream& stream, const Vector2& v)
	{
		stream << v.x << " " << v.y;
		return stream;
	}

	using vec2 = Vector2;
}