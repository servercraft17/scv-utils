#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <type_traits>
#include <math.h>

/*
 *
 * I absolutely fucking despise templates, but they also make things like
 * this SO much easier, instead of spending hours writing the struct(s) 
 * you get to spend hours debuging.
 * 
*/

#define ML_VEC(__vec, __type) printf("<"#__type", "#__type">\n", __vec.x, __vec.y);

template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
struct SS_Vector {
    T x, y;
    
    SS_Vector(T x, T y) {
        this->x=x; this->y=y;
    }
    SS_Vector() {x=y=(T)0;}

    void nullify() {x=y=(T)0;}

    SS_Vector<T> operator-() {
        return SS_Vector<T>(-x, -y);
    }

    SS_Vector<T> operator+(SS_Vector<T> v) {
        return SS_Vector<T>(x+v.x, y+v.y);
    }
    SS_Vector<T> operator+(T v) {
        return SS_Vector<T>(x+v, y+v);
    }
    void operator+=(SS_Vector<T> v) {
        x+=v.x; y+=v.y; 
    }
    void operator+=(T v) {
        x+=v; y+=v;
    }

    SS_Vector<T> operator-(SS_Vector<T> v) {
        return SS_Vector<T>(x-v.x, y-v.y);
    }
    SS_Vector<T> operator-(T v) {
        return SS_Vector<T>(x-v, y-v);
    }
    void operator-=(SS_Vector<T> v) {
        x-=v.x; y-=v.y; 
    }
    void operator-=(T v) {
        x-=v; y-=v;
    }

    SS_Vector<T> operator*(SS_Vector<T> v) {
        return SS_Vector<T>(x*v.x, y*v.y);
    }
    SS_Vector<T> operator*(T v) {
        return SS_Vector<T>(x*v, y*v);
    }
    void operator*=(SS_Vector<T> v) {
        x*=v.x; y*=v.y; 
    }
    void operator*=(T v) {
        x*=v; y*=v;
    }

    SS_Vector<T> operator/(SS_Vector<T> v) {
        return SS_Vector<T>(x/v.x, y/v.y);
    }
    SS_Vector<T> operator/(T v) {
        return SS_Vector<T>(x/v, y/v);
    }
    void operator/=(SS_Vector<T> v) {
        x/=v.x; y/=v.y; 
    }
    void operator/=(T v) {
        x/=v; y/=v;
    }

    bool operator==(SS_Vector<T> o) const {
        return x==o.x && y==o.y;
    }

    void operator=(SS_Vector<T> v) {
        x=v.x; y=v.y;
    }

    float length() {
        return sqrt(x * x + y * y);
    }

    void normalize() {
        this->operator/=(length());
    }

    SS_Vector<T> normalized() {
        return this->operator/(length());
    }

    float dot(SS_Vector<T> other) {
        return x * other.x + y * other.y;
    }

    static float dot(SS_Vector<T> a, SS_Vector<T> b) {
        return a.x * b.y + a.y * b.y;
    }

    template <typename _T, typename = typename std::enable_if<std::is_arithmetic<_T>::value, _T>::type>
    operator SS_Vector<_T>() const {
        return SS_Vector<_T>((_T)x, (_T)y);
    }

#ifdef SDL_h_
    operator SDL_Point() const {
        return SDL_Point {.x=(int)x, .y=(int)y};
    }

    operator SDL_FPoint() const {
        return SDL_FPoint {.x=(float)x, .y=(float)y};
    }
#endif/* VECTOR_HPP */
};

template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
struct SS_Rect {
    T x, y, w, h;
    SS_Rect(T x, T y, T w, T h) {
        this->x=x;
        this->y=y;
        this->w=w;
        this->h=h;
    }
    SS_Rect() {x=y=w=h=(T)0;}

    bool operator==(SS_Rect<T> o) const {
        return x==o.x && y==o.y && w==o.w && h==o.h;
    }

    void operator=(SS_Rect<T> v) {
        x=v.x; y=v.y; w=v.w; h=v.h;
    }

    template <typename _T, typename = typename std::enable_if<std::is_arithmetic<_T>::value, _T>::type>
    operator SS_Rect<_T>() const {
        return SS_Rect<_T>((_T)x, (_T)y, (_T)w, (_T)h);
    }

#ifdef SDL_h_
    operator SDL_Rect() const {
        return SDL_Rect {.x=(int)x, .y=(int)y, .w=(int)w, .h=(int)h};
    }
    
