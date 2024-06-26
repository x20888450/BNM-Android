#pragma once
namespace BNM::Structures::Unity {
    struct Vector3;
    struct Vector2 {
        union {
            struct { float x, y; };
            float data[2]{0.f, 0.f};
        };
        inline Vector2() noexcept : x(0), y(0) {};
        inline Vector2(float x, float y) noexcept : x(x), y(y) {};
        inline static Vector2 Down() { return Vector2(0, -1); }
        inline static Vector2 Left() { return Vector2(-1, 0); }
        inline static Vector2 One() { return Vector2(1, 1); }
        inline static Vector2 Right() { return Vector2(1, 0); }
        inline static Vector2 Up() { return Vector2(0, 1); }
        inline static Vector2 Zero() { return Vector2(0, 0); }
        inline static float Angle(Vector2, Vector2);
        inline static Vector2 ClampMagnitude(Vector2, float);
        inline static float Component(Vector2, Vector2);
        inline static float Distance(Vector2, Vector2);
        inline static float Dot(Vector2, Vector2);
        inline static Vector2 FromPolar(float, float);
        inline static Vector2 Lerp(Vector2, Vector2, float) ;
        inline static Vector2 LerpUnclamped(Vector2, Vector2, float);
        inline static float Magnitude(Vector2);
        inline static Vector2 Max(Vector2, Vector2);
        inline static Vector2 Min(Vector2, Vector2);
        inline static Vector2 MoveTowards(Vector2, Vector2, float);
        inline static Vector2 Normalize(Vector2);
        inline static void OrthoNormalize(Vector2 &, Vector2 &);
        inline static Vector2 Project(Vector2, Vector2);
        inline static Vector2 Reflect(Vector2, Vector2);
        inline static Vector2 Reject(Vector2, Vector2);
        inline static Vector2 RotateTowards(Vector2, Vector2, float, float);
        inline static Vector2 Scale(Vector2, Vector2);
        inline static Vector2 Slerp(Vector2, Vector2, float);
        inline static Vector2 SlerpUnclamped(Vector2, Vector2, float);
        inline static float SqrMagnitude(Vector2);
        inline static void ToPolar(Vector2, float &, float &);
        inline float magnitude() { return Magnitude(*this); }
        inline float sqrMagnitude() { return SqrMagnitude(*this); }
        inline Vector2 normalized() { return Normalize(*this); }
        inline std::string str() const { return std::to_string(x) + OBFUSCATE_BNM(", ") + std::to_string(y); }
        inline Vector2& operator+=(float rhs) { x += rhs; y += rhs; return *this; }
        inline Vector2& operator-=(float rhs) { x -= rhs; y -= rhs; return *this; }
        inline Vector2& operator*=(float rhs) { x *= rhs; y *= rhs; return *this; }
        inline Vector2& operator/=(float rhs) { x /= rhs; y /= rhs; return *this; }
        inline Vector2& operator+=(Vector2 rhs) { x += rhs.x; y += rhs.y; return *this; }
        inline Vector2& operator-=(Vector2 rhs) { x -= rhs.x; y -= rhs.y; return *this; }
        operator Vector3() const;
    };

    inline Vector2 operator+(Vector2 lhs, const float rhs) { return Vector2(lhs.x + rhs, lhs.y + rhs); }
    inline Vector2 operator-(Vector2 lhs, const float rhs) { return Vector2(lhs.x - rhs, lhs.y - rhs); }
    inline Vector2 operator*(Vector2 lhs, const float rhs) { return Vector2(lhs.x * rhs, lhs.y * rhs); }
    inline Vector2 operator/(Vector2 lhs, const float rhs) { return Vector2(lhs.x / rhs, lhs.y / rhs); }
    inline Vector2 operator+(const float lhs, Vector2 rhs) { return Vector2(lhs + rhs.x, lhs + rhs.y); }
    inline Vector2 operator-(const float lhs, Vector2 rhs) { return Vector2(lhs - rhs.x, lhs - rhs.y); }
    inline Vector2 operator*(const float lhs, Vector2 rhs) { return Vector2(lhs * rhs.x, lhs * rhs.y); }
    inline Vector2 operator/(const float lhs, Vector2 rhs) { return Vector2(lhs / rhs.x, lhs / rhs.y); }
    inline Vector2 operator+(Vector2 lhs, const Vector2 rhs) { return Vector2(lhs.x + rhs.x, lhs.y + rhs.y); }
    inline Vector2 operator-(Vector2 lhs, const Vector2 rhs) { return Vector2(lhs.x - rhs.x, lhs.y - rhs.y); }
    inline Vector2 operator*(Vector2 lhs, const Vector2 rhs) { return Vector2(lhs.x * rhs.x, lhs.y * rhs.y); }
    inline Vector2 operator/(Vector2 lhs, const Vector2 rhs) { return Vector2(lhs.x / rhs.x, lhs.y / rhs.y); }
    inline bool operator==(const Vector2 lhs, const Vector2 rhs) { return lhs.x == rhs.x && lhs.y == rhs.y; }
    inline bool operator!=(const Vector2 lhs, const Vector2 rhs) { return lhs.x != rhs.x && lhs.y != rhs.y; }
    inline Vector2 operator-(Vector2 v) {return v * -1;}

