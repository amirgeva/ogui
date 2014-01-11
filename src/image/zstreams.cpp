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
#include <zstreams.h>
#include <fstream>
#include <xstring.h>
#include <prims.h>
#include "zlib.h"

using std::streamsize;

class filtering_input_streambuf : public std::streambuf
{
protected:
  virtual int_type read_buffer(char* buffer, int len) = 0;
  virtual bool     avail() = 0;
  virtual int_type peek() = 0;

  virtual int_type underflow( ) override
  {
    if (!avail()) return std::char_traits<char>::eof();
    return peek();
  }

  virtual int_type uflow( ) override
  {
    int_type res=0;
    int_type act=read_buffer(reinterpret_cast<char*>(&res),1);
    if (act==0) return std::char_traits<char>::eof(); 
    return res;
  }

  virtual streamsize xsgetn(char_type* buffer, streamsize len) override
  {
    return read_buffer(buffer,int(len));
  }
};


class filtering_output_streambuf : public std::streambuf
{
protected:
  virtual int_type write_buffer(const char_type* buffer, int_type len) = 0;

  virtual int_type overflow(int_type n = traits_type::eof()) override
  {
    char_type ch=char_type(n);
    int_type res=write_buffer(&ch,1);
    if (res>0) return res;
    return traits_type::eof();
  }

  virtual streamsize xsputn(const char_type* buffer, streamsize len) override
  {
    return write_buffer(buffer,int(len));
  }
};

const int CHUNK=1048576;

class inflate_input_streambuf : public filtering_input_streambuf
{
  std::istream& m_Source;
  typedef std::vector<unsigned char> ucvec;
  typedef std::list<ucvec> buffers_list;
  int ret;
  unsigned have;
  z_stream strm;
  unsigned char in[CHUNK];
  buffers_list out;
  unsigned char* next;
  //std::ofstream flog;
  bool done;
public:
  inflate_input_streambuf(std::istream& is) 
  : m_Source(is)
  , next(0)
  , have(0)
  , done(false)
  //, flog("inflate.log",std::ios::out|std::ios::binary)
  {
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.avail_in = 0;
    strm.next_in = Z_NULL;
    ret = inflateInit(&strm);
    if (ret != Z_OK) throw xstring("Failed to initialize inflate: "+xstring(ret));
  }

  ~inflate_input_streambuf()
  {
    inflateEnd(&strm);
  }
protected:
  void copy_data(char*& buffer, int& len, int& total)
  {
    int act=Min(int(have),len);
    std::copy_n(next,act,buffer);
    //flog.write((const char*)next,act); flog.flush();
    have-=act;
    next+=act;
    len-=act;
    buffer+=act;
    total+=act;
    if (have==0) 
    {
      out.pop_front();
      if (!out.empty())
      {
        next=&((out.front())[0]);
        have=out.front().size();
      }
    }
  }

  bool inflate_buffer()
  {
    if (have>0) return true;
    int flush=Z_NO_FLUSH;
    if (!done)
    {
      m_Source.read((char*)in,CHUNK);
      int act=int(m_Source.gcount());
      bool eof=(act<CHUNK);
      if (eof) 
      {
        done=true;
        flush=Z_FINISH;
      }
      strm.next_in=in;
      strm.avail_in=act;
    }
    else
    {
      strm.avail_in=0;
      flush=Z_FINISH;
    }
    do 
    {
      out.push_back(ucvec(CHUNK));
      strm.avail_out=CHUNK;
      strm.next_out=&((out.back())[0]);
      ret = inflate(&strm, flush);
      if (ret==Z_STREAM_ERROR) throw xstring("Failed to inflate");
      if (ret==Z_NEED_DICT || ret==Z_DATA_ERROR || ret==Z_MEM_ERROR) throw xstring("Inflate error: "+xstring(ret));
      int decoded=CHUNK-strm.avail_out;
      out.back().resize(decoded);
    } while (strm.avail_out==0);
    have = out.front().size();
    if (have>0) next = &((out.front())[0]);
    return have>0;
  }

  virtual int_type read_buffer(char* buffer, int len) override
  {
    int total=0;
    while (len>0)
    {
      if (have>0) copy_data(buffer,len,total);
      else
      if (!inflate_buffer()) break;
    }
    return total;
  }

  virtual bool     avail() override
  {
    return peek()!=EOF;
  }

  virtual int_type peek() override
  {
    int_type res=EOF;
    if (have>0) res=*next;
    else
    {
      if (inflate_buffer())
        res=*next;
    }
    return res;
  }
};

class deflate_output_streambuf : public filtering_output_streambuf
{
  std::ostream& m_Target;
  int ret, flush;
  unsigned have;
  z_stream strm;
  unsigned char out[CHUNK];
  //std::ofstream flog;
public:
  deflate_output_streambuf(std::ostream& os) 
  : m_Target(os) 
  //, flog("deflate.log",std::ios::out|std::ios::binary)
  {
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    int level=9;
    ret = deflateInit(&strm, level);
    if (ret != Z_OK) throw xstring("zlib deflate init failed: "+xstring(ret));
  }

  ~deflate_output_streambuf()
  {
    flush=Z_FINISH;
    strm.avail_in=0;
    do 
    {
      strm.avail_out = CHUNK;
      strm.next_out = out;
      ret = deflate(&strm, flush);
      if (ret==Z_STREAM_ERROR) throw xstring("Failure in zlib deflate");
      have = CHUNK - strm.avail_out;
      m_Target.write((const char*)out,have);
    } while (strm.avail_out==0);
    deflateEnd(&strm);
  }

protected:
  virtual int_type write_buffer(const char_type* buffer, int_type len) override
  {
    //flog.write(buffer,len);
    int total=0;
    while (len>0)
    {
      int act=Min(len,CHUNK);
      strm.avail_in=act;
      flush = Z_NO_FLUSH;
      strm.next_in=(unsigned char*)buffer;
      do 
      {
        strm.avail_out = CHUNK;
        strm.next_out = out;
        ret = deflate(&strm, flush);
        if (ret==Z_STREAM_ERROR) throw xstring("Failure in zlib deflate");
        have = CHUNK - strm.avail_out;
        if (have>0) m_Target.write((const char*)out,have);
      } while (strm.avail_out==0);
      buffer+=act;
      len-=act;
      total+=act;
    }
    return total;
  }
};

class inflate_input_stream : public std::istream
{
  std::streambuf* m_Buf;
public:
  inflate_input_stream(std::istream& is)
    : std::istream(new inflate_input_streambuf(is))
  {
    m_Buf=rdbuf();
  }

  ~inflate_input_stream()
  {
    delete m_Buf;
  }
};

class deflate_output_stream : public std::ostream
{
  std::streambuf* m_Buf;
public:
  deflate_output_stream(std::ostream& os)
    : std::ostream(new deflate_output_streambuf(os))
  {
    m_Buf=rdbuf();
  }

  ~deflate_output_stream()
  {
    delete m_Buf;
  }
};

std::shared_ptr<std::istream> inflate_stream(std::istream& is)
{
  return std::shared_ptr<std::istream>(new inflate_input_stream(is));
}

std::shared_ptr<std::ostream> deflate_stream(std::ostream& os)
{
  return std::shared_ptr<std::ostream>(new deflate_output_stream(os));
}

