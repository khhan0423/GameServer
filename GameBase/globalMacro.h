#pragma once
#define OUT
#define IN

#include <assert.h>
#ifdef _DEBUG
#define ASSERT_REPORT(exp, msg) _wassert(_CRT_WIDE(#exp), _CRT_WIDE(__FILE__), __LINE__)
#else
#define ASSERT_REPORT(exp, msg)
#endif

#ifdef _DEBUG
#define ASSERT(exp)												{ if(!(exp)) { ASSERT_REPORT(exp, _T(#exp)); } }
#define ASSERT_MSG(exp, msg)									{ if(!(exp)) { ASSERT_REPORT(exp, _T(#exp)##msg); } }
#else
#define ASSERT(exp)
#define ASSERT_MSG(exp, msg)
#endif

#ifndef _QUOTE
#define _QUOTE(x) # x
#endif
#ifndef QUOTE
#define QUOTE(x) _QUOTE(x)
#endif
#ifndef __FILE__LINE__
#define __FILE__LINE__ __FILE__ "(" QUOTE(__LINE__) ") : "
#endif
#ifndef TODO
#define TODO(x) message( __FILE__LINE__ " TODO : "x"\n")
#endif
#ifndef FIXME
#define FIXME(x) message(__FILE__LINE__ " FIXME : "x"\n")
#endif