    float Vector2::Angle(Vector2 a, Vector2 b) {
        float v = Dot(a, b) / (a.magnitude() * b.magnitude());
        v = fmax(v, -1.f);
        v = fmin(v, 1.f);
        return acos(v);
    }

    Vector2 Vector2::ClampMagnitude(Vector2 vector, float maxLength) {
        float length = vector.magnitude();
        if (length > maxLength) vector *= maxLength / length;
        return vector;
    }

    float Vector2::Component(Vector2 a, Vector2 b) {
        return Dot(a, b) / b.magnitude();
    }

    float Vector2::Distance(Vector2 a, Vector2 b) {
        return (a - b).magnitude();
    }

    float Vector2::Dot(Vector2 lhs, Vector2 rhs) {
        return lhs.x * rhs.x + lhs.y * rhs.y;
    }

    Vector2 Vector2::FromPolar(float rad, float theta) {
        Vector2 v;
        v.x = rad * cos(theta);
        v.y = rad * sin(theta);
        return v;
    }

    Vector2 Vector2::Lerp(Vector2 a, Vector2 b, float t) {
        if (t < 0) return a;
        else if (t > 1) return b;
        return LerpUnclamped(a, b, t);
    }

    Vector2 Vector2::LerpUnclamped(Vector2 a, Vector2 b, float t) {
        return (b - a) * t + a;
    }

    float Vector2::Magnitude(Vector2 v) {
        return sqrt(v.sqrMagnitude());
    }

    Vector2 Vector2::Max(Vector2 a, Vector2 b) {
        float x = a.x > b.x ? a.x : b.x;
        float y = a.y > b.y ? a.y : b.y;
        return {x, y};
    }

    Vector2 Vector2::Min(Vector2 a, Vector2 b) {
        float x = a.x > b.x ? b.x : a.x;
        float y = a.y > b.y ? b.y : a.y;
        return {x, y};
    }

    Vector2 Vector2::MoveTowards(Vector2 current, Vector2 target, float maxDistanceDelta) {
        Vector2 d = target - current;
        float m = d.magnitude();
        if (m < maxDistanceDelta || m == 0) return target;
        return current + (d * maxDistanceDelta / m);
    }

    Vector2 Vector2::Normalize(Vector2 v) {
        float mag = v.magnitude();
        if (mag == 0) return Vector2::Zero();
        return v / mag;
    }

    void Vector2::OrthoNormalize(Vector2 &normal, Vector2 &tangent) {
        normal = normal.normalized();
        tangent = Reject(tangent, normal);
        tangent = tangent.normalized();
    }

    Vector2 Vector2::Project(Vector2 a, Vector2 b) {
        float m = b.magnitude();
        return Dot(a, b) / (m * m) * b;
    }

    Vector2 Vector2::Reflect(Vector2 vector, Vector2 planeNormal) {
        return vector - 2 * Project(vector, planeNormal);
    }

    Vector2 Vector2::Reject(Vector2 a, Vector2 b) {
        return a - Project(a, b);
    }

    Vector2 Vector2::RotateTowards(Vector2 current, Vector2 target, float maxRadiansDelta, float maxMagnitudeDelta) {
        float magCur = current.magnitude();
        float magTar = target.magnitude();
        float newMag = magCur + maxMagnitudeDelta * (float) ((magTar > magCur) - (magCur > magTar));
        newMag = fmin(newMag, fmax(magCur, magTar));
        newMag = fmax(newMag, fmin(magCur, magTar));
        float totalAngle = Angle(current, target) - maxRadiansDelta;
        if (totalAngle <= 0) return target.normalized() * newMag;
        else if (totalAngle >= M_PI) return -target.normalized() * newMag;
        float axis = current.x * target.y - current.y * target.x;
        axis = axis / fabs(axis);
        if (1 - fabs(axis) >= 0.00001) axis = 1;
        current = current.normalized();
        Vector2 newVector = current * cos(maxRadiansDelta) + Vector2(-current.y, current.x) * sin(maxRadiansDelta) * axis;
        return newVector * newMag;
    }

    Vector2 Vector2::Scale(Vector2 a, Vector2 b) {
        return {a.x * b.x, a.y * b.y};
    }

    Vector2 Vector2::Slerp(Vector2 a, Vector2 b, float t) {
        if (t < 0) return a;
        else if (t > 1) return b;
        return SlerpUnclamped(a, b, t);
    }

    Vector2 Vector2::SlerpUnclamped(Vector2 a, Vector2 b, float t) {
        float magA = a.magnitude();
        float magB = b.magnitude();
        a /= magA;
        b /= magB;
        float dot = Dot(a, b);
        dot = fmax(dot, -1.f);
        dot = fmin(dot, 1.f);
        float theta = acos(dot) * t;
        Vector2 relativeVec = (b - a * dot).normalized();
        Vector2 newVec = a * cos(theta) + relativeVec * sin(theta);
        return newVec * (magA + (magB - magA) * t);
    }

    float Vector2::SqrMagnitude(Vector2 v) {
        return v.x * v.x + v.y * v.y;
    }

    void Vector2::ToPolar(Vector2 vector, float &rad, float &theta) {
        rad = vector.magnitude();
        theta = atan2(vector.y, vector.x);
    }
    struct Vector2Int {
        union {
            struct { int x, y; };
            int data[2]{0, 0};
        };
    };
}