    operator SDL_FRect() const {
        return SDL_FRect {.x=(float)x, .y=(float)y, .w=(float)w, .h=(float)h};
    }
#endif/* VECTOR_HPP */
};

template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
struct SS_Vector3 {
    T x, y, z;
    SS_Vector3(T x, T y, T z) {
        this->x=x; this->y=y; this->z=z;
    }
    SS_Vector3() {x=y=z=(T)0;}

    void nullify() {x=y=z=(T)0;}

    SS_Vector3<T> operator-() {
        return SS_Vector3<T>(-x, -y, -z);
    }

    SS_Vector3<T> operator+(SS_Vector3<T> v) {
        return SS_Vector3<T>(x+v.x, y+v.y, z+v.z);
    }
    SS_Vector3<T> operator+(T v) {
        return SS_Vector3<T>(x+v, y+v, z+v);
    }
    void operator+=(SS_Vector3<T> v) {
        x+=v.x; y+=v.y; z+=v.z; 
    }
    void operator+=(T v) {
        x+=v; y+=v; z+=v;
    }

    SS_Vector3<T> operator-(SS_Vector3<T> v) {
        return SS_Vector3<T>(x-v.x, y-v.y, z-v.z);
    }
    SS_Vector3<T> operator-(T v) {
        return SS_Vector3<T>(x-v, y-v, z-v);
    }
    void operator-=(SS_Vector3<T> v) {
        x-=v.x; y-=v.y; z-=v.z;
    }
    void operator-=(T v) {
        x-=v; y-=v; z-=v;
    }

    SS_Vector3<T> operator*(SS_Vector3<T> v) {
        return SS_Vector3<T>(x*v.x, y*v.y, z*v.z);
    }
    SS_Vector3<T> operator*(T v) {
        return SS_Vector3<T>(x*v, y*v, z*v);
    }
    void operator*=(SS_Vector3<T> v) {
        x*=v.x; y*=v.y; z*=v.z;
    }
    void operator*=(T v) {
        x*=v; y*=v; z*=v;
    }

    SS_Vector3<T> operator/(SS_Vector3<T> v) {
        return SS_Vector3<T>(x/v.x, y/v.y, z/v.z);
    }
    SS_Vector3<T> operator/(T v) {
        return SS_Vector3<T>(x/v, y/v, z/v);
    }
    void operator/=(SS_Vector3<T> v) {
        x/=v.x; y/=v.y; z/=v.z; 
    }
    void operator/=(T v) {
        x/=v; y/=v; z/=v;
    }

    bool operator==(SS_Vector3<T> o) const {
        return this->x==o.x && this->y==o.y && this->z==o.z;
    }

    void operator=(SS_Vector3<T> v) {
        x=v.x; y=v.y; z=v.z;
    }

    float length() {
        return sqrt(x * x + y * y + z * z);
    }

    void normalize() {
        this->operator/=(length());
    }

    SS_Vector3<T> normalized() {
        return this->operator/(length());
    }

    SS_Vector3<T> cross(SS_Vector3<T> other) {
        return SS_Vector3<T>(y*other.z - z*other.y, z*other.x - x*other.z, x*other.y - y*other.x);
    }
    
    //template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    static SS_Vector3<T> cross(SS_Vector3<T> a, SS_Vector3<T> b) {
        return SS_Vector3<T>(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
    }

    float dot(SS_Vector3<T> other) {
        return x * other.x + y * other.y + z * other.z;
    }

    //template <typename _T, typename = typename std::enable_if<std::is_arithmetic<_T>::value, T>::type>
    static float dot(SS_Vector3<T> a, SS_Vector3<T> b) {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }

    template <typename _T, typename = typename std::enable_if<std::is_arithmetic<_T>::value, _T>::type>
    operator SS_Vector3<_T>() const {
        return SS_Vector3<_T>((_T)x, (_T)y, (_T)z);
    }

#ifdef SDL_h_
    operator SDL_Point() const {
        return SDL_Point {.x=(int)x, .y=(int)y};
    }

    operator SDL_FPoint() const {
        return SDL_FPoint {.x=(float)x, .y=(float)y};
    }
#endif /* SDL_h_ */
};

template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
struct SS_Vector4 {
    T x, y, z, w;
    SS_Vector4(T x, T y, T z, T w = (T)1) {
        this->x=x; this->y=y; this->z=z; this->w=w;
    }
    SS_Vector4() {x=y=z=(T)0;w=(T)1;}

    void nullify() {x=y=z=w=(T)0;}

    SS_Vector4<T> operator-() {
        return SS_Vector4<T>(-x, -y, -z, -w);
    }

