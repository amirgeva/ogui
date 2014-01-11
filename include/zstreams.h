#ifndef zstreams_h__
#define zstreams_h__

#include <iostream>
#include <memory>

typedef std::shared_ptr<std::istream> is_ptr;
typedef std::shared_ptr<std::ostream> os_ptr;

is_ptr inflate_stream(std::istream& is);
os_ptr deflate_stream(std::ostream& os);

#endif // zstreams_h__
