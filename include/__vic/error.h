// Error handling and diagnostic utilities
//
// Platform: ISO C++ 98/11
// $Id$
//
// (c) __vic 2007

#ifndef __VIC_ERROR_H
#define __VIC_ERROR_H

#include<__vic/defs.h>
#include<__vic/readonly_cstring.h>
#include<cerrno>
#include<exception>

namespace __vic {

//////////////////////////////////////////////////////////////////////////////
// Simple exception class
//////////////////////////////////////////////////////////////////////////////
class exception : public std::exception
{
    readonly_cstring msg;
public:
    explicit exception(const char *msg) : msg(msg) {}
    const char *what() const noexcept { return msg; }
protected:
    exception() __VIC_DEFAULT_CTR
    void set_message(const char *st) { msg = st; }
};
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// Replacement for C error reporting mechanism with C++ exceptions
//////////////////////////////////////////////////////////////////////////////
class libc_error : public std::exception
{
    int code_;
    mutable bool formatted;
    mutable readonly_cstring msg;
public:
    explicit libc_error(int = errno);
    explicit libc_error(const char * , int = errno);

    const char *what() const noexcept;
    int code() const { return code_; }
    int get_errno() const { return code(); }
};
//////////////////////////////////////////////////////////////////////////////

} // namespace

#endif // header guard