    SS_Vector4<T> operator+(SS_Vector3<T> v) {
        return SS_Vector4<T>(x+v.x, y+v.y, z+v.z, w+v.w);
    }
    SS_Vector4<T> operator+(T v) {
        return SS_Vector4<T>(x+v, y+v, z+v, w+v);
    }
    void operator+=(SS_Vector4<T> v) {
        x+=v.x; y+=v.y; z+=v.z; 
    }
    void operator+=(T v) {
        x+=v; y+=v; z+=v;
    }

    SS_Vector4<T> operator-(SS_Vector4<T> v) {
        return SS_Vector4<T>(x-v.x, y-v.y, z-v.z, w-z.w);
    }
    SS_Vector4<T> operator-(T v) {
        return SS_Vector4<T>(x-v, y-v, z-v, w-v);
    }
    void operator-=(SS_Vector4<T> v) {
        x-=v.x; y-=v.y; z-=v.z; w-=v.w;
    }
    void operator-=(T v) {
        x-=v; y-=v; z-=v;
    }

    SS_Vector4<T> operator*(SS_Vector4<T> v) {
        return SS_Vector4<T>(x*v.x, y*v.y, z*v.z, w*v.w);
    }
    SS_Vector4<T> operator*(T v) {
        return SS_Vector4<T>(x*v, y*v, z*v, w*v);
    }
    void operator*=(SS_Vector4<T> v) {
        x*=v.x; y*=v.y; z*=v.z; w*=v.z;
    }
    void operator*=(T v) {
        x*=v; y*=v; z*=v; w*=v;
    }

    SS_Vector4<T> operator/(SS_Vector4<T> v) {
        return SS_Vector4<T>(x/v.x, y/v.y, z/v.z, w/v.w);
    }
    SS_Vector4<T> operator/(T v) {
        return SS_Vector4<T>(x/v, y/v, z/v, w/v);
    }
    void operator/=(SS_Vector4<T> v) {
        x/=v.x; y/=v.y; z/=v.z; w/=v.w; 
    }
    void operator/=(T v) {
        x/=v; y/=v; z/=v;
    }

    bool operator==(SS_Vector4<T> o) const {
        return this->x==o.x && this->y==o.y && this->z==o.z && this->w==o.w;
    }

    void operator=(SS_Vector4<T> v) {
        x=v.x; y=v.y; z=v.z; w=v.w;
    }

    float length() {
        return sqrt(x * x + y * y + z * z + w * w);
    }

    void normalize() {
        this->operator/=(length());
    }

    SS_Vector4<T> normalized() {
        return this->operator/(length());
    }

    float dot(SS_Vector4<T> other) {
        return x * other.x + y * other.y + z * other.z + w * other.w;
    }

    //template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    static float dot(SS_Vector4<T> a, SS_Vector4<T> b) {
        return a.x * b.y + a.y * b.y + a.z * b.z + a.w * b.w;
    }

    template <typename _T, typename = typename std::enable_if<std::is_arithmetic<_T>::value, _T>::type>
    operator SS_Vector4<_T>() const {
        return SS_Vector4<_T>((_T)x, (_T)y, (_T)z, (_T)w);
    }

    //operator SS_Vector3<T>() const {
    //    return SS_Vector3<T>(x, y, z);
    //}

#ifdef SDL_h_
    operator SDL_Point() const {
        return SDL_Point {.x=(int)x, .y=(int)y};
    }

    operator SDL_FPoint() const {
        return SDL_FPoint {.x=(float)x, .y=(float)y};
    }
#endif /* SDL_h_ */
};

template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
struct SS_Color {
    T r, g, b, a;

    SS_Color(T r, T g, T b, T a = (T)255) {
        this->r=r; this->b=b; this->g=g; this->a=a;
    }

#ifdef SDL_h_
    SS_Color(SDL_Color color) {
        r=(T)color.r; g=(T)color.g; b=(T)color.b; a=(T)color.a;
    }

    SS_Color(SDL_FColor color) {
        r=(T)color.r; g=(T)color.g; b=(T)color.b; a=(T)color.a;
    }

    operator SDL_Color() const {
        return SDL_Color {.r=(int)r, .g=(int)g, .b=(int)b, .a=(int)a};
    }

    operator SDL_FColor() const {
        return SDL_FColor {.r=(float)r, .g=(float)g, .b=(float)b, .a=(float)a};
    }
#endif /* SDL_h_ */
    
};

#endif/* VECTOR_HPP */