/***************************************************************************
Copyright (c) 2013-2014, Amir Geva
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
#ifndef H_XSTRING
#define H_XSTRING

#include <string>
#include <sstream>
#include <vector>
//#include <allocators>
#include <algorithm>
#include <unordered_map>

template<class E, class T=std::char_traits<E>, class A=typename std::allocator<E> >
class basic_params
{
  typedef basic_params<E,T,A> self;
  typedef std::basic_string<E,T,A> str;
  typedef std::vector<str> vec;
  vec m_Params;
public:
  template<class U>
  self& operator<< (const U& u)
  {
    std::basic_ostringstream<E,T,A> os;
    os << u;
    m_Params.push_back(os.str());
    return *this;
  }

  typedef typename vec::const_iterator const_iterator;
  const_iterator begin() const { return m_Params.begin(); }
  const_iterator end()   const { return m_Params.end(); }
};

typedef basic_params<char> params;

template<class E, class T=std::char_traits<E>, class A=std::allocator<E> >
class basic_xstring : public std::basic_string<E,T,A>
{
  typedef E                           value_type;
  typedef A                           allocator_type;
  typedef std::basic_string<E,T,A>    parent;
  typedef basic_xstring<E,T,A>        self;
  typedef typename parent::size_type  size_type;
  using parent::npos;
public:
  basic_xstring(const value_type* ptr, size_type n, const allocator_type& al = allocator_type())
    : parent(ptr,n,al) {}
  basic_xstring(const value_type* ptr, const allocator_type& al = allocator_type())
    : parent(ptr,al) {}
  basic_xstring(const basic_xstring& s, size_type off = 0, size_type n = npos, const allocator_type& al = allocator_type())
    : parent(s,off,n,al) {}
  basic_xstring(size_type n, value_type c, const allocator_type& al = allocator_type())
    : parent(n,c,al) {}
  explicit basic_xstring(const allocator_type& al = allocator_type())
    : parent(al) {}
  basic_xstring(const parent& p) : parent(p) {}
  template<class U>
  explicit basic_xstring(const U& u)
  {
    std::basic_ostringstream<E,T,A> os;
    os << u;
    *this=os.str();
  }

  operator const value_type* () const { return parent::c_str(); }
  
  self& to_lower()
  {
    std::transform(parent::begin(), parent::end(), parent::begin(), tolower);
    return *this;
  }

  self& to_upper()
  {
    std::transform(parent::begin(),parent::end(),parent::begin(),toupper);
    return *this;
  }

  int as_int() const
  {
    if (parent::empty()) return 0;
    try
    {
      if (begins_with("-"))
        return std::stoi(parent::c_str());
      return std::stoul(parent::c_str());
    } catch (const std::invalid_argument&)
    {
      throw self("Invalid integer value: "+*this);
    }
    return 0;
  }

  double as_double() const
  {
    if (parent::empty()) return 0;
    return std::stod(parent::c_str());
  }

  self& trim_left()
  {
    int p=parent::find_first_not_of(" \t\n\r");
    if (p>0) *this=parent::substr(p);
    return *this;
  }

  self& trim_right()
  {
    int p=parent::find_last_not_of(" \t\n\r");
    if (p>=0)
      *this=parent::substr(0,p+1);
    return *this;
  }

  self& trim()
  {
    trim_left();
    return trim_right();
  }

  bool begins_with(const self& s) const
  {
    unsigned n=s.length();
    if (n>parent::length()) return false;
    return std::equal(parent::begin(),parent::begin()+n,s.begin());
  }

  bool ends_with(const self& s) const
  {
    unsigned n=s.length();
    if (n>parent::length()) return false;
    return std::equal(parent::begin()+(parent::length()-n),parent::end(),s.begin());
  }

  bool read_line(std::istream& is)
  {
    *this="";
    if (is.eof()) return false;
    char buffer[1024];
    while (true)
    {
      is.getline(buffer,1000);
      if (is.eof()) return !parent::empty();
      self s=buffer;
      if (s.ends_with("\r")) s=s.substr(0,s.length()-1);
      *this+=s;
      if (s.length()<1000) return !parent::empty();
    }
  }

  self format(const basic_params<E,T,A>& params)
  {
    auto it=params.begin();
    self res=*this;
    int p;
    while ((p=res.find("{}"))>=0 && it!=params.end())
      res.replace(p,2,*it++);
    return res;
  }

  template<class U>
  self& operator<< (const U& u)
  {
    std::basic_ostringstream<E,T,A> os;
    os << u;
    int p=parent::find("{}");
    if (p>=0)
      parent::replace(p,2,os.str());
    return *this;
  }

};

template<class T>
class basic_string_tokenizer
{
  typedef basic_xstring<T> str;
  typedef std::vector<str> seq;
  seq      m_Tokens;
  unsigned m_Current;
public:
  basic_string_tokenizer(const str& s, const str& delim=" \t")
    : m_Current(0)
  {
    int p=-1;
    int len=s.length();
    while (true)
    {
      p=s.find_first_not_of(delim,p+1);
      if (p<0) break;
      int e=s.find_first_of(delim,p+1);
      if (e<0) e=len;
      m_Tokens.push_back(s.substr(p,e-p));
      p=e;
    }
  }

  typedef typename seq::const_iterator const_iterator;
  const_iterator begin() const { return m_Tokens.begin();  }
  const_iterator end()   const { return m_Tokens.end();    }

  unsigned size() const { return m_Tokens.size(); }
  bool     has_more_tokens() const { return m_Current<m_Tokens.size(); }
  str      get_next_token() 
  { 
    if (m_Current<m_Tokens.size()) return m_Tokens[m_Current++]; 
    return str("");
  }
};

typedef basic_xstring<char> xstring;
typedef basic_string_tokenizer<char> xstring_tokenizer;

namespace std {
template<> struct hash<xstring>
{
  size_t operator()(const xstring& s) const
  {
    hash<string> h;
    return h(s);
  }
};
} // namespace std

inline void make_lower(xstring& s)
{
  xstring::iterator b=s.begin(),e=s.end();
  for(;b!=e;++b)
  {
    char& c=*b;
    if (c>='A' && c<='Z') c+=32;
  }
}

template<class T>
inline xstring S(const T& t) { return xstring(t); }

inline unsigned as_hex(const xstring& s)
{
  static const xstring chars = "0123456789ABCDEF";
  unsigned res=0;
  unsigned i=0;
  if (s.begins_with("0x")) i=2;
  for(;i<s.length();++i)
  {
    res<<=4;
    char c=toupper(s.at(i));
    int p=chars.find(c);
    if (p<0) return 0;
    res+=p;
  }
  return res;
}

#endif // H_XSTRING

