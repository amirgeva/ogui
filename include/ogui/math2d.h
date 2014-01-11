/***************************************************************************
Copyright (c) 2013, Amir Geva
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
***************************************************************************/
#ifndef H_MATH_2D
#define H_MATH_2D

#include <iostream>
#include <prims.h>

namespace OGUI {

template<class T> inline T sqr(T t)      { return t*t;  }

template<class T>
struct TPoint
{
  typedef TPoint<T> self;

  T x,y;

  TPoint(T _x=T(0), T _y=T(0)) : x(_x), y(_y) {}
  TPoint(const self& p) : x(p.x), y(p.y) {}
  template<class U>
  explicit TPoint(const TPoint<U>& p) : x(T(p.x)), y(T(p.y)) {}
  self& operator=(const self& p) { x=p.x; y=p.y; return *this; }

  self& offset(const self& o)      { x+=o.x; y+=o.y; return *this; }
  self& operator+= (const self& o) { x+=o.x; y+=o.y; return *this; }
  self& operator-= (const self& o) { x-=o.x; y-=o.y; return *this; }
  self  operator-  () const        { return self(-x,-y); }
  self& operator*= (T s)           { x*=s; y*=s; return *this; }

  float magnitude() const { return float(sqrt(x*x+y*y)); }
};

typedef TPoint<int>   Point;
typedef TPoint<float> fPoint;

template<class T>
inline TPoint<T> operator* (const T& t, const TPoint<T>& p)
{
  return TPoint<T>(t*p.x,t*p.y);
}

template<class T>
inline TPoint<T> operator* (const TPoint<T>& p, const T& t)
{
  return TPoint<T>(t*p.x, t*p.y);
}

template<class T>
inline TPoint<T> operator+ (const TPoint<T>& a, const TPoint<T>& b)
{
  TPoint<T> p=a;
  return p+=b;
}

template<class T>
inline TPoint<T> operator- (const TPoint<T>& a, const TPoint<T>& b)
{
  TPoint<T> p=a;
  return p-=b;
}

template<class T>
inline bool operator== (const TPoint<T>& a, const TPoint<T>& b)
{
  return (a.x==b.x && a.y==b.y);
}

template<class T>
inline bool operator!= (const TPoint<T>& a, const TPoint<T>& b)
{
  return !(a==b);
}


template<class T>
std::ostream& operator<< (std::ostream& os, const TPoint<T>& p)
{
  return os << p.x << ',' << p.y;
}

template<class T>
struct TRect
{
  typedef TRect<T>  self;
  typedef TPoint<T> point;

  T left,top,right,bottom;

  TRect(T l=0, T t=0, T r=0, T b=0) : left(l), top(t), right(r), bottom(b) {}
  TRect(const point& tl, const point& br) : left(tl.x), top(tl.y), right(br.x), bottom(br.y) {}
  TRect(const self& r) : left(r.left), top(r.top), right(r.right), bottom(r.bottom) {}
  template<class U>
  explicit TRect(const TRect<U>& r) : left(T(r.left)), top(T(r.top)), right(T(r.right)), bottom(T(r.bottom)) {}
  self& operator=(const self& r) { left=r.left; top=r.top; right=r.right; bottom=r.bottom; return *this; }

  self& offset(const point& p)      { left+=p.x; top+=p.y; right+=p.x; bottom+=p.y; return *this; }
  self& operator+= (const point& p) { left+=p.x; top+=p.y; right+=p.x; bottom+=p.y; return *this; }
  self& operator-= (const point& p) { left-=p.x; top-=p.y; right-=p.x; bottom-=p.y; return *this; }
  self& move_to(const point& p)     { return offset(p-top_left()); }
  point get_size() const            { return point(get_width(),get_height()); }

  bool empty() const                { return left==0 && top==0 && right==0 && bottom==0; }

  self& intersect(const self& r)
  {
    left=Max(left,r.left);
    top=Max(top,r.top);
    right=Min(right,r.right);
    bottom=Min(bottom,r.bottom);
    return *this;
  }

  bool intersects(self r) const
  {
    r.intersect(*this);
    return r.valid();
  }

  self& unite(const self& r)
  {
    left=Min(left,r.left);
    top=Min(top,r.top);
    right=Max(right,r.right);
    bottom=Max(bottom,r.bottom);
    return *this;
  }

  self& accumulate(const self& r)
  {
    if (empty()) *this=r;
    else unite(r);
    return *this;
  }

  self& inflate(int l, int t, int r, int b)
  {
    left-=l;
    top-=t;
    right+=r;
    bottom+=b;
    return *this;
  }

  self& inflate(int d)
  {
    return inflate(d,d,d,d);
  }

  T     get_width()    const { return right-left; }
  T     get_height()   const { return bottom-top; }
  point top_left()     const { return point(left,top); }
  point bottom_right() const { return point(right,bottom); }

  bool valid() const { return right>left && bottom>top; }

  void normalize()
  {
    if (left>right) std::swap(left,right);
    if (top>bottom) std::swap(top,bottom);
  }

  bool point_inside(const point& p) const
  {
    return (p.x>=left && p.y>=top && p.x<right && p.y<bottom);
  }
};

template<class T>
std::ostream& operator<< (std::ostream& os, const TRect<T>& r)
{
  return os << r.left << ',' << r.top << ',' << r.right << ',' << r.bottom;
}

template<class T>
inline bool operator== (const TRect<T>& a, const TRect<T>& b)
{
  return (a.left==b.left && a.top==b.top && a.right==b.right && a.bottom==b.bottom);
}

template<class T>
inline bool operator!= (const TRect<T>& a, const TRect<T>& b)
{
  return !(a==b);
}

typedef TRect<int>   Rect;
typedef TRect<float> fRect;

}; // namespace OGUI

#endif // H_MATH_2D

